#pragma once

// STL
#include <mutex>
#include <string>
#include <deque>
#include <variant>


// 3rdparty
#include <nlohmann/json.hpp>
using json = nlohmann::json;


// include
#include <singleton_mutex.hpp>

#include "Config.h"
#include <UmaData/UmaEventData.h>
#include <UmaData/UmaEventNameData.h>
#include <UmaData/ScenarioEventData.h>
#include <UmaData/UmaGetCharData.h>
#include <Util/CharacterCompare.h>
#include <RefManager/WebViewManager.h>
#include <Global/form.h>

class DataManager : public SingletonMutex<DataManager>
{
public:
	void InitEventDataJson();
	
	bool SetCurrentCharacterInfoDict(std::string event_owner);

	bool TryGetCurrentCharacterByList(std::deque<std::string> scanned_text_list);

	UmaEventNameData GetMaxSimilarityUmaEventNameDataByList(std::deque<std::string> scanned_text_list);

	std::variant<UmaEventData, ScenarioEventData> GetEventDataByUmaEventNameData(UmaEventNameData umaEventNameData);

	bool TryFindScheduledRace(std::string scanned_date);

	bool TryFindCurrentDate(std::string scanned_race_date);
public:
	inline std::map<std::string, std::string> GetCurrentCharacterInfoDict()	{ return m_CurrentCharacterInfoDict;	} const

	inline std::string GetCurrentDate()	{ return m_current_date; } const

	inline std::string GetCurrentCharacter() { return m_CurrentCharacterInfoDict["event_owner"];	} const

	inline bool IsCurrentCharacterInfoLocked() { return m_CurrentCharacterInfoLocked; } const

	inline void SetCurrentCharacterInfoLock(bool value) { m_CurrentCharacterInfoLocked = value;	}

	inline void SetRaceScheduleJson(json jsonData)	{ loaded_race_schedule_json = jsonData; }
private:
	UmaEventNameData m_FindMaxSimilarityData(const std::deque<UmaEventNameData>& dataList) const;
private:
	static std::map<std::string, std::string> m_CurrentCharacterInfoDict;
	static inline constexpr double m_SIMILAR_METRIC = 0.5;
private:
	bool m_CurrentCharacterInfoLocked = false;

	std::map<GameServerType, json> m_EventDataMap;
	std::map<GameServerType, json> m_EventNameDataMap;

	json event_data_jp_json;
	json event_data_tw_json;
	json event_data_jp_trans_tw_json;

	json event_name_data_jp_json;
	json event_name_data_tw_json;

	json loaded_race_schedule_json;

	json race_date_data_json;

	std::string m_current_date;

	std::mutex dataMutex;
};
