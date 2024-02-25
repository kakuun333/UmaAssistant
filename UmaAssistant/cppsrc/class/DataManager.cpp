#include "DataManager.h"

#using "CSharpRuntime/UmaCSharpLibrary.dll"

DataManager* DataManager::_instance = nullptr;
bool DataManager::_currentCharacterInfoLocked = false;
std::map<std::string, std::string> DataManager::_currentCharacterInfoDict =
{
	// route
	{ "rare", "" },

	// characterName
	{ "event_owner", "" },
};

bool DataManager::TryFindScheduledRace(std::string scanned_race_date)
{
	if (race_schedule_json.empty()) return false;

	for (const auto& race_obj : race_schedule_json)
	{
		std::string race_date_grade = race_obj["race_date_grade"];
		std::string race_date_day = race_obj["race_date_day"];

		std::string race_date = race_date_grade + race_date_day;
		
		if (util::GetSimilarity(race_date, scanned_race_date) > 80) return true;
	}

	return false;
}

bool DataManager::SetCurrentCharacterInfoDict(std::string event_owner)
{
	if (event_owner.empty()) return false;

	json event_data_json;

	switch (Config::GetInstance()->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		event_data_json = event_data_jp_json;
		break;
	case static_cast<int>(GameServerType::TW):
		event_data_json = event_data_tw_json;
		break;
	}

	for (json::iterator it = event_data_json["character"].begin(); it != event_data_json["character"].end(); ++it)
	{
		std::string rare = it.key();

		for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
		{
			std::string json_event_owner = it2.key();
			if (json_event_owner == event_owner)
			{
				_currentCharacterInfoDict["rare"] = rare;
				_currentCharacterInfoDict["event_owner"] = json_event_owner;

				// config
				Config::GetInstance()->PreviousCurrentCharacterName = json_event_owner;
				Config::GetInstance()->WriteToJson();

				return true;
			}
		}
	}

	return false;
}

void DataManager::InitEventDataJson()
{
	FileManager* fileManager = FileManager::GetInstance();

	// event_data
	event_data_jp_json = fileManager->ReadJson(global::path::std_event_data_jp_json);
	event_name_data_jp_json = fileManager->ReadJson(global::path::std_UmaData + "\\event_name_data_jp.json");

	event_data_tw_json = fileManager->ReadJson(global::path::std_event_data_tw_json);
	event_name_data_tw_json = fileManager->ReadJson(global::path::std_UmaData + "\\event_name_data_tw.json");

	// jp server translation data //
	event_data_jp_trans_tw_json = fileManager->ReadJson(global::path::std_event_data_jp_trans_tw_json);

}

bool DataManager::TryGetCurrentCharacterByList(std::deque<std::string> scanned_text_list)
{
	bool foundChar = false;
	json event_data_json;

	switch (Config::GetInstance()->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		event_data_json = event_data_jp_json;
		break;
	case static_cast<int>(GameServerType::TW):
		event_data_json = event_data_tw_json;
		break;
	}

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
				float similarity = util::GetCharacterNameSimilarity(scanned_text, event_owner);

				/*
				為什麼 similarity == 100 ？？？？？？......

				scanned_text: IButterflyStingl, event_owner:アドマイヤベガ（Starry Nocturne）, similarity:-1
				scanned_text: IButterflyStingl, event_owner:アドマイヤベガ（Starry Nocturne）, similarity:-1
				scanned_text: IButterflyStingl, event_owner:アドマイヤベガ（Starry Nocturne）, similarity:-1
				scanned_text: ButterflySting, event_owner:アドマイヤベガ（Starry Nocturne）, similarity:100
				*/

				
				if (similarity < util::SIMILAR_METRIC) continue;

				std::cout << "scanned_text: " << scanned_text << ", event_owner: " << event_owner << ", similarity: " << similarity << std::endl;


				UmaGetCharData umaGetCharData;
				umaGetCharData.event_owner = event_owner;
				umaGetCharData.rare = rare;
				umaGetCharData.similarity = similarity;

				// 以防萬一，加上互斥鎖保護共享資源
				std::unique_lock<std::mutex> lock(dataMutex);
				similarCharList.push_back(umaGetCharData);
				lock.unlock();

				std::cout << "FOUND CHARACTER: " << event_owner << std::endl;
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
		_currentCharacterInfoDict["rare"] = maxElement->rare;
		_currentCharacterInfoDict["event_owner"] = maxElement->event_owner;
		_currentCharacterInfoLocked = true;
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

	json event_data_name_json;

	switch (Config::GetInstance()->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		event_data_name_json = event_name_data_jp_json;
		break;
	case static_cast<int>(GameServerType::TW):
		event_data_name_json = event_name_data_tw_json;
		break;
	}

	
	for (json::iterator it_event_type = event_data_name_json.begin(); it_event_type != event_data_name_json.end(); ++it_event_type)
	{
		for (const auto& event_name : it_event_type.value())
		{
			for (std::string scanned_text : scanned_text_list)
			{
				float similarity = util::GetSimilarity(scanned_text, event_name);
				
				if (similarity >= util::SIMILAR_METRIC)
				{
					UmaEventNameData simEventData;

					simEventData.event_type = it_event_type.key();
					simEventData.event_name = event_name;
					simEventData.matched_scanned_text = scanned_text;
					simEventData.similarity = similarity;

					similarEventNameList.push_back(simEventData);
				}
			}
		}
	}

	if (similarEventNameList.empty()) return UmaEventNameData();

	// 使用 std::max_element 找到最大的 similarity
	auto maxElement = std::max_element(similarEventNameList.begin(), similarEventNameList.end(),
		[](const UmaEventNameData& sim_data1, const UmaEventNameData& sim_data2)
		{
			return sim_data1.similarity < sim_data2.similarity;
		}
	);

	return *maxElement;
}

std::variant<UmaEventData, ScenarioEventData> DataManager::GetEventDataByUmaEventNameData(UmaEventNameData umaEventNameData)
{
	json event_data_json;

	switch (Config::GetInstance()->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (Config::GetInstance()->JpServerLang)
		{
		case static_cast<int>(JpServerLangType::JP):
			event_data_json = event_data_jp_json;
			break;
		case static_cast<int>(JpServerLangType::TW):
			event_data_json = event_data_jp_trans_tw_json;
			break;
		}
		break;
	case static_cast<int>(GameServerType::TW):
		event_data_json = event_data_tw_json;
		break;
	}

	if (umaEventNameData.event_type == "character")
	{
		std::cout << "umaEventNameData.event_type == character" << std::endl;

		UmaEventData umaEventData;
		umaEventData.event_owner = _currentCharacterInfoDict["event_owner"];
		umaEventData.umaEvent.event_name = umaEventNameData.event_name;


		for (const auto& choice_obj : event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]][umaEventNameData.event_name])
		{
			UmaChoice umaChoice;

			umaChoice.choice_name = choice_obj["choice_name"].get<std::string>();
			umaChoice.choice_effect = choice_obj["choice_effect"].get<std::string>();

			umaEventData.umaEvent.choice_list.push_back(umaChoice);
		}
		return umaEventData;
	}
	else if (umaEventNameData.event_type == "sapoka")
	{
		std::cout << "umaEventNameData.event_type == sapoka" << std::endl;

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
						
						foundEventDataList.push_back(umaEventData);
					}
				}
			}
		}

		if (foundEventDataList.empty())
		{
			std::cout << "foundEventDataList.empty()" << std::endl;
			return UmaEventData{};
		}


		// 使用 std::max_element 找到 rare 最大的 UmaEventData
		auto maxElement = std::max_element(foundEventDataList.begin(), foundEventDataList.end(),
			[](const UmaEventData& event_data1, const UmaEventData& sim_data2)
			{
				return event_data1.rare.size() < sim_data2.rare.size();
			}
		);

		return *maxElement;
	}
	else if (umaEventNameData.event_type == "scenario")
	{
		std::cout << "umaEventNameData.event_type == scenario" << std::endl;

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

}