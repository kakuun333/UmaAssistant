﻿#include "../stdafx.h"

# pragma region 初始化靜態變數
Scanner* Scanner::_instance = nullptr;
std::string Scanner::_previousEventText = "";
std::string Scanner::_previousCharacterNameText = "";
bool Scanner::_scanning = false;

tesseract::TessBaseAPI* Scanner::ocr_jpn = nullptr;
tesseract::TessBaseAPI* Scanner::ocr_jpn_character = nullptr;
#pragma endregion

/*
	類型轉換
	utf8 => utf16 => System::String^
*/

Scanner::Scanner()
{
	this->InitOcrJpn();
}


void Scanner::InitOcrJpn()
{
	tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

	ocr->Init(global::path::c_tessdata_best, "jpn"); // 英文 "eng"、日文 "jpn"

	ocr->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=");

	ocr_jpn = ocr;

	//ocr->End();

	tesseract::TessBaseAPI* ocr_char = new tesseract::TessBaseAPI();

	ocr_char->Init(global::path::c_tessdata_best, "jpn"); // 英文 "eng"、日文 "jpn"

	ocr_char->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=「」【】『』〈〉［］〔〕≪≫（）");

	ocr_jpn_character = ocr_char;
}


#pragma region 私人函數
std::string Scanner::GetScannedText(const char* imgPath, const char* language)
{
	// 讀取圖片
	Pix* image = pixRead(imgPath);

	// 設置圖片到 ocr
	ocr_jpn->SetImage(image);

	// 進行文字辨識
	char* utf8 = ocr_jpn->GetUTF8Text();

	std::string stdString(utf8);
	std::string result = utility::RemoveSpace(stdString);

	//// utf8 轉 utf16
	//wchar_t* utf16 = utility::utf8to16(utf8);
	//// wchar_t 轉 System::String^
	//System::String^ scanResult = marshal_as<System::String^>(utf16);
	//// 去除空白鍵
	//System::String^ removed_space = utility::RemoveSpace(scanResult);

#pragma region 釋放記憶體
	//ocr->End();
	delete[] utf8;
	pixDestroy(&image);
#pragma endregion 釋放記憶體

	return result;
}

std::string Scanner::GetCharacterName(const char* imgPath, const char* language)
{
	// 讀取圖片
	Pix* image = pixRead(imgPath);

	// 設置圖片到 ocr
	ocr_jpn_character->SetImage(image);

	// 進行文字辨識
	char* utf8 = ocr_jpn_character->GetUTF8Text();

	std::string stdString(utf8);
	std::string result = utility::RemoveSpace(stdString);

	//// utf8 轉 utf16
	//wchar_t* utf16 = utility::utf8to16(utf8);
	//// wchar_t 轉 System::String^
	//System::String^ scanResult = marshal_as<System::String^>(utf16);
	//// 去除空白鍵
	//System::String^ removed_space = utility::RemoveSpace(scanResult);

#pragma region 釋放記憶體
	//ocr->End();
	delete[] utf8;
	pixDestroy(&image);
#pragma endregion 釋放記憶體

	return result;
}


#pragma endregion 私人函數



void Scanner::Start(const char* language)
{
	if (global::umaswitch::Scanning)
	{
		std::cout << "必須先停止掃描 Scanner::Stop()" << std::endl;
		return;
	}




	global::umaswitch::Scanning = true;

	std::thread scanThread([=]()
		{
			DataManager* dataManager = DataManager::GetInstance();
			WebManager* webManager = WebManager::GetInstance();

			_scanning = true;
			while (global::umaswitch::Scanning)
			{
				std::unique_ptr<Screenshot>ss(new Screenshot());
				global::form::previewForm->pictureBox1->Image = ss->bmp_window;

				///
				/// 獲取圖片裡的文字
				/// 
				std::string eventText;
				std::string characterNameText;

				std::thread eventTextThread([=, &eventText]()
					{
						eventText = this->GetScannedText(global::path::c_screenshot_event, language);
					});

				std::thread characterNameTextThread([=, &characterNameText]()
					{
						characterNameText = this->GetCharacterName(global::path::c_screenshot_character_name, language);
					});

				eventTextThread.join();
				characterNameTextThread.join();

				std::cout << "eventText: " << eventText << std::endl;
				std::cout << "characterNameText: " << characterNameText << std::endl;

				///
				/// 更新 UmaForm 的 ChoicePanel
				/// 




				if (_previousEventText != eventText || _previousCharacterNameText != characterNameText)
				{
					if (dataManager->IsCurrentCharacterInfoLocked())
					{
						std::cout << "locked" << std::endl;
						
					}
					else
					{
						dataManager->TryGetCurrentCharacterName(characterNameText);
					}

					UmaEventData charUmaEventData = dataManager->GetCurrentCharacterUmaEventData(eventText);

					/*
					* TODO
					* dataManager->GetCurrentCharacterUmaEventData()
					* dataManager->GetSupportCardUmaEventData()
					* 
					* 
					*/

					
					//UmaEventData event_data = dataManager->GetUmaEventDataFromJson(characterNameText); // 從 event_data_jp.json 中獲取資料;



					///
					/// 防止 System.NullReferenceException: '並未將物件參考設定為物件的執行個體。'
					/// 

					//if (!event_data.IsDataComplete())
					//{
					//	std::cout << u8"[資料不完整]" << std::endl;
					//	continue;
					//};


					//webManager->CleanChoiceTable();

					////utility::formctrl::Clear(global::form::umaForm->choicePanel); // 清除先前創建的 WinForm 物件
					//for (UmaChoice choice : event_data.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
					//{
					//	webManager->CreateChoice(choice.sys_choice_title, choice.sys_choice_effect);


					//	//FormDesigner::Instance->CreateChoiceTable(choice);
					//}

					//System::String^ sys_event_owner = event_data.Get<System::String^>(UmaEventDataType::EVENT_OWNER);
					////utility::formctrl::Text(global::form::umaForm->event_owner_textBox, sys_event_owner);


					//webManager->ChangeEventOwner(sys_event_owner);


					//System::String^ sys_event_title = event_data.Get<System::String^>(UmaEventDataType::EVENT_TITLE);
					////utility::formctrl::Text(global::form::umaForm->event_title_textbox, sys_event_owner);


					//webManager->ChangeEventTitle(sys_event_title);

				}
				else
				{
					std::cout << u8"偵測結果與上次一致" << std::endl;
				}

				//
				// 更新上次辨識到的文字
				//
				_previousEventText = eventText; 
				_previousCharacterNameText = characterNameText;

				std::cout << u8"scanned" << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(800));
			}
			_scanning = false;
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