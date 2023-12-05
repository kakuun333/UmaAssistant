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

/*
	類型轉換
	utf8 => utf16 => System::String^
*/

Scanner::Scanner()
{

}


void Scanner::InitOcrJpn()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::c_tessdata_best, "jpn", tesseract::OEM_DEFAULT); // 日文 "jpn"、繁體中文 "chi_tra"

			ocr->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=");

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

			ocr->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=");

			ocr->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);

			ocr_tw = ocr;
		});

	initThread.detach();
}


#pragma region 私人函數
std::string Scanner::GetScannedText(cv::Mat image, std::string language, ImageType imgType = ImageType::IMG_EVENT_TITLE)
{
	char* utf8;

	//ocr_jpn->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);

	switch (global::config->GameServer)
	{
	case GameServerType::JP:
		switch (imgType)
		{
		case ImageType::IMG_EVENT_TITLE:
			ocr_jpn->SetVariable("tessedit_char_blacklist", u8"@#$%^&*_-+<>()[]{}|/\\`~0123456789†.,:;；=");
			//ocr_jpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
			break;
		case ImageType::IMG_HENSEI_CHARACTER_NAME:
			ocr_jpn->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
			//ocr_jpn->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
			break;
		}

		// 設置圖片到 ocr
		//ocr_jpn->SetImage(image.data, image.size().width, image.size().height, image.channels(), image.step);
		ocr_jpn->SetImage(image.data, image.cols, image.rows, 1, image.cols);

		ocr_jpn->Recognize(0);

		// 進行文字辨識
		utf8 = ocr_jpn->GetUTF8Text();
		break;

	case GameServerType::TW:
		switch (imgType)
		{
		case ImageType::IMG_EVENT_TITLE:
			ocr_tw->SetVariable("tessedit_char_blacklist", u8"@#$%^&*_-+<>()[]{}|/\\`~0123456789†.,:;；=");
			break;
		case ImageType::IMG_HENSEI_CHARACTER_NAME:
			ocr_tw->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
			break;
		}

		// 設置圖片到 ocr
		//ocr_jpn->SetImage(image.data, image.size().width, image.size().height, image.channels(), image.step);
		ocr_tw->SetImage(image.data, image.cols, image.rows, 1, image.cols);

		ocr_tw->Recognize(0);

		// 進行文字辨識
		utf8 = ocr_tw->GetUTF8Text();
		break;
	}



	std::string stdString(utf8);
	std::string result = utility::RemoveSpace(stdString);


#pragma region 釋放記憶體
	//ocr->End();
	delete[] utf8;
#pragma endregion 釋放記憶體

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
		std::cout << "[Scanner] 必須先停止掃描 Scanner::Stop()" << std::endl;
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
				auto start_time = std::chrono::system_clock::now();
				//std::unique_ptr<Screenshot> ss(new Screenshot());
				Screenshot ss;
				if (!ss.IsDataComplete())
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					continue;
				}

				///
				/// 獲取圖片裡的文字
				/// 
				std::string eventText;
				std::string characterNameText;
				std::string henseiCharNameText;


				//eventText = this->GetScannedText(ss.event_title_oimg, language);
				//std::cout << "event_title_oimg: " << eventText << std::endl;

				//eventText = this->GetScannedText(ss.event_title_resize, language);
				//std::cout << "event_title_resize: " << eventText << std::endl;

				//eventText = this->GetScannedText(ss.event_title_gray, language);
				//std::cout << "event_title_gray: " << eventText << std::endl;

				//eventText = this->GetScannedText(ss.event_title_gray_bin_inv, language);
				//std::cout << "event_title_gray_bin_inv: " << eventText << std::endl;

				eventText = this->GetScannedText(ss.event_title_gray_bin, language);

				henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray, language, ImageType::IMG_HENSEI_CHARACTER_NAME);

				if (eventText.empty() && henseiCharNameText.empty())
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					std::cout << u8"[Scanner] 都是空字串" << std::endl;
					continue;
				}

				std::cout << u8"[Scanner] event_title_gray_bin: " << eventText << std::endl;
				std::cout << u8"[Scanner] henseiCharNameText: " << henseiCharNameText << std::endl;
				//henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_inv, language, ImageType::IMG_HENSEI_CHARACTER_NAME);
				//std::cout << "henseiCharNameText_inv: " << henseiCharNameText << std::endl;

				if (_previousEventText != eventText ||
					_previousCharacterNameText != characterNameText ||
					_previousHenseiCharacterNameText != henseiCharNameText)
				{
#pragma region Looking for Current Character
					if (!dataManager->IsCurrentCharacterInfoLocked())
					{
						if (!dataManager->TryGetCurrentCharacterName(henseiCharNameText))
						{
							std::cout << u8"[Scanner] TryGetCurrentCharacterName 失敗" << std::endl;

							henseiCharNameText = this->GetScannedText(ss.hensei_character_name_gray_inv, language);
							std::cout << "[Scanner] hensei_character_name_gray_inv: " << henseiCharNameText << std::endl;
							std::cout << u8"[Scanner] 嘗試 hensei_character_name_gray_inv" << std::endl;
							dataManager->TryGetCurrentCharacterName(henseiCharNameText);
						}
					}
					else
					{
						std::cout << "[Scanner] CURRENT CHARACTER LOCKED" << std::endl;
					}
#pragma endregion




#pragma region Character Event Data
					UmaEventData charUmaEventData = dataManager->GetCurrentCharacterUmaEventData(eventText);
					std::cout << "[Scanner] charUmaEventData.IsDataComplete: " << charUmaEventData.IsDataComplete() << std::endl;

					if (charUmaEventData.IsDataComplete())
					{
						// 這裡更新 UI
						webManager->CleanChoiceTable();

						for (UmaChoice choice : charUmaEventData.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
						{
							webManager->CreateChoice(choice.sys_choice_title, choice.sys_choice_effect);
						}

						System::String^ sys_event_owner = charUmaEventData.Get<System::String^>(UmaEventDataType::EVENT_OWNER);

						webManager->ChangeEventOwner(sys_event_owner);

						System::String^ sys_event_title = charUmaEventData.Get<System::String^>(UmaEventDataType::EVENT_TITLE);

						webManager->ChangeEventTitle(sys_event_title);

						webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
						webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
#pragma endregion
					}
					else
					{
						/*
						* 有時候名字很像的事件名稱會先偵測到 scenarioEventData ，但是正確的事件在 sapokaUmaEventData
						* 為了避免先偵測到 scenarioEventData ，應該要先比較 similarity 再判斷要更新的事件是
						* scenarioEventData 還是 sapokaUmaEventData
						*/
						ScenarioEventData scenarioEventData = dataManager->GetScenarioEventData(eventText);
						UmaEventData sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);


						if (scenarioEventData.similarity > sapokaUmaEventData.similarity)
						{
							if (!scenarioEventData.IsDataComplete()) continue;

							webManager->CleanChoiceTable();

							for (ScenarioChoice choice : scenarioEventData.event_list)
							{
								webManager->CreateChoice(utility::stdStr2system(choice.choice_title), utility::stdStr2system(choice.choice_effect));
							}

							System::String^ sys_event_title = utility::stdStr2system(scenarioEventData.event_title);

							switch (global::config->GameServer)
							{
							case GameServerType::JP:
								webManager->ChangeEventOwner(u8"メインシナリオイベント");
								break;
							case GameServerType::TW:
								webManager->ChangeEventOwner(u8"主要劇情事件");
								break;
							}

							webManager->ChangeEventTitle(sys_event_title);

							webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
							webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽

							std::cout << u8"[Scanner] scenarioEventData 資料不完整" << std::endl;
						}
						else
						{
							if (!sapokaUmaEventData.IsDataComplete())
							{
								std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整" << std::endl;

								eventText = this->GetScannedText(ss.event_title_gray, language);
								std::cout << "[Scanner] event_title_gray: " << eventText << std::endl;
								sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

								if (!sapokaUmaEventData.IsDataComplete())
								{
									std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整2" << std::endl;

									eventText = this->GetScannedText(ss.event_title_oimg, language);
									std::cout << "[Scanner] event_title_oimg: " << eventText << std::endl;
									sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

									if (!sapokaUmaEventData.IsDataComplete())
									{
										std::cout << u8"[Scanner] sapokaUmaEventData 資料不完整3" << std::endl;

										auto end_time = std::chrono::system_clock::now();
										auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
										double seconds = duration.count() * 1.0f / 1000;
										printf("[Scanner] SCANNED [%.2fs]\n", seconds);

										continue;
									}
								}
							};

							webManager->CleanChoiceTable();

							for (UmaChoice choice : sapokaUmaEventData.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
							{
								webManager->CreateChoice(choice.sys_choice_title, choice.sys_choice_effect);
							}

							System::String^ sys_event_owner = sapokaUmaEventData.Get<System::String^>(UmaEventDataType::EVENT_OWNER);
							webManager->ChangeEventOwner(sys_event_owner);

							System::String^ sys_event_title = sapokaUmaEventData.Get<System::String^>(UmaEventDataType::EVENT_TITLE);
							webManager->ChangeEventTitle(sys_event_title);

							webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
							webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
						}
					}
				}
				else
				{
					std::cout << u8"[Scanner] 偵測結果與上次一致" << std::endl;
				}

				//
				// 更新上次辨識到的文字
				//
				_previousEventText = eventText; 
				_previousCharacterNameText = characterNameText;
				_previousHenseiCharacterNameText = henseiCharNameText;

				// 記錄結束時間
				auto end_time = std::chrono::system_clock::now();

				// 計算執行時間（毫秒）
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

				// 將時間差轉換為秒
				double seconds = duration.count() * 1.0f / 1000;

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