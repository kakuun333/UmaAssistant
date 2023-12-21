#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include "data/UmaEventData.h"
#include "data/ScenarioEventData.h"

#include <mutex>

class DataManager
{
private:
	DataManager() {}

	static DataManager* _instance;

	static std::map<std::string, std::string> _currentCharacterInfoDict;

	static bool _currentCharacterInfoLocked;

	static nlohmann::json event_data_jp_json;
	static nlohmann::json event_data_tw_json;

	static nlohmann::json event_data_jp_trans_tw_json;

	static nlohmann::json scenario_event_data_jp_json;
	static nlohmann::json scenario_event_data_tw_json;

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

	static void InitEventDataJson();

	//UmaEventData GetUmaEventDataFromJson(std::string scanned_text);

	UmaEventData GetCurrentCharacterUmaEventData(std::string scanned_text);

	UmaEventData GetSupportCardUmaEventData(std::string scanned_text);

	ScenarioEventData GetScenarioEventData(std::string scanned_text);

	bool TryGetCurrentCharacterName(std::string scanned_text);

	bool SetCurrentCharacterInfoDict(std::string event_owner);

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
};

