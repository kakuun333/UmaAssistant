#pragma once

#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <mutex>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>

#include "../class/WebManager.h"
#include "../class/data/ScenarioEventData.h"
#include "../class/data/UmaEventData.h"

#include "../enum/ImageType.h"


class Scanner
{
private:
	Scanner() {};

	static Scanner* _instance;

	static std::string _previousEventText;
	static std::string _previousCharacterNameText;
	static std::string _previousHenseiCharacterNameText;

	static bool _scanning;

	static tesseract::TessBaseAPI* ocr_jpn;

	static tesseract::TessBaseAPI* ocr_tw;

	std::mutex ocrMutex;  // 用於保護 OCR 物件

	std::string GetScannedText(cv::Mat image, std::string language, ImageType imgType);

	void UpdateSapokaChoice(WebManager* webManager, UmaEventData sapokaUmaEventData);

	void UpdateCharChoice(WebManager* webManager, UmaEventData charUmaEventData);

	void UpdateScenarioChoice(WebManager* webManager, ScenarioEventData scenarioEventData);
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

	static void InitOcrTw();

	void Start(std::string language = "jpn");

	void Stop();
};