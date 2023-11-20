#include "../stdafx.h"

Scanner::Scanner() {}
Scanner* Scanner::_instance = nullptr;

System::String^ Scanner::Scan(const char* imgPath, const char* language)
{
	// 初始化 Tesseract
	tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();

	ocr->Init(global::path::c_tessdata_best, language); // 英文 "eng"、日文 "jpn"

	// 讀取圖片
	Pix* image = pixRead(imgPath);

	// 設置圖片到 ocr
	ocr->SetImage(image);

	/*
		類型轉換
		utf8 => utf16 => System::String^
	
	*/

	// 進行文字辨識
	char* utf8 = ocr->GetUTF8Text();


	// utf8 轉 utf16
	wchar_t* utf16 = utility::utf8to16(utf8);

	// wchar_t 轉 System::String^
	System::String^ scanResult = marshal_as<System::String^>(utf16);

	// 去除空白鍵
	System::String^ removed_space = utility::RemoveSpace(scanResult);


#pragma region 釋放記憶體
	ocr->End();
	delete[] utf8;
	pixDestroy(&image);
#pragma endregion

	return removed_space;
}