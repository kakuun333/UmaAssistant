#pragma once

#include <string>
#include <functional>
#include <vector>
#include <iostream>



class Scanner
{
private:
	Scanner() {}

	static Scanner* _instance;

	static std::string _previousText;

	static bool _scanning;

	std::string Scanner::GetScannedText(const char* imgPath, const char* language);
public:
	static Scanner* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new Scanner();
		}
		return _instance;
	}

	void Start(const char* imgPath, const char* language = "jpn");

	void Stop();
};