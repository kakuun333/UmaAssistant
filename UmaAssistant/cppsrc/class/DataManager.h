#pragma once

// STL
#include <mutex>
#include <string>
#include <deque>
#include <variant>

// 3rdparty
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// util
#include "../util/CharacterCompare.h"

// class
#include "Config.h"
#include "data/UmaEventData.h"
#include "data/UmaEventNameData.h"
#include "data/ScenarioEventData.h"
#include "data/UmaGetCharData.h"

// ref class
#include "ref/WebViewManager.h"

// global
#include "../global/form.h"

class DataManager
{
private:
	DataManager() {}

	static DataManager* _instance;

	static std::map<std::string, std::string> _currentCharacterInfoDict;

	static bool _currentCharacterInfoLocked;

	json event_data_jp_json;
	json event_data_tw_json;
	json event_data_jp_trans_tw_json;

	json event_name_data_jp_json;
	json event_name_data_tw_json;

	std::mutex dataMutex;
public:
	static DataManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new DataManager();
		}
		return _instance;
	}

	void InitEventDataJson();
	
	bool SetCurrentCharacterInfoDict(std::string event_owner);

	bool TryGetCurrentCharacterByList(std::deque<std::string> scanned_text_list);

	UmaEventNameData GetMaxSimilarityUmaEventNameDataByList(std::deque<std::string> scanned_text_list);

	std::variant<UmaEventData, ScenarioEventData> GetEventDataByUmaEventNameData(UmaEventNameData umaEventNameData);


#pragma region ¤º´O¨ç¦¡
	inline std::string GetCurrentCharacter()
	{
		return _currentCharacterInfoDict["event_owner"];
	}

	inline bool IsCurrentCharacterInfoLocked()
	{
		return _currentCharacterInfoLocked;
	}

	inline void SetCurrentCharacterInfoLock(bool value)
	{
		_currentCharacterInfoLocked = value;
	}

	inline std::map<std::string, std::string> GetCurrentCharacterInfoDict()
	{
		return _currentCharacterInfoDict;
	}
#pragma endregion
};
