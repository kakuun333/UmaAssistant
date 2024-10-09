#pragma once

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

// Util
#include <Util/CharacterFilter.h>

#include "Config.h"
#include "Screenshot.h"
#include "UmaTimer.h"
#include <RefManager/WebViewManager.h>
#include <UmaData/ScenarioEventData.h>
#include <UmaData/UmaEventData.h>
#include <UmaData/UmaEventNameData.h>

// include
#include <singleton_mutex.hpp>

// Enum
#include <Enum/ImageType.h>

// Global
#include <Global/form.h>
#include <Global/umaswitch.h>
//#include <Global/path.h>



#using "CSharpDLL/UmaCSharpLibrary.dll"

const std::string INIT_EVENT_TITLE_TEXT = "INIT_EVENT_TITLE_TEXT";
const std::string INIT_HENSEI_CHAR_NAME_TEXT = "INIT_HENSEI_CHAR_NAME_TEXT";

class Scanner : public SingletonMutex<Scanner>
{
public:
	void InitOcrJpn();
	void InitOcrTw();
	void InitOcrEng();

	inline bool IsInited()
	{
		if (m_OcrJpn != nullptr && m_OcrTw != nullptr && m_OcrEng != nullptr)
			return true;
		else
			return false;
	}

	void Start();

	void Stop();

private:
	void m_Scan();

	std::string m_GetScannedText(cv::Mat image, ImageType imgType = ImageType::IMG_EVENT_NAME, bool englishMode = false);

	void m_UpdateSapokaOrCharacterChoice(UmaEventData sapokaUmaEventData);

	void m_UpdateScenarioChoice(ScenarioEventData scenarioEventData);

	// 尋找 CurrentCharacter
	void m_LookingForCurrentCharacter(Screenshot& ss, std::string& henseiCharNameText);

	inline void m_PrintScanned(const double& elapsedTime)
	{
		printf("[Scanner] ============== SCANNED [%.2fs] ==============\n", elapsedTime);
	}

	// 檢查使否與上次掃描更新的 EventData 的 event_title 相同。
	template<typename T>
	inline bool m_IsSameAsPreviousUpdatedEventData(T currentEventData)
	{
		if constexpr (std::is_same_v<T, UmaEventData>)
		{
			if (currentEventData.umaEvent.event_title == m_PreviousUpdatedUmaEventData.umaEvent.event_name)
				return true;
		}
		else if constexpr (std::is_same_v<T, ScenarioEventData>)
		{
			if (currentEventData.event_name == m_PreviousUpdatedScenarioEventData.event_name)
				return true;
		}

		return false;
	}

private:
	bool m_Scanning = false;

	tesseract::TessBaseAPI* m_OcrJpn = nullptr;
	tesseract::TessBaseAPI* m_OcrTw = nullptr;
	tesseract::TessBaseAPI* m_OcrEng = nullptr;


	// 互斥鎖，用來保護共享資料，避免程式崩潰。
	std::mutex m_OcrMutex;
	std::mutex m_DataMutex;

	std::string m_PreviousEventText = INIT_EVENT_TITLE_TEXT;
	//std::string _previousCharacterNameText;
	//std::string _previousHenseiCharNameText = INIT_HENSEI_CHAR_NAME_TEXT;

	UmaEventData m_PreviousUpdatedUmaEventData;

	ScenarioEventData m_PreviousUpdatedScenarioEventData;

	bool m_UpdatedChoice = false;
};