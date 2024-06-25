#include "DataManager.h"


#using "CSharpDLL/UmaCSharpLibrary.dll"

std::map<std::string, std::string> DataManager::m_CurrentCharacterInfoDict =
{
	// route
	{ "rare", "" },

	// characterName
	{ "event_owner", "" },
};

void DataManager::InitEventDataJson()
{
	FileManager* fileManager = FileManager::GetInstance();

	// event_data //
	event_data_jp_json = fileManager->ReadJson(global::path::std_event_data_jp_json);
	event_name_data_jp_json = fileManager->ReadJson(global::path::std_UmaData + "\\event_name_data_jp.json");

	event_data_tw_json = fileManager->ReadJson(global::path::std_event_data_tw_json);
	event_name_data_tw_json = fileManager->ReadJson(global::path::std_UmaData + "\\event_name_data_tw.json");

	// jp server translation data //
	event_data_jp_trans_tw_json = fileManager->ReadJson(global::path::std_event_data_jp_trans_tw_json);

	// race_date_data //
	race_date_data_json = fileManager->ReadJson(global::path::std_UmaData + "\\race_date_data.json");

	m_EventDataMap.emplace(GameServerType::JP, event_data_jp_json);
	m_EventDataMap.emplace(GameServerType::TW, event_data_tw_json);
	m_EventNameDataMap.emplace(GameServerType::JP, event_name_data_jp_json);
	m_EventNameDataMap.emplace(GameServerType::TW, event_name_data_tw_json);
}

bool DataManager::TryFindScheduledRace(std::string scanned_race_date)
{
	if (scanned_race_date.empty()) return false;
	if (loaded_race_schedule_json.empty()) return false;

	for (const auto& race_obj : loaded_race_schedule_json)
	{
		std::string race_date_grade = race_obj["race_date_grade"];
		std::string race_date_day = race_obj["race_date_day"];

		std::string race_date = race_date_grade + race_date_day;
		
		if (util::GetSimilarity(race_date, scanned_race_date) > 80) return true;
	}

	return false;
}

bool DataManager::TryFindCurrentDate(std::string scanned_race_date)
{
	if (scanned_race_date.empty()) return false;

	std::string dateType;

	switch (Config::GetInstance()->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		dateType = "jp";
		break;
	case static_cast<int>(GameServerType::TW):
		dateType = "tw";
		break;
	}
	
	for (const auto& race_date : race_date_data_json[dateType])
	{
		if (race_date == scanned_race_date)
		{
			m_current_date = race_date;
			return true;
		}
	}

	return false;
}

bool DataManager::SetCurrentCharacterInfoDict(std::string event_owner)
{
	if (event_owner.empty()) return false;

	json& event_data_json = m_EventDataMap[static_cast<GameServerType>(Config::GetInstance()->GameServer)];

	for (json::iterator it = event_data_json["character"].begin(); it != event_data_json["character"].end(); ++it)
	{
		std::string rare = it.key();

		for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
		{
			std::string json_event_owner = it2.key();
			if (json_event_owner == event_owner)
			{
				m_CurrentCharacterInfoDict["rare"] = rare;
				m_CurrentCharacterInfoDict["event_owner"] = json_event_owner;

				// config
				Config::GetInstance()->PreviousCurrentCharacterName = json_event_owner;
				Config::GetInstance()->WriteToJson();

				return true;
			}
		}
	}

	return false;
}

bool DataManager::TryGetCurrentCharacterByList(std::deque<std::string> scanned_text_list)
{
	bool foundChar = false;

	json& event_data_json = m_EventDataMap[static_cast<GameServerType>(Config::GetInstance()->GameServer)];

	// event_owner		
	std::deque<UmaGetCharData> similarCharList = {};

	for (json::iterator it = event_data_json["character"].begin(); it != event_data_json["character"].end(); ++it) // it.value() == characterRare
	{

		for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
		{
			// it2.key() == event_owner;

			std::string rare = it.key();
			std::string event_owner = it2.key();

			for (const auto& scanned_text : scanned_text_list)
			{
				const float similarity = util::GetSimilarity(scanned_text, event_owner);
				
				if (similarity < m_SIMILAR_METRIC) continue;

				std::cout << "scanned_text: " << scanned_text << ", event_owner: " << event_owner << ", similarity: " << similarity << '\n';


				UmaGetCharData umaGetCharData;
				umaGetCharData.event_owner = event_owner;
				umaGetCharData.rare = rare;
				umaGetCharData.similarity = similarity;

				// 以防萬一，加上互斥鎖保護共享資源
				std::unique_lock<std::mutex> lock(dataMutex);
				similarCharList.push_back(umaGetCharData);
				lock.unlock();

				std::cout << "FOUND CHARACTER: " << event_owner << '\n';
			}
		}
	}



	if (similarCharList.empty()) return false;

	// 使用 std::max_element 找到最大的 similarity
	auto maxElement = std::max_element(similarCharList.begin(), similarCharList.end(),
		[](const UmaGetCharData& data1, const UmaGetCharData& data2)
		{
			return data1.similarity < data2.similarity;
		}
	);

	if (maxElement != similarCharList.end())
	{
		m_CurrentCharacterInfoDict["rare"] = maxElement->rare;
		m_CurrentCharacterInfoDict["event_owner"] = maxElement->event_owner;
		m_CurrentCharacterInfoLocked = true;
		foundChar = true;
		WebViewManager::Instance->ChangeCharacterName(util::stdStr2system(maxElement->event_owner));

		// config
		Config::GetInstance()->PreviousCurrentCharacterName = maxElement->event_owner;
		Config::GetInstance()->WriteToJson();
	}


	return foundChar;
}

UmaEventNameData DataManager::GetMaxSimilarityUmaEventNameDataByList(std::deque<std::string> scanned_text_list)
{
	std::deque<UmaEventNameData> similarEventNameList = {};

	json& event_data_name_json = m_EventNameDataMap[static_cast<GameServerType>(Config::GetInstance()->GameServer)];

	
	for (json::iterator it_event_type = event_data_name_json.begin(); it_event_type != event_data_name_json.end(); ++it_event_type)
	{
		for (const auto& event_name : it_event_type.value())
		{
			for (const std::string& scanned_text : scanned_text_list)
			{
				const double similarity = util::GetSimilarity(scanned_text, event_name);

				if (similarity > m_SIMILAR_METRIC)
				{
					UmaEventNameData simEventData;
					simEventData.event_type = it_event_type.key();
					simEventData.event_name = event_name;
					simEventData.matched_scanned_text = scanned_text;
					simEventData.similarity = similarity;

					// Add the simEventData object to the vector directly
					similarEventNameList.push_back(std::move(simEventData));
				}
			}
		}
	}

	if (similarEventNameList.empty()) return UmaEventNameData();

	// 找到最大的 similarity
	return m_FindMaxSimilarityData(similarEventNameList);
}

std::variant<UmaEventData, ScenarioEventData> DataManager::GetEventDataByUmaEventNameData(UmaEventNameData umaEventNameData)
{
	json& event_data_json = m_EventDataMap[static_cast<GameServerType>(Config::GetInstance()->GameServer)];

	if (umaEventNameData.event_type == "character")
	{
		std::cout << "umaEventNameData.event_type == character" << '\n';

		UmaEventData umaEventData;
		umaEventData.event_owner = m_CurrentCharacterInfoDict["event_owner"];
		umaEventData.umaEvent.event_name = umaEventNameData.event_name;

		for (const auto& choice_obj : event_data_json["character"][m_CurrentCharacterInfoDict["rare"]][m_CurrentCharacterInfoDict["event_owner"]][umaEventNameData.event_name])
		{
			UmaChoice umaChoice;

			umaChoice.choice_name = choice_obj["choice_name"].get<std::string>();
			umaChoice.choice_effect = choice_obj["choice_effect"].get<std::string>();

			umaEventData.umaEvent.choice_list.push_back(std::move(umaChoice));
		}
		return umaEventData;
	}
	else if (umaEventNameData.event_type == "sapoka")
	{
		std::cout << "umaEventNameData.event_type == sapoka" << '\n';

		std::deque<UmaEventData> foundEventDataList;

		for (json::iterator it_rare = event_data_json[umaEventNameData.event_type].begin(); it_rare != event_data_json[umaEventNameData.event_type].end(); ++it_rare)
		{
			for (json::iterator it_event_owner = it_rare.value().begin(); it_event_owner != it_rare.value().end(); ++it_event_owner)
			{
				for (json::iterator it_event_name = it_event_owner.value().begin(); it_event_name != it_event_owner.value().end(); ++it_event_name)
				{
					if (it_event_name.key() == umaEventNameData.event_name)
					{
						UmaEventData umaEventData;
						umaEventData.umaEvent.event_name = umaEventNameData.event_name;
						umaEventData.rare = it_rare.key();
						umaEventData.event_owner = it_event_owner.key();

						for (const auto& choice_obj : it_event_name.value())
						{
							UmaChoice umaChoice;
							umaChoice.choice_name = choice_obj["choice_name"].get<std::string>();
							umaChoice.choice_effect = choice_obj["choice_effect"].get<std::string>();

							umaEventData.umaEvent.choice_list.push_back(umaChoice);
						}
						
						foundEventDataList.push_back(std::move(umaEventData));
					}
				}
			}
		}

		if (foundEventDataList.empty())
		{
			std::cout << "foundEventDataList.empty()" << '\n';
			return UmaEventData{};
		}


		// 使用 std::max_element 找到 rare 最大的 UmaEventData
		auto maxElement = std::max_element(foundEventDataList.begin(), foundEventDataList.end(),
			[](const UmaEventData& sim_data1, const UmaEventData& sim_data2)
			{
				return sim_data1.rare.size() < sim_data2.rare.size();
			}
		);

		return *maxElement;
	}
	else if (umaEventNameData.event_type == "scenario")
	{
		std::cout << "umaEventNameData.event_type == scenario" << '\n';

		ScenarioEventData scenarioEventData;
		scenarioEventData.event_name = umaEventNameData.event_name;
		
		for (json::iterator it_scenario_type = event_data_json[umaEventNameData.event_type].begin(); it_scenario_type != event_data_json[umaEventNameData.event_type].end(); ++it_scenario_type)
		{
			for (json::iterator it_event_name = it_scenario_type.value().begin(); it_event_name != it_scenario_type.value().end(); ++it_event_name)
			{
				if (it_event_name.key() == umaEventNameData.event_name)
				{
					for (const auto& choice_obj : it_event_name.value())
					{
						UmaChoice umaChoice;
						umaChoice.choice_name = choice_obj["choice_name"].get<std::string>();
						umaChoice.choice_effect = choice_obj["choice_effect"].get<std::string>();

						scenarioEventData.choice_list.push_back(umaChoice);
					}
				}
			}
		}

		return scenarioEventData;
	}

	return {};
}


UmaEventNameData DataManager::m_FindMaxSimilarityData(const std::deque<UmaEventNameData>& dataList) const
{
	return *std::max_element(dataList.begin(), dataList.end(),
							 [](const UmaEventNameData& data1, const UmaEventNameData& data2)
							 {
								 return data1.similarity < data2.similarity;
							 }
	);
}