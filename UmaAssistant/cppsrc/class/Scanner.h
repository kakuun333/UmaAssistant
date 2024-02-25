﻿#pragma once

// STL
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <vector>
#include <mutex>

// 3rdparty
#include <tesseract/baseapi.h> // Tesseract OCR Version: 5.3.3
#include <leptonica/allheaders.h>

// util
#include "../util/CharacterFilter.h"

// class
#include "Config.h"
#include "Screenshot.h"
#include "UmaTimer.h"
#include "ref/WebViewManager.h"
#include "data/ScenarioEventData.h"
#include "data/UmaEventData.h"
#include "data/ScenarioEventData.h"

// enum
#include "../enum/ImageType.h"

// global
#include "../global/form.h"
#include "../global/umaswitch.h"

#using "CSharpRuntime/UmaCSharpLibrary.dll"

const std::string INIT_EVENT_TITLE_TEXT = "INIT_EVENT_TITLE_TEXT";
const std::string INIT_HENSEI_CHAR_NAME_TEXT = "INIT_HENSEI_CHAR_NAME_TEXT";

class Scanner
{
private:

#pragma region 私人成員變數
	static Scanner* _instance;

	static bool _scanning;

	static tesseract::TessBaseAPI* ocr_jpn;

	static tesseract::TessBaseAPI* ocr_tw;

	static tesseract::TessBaseAPI* ocr_eng;


	// 互斥鎖，用來保護共享資料，避免程式崩潰。
	std::mutex ocrMutex;
	std::mutex dataMutex;

	std::string _previousEventText = INIT_EVENT_TITLE_TEXT;
	//std::string _previousCharacterNameText;
	//std::string _previousHenseiCharNameText = INIT_HENSEI_CHAR_NAME_TEXT;

	UmaEventData _previousUpdatedUmaEventData;

	ScenarioEventData _previousUpdatedScenarioEventData;

	bool _updatedChoice = false;
#pragma endregion

#pragma region 私人成員函數
	Scanner() {};

	void _Scan();

	std::string _GetScannedText(cv::Mat image, ImageType imgType = ImageType::IMG_EVENT_TITLE, bool englishMode = false);

	void _UpdateSapokaOrCharacterChoice(UmaEventData sapokaUmaEventData);

	void _UpdateScenarioChoice(ScenarioEventData scenarioEventData);

	// 尋找 CurrentCharacter
	void _LookingForCurrentCharacter(Screenshot& ss, std::string& henseiCharNameText);

	inline void _PrintScanned(double elapsedTime)
	{
		printf("[Scanner] ============== SCANNED [%.2fs] ==============\n", elapsedTime);
	}

	// 檢查使否與上次掃描更新的 EventData 的 event_title 相同。
	template<typename T>
	inline bool _IsSameAsPreviousUpdatedEventData(T currentEventData)
	{
		if constexpr (std::is_same_v<T, UmaEventData>)
		{
			if (currentEventData.umaEvent.event_title == _previousUpdatedUmaEventData.umaEvent.event_name)
				return true;
		}
		else if constexpr (std::is_same_v<T, ScenarioEventData>)
		{
			if (currentEventData.event_name == _previousUpdatedScenarioEventData.event_name)
				return true;
		}

		return false;
	}
#pragma endregion

public:
#pragma region 公共靜態成員函數
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

	static void InitOcrEng();

	inline static bool IsInited()
	{
		if (ocr_eng != nullptr && ocr_jpn != nullptr && ocr_tw != nullptr)
			return true;
		else
			return false;
	}
#pragma endregion

	void Start();

	void Stop();
};