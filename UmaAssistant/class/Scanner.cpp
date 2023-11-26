#include "../stdafx.h"

# pragma region 初始化靜態變數
Scanner* Scanner::_instance = nullptr;
std::string Scanner::_previousEventText = "";
std::string Scanner::_previousCharacterNameText = "";
std::string Scanner::_previousHenseiCharacterNameText = "";
bool Scanner::_scanning = false;

tesseract::TessBaseAPI* Scanner::ocr_jpn = nullptr;
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

			ocr->Init(global::path::c_tessdata_best, "jpn"); // 英文 "eng"、日文 "jpn"

			ocr->SetVariable("tessedit_char_blacklist", u8"!@#$%^&*_-+<>?()[]{}|/\\`~0123456789†.,:;；=");


			ocr_jpn = ocr;
		});

	initThread.detach();
}


#pragma region 私人函數
std::string Scanner::GetScannedText(cv::Mat cvmat, std::string language)
{
	ocr_jpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE);


	// 設置圖片到 ocr
	ocr_jpn->SetImage(cvmat.data, cvmat.size().width, cvmat.size().height, cvmat.channels(), cvmat.step);

	ocr_jpn->Recognize(0);

	// 進行文字辨識
	char* utf8 = ocr_jpn->GetUTF8Text();

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
				//std::unique_ptr<Screenshot> ss(new Screenshot());
				Screenshot ss;
				
				//global::form::previewForm->pictureBox1->Image = ss->bmp_window;

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

				eventText = this->GetScannedText(ss.event_title_gray_bin, language);
				std::cout << "event_title_gray_bin: " << eventText << std::endl;

				eventText = this->GetScannedText(ss.event_title_gray_bin_inv, language);
				std::cout << "event_title_gray_bin_inv: " << eventText << std::endl;

				//std::thread eventTextThread([=, &eventText]()
				//	{
						
				//	});

				//std::thread* characterNameTextThread = nullptr;

				//std::thread* henseiCharNameTextThread = nullptr;

				//if (!dataManager->IsCurrentCharacterInfoLocked())
				//{
				//	characterNameTextThread = new std::thread([=, &characterNameText]()
				//		{
				//			characterNameText = this->GetCharacterName(global::path::c_screenshot_character_name, language);
				//		});

				//	henseiCharNameTextThread = new std::thread([=, &henseiCharNameText]()
				//		{
				//			henseiCharNameText = this->GetHenseiCharacterName(global::path::c_screenshot_hensei_character_name, language);
				//		});

				//	characterNameTextThread->join();
				//	henseiCharNameTextThread->join();

				//	delete characterNameTextThread;
				//	delete henseiCharNameTextThread;
				//}


				//eventTextThread.join();


				//std::cout << "eventText: " << eventText << std::endl;
				//std::cout << "characterNameText: " << characterNameText << std::endl;
				//std::cout << "henseiCharNameText: " << henseiCharNameText << std::endl;


				//if (_previousEventText != eventText ||
				//	_previousCharacterNameText != characterNameText ||
				//	_previousHenseiCharacterNameText != henseiCharNameText)
				//{
				//	if (dataManager->IsCurrentCharacterInfoLocked())
				//	{
				//		std::cout << "locked" << std::endl;
				//	}
				//	else
				//	{
				//		//dataManager->TryGetCurrentCharacterName(henseiCharNameText);
				//		if (!dataManager->TryGetCurrentCharacterName(henseiCharNameText))
				//		{
				//			dataManager->TryGetCurrentCharacterName(characterNameText);
				//		}
				//	}
				//	UmaEventData charUmaEventData = dataManager->GetCurrentCharacterUmaEventData(eventText);
				//	std::cout << "charUmaEventData.IsDataComplete: " << charUmaEventData.IsDataComplete() << std::endl;

				//	if (charUmaEventData.IsDataComplete())
				//	{
				//		// 這裡更新 UI
				//		webManager->CleanChoiceTable();

				//		utility::formctrl::Clear(global::form::umaForm->choicePanel); // 清除先前創建的 WinForm 物件
				//		for (UmaChoice choice : charUmaEventData.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
				//		{
				//			webManager->CreateChoice(choice.sys_choice_title, choice.sys_choice_effect);

				//			FormDesigner::Instance->CreateChoiceTable(choice);
				//		}

				//		System::String^ sys_event_owner = charUmaEventData.Get<System::String^>(UmaEventDataType::EVENT_OWNER);
				//		utility::formctrl::Text(global::form::umaForm->event_owner_textBox, sys_event_owner);

				//		webManager->ChangeEventOwner(sys_event_owner);

				//		System::String^ sys_event_title = charUmaEventData.Get<System::String^>(UmaEventDataType::EVENT_TITLE);
				//		utility::formctrl::Text(global::form::umaForm->event_title_textbox, sys_event_owner);

				//		webManager->ChangeEventTitle(sys_event_title);

				//	}
				//	else
				//	{
				//		UmaEventData sapokaUmaEventData = dataManager->GetSupportCardUmaEventData(eventText);

				//		if (!sapokaUmaEventData.IsDataComplete())
				//		{
				//			std::cout << u8"[sapokaUmaEventData 資料不完整]" << std::endl;
				//			continue;
				//		};

				//		webManager->CleanChoiceTable();

				//		utility::formctrl::Clear(global::form::umaForm->choicePanel); // 清除先前創建的 WinForm 物件
				//		for (UmaChoice choice : sapokaUmaEventData.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
				//		{
				//			webManager->CreateChoice(choice.sys_choice_title, choice.sys_choice_effect);

				//			FormDesigner::Instance->CreateChoiceTable(choice);
				//		}

				//		System::String^ sys_event_owner = sapokaUmaEventData.Get<System::String^>(UmaEventDataType::EVENT_OWNER);
				//		utility::formctrl::Text(global::form::umaForm->event_owner_textBox, sys_event_owner);

				//		webManager->ChangeEventOwner(sys_event_owner);

				//		System::String^ sys_event_title = sapokaUmaEventData.Get<System::String^>(UmaEventDataType::EVENT_TITLE);
				//		utility::formctrl::Text(global::form::umaForm->event_title_textbox, sys_event_owner);

				//		webManager->ChangeEventTitle(sys_event_title);

				//	}

				//}
				//else
				//{
				//	std::cout << u8"偵測結果與上次一致" << std::endl;
				//}

				//
				// 更新上次辨識到的文字
				//
				_previousEventText = eventText; 
				_previousCharacterNameText = characterNameText;

				std::cout << u8"scanned" << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
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