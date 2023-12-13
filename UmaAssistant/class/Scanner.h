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


const std::string INIT_EVENT_TITLE_TEXT = "INIT_EVENT_TITLE_TEXT";
const std::string INIT_HENSEI_CHAR_NAME_TEXT = "INIT_HENSEI_CHAR_NAME_TEXT";

class Scanner
{
private:
	Scanner() {};

	static Scanner* _instance;

	static bool _scanning;

	static tesseract::TessBaseAPI* ocr_jpn;

	static tesseract::TessBaseAPI* ocr_tw;

	// 互斥鎖。用於保護 OCR 物件
	std::mutex ocrMutex;

	std::string GetScannedText(cv::Mat image, std::string language, ImageType imgType);

	void UpdateSapokaChoice(WebManager* webManager, UmaEventData sapokaUmaEventData);

	void UpdateCharChoice(WebManager* webManager, UmaEventData charUmaEventData);

	void UpdateScenarioChoice(WebManager* webManager, ScenarioEventData scenarioEventData);

	std::string _previousEventText = INIT_EVENT_TITLE_TEXT;
	std::string _previousCharacterNameText;
	std::string _previousHenseiCharNameText = INIT_HENSEI_CHAR_NAME_TEXT;

	bool _updatedChoice = false;

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