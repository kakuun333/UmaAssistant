#include "../stdafx.h"

#pragma region 靜態變數
DataManager* DataManager::_instance = nullptr;

bool DataManager::_currentCharacterInfoLocked = false;

nlohmann::json DataManager::event_data_jp_json;
nlohmann::json DataManager::event_data_tw_json;

nlohmann::json DataManager::event_data_jp_trans_tw_json;

nlohmann::json DataManager::scenario_event_data_jp_json;
nlohmann::json DataManager::scenario_event_data_tw_json;

std::map<std::string, std::string> DataManager::_currentCharacterInfoDict =
{
	// route
	{ "rare", "" },

	// characterName
	{ "event_owner", "" },
};
#pragma endregion 靜態變數

bool DataManager::SetCurrentCharacterInfoDict(std::string event_owner)
{
	if (event_owner.empty()) return false;

	json event_data_json;

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (global::config->JpServerLang)
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
				global::config->PreviousCurrentCharacterName = json_event_owner;
				global::config->WriteToJson();

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
	event_data_tw_json = fileManager->ReadJson(global::path::std_event_data_tw_json);

	// jp server translation data
	event_data_jp_trans_tw_json = fileManager->ReadJson(global::path::std_event_data_jp_trans_tw_json);

	// scenario_event_data
	scenario_event_data_jp_json = fileManager->ReadJson(global::path::std_scenario_event_data_jp_json);
	scenario_event_data_tw_json = fileManager->ReadJson(global::path::std_scenario_event_data_tw_json);
}

bool DataManager::TryGetCurrentCharacterName(std::string scanned_text)
{
	bool foundChar = false;
	json event_data_json;

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (global::config->JpServerLang)
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

	// event_owner		
	std::vector<UmaGetCharData> similarCharList = {};

	WebManager* webManager = WebManager::GetInstance();

	std::unique_ptr<std::thread> oneStarThread;
	std::unique_ptr<std::thread> twoStarThread;
	std::unique_ptr<std::thread> threeStarThread;

	for (json::iterator it = event_data_json["character"].begin(); it != event_data_json["character"].end(); ++it) // it.value() == characterRare
	{
		if (it.key() == "1_star")
		{
			oneStarThread = std::make_unique<std::thread>([=, &similarCharList]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						std::string rare = it.key();
						std::string event_owner = it2.key();

						float similarity = utility::GetCharacterNameSimilarity(scanned_text, event_owner);

						switch (global::config->GameServer)
						{
						case static_cast<int>(GameServerType::JP):
							if (utility::JP_CHAR_SIMILAR_METRIC > similarity) continue;
							break;
						case static_cast<int>(GameServerType::TW):
							if (utility::SIMILAR_METRIC > similarity) continue;
							break;
						}
						
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
				});
		}
		else if (it.key() == "2_star")
		{
			twoStarThread = std::make_unique<std::thread>([=, &similarCharList]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						std::string rare = it.key();
						std::string event_owner = it2.key();

						float similarity = utility::GetCharacterNameSimilarity(scanned_text, event_owner);

						switch (global::config->GameServer)
						{
						case static_cast<int>(GameServerType::JP):
							if (utility::JP_CHAR_SIMILAR_METRIC > similarity) continue;
							break;
						case static_cast<int>(GameServerType::TW):
							if (utility::SIMILAR_METRIC > similarity) continue;
							break;
						}

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
				});
		}
		else if (it.key() == "3_star")
		{
			threeStarThread = std::make_unique<std::thread>([=, &similarCharList]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						std::string rare = it.key();
						std::string event_owner = it2.key();

						float similarity = utility::GetCharacterNameSimilarity(scanned_text, event_owner);

						switch (global::config->GameServer)
						{
						case static_cast<int>(GameServerType::JP):
							if (utility::JP_CHAR_SIMILAR_METRIC > similarity) continue;
							break;
						case static_cast<int>(GameServerType::TW):
							if (utility::SIMILAR_METRIC > similarity) continue;
							break;
						}

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
				});
		}
	}



	//_currentCharacterInfoDict["rare"] = it.key();
//_currentCharacterInfoDict["event_owner"] = event_owner;
//_currentCharacterInfoLocked = true;

//webManager->ChangeCharacterName(utility::stdStr2system(event_owner));



	oneStarThread->join();
	twoStarThread->join();
	threeStarThread->join();


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
		webManager->ChangeCharacterName(utility::stdStr2system(maxElement->event_owner));

		// config
		global::config->PreviousCurrentCharacterName = maxElement->event_owner;
		global::config->WriteToJson();
	}
	

	return foundChar;
}

ScenarioEventData DataManager::GetScenarioEventData(std::string scanned_text)
{
	if (scanned_text.empty()) return ScenarioEventData();

	json event_data_json;

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		event_data_json = scenario_event_data_jp_json;
		break;
	case static_cast<int>(GameServerType::TW):
		event_data_json = scenario_event_data_tw_json;
	}


	std::vector<ScenarioEventData> similarDataList = {};

	for (json::iterator it = event_data_json.begin(); it != event_data_json.end(); ++it)
	{
		std::string scenario_type = it.key();
		json scenario_type_v = it.value();
		for (json::iterator it2 = scenario_type_v.begin(); it2 != scenario_type_v.end(); ++it2)
		{
			std::string event_title = it2.key();

			float similarity = utility::GetSimilarity(scanned_text, event_title);

			if (similarity >= utility::SIMILAR_METRIC)
			{
				ScenarioEventData scenarioEventData;

				scenarioEventData.event_title = event_title;

				scenarioEventData.similarity = similarity;
				

				for (const auto& event : it2.value())
				{
					ScenarioChoice scenarioChoice;

					for (const auto& choice : event.items())
					{
						if (choice.key() == "choice_title")
						{
							scenarioChoice.choice_title = choice.value().get<std::string>();
							//std::cout << "scenarioEvent.choice_title: " << scenarioChoice.choice_title << std::endl;
						}
						else
						{
							scenarioChoice.choice_effect = choice.value().get<std::string>();
						}
						//choice["choice_effect"] = scenarioEvent.choice_effect;

					}
					scenarioEventData.event_list.push_back(scenarioChoice);
				}

				similarDataList.push_back(scenarioEventData);
			}
		}
	}

	if (similarDataList.empty()) return ScenarioEventData();

	// 使用 std::max_element 找到最大的 similarity
	auto maxElement = std::max_element(similarDataList.begin(), similarDataList.end(),
		[](const ScenarioEventData& data1, const ScenarioEventData& data2)
		{
			return data1.similarity < data2.similarity;
		}
	);

	ScenarioEventData scenarioEventData = *maxElement;


	return scenarioEventData;
}

ScenarioEventData DataManager::GetScenarioEventDataByList(std::deque<std::string> scanned_text_list)
{
	if (scanned_text_list.empty()) return ScenarioEventData();

	json event_data_json;

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		event_data_json = scenario_event_data_jp_json;
		break;
	case static_cast<int>(GameServerType::TW):
		event_data_json = scenario_event_data_tw_json;
	}


	std::vector<ScenarioEventData> similarDataList = {};

	for (json::iterator it = event_data_json.begin(); it != event_data_json.end(); ++it)
	{
		std::string scenario_type = it.key();
		json scenario_type_v = it.value();
		for (json::iterator it2 = scenario_type_v.begin(); it2 != scenario_type_v.end(); ++it2)
		{
			std::string event_title = it2.key();


			for (const auto& scanned_text : scanned_text_list)
			{
				float similarity = utility::GetSimilarity(scanned_text, event_title);

				if (similarity >= utility::SIMILAR_METRIC)
				{
					ScenarioEventData scenarioEventData;
					scenarioEventData.event_title = event_title;
					scenarioEventData.similarity = similarity;
					scenarioEventData.matched_scanned_text = scanned_text;

					for (const auto& event : it2.value())
					{
						ScenarioChoice scenarioChoice;

						for (const auto& choice : event.items())
						{
							if (choice.key() == "choice_title")
							{
								scenarioChoice.choice_title = choice.value().get<std::string>();
								//std::cout << "scenarioEvent.choice_title: " << scenarioChoice.choice_title << std::endl;
							}
							else
							{
								scenarioChoice.choice_effect = choice.value().get<std::string>();
							}
							//choice["choice_effect"] = scenarioEvent.choice_effect;

						}
						scenarioEventData.event_list.push_back(scenarioChoice);
					}

					similarDataList.push_back(scenarioEventData);
				}
			}
		}
	}

	if (similarDataList.empty()) return ScenarioEventData();

	// 使用 std::max_element 找到最大的 similarity
	auto maxElement = std::max_element(similarDataList.begin(), similarDataList.end(),
		[](const ScenarioEventData& data1, const ScenarioEventData& data2)
		{
			return data1.similarity < data2.similarity;
		}
	);

	ScenarioEventData scenarioEventData = *maxElement;


	return scenarioEventData;
}

UmaEventData DataManager::GetCurrentCharacterUmaEventData(std::string scanned_text)
{
	if (scanned_text.empty()) return UmaEventData();

	json event_data_json;

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (global::config->JpServerLang)
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


	UmaEventData umaEventData;


	umaEventData.event_owner = _currentCharacterInfoDict["event_owner"];
	//umaEventData.sys_event_owner = utility::stdStr2system(_currentCharacterInfoDict["event_owner"]);

	std::map<std::string, float> similarEventTitleList = {};

	for (json::iterator it = event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]].begin();
						it != event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]].end(); ++it)
	{
		for (const auto& event : it.value())
		{
			for (const auto& choice : event.items())
			{
				//std::cout << "Event Title: " << choice.key() << std::endl;

				float similarity = utility::GetSimilarity(scanned_text, choice.key());


				if (similarity >= utility::SIMILAR_METRIC)
				{

					similarEventTitleList.emplace(choice.key(), similarity);
				}
			}
		}
	}

	auto maxElement = std::max_element(
		similarEventTitleList.begin(), similarEventTitleList.end(),
		[](const auto& p1, const auto& p2)
		{
			//std::cout << "first: " << p1.first << "second: " << p1.second << std::endl;
			return p1.second < p2.second;
		}
	);



	for (json::iterator it = event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]].begin();
						it != event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]].end(); ++it)
	{
		for (const auto& event : it.value())
		{
			for (const auto& choice : event.items())
			{
				// choice.key() == event_title
				if (choice.key() != maxElement->first) continue;

				float similarity = maxElement->second;

				umaEventData.similarity = similarity;

				umaEventData.event_owner = _currentCharacterInfoDict["event_owner"];
				//umaEventData.sys_event_owner = utility::stdStr2system(umaEventData.event_owner);

				UmaEvent umaEvent;
				umaEvent.event_title = choice.key();
				//umaEvent.sys_event_title = utility::stdStr2system(umaEvent.event_title);

				for (const auto& choice_info : choice.value())
				{
					// choice_info["choice_title"]
					// choice_info["choice_effect"]

					UmaChoice umaChoice;
					umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
					//umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);

					umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
					//umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);

					umaEvent.choice_list.push_back(umaChoice);
				}

				umaEventData.umaEvent = umaEvent;
			}
		}
	}

	return umaEventData;
}

UmaEventData DataManager::GetCurrentCharacterUmaEventDataByList(std::deque<std::string> scanned_text_list)
{
	if (scanned_text_list.empty()) return UmaEventData();

	json event_data_json;

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (global::config->JpServerLang)
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


	UmaEventData umaEventData;
	umaEventData.event_owner = _currentCharacterInfoDict["event_owner"];


	std::vector<SimilarUmaEventData> similarDataList = {};


	for (json::iterator it = event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]].begin();
		it != event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]].end(); ++it)
	{
		for (const auto& event : it.value())
		{
			for (const auto& choice : event.items())
			{
				//std::cout << "Event Title: " << choice.key() << std::endl;

				std::string event_title = choice.key();

				for (const auto& scanned_text : scanned_text_list)
				{
					float similarity = utility::GetSimilarity(scanned_text, event_title);

					if (similarity >= utility::SIMILAR_METRIC)
					{
						SimilarUmaEventData sim_data;
						sim_data.similarity = similarity;
						sim_data.event_title = event_title;
						sim_data.matched_scanned_text = scanned_text;

						similarDataList.push_back(sim_data);
					}
				}
			}
		}
	}

	if (similarDataList.empty()) return umaEventData;

	// 使用 std::max_element 找到最大的 similarity
	auto maxElement = std::max_element(similarDataList.begin(), similarDataList.end(),
		[](const SimilarUmaEventData& sim_data1, const SimilarUmaEventData& sim_data2)
		{
			return sim_data1.similarity < sim_data2.similarity;
		}
	);


	for (json::iterator it = event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]].begin();
		it != event_data_json["character"][_currentCharacterInfoDict["rare"]][_currentCharacterInfoDict["event_owner"]].end(); ++it)
	{
		for (const auto& event : it.value())
		{
			for (const auto& choice : event.items())
			{
				/*
				choice.key() == event_title
				*/

				std::string event_title = choice.key();

				if (event_title != maxElement->event_title) continue;

				float similarity = maxElement->similarity;

				umaEventData.similarity = similarity;
				umaEventData.event_owner = _currentCharacterInfoDict["event_owner"];
				umaEventData.matched_scanned_text = maxElement->matched_scanned_text;

				UmaEvent umaEvent;
				umaEvent.event_title = event_title;

				for (const auto& choice_info : choice.value())
				{
					/*
					choice_info["choice_title"]
					choice_info["choice_effect"]
					*/
					
					UmaChoice umaChoice;
					umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
					umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();

					umaEvent.choice_list.push_back(umaChoice);
				}

				umaEventData.umaEvent = umaEvent;
			}
		}
	}

	return umaEventData;
}


UmaEventData DataManager::GetSapokaUmaEventData(std::string scanned_text)
{
	if (scanned_text.empty()) return UmaEventData();

	json event_data_json;

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (global::config->JpServerLang)
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


	UmaEventData umaEventData;

	std::vector<SimilarUmaEventData> similarDataList = {};

	std::unique_ptr<std::thread> rStarThread;
	std::unique_ptr<std::thread> srStarThread;
	std::unique_ptr<std::thread> ssrStarThread;


	for (json::iterator it = event_data_json["support_card"].begin(); it != event_data_json["support_card"].end(); ++it)
	{
		// it == rare;
		if (it.key() == "R")
		{
			rStarThread = std::make_unique<std::thread>([=, &similarDataList]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						for (const auto& event : it2.value()["event"])
						{
							for (const auto& choice : event.items())
							{
								//std::cout << "Event Title: " << choice.key() << std::endl;
								float similarity = utility::GetSimilarity(scanned_text, choice.key().c_str());

								if (similarity >= utility::SIMILAR_METRIC)
								{
									SimilarUmaEventData eventRoute;

									eventRoute.rare = it.key();
									eventRoute.event_owner = it2.key();
									eventRoute.event_title = choice.key();
									eventRoute.similarity = similarity;

									std::unique_lock<std::mutex> lock(dataMutex);
									similarDataList.push_back(eventRoute);
									lock.unlock();
								}
							}
						}
					}
				});
		}
		else if (it.key() == "SR")
		{
			srStarThread = std::make_unique<std::thread>([=, &similarDataList]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						for (const auto& event : it2.value()["event"])
						{
							for (const auto& choice : event.items())
							{
								//std::cout << "Event Title: " << choice.key() << std::endl;
								float similarity = utility::GetSimilarity(scanned_text, choice.key().c_str());

								if (similarity >= utility::SIMILAR_METRIC)
								{
									SimilarUmaEventData eventRoute;

									eventRoute.rare = it.key();
									eventRoute.event_owner = it2.key();
									eventRoute.event_title = choice.key();
									eventRoute.similarity = similarity;

									std::unique_lock<std::mutex> lock(dataMutex);
									similarDataList.push_back(eventRoute);
									lock.unlock();
								}
							}
						}
					}
				});
		}
		else if (it.key() == "SSR")
		{
			ssrStarThread = std::make_unique<std::thread>([=, &similarDataList]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						for (const auto& event : it2.value()["event"])
						{
							for (const auto& choice : event.items())
							{
								//std::cout << "Event Title: " << choice.key() << std::endl;
								float similarity = utility::GetSimilarity(scanned_text, choice.key().c_str());

								if (similarity >= utility::SIMILAR_METRIC)
								{
									SimilarUmaEventData eventRoute;

									eventRoute.rare = it.key();
									eventRoute.event_owner = it2.key();
									eventRoute.event_title = choice.key();
									eventRoute.similarity = similarity;

									std::unique_lock<std::mutex> lock(dataMutex);
									similarDataList.push_back(eventRoute);
									lock.unlock();
								}
							}
						}
					}
				});
		}
	}

	rStarThread->join();
	srStarThread->join();
	ssrStarThread->join();

	if (similarDataList.empty()) return umaEventData;

	// 使用 std::max_element 找到最大的 similarity
	auto maxElement = std::max_element(similarDataList.begin(), similarDataList.end(),
		[](const SimilarUmaEventData& route1, const SimilarUmaEventData& route2)
		{
			/*
			用 rare.size() 來判斷支援卡的稀有度
			"SSR" 的 byte 一定比 "SR" 還要多
			"SR" 的 byte 一定比 "R" 還要多
			*/

			//std::cout << "route1: " << route1.rare << " size: " << route1.rare.size() << " similarity: " << route1.similarity << std::endl;
			//std::cout << "route2: " << route2.rare << " size: " << route2.rare.size() << " similarity: " << route2.similarity << std::endl;

			return (route1.similarity < route2.similarity || (route1.similarity == route2.similarity && route1.rare.size() < route2.rare.size()));
		}
	);

	auto& event_array = event_data_json["support_card"][maxElement->rare][maxElement->event_owner]["event"];
	for (const auto& event : event_array)
	{
		std::string event_title = event.begin().key();
		if (event_title == maxElement->event_title)
		{
			UmaEvent umaEvent;

			umaEventData.similarity = maxElement->similarity;

			umaEventData.event_owner = maxElement->event_owner;
			//umaEventData.sys_event_owner = utility::stdStr2system(umaEventData.event_owner);

			umaEvent.event_title = maxElement->event_title;
			//umaEvent.sys_event_title = utility::stdStr2system(umaEvent.event_title);

			for (const auto& choice_info : event.begin().value())
			{
				UmaChoice umaChoice;

				umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
				//umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);

				umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
				//umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);

				umaEvent.choice_list.push_back(umaChoice);
			}

			umaEventData.umaEvent = umaEvent;
			break;
		}
	}

	return umaEventData;
}

UmaEventData DataManager::GetSapokaUmaEventDataByList(std::deque<std::string> scanned_text_list)
{
	if (scanned_text_list.empty()) return UmaEventData();

	json event_data_json;

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		switch (global::config->JpServerLang)
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


	UmaEventData umaEventData;

	std::vector<SimilarUmaEventData> similarDataList = {};


	for (json::iterator it = event_data_json["support_card"].begin(); it != event_data_json["support_card"].end(); ++it)
	{
		// it == rare;

		for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
		{
			// it2.key() == event_owner;

			for (const auto& event : it2.value()["event"])
			{
				for (const auto& choice : event.items())
				{
					//std::cout << "Event Title: " << choice.key() << std::endl;

					for (const auto& scanned_text : scanned_text_list)
					{
						float similarity = utility::GetSimilarity(scanned_text, choice.key().c_str());

						if (similarity >= utility::SIMILAR_METRIC)
						{
							SimilarUmaEventData sim_data;

							sim_data.rare = it.key();
							sim_data.event_owner = it2.key();
							sim_data.event_title = choice.key();
							sim_data.similarity = similarity;
							sim_data.matched_scanned_text = scanned_text;

							std::unique_lock<std::mutex> lock(dataMutex);
							similarDataList.push_back(sim_data);
						}
					}
				}
			}
		}

	}


	if (similarDataList.empty()) return umaEventData;

	// 使用 std::max_element 找到最大的 similarity
	auto maxElement = std::max_element(similarDataList.begin(), similarDataList.end(),
		[](const SimilarUmaEventData& sim_data1, const SimilarUmaEventData& sim_data2)
		{
			/*
			用 rare.size() 來判斷支援卡的稀有度
			"SSR" 的 byte 一定比 "SR" 還要多
			"SR" 的 byte 一定比 "R" 還要多
			*/

			return (sim_data1.similarity < sim_data2.similarity || (sim_data1.similarity == sim_data2.similarity && sim_data1.rare.size() < sim_data2.rare.size()));
		}
	);

	auto& event_array = event_data_json["support_card"][maxElement->rare][maxElement->event_owner]["event"];
	for (const auto& event : event_array)
	{
		std::string event_title = event.begin().key();
		if (event_title == maxElement->event_title)
		{
			UmaEvent umaEvent;

			umaEventData.similarity = maxElement->similarity;

			umaEventData.event_owner = maxElement->event_owner;

			umaEventData.matched_scanned_text = maxElement->matched_scanned_text;
			//umaEventData.sys_event_owner = utility::stdStr2system(umaEventData.event_owner);

			umaEvent.event_title = maxElement->event_title;
			//umaEvent.sys_event_title = utility::stdStr2system(umaEvent.event_title);

			for (const auto& choice_info : event.begin().value())
			{
				UmaChoice umaChoice;

				umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
				//umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);

				umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
				//umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);

				umaEvent.choice_list.push_back(umaChoice);
			}

			umaEventData.umaEvent = umaEvent;
			break;
		}
	}

	return umaEventData;
}