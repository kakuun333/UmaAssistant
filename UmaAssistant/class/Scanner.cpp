#include "../stdafx.h"
#include <tesseract/baseapi.h>

# pragma region 初始化靜態變數
Scanner* Scanner::_instance = nullptr;
std::string Scanner::_previousEventText = "";
std::string Scanner::_previousCharacterNameText = "";
std::string Scanner::_previousHenseiCharacterNameText = "";
bool Scanner::_scanning = false;

tesseract::TessBaseAPI* Scanner::ocr_jpn = nullptr;
tesseract::TessBaseAPI* Scanner::ocr_tw = nullptr;
#pragma endregion


void Scanner::InitOcrJpn()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "jpn", tesseract::OEM_DEFAULT); // 日文 "jpn"、繁體中文 "chi_tra"

			//ocr->SetVariable("tessedit_char_blacklist", u8"!@$%^&*_-+<>?()[]{}|/\\`0123456789†.,:;；=");

			// 省略 OSD
			//ocr->SetVariable("load_system_dawg", "F");
			//ocr->SetVariable("load_freq_dawg", "F");

			ocr->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);


			ocr_jpn = ocr;
		});

	initThread.detach();
}

void Scanner::InitOcrTw()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "chi_tra", tesseract::OEM_DEFAULT); // 日文 "jpn"、繁體中文 "chi_tra"

			//ocr->SetVariable("tessedit_char_blacklist", u8"!@$%^&*_-+<>?()[]{}|/\\`0123456789†.,:;；=");

			// 省略 OSD
			//ocr->SetVariable("load_system_dawg", "F");
			//ocr->SetVariable("load_freq_dawg", "F");

			ocr->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);

			ocr_tw = ocr;
		});

	initThread.detach();
}


#pragma region 私人函數

void Scanner::UpdateSapokaChoice(WebManager* webManager, UmaEventData sapokaUmaEventData)
{
	webManager->CleanChoiceTable();

	for (UmaChoice choice : sapokaUmaEventData.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
	{
		webManager->CreateChoice(utility::stdStr2system(choice.choice_title), utility::stdStr2system(choice.choice_effect));
	}

	System::String^ sys_event_owner = utility::stdStr2system(sapokaUmaEventData.Get<std::string>(UmaEventDataType::EVENT_OWNER));
	webManager->ChangeEventOwner(sys_event_owner);

	System::String^ sys_event_title = utility::stdStr2system(sapokaUmaEventData.Get<std::string>(UmaEventDataType::EVENT_TITLE));
	webManager->ChangeEventTitle(sys_event_title);

	webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
	webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
}

void Scanner::UpdateCharChoice(WebManager* webManager, UmaEventData charUmaEventData)
{
	// 這裡更新 UI
	webManager->CleanChoiceTable();

	for (UmaChoice choice : charUmaEventData.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
	{
		webManager->CreateChoice(utility::stdStr2system(choice.choice_title), utility::stdStr2system(choice.choice_effect));
	}

	System::String^ sys_event_owner = utility::stdStr2system(charUmaEventData.Get<std::string>(UmaEventDataType::EVENT_OWNER));
	webManager->ChangeEventOwner(sys_event_owner);

	System::String^ sys_event_title = utility::stdStr2system(charUmaEventData.Get<std::string>(UmaEventDataType::EVENT_TITLE));
	webManager->ChangeEventTitle(sys_event_title);

	webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
	webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
}

void Scanner::UpdateScenarioChoice(WebManager* webManager, ScenarioEventData scenarioEventData)
{
	webManager->CleanChoiceTable();

	for (ScenarioChoice choice : scenarioEventData.event_list)
	{
		webManager->CreateChoice(utility::stdStr2system(choice.choice_title), utility::stdStr2system(choice.choice_effect));
	}

	System::String^ sys_event_title = utility::stdStr2system(scenarioEventData.event_title);

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		webManager->ChangeEventOwner(u8"メインシナリオイベント");
		break;
	case static_cast<int>(GameServerType::TW):
		webManager->ChangeEventOwner(u8"主要劇情事件");
		break;
	}

	webManager->ChangeEventTitle(sys_event_title);

	webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
	webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
}


std::string Scanner::GetScannedText(cv::Mat image, std::string language, ImageType imgType = ImageType::IMG_EVENT_TITLE)
{
	std::unique_lock<std::mutex> lock(ocrMutex);

	int charCount = 0;
	char* utf8 = nullptr;

	//ocr_jpn->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (imgType)
		{
		case ImageType::IMG_EVENT_TITLE:
			ocr_jpn->SetVariable("tessedit_char_blacklist", u8"@$%^&*_-+<>()[]{}|/\\`0123456789†.,:;；=");
			ocr_jpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
			break;
		case ImageType::IMG_HENSEI_CHARACTER_NAME:
			ocr_jpn->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
			ocr_jpn->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_BLOCK*/);
			break;
		}

		// 設置圖片到 ocr
		ocr_jpn->SetImage(image.data, image.cols, image.rows, 1, image.step);

		// 進行文字辨識
		ocr_jpn->Recognize(0);

		utf8 = ocr_jpn->GetUTF8Text();
		break;

	case static_cast<int>(GameServerType::TW):
		switch (imgType)
		{
		case ImageType::IMG_EVENT_TITLE:
			ocr_tw->SetVariable("tessedit_char_blacklist", u8"@$%^&*_-+<>()[]{}|/\\`0123456789†.,:;；=");
			ocr_tw->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
			break;
		case ImageType::IMG_HENSEI_CHARACTER_NAME:
			ocr_tw->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
			ocr_tw->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_BLOCK*/);
			break;
		}

		// 設置圖片到 ocr
		ocr_tw->SetImage(image.data, image.cols, image.rows, 1, image.step);

		// 進行文字辨識
		ocr_tw->Recognize(0);

		utf8 = ocr_tw->GetUTF8Text();
		break;
	}

	std::string result = utility::RemoveSpace(utf8);

#pragma region 釋放記憶體
	//ocr->End();
	delete[] utf8;
#pragma endregion

	lock.unlock();

	if (utility::IsRepeatingString(result, 4))
	{
		std::cout << u8"[Scanner] 連續且重複的字符過多 result: " << result << std::endl;
		return std::string();
	}

	if (utility::HasBlackListedString(result))
	{
		std::cout << u8"[Scanner] 檢查到含有黑名單字串 result: " << result << std::endl;
		return std::string();
	}

	return result;
}


#pragma endregion 私人函數


void Scanner::Start(std::string language)
{
	if (global::umaswitch::Scanning)
	{
		std::cout << u8"[Scanner] 必須先停止掃描 Scanner::GetInstance()->Stop()" << std::endl;
		return;
	}

	global::umaswitch::Scanning = true;

	std::thread scanThread([=]()
		{
			DataManager* dataManager = DataManager::GetInstance();
			WebManager* webManager = WebManager::GetInstance();

			this->_scanning = true;
			while (global::umaswitch::Scanning)
			{
				std::unique_ptr<UmaTimer> timer = std::make_unique<UmaTimer>();
				timer->Start();

				Screenshot ss;

				if (!ss.IsDataComplete())
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					continue;
				}


				///
				/// 獲取圖片裡的文字
				/// 
				std::string eventText /*characterNameText,*/;
				std::string henseiCharNameText = "INIT_HENSEI_CHAR_NAME_TEXT";

				//eventText = this->GetScannedText(ss.event_title_oimg, language);
				//std::cout << "event_title_oimg: " << eventText << std::endl;

				//eventText = this->GetScannedText(ss.event_title_resize, language);
				//std::cout << "event_title_resize: " << eventText << std::endl;

				//eventText = this->GetScannedText(ss.event_title_gray, language);
				//std::cout << "event_title_gray: " << eventText << std::endl;

				//eventText = this->GetScannedText(ss.event_title_gray_bin_inv, language);
				//std::cout << "event_title_gray_bin_inv: " << eventText << std::endl;


				//eventText = this->GetScannedText(ss.event_title_gray_bin, language);
				//henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray, language, ImageType::IMG_HENSEI_CHARACTER_NAME);


				std::unique_ptr<std::thread> tryCharThread;
				UmaEventData charUmaEventData;

				eventText = this->GetScannedText(ss.event_title_gray_bin, language);

				/*
				* 如果 eventText 是空字串就再用其他圖片比較
				* 如果還是空字串才算是真的空字串
				*/
				if (eventText.empty() && dataManager->IsCurrentCharacterInfoLocked())
				{
					std::unique_ptr<std::thread> testThread, test2Thread;

					std::string gray_event_text, resize_event_text;

					try
					{
						testThread = std::make_unique<std::thread>([=, &eventText, &gray_event_text]()
							{
								gray_event_text = this->GetScannedText(ss.event_title_gray, language);
								if (eventText.empty() && !gray_event_text.empty())
								{
									eventText = gray_event_text;
								}
							});
					}
					catch (System::Exception^ ex)
					{
						std::cout << u8"[exception] 捕捉到 testThread 區塊的 exception" << std::endl;
						System::Console::WriteLine("Caught exception: " + ex->Message);
						std::cout << u8"已終止 Scanner 運作" << std::endl;
						return;
					}


					try
					{
						test2Thread = std::make_unique<std::thread>([=, &eventText, &resize_event_text]()
							{
								resize_event_text = this->GetScannedText(ss.event_title_resize, language);
								if (eventText.empty() && !resize_event_text.empty())
								{
									eventText = resize_event_text;
								}
							});
					}
					catch (System::Exception^ ex)
					{
						std::cout << u8"[exception] 捕捉到 test2Thread 區塊的 exception" << std::endl;
						System::Console::WriteLine("Caught exception: " + ex->Message);
						std::cout << u8"已終止 Scanner 運作" << std::endl;
						return;
					}

					testThread->join();
					test2Thread->join();

					if (gray_event_text.empty() && resize_event_text.empty())
					{
						std::cout << u8"[Scanner] 都是空字串" << std::endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(global::config->ScanInterval));
						continue;
					}
				}

				std::cout << u8"[Scanner] event_title_gray_bin: " << eventText << std::endl;
				
				

				if (_previousHenseiCharacterNameText != henseiCharNameText)
				{
#pragma region Looking for Current Character
					if (!dataManager->IsCurrentCharacterInfoLocked())
					{
						try
						{
							tryCharThread = std::make_unique<std::thread>([=, &henseiCharNameText]()
								{
									henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray, language, ImageType::IMG_HENSEI_CHARACTER_NAME);
									if (!henseiCharNameText.empty()) std::cout << u8"[Scanner] hensei_character_name_gray: " << henseiCharNameText << std::endl;

									if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) return;

									henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_bin_inv, language, ImageType::IMG_HENSEI_CHARACTER_NAME);
									if (!henseiCharNameText.empty()) std::cout << "[Scanner] hensei_character_name_gray_bin_inv: " << henseiCharNameText << std::endl;

									if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) return;

									henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_bin, language, ImageType::IMG_HENSEI_CHARACTER_NAME);
									if (!henseiCharNameText.empty()) std::cout << "[Scanner] hensei_character_name_gray_bin: " << henseiCharNameText << std::endl;

									dataManager->TryGetCurrentCharacterName(henseiCharNameText);
								});
						}
						catch (System::Exception^ ex)
						{
							std::cout << u8"[exception] 捕捉到 tryCharThread 區塊的 exception" << std::endl;
							System::Console::WriteLine("Caught exception: " + ex->Message);
							std::cout << u8"已終止 Scanner 運作" << std::endl;
							return;
						}

					}
					else
					{
						std::cout << "[Scanner] CURRENT CHARACTER LOCKED" << std::endl;

						charUmaEventData = dataManager->GetCurrentCharacterUmaEventData(eventText);
						if (charUmaEventData.IsDataComplete())
						{
							this->UpdateCharChoice(webManager, charUmaEventData);
						}

					}
#pragma endregion
				}


				if (_previousEventText != eventText)
				{
					if (!charUmaEventData.IsDataComplete())
					{
						/*
						* 有時候名字很像的事件名稱會先偵測到 scenarioEventData ，但是正確的事件在 sapokaUmaEventData
						* 為了避免先偵測到 scenarioEventData ，應該要先比較 similarity 再判斷要更新的事件是
						* scenarioEventData 還是 sapokaUmaEventData
						*/

						std::unique_ptr<std::thread> sapokaThread, scenarioThread;

						UmaEventData sapokaUmaEventData;
						ScenarioEventData scenarioEventData;

						try
						{
							sapokaThread = std::make_unique<std::thread>([=, &eventText, &sapokaUmaEventData]()
								{

									sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

									if (sapokaUmaEventData.IsDataComplete()) return;

									std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整" << std::endl;

									eventText = this->GetScannedText(ss.event_title_gray, language);
									std::cout << "[Scanner] event_title_gray: " << eventText << std::endl;
									sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

									if (sapokaUmaEventData.IsDataComplete()) { eventText = eventText; return; }

									std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整2" << std::endl;

									eventText = this->GetScannedText(ss.event_title_gray_bin_inv, language);
									std::cout << "[Scanner] event_title_gray_bin_inv: " << eventText << std::endl;
									sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

									if (sapokaUmaEventData.IsDataComplete()) { eventText = eventText; return; }

									std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整3" << std::endl;
								});
						}
						catch (System::Exception^ ex)
						{
							std::cout << u8"[exception] 捕捉到 sapokaThread 區塊的 exception" << std::endl;
							System::Console::WriteLine("Caught exception: " + ex->Message);
							std::cout << u8"已終止 Scanner 運作" << std::endl;
							return;
						}

						try
						{
							scenarioThread = std::make_unique<std::thread>([=, &scenarioEventData]()
								{
									scenarioEventData = dataManager->GetScenarioEventData(eventText);
								});
						}
						catch (System::Exception^ ex)
						{
							std::cout << u8"[exception] 捕捉到 scenarioThread 區塊的 exception" << std::endl;
							System::Console::WriteLine("Caught exception: " + ex->Message);
							std::cout << u8"已終止 Scanner 運作" << std::endl;
							return;
						}


						sapokaThread->join();
						scenarioThread->join();



						if (sapokaUmaEventData.similarity > scenarioEventData.similarity)
						{
							if (sapokaUmaEventData.IsDataComplete()) this->UpdateSapokaChoice(webManager, sapokaUmaEventData);
						}
						else
						{
							if (scenarioEventData.IsDataComplete()) this->UpdateScenarioChoice(webManager, scenarioEventData);
						}

					}
				}
				else
				{
					std::cout << u8"[Scanner] 偵測結果與上次一致" << std::endl;
				}


				// 如果有 tryCharThread 就等待它執行完畢
				if (tryCharThread != nullptr && tryCharThread->joinable()) tryCharThread->join();


				//
				// 更新上次辨識到的文字
				//
				_previousEventText = eventText;
				std::cout << "_previousEventText: " << _previousEventText << std::endl;
				//_previousCharacterNameText = characterNameText;
				_previousHenseiCharacterNameText = henseiCharNameText;
				std::cout << "_previousHenseiCharacterNameText: " << _previousHenseiCharacterNameText << std::endl;

				
				double seconds = timer->Stop();

				printf("[Scanner] SCANNED [%.2fs]\n", seconds);

				std::this_thread::sleep_for(std::chrono::milliseconds(global::config->ScanInterval));
			}
			this->_scanning = false;


		});

	scanThread.detach();
}

void Scanner::Stop()
{
	std::thread stopThread([=]()
		{
			bool stopped = false;

			do
			{
				if (_scanning)
				{
					global::umaswitch::Scanning = false;
					stopped = true;
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(300));
			} while (!stopped);
		});
	
	stopThread.detach();
}