#pragma once

#include <string>
#include <functional>
#include <vector>
#include <iostream>



class Scanner
{
private:
	Scanner();

	static Scanner* _instance;

	static std::string _previousEventText;
	static std::string _previousCharacterNameText;

	static bool _scanning;

	static tesseract::TessBaseAPI* ocr_jpn;

	static tesseract::TessBaseAPI* ocr_jpn_character;


	std::string Scanner::GetScannedText(const char* imgPath, const char* language);

	std::string Scanner::GetCharacterName(const char* imgPath, const char* language);
public:
	static Scanner* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new Scanner();
		}
		return _instance;
	}

	static void InitOcrJpn();

	void Start(const char* language = "jpn");

	void Stop();
};