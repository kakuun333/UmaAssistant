#include "../stdafx.h"

# pragma region 初始化靜態變數
Scanner* Scanner::_instance = nullptr;
std::string Scanner::_previousEventText = "";
std::string Scanner::_previousCharacterNameText = "";
std::string Scanner::_previousHenseiCharacterNameText = "";
bool Scanner::_scanning = false;

tesseract::TessBaseAPI* Scanner::ocr_jpn = nullptr;
tesseract::TessBaseAPI* Scanner::ocr_tw = nullptr;

#pragma endregion

#include <tesseract/baseapi.h>
void Scanner::InitOcrJpn()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::c_tessdata_best, "jpn", tesseract::OEM_DEFAULT); // 日文 "jpn"、繁體中文 "chi_tra"

			//ocr->SetVariable("tessedit_char_blacklist", u8"!@$%^&*_-+<>?()[]{}|/\\`0123456789†.,:;；=");

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

			ocr->Init(global::path::c_tessdata_best, "chi_tra", tesseract::OEM_DEFAULT); // 日文 "jpn"、繁體中文 "chi_tra"

			//ocr->SetVariable("tessedit_char_blacklist", u8"!@$%^&*_-+<>?()[]{}|/\\`0123456789†.,:;；=");

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
		webManager->CreateChoice(choice.sys_choice_title, choice.sys_choice_effect);
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
		webManager->CreateChoice(choice.sys_choice_title, choice.sys_choice_effect);
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

	char* utf8 = nullptr;

	//ocr_jpn->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (imgType)
		{
		case ImageType::IMG_EVENT_TITLE:
			ocr_jpn->SetVariable("tessedit_char_blacklist", u8"@$%^&*_-+<>()[]{}|/\\`0123456789†.,:;；=");
			//ocr_jpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
			break;
		case ImageType::IMG_HENSEI_CHARACTER_NAME:
			ocr_jpn->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
			//ocr_jpn->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_BLOCK*/);
			break;
		}

		// 設置圖片到 ocr
		//ocr_jpn->SetImage(image.data, image.size().width, image.size().height, image.channels(), image.step);
		ocr_jpn->SetImage(image.data, image.cols, image.rows, 1, image.cols);

		// 進行文字辨識
		ocr_jpn->Recognize(0);

		utf8 = ocr_jpn->GetUTF8Text();
		break;

	case static_cast<int>(GameServerType::TW):
		switch (imgType)
		{
		case ImageType::IMG_EVENT_TITLE:
			ocr_tw->SetVariable("tessedit_char_blacklist", u8"@$%^&*_-+<>()[]{}|/\\`0123456789†.,:;；=");
			//ocr_tw->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
			break;
		case ImageType::IMG_HENSEI_CHARACTER_NAME:
			ocr_tw->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
			//ocr_tw->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_BLOCK*/);
			break;
		}

		// 設置圖片到 ocr
		//ocr_jpn->SetImage(image.data, image.size().width, image.size().height, image.channels(), image.step);
		ocr_tw->SetImage(image.data, image.cols, image.rows, 1, image.cols);

		// 進行文字辨識
		ocr_tw->Recognize(0);

		utf8 = ocr_tw->GetUTF8Text();
		break;
	}

	std::string result = utility::RemoveSpace(utf8);


#pragma region 釋放記憶體
	//ocr->End();
	delete[] utf8;
#pragma endregion 釋放記憶體

	lock.unlock();
	return result;
}

//std::string Scanner::GetCharacterName(const char* imgPath, const char* language)
//{
//	// 讀取圖片
//	Pix* image = pixRead(imgPath);
//
//	// 設置圖片到 ocr
//	ocr_jpn_character->SetImage(image);
//
//	// 進行文字辨識
//	char* utf8 = ocr_jpn_character->GetUTF8Text();
//
//	std::string stdString(utf8);
//	std::string result = utility::RemoveSpace(stdString);
//
//	//// utf8 轉 utf16
//	//wchar_t* utf16 = utility::utf8to16(utf8);
//	//// wchar_t 轉 System::String^
//	//System::String^ scanResult = marshal_as<System::String^>(utf16);
//	//// 去除空白鍵
//	//System::String^ removed_space = utility::RemoveSpace(scanResult);
//
//#pragma region 釋放記憶體
//	//ocr->End();
//	delete[] utf8;
//	pixDestroy(&image);
//#pragma endregion 釋放記憶體
//
//	return result;
//}
//
//std::string Scanner::GetHenseiCharacterName(const char* imgPath, const char* language)
//{
//	// 讀取圖片
//	Pix* image = pixRead(imgPath);
//
//	// 設置圖片到 ocr
//	ocr_jpn_hensei_char->SetImage(image);
//
//	// 進行文字辨識
//	char* utf8 = ocr_jpn_hensei_char->GetUTF8Text();
//
//	std::string stdString(utf8);
//	std::string result = utility::RemoveSpace(stdString);
//
//	//// utf8 轉 utf16
//	//wchar_t* utf16 = utility::utf8to16(utf8);
//	//// wchar_t 轉 System::String^
//	//System::String^ scanResult = marshal_as<System::String^>(utf16);
//	//// 去除空白鍵
//	//System::String^ removed_space = utility::RemoveSpace(scanResult);
//
//#pragma region 釋放記憶體
//	//ocr->End();
//	delete[] utf8;
//	pixDestroy(&image);
//#pragma endregion 釋放記憶體
//
//	return result;
//}


#pragma endregion 私人函數


void Scanner::Start(std::string language)
{
	if (global::umaswitch::Scanning)
	{
		std::cout << u8"[Scanner] 必須先停止掃描 Scanner::Stop()" << std::endl;
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
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					continue;
				}


				///
				/// 獲取圖片裡的文字
				/// 
				std::string eventText, /*characterNameText,*/ henseiCharNameText;


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


				eventText = this->GetScannedText(ss.event_title_gray_bin, language);

				/*
				* 如果 eventText 是空字串就再用其他圖片比較
				* 如果還是空字串才算是真的空字串
				*/
				if (eventText.empty() && dataManager->IsCurrentCharacterInfoLocked())
				{
					std::unique_ptr<std::thread> test, test2;

					std::string gray_event_text, oimg_event_text;

					test = std::make_unique<std::thread>([=, &eventText, &gray_event_text]()
						{
							
							gray_event_text = this->GetScannedText(ss.event_title_gray, language);
							if (eventText.empty() && !gray_event_text.empty())
							{
								eventText = gray_event_text;
							}
						});

					test2 = std::make_unique<std::thread>([=, &eventText, &oimg_event_text]()
						{
							oimg_event_text = this->GetScannedText(ss.event_title_oimg, language);
							if (eventText.empty() && !oimg_event_text.empty())
							{
								eventText = oimg_event_text;
							}
						});

					test->join();
					test2->join();

					if (gray_event_text.empty() && oimg_event_text.empty())
					{
						std::cout << u8"[Scanner] 都是空字串" << std::endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
						continue;
					}
				}

				std::cout << u8"[Scanner] event_title_gray_bin: " << eventText << std::endl;
				
				if (_previousEventText != eventText ||
					//_previousCharacterNameText != characterNameText ||
					_previousHenseiCharacterNameText != henseiCharNameText)
				{
#pragma region Looking for Current Character
					if (!dataManager->IsCurrentCharacterInfoLocked())
					{
						

						tryCharThread = std::make_unique<std::thread>([=, &henseiCharNameText]()
							{
								henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray, language, ImageType::IMG_HENSEI_CHARACTER_NAME);
								if (!henseiCharNameText.empty()) std::cout << u8"[Scanner] hensei_character_name_gray: " << henseiCharNameText << std::endl;

								if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) return;

								henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_bin_inv, language, ImageType::IMG_HENSEI_CHARACTER_NAME);
								if (!henseiCharNameText.empty()) std::cout << "[Scanner] hensei_character_name_gray_bin_inv: " << henseiCharNameText << std::endl;

								dataManager->TryGetCurrentCharacterName(henseiCharNameText);
							});
						//tryThread->join();
					}
					else
					{
						std::cout << "[Scanner] CURRENT CHARACTER LOCKED" << std::endl;
					}
#pragma endregion




#pragma region Character Event Data
					UmaEventData charUmaEventData = dataManager->GetCurrentCharacterUmaEventData(eventText);
					if (charUmaEventData.IsDataComplete())
					{
						this->UpdateCharChoice(webManager, charUmaEventData);
					}
					else
#pragma endregion
					{
						/*
						* 有時候名字很像的事件名稱會先偵測到 scenarioEventData ，但是正確的事件在 sapokaUmaEventData
						* 為了避免先偵測到 scenarioEventData ，應該要先比較 similarity 再判斷要更新的事件是
						* scenarioEventData 還是 sapokaUmaEventData
						*/

						std::unique_ptr<std::thread> sapokaThread, scenarioThread;

						UmaEventData sapokaUmaEventData;
						ScenarioEventData scenarioEventData;

						sapokaThread = std::make_unique<std::thread>([=, &eventText, &sapokaUmaEventData]()
							{
								sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

								if (sapokaUmaEventData.IsDataComplete()) return;

								std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整" << std::endl;

								eventText = this->GetScannedText(ss.event_title_gray, language);
								std::cout << "[Scanner] event_title_gray: " << eventText << std::endl;
								sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

								if (sapokaUmaEventData.IsDataComplete()) return;

								std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整2" << std::endl;

								eventText = this->GetScannedText(ss.event_title_oimg, language);
								std::cout << "[Scanner] event_title_oimg: " << eventText << std::endl;
								sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

								if (sapokaUmaEventData.IsDataComplete()) return;

								std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整3" << std::endl;
							});

						scenarioThread = std::make_unique<std::thread>([=, &scenarioEventData]()
							{
								scenarioEventData = dataManager->GetScenarioEventData(eventText);
							});

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
				//_previousCharacterNameText = characterNameText;
				_previousHenseiCharacterNameText = henseiCharNameText;

				
				double seconds = timer->Stop();

				printf("[Scanner] SCANNED [%.2fs]\n", seconds);

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
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