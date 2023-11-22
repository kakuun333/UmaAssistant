#include "../stdafx.h"

# pragma region 初始化靜態變數
Scanner* Scanner::_instance = nullptr;
std::string Scanner::_previousText = "";
bool Scanner::_scanning = false;
#pragma endregion

/*
	類型轉換
	utf8 => utf16 => System::String^
*/

#pragma region 私人函數
std::string Scanner::GetScannedText(const char* imgPath, const char* language)
{
	// 初始化 Tesseract
	tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();

	ocr->Init(global::path::c_tessdata_best, language); // 英文 "eng"、日文 "jpn"

	// 讀取圖片
	Pix* image = pixRead(imgPath);

	// 設置圖片到 ocr
	ocr->SetImage(image);

	// 進行文字辨識
	char* utf8 = ocr->GetUTF8Text();

	std::string stdString(utf8);
	std::string result = utility::RemoveSpace(stdString);

	//// utf8 轉 utf16
	//wchar_t* utf16 = utility::utf8to16(utf8);
	//// wchar_t 轉 System::String^
	//System::String^ scanResult = marshal_as<System::String^>(utf16);
	//// 去除空白鍵
	//System::String^ removed_space = utility::RemoveSpace(scanResult);

#pragma region 釋放記憶體
	ocr->End();
	delete[] utf8;
	pixDestroy(&image);
#pragma endregion 釋放記憶體

	return result;
}
#pragma endregion 私人函數



void Scanner::Start(const char* imgPath, const char* language)
{
	if (global::umaswitch::Scanning)
	{
		std::cout << "必須先停止掃描 Scanner::Stop()" << std::endl;
		return;
	}

	std::string text = u8"食いしん坊は伊達じゃない";

	//utility::SplitText(text, 4);

	/*utility::SplitJpnChar(text);*/

	//utility::IsSimilar(u8"食いしん坊は伊達じゃない", u8"食いじん坊は伊達じゃない");



	DataManager* dataManager = DataManager::GetInstance();

	global::umaswitch::Scanning = true;

	std::thread scanThread([=]()
		{
			_scanning = true;
			while (global::umaswitch::Scanning)
			{
				std::unique_ptr<Screenshot>ss(new Screenshot());
				global::form::previewForm->pictureBox1->Image = ss->bmp_window;

				std::string scannedText = this->GetScannedText(imgPath, language);
				

				std::cout << "scannedText: " << scannedText << std::endl;

				///
				/// 更新 UmaForm 的 ChoicePanel
				/// 
				if (_previousText != scannedText)
				{
					UmaEventData event_data = dataManager->GetUmaEventDataFromJson(scannedText); // 從 event_data_jp.json 中獲取資料;

					///
					/// 防止 System.NullReferenceException: '並未將物件參考設定為物件的執行個體。'
					/// 
					if (!event_data.IsDataComplete())
					{
						std::cout << u8"[資料不完整]" << std::endl;
						//std::cout << u8"scannedText: " << scannedText << std::endl;
						//std::cout << u8"length: " << scannedText.length() << " size: " << scannedText.size() << std::endl;
						continue;
					};


					utility::formctrl::Clear(global::form::umaForm->choicePanel); // 清除先前創建的 WinForm 物件
					for (UmaChoice choice : event_data.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
					{
						FormDesigner::Instance->CreateChoiceTable(choice);
					}

					System::String^ sys_event_owner = event_data.Get<System::String^>(UmaEventDataType::EVENT_OWNER);
					utility::formctrl::Text(global::form::umaForm->event_owner_textBox, sys_event_owner);

					System::String^ sys_event_title = event_data.Get<System::String^>(UmaEventDataType::EVENT_TITLE);
					utility::formctrl::Text(global::form::umaForm->event_title_textbox, sys_event_owner);

				}
				else
				{
					std::cout << u8"偵測結果與上次一致" << std::endl;
				}

				_previousText = scannedText; // 更新上次辨識到的文字

				std::cout << u8"scanned" << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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