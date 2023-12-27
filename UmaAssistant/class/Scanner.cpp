#include "../stdafx.h"
#include <tesseract/baseapi.h>


# pragma region 初始化靜態變數
Scanner* Scanner::_instance = nullptr;
bool Scanner::_scanning = false;
tesseract::TessBaseAPI* Scanner::ocr_jpn = nullptr;
tesseract::TessBaseAPI* Scanner::ocr_tw = nullptr;
tesseract::TessBaseAPI* Scanner::ocr_eng = nullptr;
#pragma endregion


void Scanner::InitOcrJpn()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "jpn", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/); // 日文 "jpn"、繁體中文 "chi_tra"

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

			ocr->Init(global::path::std_tessdata_best.c_str(), "chi_tra", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/); // 日文 "jpn"、繁體中文 "chi_tra"

			//ocr->SetVariable("tessedit_char_blacklist", u8"!@$%^&*_-+<>?()[]{}|/\\`0123456789†.,:;；=");

			// 省略 OSD
			//ocr->SetVariable("load_system_dawg", "F");
			//ocr->SetVariable("load_freq_dawg", "F");

			ocr->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);

			ocr_tw = ocr;
		});

	initThread.detach();
}

void Scanner::InitOcrEng()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "eng", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/);
			ocr->SetVariable("tessedit_char_whitelist", u8"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-!.");

			ocr->SetPageSegMode(/*tesseract::PSM_AUTO*/tesseract::PSM_SINGLE_LINE/*tesseract::PSM_SINGLE_BLOCK*/);

			ocr_eng = ocr;
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


std::string Scanner::GetScannedText(cv::Mat image, ImageType imgType, bool englishMode)
{
	std::unique_lock<std::mutex> lock(ocrMutex);

	UmaLog* umalog = UmaLog::GetInstance();

	int charCount = 0;
	char* utf8 = nullptr;

	switch (englishMode)
	{
	case true:
		// 設置圖片到 ocr
		ocr_eng->SetImage(image.data, image.cols, image.rows, 1, image.step);

		// 進行文字辨識
		ocr_eng->Recognize(0);

		utf8 = ocr_eng->GetUTF8Text();
		break;
	case false:
		switch (global::config->GameServer)
		{
		case static_cast<int>(GameServerType::JP):
			switch (imgType)
			{
			case ImageType::IMG_EVENT_TITLE:
				ocr_jpn->SetVariable("tessedit_char_blacklist", u8"@$%^*_-+<>[]{}|/\\`0123456789†:;；=");
				ocr_jpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
				break;
			case ImageType::IMG_HENSEI_CHARACTER_NAME:
				ocr_jpn->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|\\`~†.,:;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
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
				ocr_tw->SetVariable("tessedit_char_blacklist", u8"@$%^*_-+<>[]{}|/\\`0123456789†:;；=");
				ocr_tw->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
				break;
			case ImageType::IMG_HENSEI_CHARACTER_NAME:
				ocr_tw->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|\\`~†.,:;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
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
	}



	std::string result = utility::RemoveSpace(utf8);

#pragma region 釋放記憶體
	//ocr->End();
	delete[] utf8;
#pragma endregion

	lock.unlock();



	if (utility::IsRepeatingString(result, 4))
	{
		umalog->print(u8"[Scanner] 連續且重複的字符過多 result: ", result);
		return std::string();
	}

	if (utility::HasBlackListedString(result))
	{
		umalog->print(u8"[Scanner] 檢查到含有黑名單字串 result: ", result);
		return std::string();
	}

	if (utility::IsStringTooLong(result))
	{
		umalog->print(u8"[Scanner] 字串太長，超過 23 個 UTF8 Char 加起來的 Byte。 result: ", result);
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
			UmaLog* umalog = UmaLog::GetInstance();

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
				/*std::string characterNameText;*/
				std::string eventText;
				std::string henseiCharNameText;

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
				UmaEventData sapokaUmaEventData;
				ScenarioEventData scenarioEventData;

				if (ss.IsEventTitle())
				{
					eventText = this->GetScannedText(ss.event_title_gray_bin);
				}


				if (!dataManager->IsCurrentCharacterInfoLocked())
				{
					henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray, ImageType::IMG_HENSEI_CHARACTER_NAME);

					umalog->print(u8"[Scanner] hensei_character_name_gray: ", henseiCharNameText);
				}

				/*
				* 如果 eventText 是空字串就再用其他圖片比較
				* 如果還是空字串才算是真的空字串
				*/
				if (eventText.empty() && dataManager->IsCurrentCharacterInfoLocked() && ss.IsEventTitle())
				{
					std::unique_ptr<std::thread> testThread, test2Thread;

					std::string gray_event_text, resize_event_text;

					try
					{
						testThread = std::make_unique<std::thread>([=, &eventText, &gray_event_text]()
							{
								gray_event_text = this->GetScannedText(ss.event_title_gray);
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
								resize_event_text = this->GetScannedText(ss.event_title_resize);
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

				umalog->print(u8"[Scanner] event_title_gray_bin: ", eventText);


#pragma region 尋找 Current Character
				if (_previousHenseiCharNameText != henseiCharNameText)
				{

					if (!dataManager->IsCurrentCharacterInfoLocked())
					{
						try
						{
							tryCharThread = std::make_unique<std::thread>([=, &ss, &henseiCharNameText]()
								{
									bool foundHenseiChar = false;

									const int TRY_RESIZE_COUNT = 5/*10*/;
									const float SCALE_FACTOR = 0.1;
									const int THRESH_FACTOR = 1;

									if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) return;

									//std::unique_ptr<std::thread> grayThread = std::make_unique<std::thread>([=, &ss, &henseiCharNameText, &foundHenseiChar]()
									//	{
									//		std::unique_lock<std::mutex> lock(dataMutex); // 以防萬一，先上鎖

									//		henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray, language, ImageType::IMG_HENSEI_CHARACTER_NAME);
									//		if (!henseiCharNameText.empty()) umalog->print(u8"[Scanner] hensei_character_name_gray: ", henseiCharNameText);

									//		if (foundHenseiChar) return;

									//		if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) { foundHenseiChar = true; return; }

									//		float currentScale = 1;
									//		for (int i = 0; i < TRY_RESIZE_COUNT; ++i)
									//		{
									//			currentScale += SCALE_FACTOR;
									//			ss.ResetCharacterImage(ss.hensei_character_name_gray, currentScale, ImagePattern::HENSEI_CHAR_GRAY);
									//			henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray, language, ImageType::IMG_HENSEI_CHARACTER_NAME);
									//			if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) { foundHenseiChar = true; return; }
									//		}
									//	});


									std::unique_ptr<std::thread> englishThread = std::make_unique<std::thread>([=, &ss, &henseiCharNameText, &foundHenseiChar]()
										{
											std::unique_lock<std::mutex> lock(dataMutex); // 以防萬一，先上鎖

											henseiCharNameText = this->GetScannedText(ss.hensei_character_another_name_gray, ImageType::IMG_HENSEI_CHARACTER_NAME, true);
											if (!henseiCharNameText.empty()) umalog->print(u8"[Scanner] ENGLISH hensei_character_another_name: ", henseiCharNameText);
											if (foundHenseiChar) return;

											if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) { foundHenseiChar = true; return; }

											//float currentScale = 1;
											//for (int i = 0; i < TRY_RESIZE_COUNT; ++i)
											//{
											//	currentScale += SCALE_FACTOR;
											//	ss.ResetCharacterImage(ss.hensei_character_another_name_gray, ImagePattern::HENSEI_CHAR_ANOTHER_NAME_GRAY, currentScale);
											//	henseiCharNameText = this->GetScannedText(ss.hensei_character_another_name_gray, ImageType::IMG_HENSEI_CHARACTER_ANOTHER_NAME, true);
											//	if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) { foundHenseiChar = true; return; }
											//}
										});



									std::unique_ptr<std::thread> gray_bin_invThread = std::make_unique<std::thread>([=, &ss, &henseiCharNameText, &foundHenseiChar]()
										{
											std::unique_lock<std::mutex> lock(dataMutex); // 以防萬一，先上鎖

											henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_bin_inv, ImageType::IMG_HENSEI_CHARACTER_NAME);
											if (!henseiCharNameText.empty()) umalog->print(u8"[Scanner] hensei_character_name_gray_bin_inv: ", henseiCharNameText);

											if (foundHenseiChar) return;

											if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) { foundHenseiChar = true; return; }

											float currentScale = 1;
											for (int i = 0; i < TRY_RESIZE_COUNT; ++i)
											{
												if (foundHenseiChar) return;
												currentScale += SCALE_FACTOR;
												ss.ResetCharacterImage(ss.hensei_character_name_gray_bin_inv, ImagePattern::HENSEI_CHAR_GRAY_BIN, currentScale);
												henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_bin_inv, ImageType::IMG_HENSEI_CHARACTER_NAME);
												if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) { foundHenseiChar = true; return; }
											}
										});

									std::unique_ptr<std::thread> gray_binThread = std::make_unique<std::thread>([=, &ss, &henseiCharNameText, &foundHenseiChar]()
										{
											std::unique_lock<std::mutex> lock(dataMutex); // 以防萬一，先上鎖

											henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_bin, ImageType::IMG_HENSEI_CHARACTER_NAME);
											if (!henseiCharNameText.empty()) umalog->print(u8"[Scanner] hensei_character_name_gray_bin: ", henseiCharNameText);

											if (foundHenseiChar) return;

											if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) { foundHenseiChar = true; return; }

											float currentScale = 1;
											for (int i = 0; i < TRY_RESIZE_COUNT; ++i)
											{
												if (foundHenseiChar) return;
												currentScale += SCALE_FACTOR;
												ss.ResetCharacterImage(ss.hensei_character_name_gray_bin, ImagePattern::HENSEI_CHAR_GRAY_BIN_INV, currentScale);
												henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_bin, ImageType::IMG_HENSEI_CHARACTER_NAME);
												if (dataManager->TryGetCurrentCharacterName(henseiCharNameText)) { foundHenseiChar = true; return; }
											}
										});

									englishThread->join();
									gray_bin_invThread->join();
									gray_binThread->join();
								});
						}
						catch (const std::exception& e)
						{
							umalog->print("[std::exception] tryCharThread:", e.what());
							umalog->print(u8"已終止 Scanner 運作");
							return;
						}
						catch (System::Exception^ ex)
						{
							umalog->print("[System::Exception] tryCharThread: ", utility::systemStr2std(ex->Message));
							umalog->print(u8"已終止 Scanner 運作");
							return;
						}

					}

					else
					{
						umalog->print("[Scanner] CURRENT CHARACTER LOCKED");
					}
				}
				else
				{
					umalog->print(u8"[Scanner] henseiCharNameText 偵測結果與上次一致");
				}
#pragma endregion


#pragma region 尋找 character 或 sapoka 或 scenario 的事件
				if (_previousEventText != eventText && ss.IsEventTitle())
				{
					_updatedChoice = false;


					// 更新 CharChoice
					if (dataManager->IsCurrentCharacterInfoLocked())
					{
						charUmaEventData = dataManager->GetCurrentCharacterUmaEventData(eventText);
						if (charUmaEventData.IsDataComplete())
						{
							this->UpdateCharChoice(webManager, charUmaEventData);
							umalog->print(u8"[Scanner] 成功更新 CharChoice");
							_previousEventText = eventText;
							_updatedChoice = true;
						}
					}


					if (!charUmaEventData.IsDataComplete())
					{
						/*
						* 有時候名字很像的事件名稱會先偵測到 scenarioEventData ，但是正確的事件在 sapokaUmaEventData
						* 為了避免先偵測到 scenarioEventData ，應該要先比較 similarity 再判斷要更新的事件是
						* scenarioEventData 還是 sapokaUmaEventData
						*/

						std::unique_ptr<std::thread> sapokaThread, scenarioThread;


						sapokaThread = std::make_unique<std::thread>([=, &eventText, &sapokaUmaEventData]()
							{
								try
								{
									sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

									if (sapokaUmaEventData.IsDataComplete()) { _previousEventText = eventText; return; }

									umalog->print(u8"[Scanner] sapokaUmaEventData 資料不完整");

									eventText = this->GetScannedText(ss.event_title_gray);
									umalog->print(u8"[Scanner] event_title_gray: ", eventText);
									sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

									if (sapokaUmaEventData.IsDataComplete()) { _previousEventText = eventText; return; }

									umalog->print(u8"[Scanner] sapokaUmaEventData 資料不完整2");

									eventText = this->GetScannedText(ss.event_title_gray_bin_inv);
									umalog->print(u8"[Scanner] event_title_gray_bin_inv: ", eventText);
									sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

									if (sapokaUmaEventData.IsDataComplete()) { _previousEventText = eventText; return; }

									umalog->print(u8"[Scanner] sapokaUmaEventData 資料不完整3");
								}
								catch (const std::exception& e)
								{
									umalog->print("[std::exception] sapokaThread:", e.what());
									umalog->print(u8"已終止 Scanner 運作");
									return;
								}
								catch (System::Exception^ ex)
								{
									umalog->print("[System::Exception] sapokaThread: ", utility::systemStr2std(ex->Message));
									umalog->print(u8"已終止 Scanner 運作");
									return;
								}
							});



						scenarioThread = std::make_unique<std::thread>([=, &scenarioEventData]()
							{
								try
								{
									scenarioEventData = dataManager->GetScenarioEventData(eventText);
									if (scenarioEventData.IsDataComplete()) { _previousEventText = eventText; return; }
								}
								catch (const std::exception& e)
								{
									umalog->print("[std::exception] dataManager->GetScenarioEventData:", e.what());
									umalog->print(u8"已終止 Scanner 運作");
									return;
								}
								catch (System::Exception^ ex)
								{
									umalog->print("[System::Exception] dataManager->GetScenarioEventData: ", utility::systemStr2std(ex->Message));
									umalog->print(u8"已終止 Scanner 運作");
									return;
								}

							});

						sapokaThread->join();
						scenarioThread->join();


						umalog->print(u8"[Scanner] sapokaUmaEventData.similarity: ", sapokaUmaEventData.similarity);
						umalog->print(u8"[Scanner] scenarioEventData.similarity: ", scenarioEventData.similarity);

						if (sapokaUmaEventData.similarity > scenarioEventData.similarity)
						{
							if (sapokaUmaEventData.IsDataComplete())
							{
								try
								{
									this->UpdateSapokaChoice(webManager, sapokaUmaEventData);
									umalog->print(u8"[Scanner] 成功更新 SapokaChoice");
								}
								catch (const std::exception& e)
								{
									umalog->print("[std::exception] UpdateSapokaChoice:", e.what());
									umalog->print(u8"已終止 Scanner 運作");
									return;
								}
								catch (System::Exception^ ex)
								{
									umalog->print("[System::Exception] UpdateSapokaChoice: ", utility::systemStr2std(ex->Message));
									umalog->print(u8"已終止 Scanner 運作");
									return;
								}
							}
						}
						else if (sapokaUmaEventData.similarity < scenarioEventData.similarity)
						{
							if (scenarioEventData.IsDataComplete())
							{
								try
								{
									this->UpdateScenarioChoice(webManager, scenarioEventData);
									umalog->print(u8"[Scanner] 成功更新 ScenarioChoice");
								}
								catch (const std::exception& e)
								{
									umalog->print("[std::exception] UpdateScenarioChoice:", e.what());
									umalog->print(u8"已終止 Scanner 運作");
									return;
								}
								catch (System::Exception^ ex)
								{
									umalog->print("[System::Exception] UpdateScenarioChoice: ", utility::systemStr2std(ex->Message));
									umalog->print(u8"已終止 Scanner 運作");
									return;
								}
							}
						}

					}
				}
				else if (_previousEventText == eventText && _updatedChoice == false && ss.IsEventTitle())
				{
					charUmaEventData = dataManager->GetCurrentCharacterUmaEventData(eventText);
					sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);
					scenarioEventData = dataManager->GetScenarioEventData(eventText);

					if (charUmaEventData.IsDataComplete())
					{
						this->UpdateCharChoice(webManager, charUmaEventData);
						umalog->print(u8"[Scanner] 成功更新 CharChoice");
						_updatedChoice = true;
					}

					else if (sapokaUmaEventData.IsDataComplete())
					{
						this->UpdateSapokaChoice(webManager, sapokaUmaEventData);
						umalog->print(u8"[Scanner] 成功更新 SapokaChoice");
						_updatedChoice = true;
					}
					else if (scenarioEventData.IsDataComplete())
					{
						this->UpdateScenarioChoice(webManager, scenarioEventData);
						umalog->print(u8"[Scanner] 成功更新 ScenarioChoice");
						_updatedChoice = true;
					}
				}
				else
				{
					umalog->print(u8"[Scanner] eventText 偵測結果與上次一致");
				}
#pragma endregion


				// 如果有 tryCharThread 就等待它執行完畢
				if (tryCharThread != nullptr && tryCharThread->joinable()) tryCharThread->join();


				//
				// 更新上次辨識到的文字
				//

				//_previousCharacterNameText = characterNameText;
				_previousHenseiCharNameText = henseiCharNameText;

				umalog->print(u8"[Scanner] _previousEventText: ", _previousEventText);
				umalog->print("[Scanner] _previousHenseiCharacterNameText: ", _previousHenseiCharNameText);


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