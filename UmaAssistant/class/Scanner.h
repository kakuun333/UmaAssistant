#pragma once

// STL
#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <mutex>

// 3rdparty
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>

// class
#include "../class/WebManager.h"
#include "../class/Screenshot.h"

// data
#include "../class/data/ScenarioEventData.h"
#include "../class/data/UmaEventData.h"
#include "../class/data/ScenarioEventData.h"

// enum
#include "../enum/ImageType.h"

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

	void _UpdateSapokaChoice(WebManager* webManager, UmaEventData sapokaUmaEventData);

	void _UpdateCharChoice(WebManager* webManager, UmaEventData charUmaEventData);

	void _UpdateScenarioChoice(WebManager* webManager, ScenarioEventData scenarioEventData);

	// 尋找 CurrentCharacter
	void _LookingForCurrentCharacter(Screenshot& ss, std::string& henseiCharNameText);

	bool _IsEventTextEmpty(Screenshot& ss, std::string& eventText);

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
			if (currentEventData.umaEvent.event_title == _previousUpdatedUmaEventData.umaEvent.event_title)
				return true;
		}
		else if constexpr (std::is_same_v<T, ScenarioEventData>)
		{
			if (currentEventData.event_title == _previousUpdatedScenarioEventData.event_title)
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
