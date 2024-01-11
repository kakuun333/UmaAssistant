#pragma once


#include <nlohmann/json.hpp>

#include "data/UmaEventData.h"
#include "data/ScenarioEventData.h"

// STL
#include <mutex>
#include <string>
#include <deque>

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
	
	UmaEventData GetCurrentCharacterUmaEventDataByList(std::deque<std::string> scanned_text_list);

	UmaEventData GetSapokaUmaEventDataByList(std::deque<std::string> scanned_text_list);

	ScenarioEventData GetScenarioEventDataByList(std::deque<std::string> scanned_text_list);

	bool TryGetCurrentCharacterByList(std::deque<std::string> scanned_text_list);

	bool SetCurrentCharacterInfoDict(std::string event_owner);

#pragma region 內嵌函式
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

#pragma region 已棄用的函式
	UmaEventData GetCurrentCharacterUmaEventData(std::string scanned_text);
	UmaEventData GetSapokaUmaEventData(std::string scanned_text);
	ScenarioEventData GetScenarioEventData(std::string scanned_text);
	bool TryGetCurrentCharacterName(std::string scanned_text);
#pragma endregion
};

