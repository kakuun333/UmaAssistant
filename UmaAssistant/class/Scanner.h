#pragma once

#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include "../enum/ImageType.h"


class Scanner
{
private:
	Scanner();

	static Scanner* _instance;

	static std::string _previousEventText;
	static std::string _previousCharacterNameText;
	static std::string _previousHenseiCharacterNameText;

	static bool _scanning;

	static tesseract::TessBaseAPI* ocr_jpn;

	std::string GetScannedText(cv::Mat image, std::string language, ImageType imgType);
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

	void Start(std::string language = "jpn");

	void Stop();
};