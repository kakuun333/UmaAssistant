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

						if (utility::SIMILAR_METRIC > similarity) continue;
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

						if (utility::SIMILAR_METRIC > similarity) continue;
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

						if (utility::SIMILAR_METRIC > similarity) continue;
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


	ScenarioEventData scenarioEventData;

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
							std::cout << "scenarioEvent.choice_title: " << scenarioChoice.choice_title << std::endl;
						}
						else
						{
							scenarioChoice.choice_effect = choice.value().get<std::string>();
						}
						//choice["choice_effect"] = scenarioEvent.choice_effect;
					}
					scenarioEventData.event_list.push_back(scenarioChoice);
				}
			}
		}
	}


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

				umaEventData.event_list.push_back(umaEvent);
			}
		}
	}

	return umaEventData;
}


UmaEventData DataManager::GetSupportCardUmaEventData(std::string scanned_text)
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

	std::vector<UmaEventRoute> similarDataList = {};

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
									UmaEventRoute eventRoute;

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
									UmaEventRoute eventRoute;

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
									UmaEventRoute eventRoute;

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
		[](const UmaEventRoute& route1, const UmaEventRoute& route2)
		{
			return route1.similarity < route2.similarity;
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

			umaEventData.event_list.push_back(umaEvent);
			break;
		}
	}

	//for (const auto& choice_info : event_data_json["support_card"][maxElement->rare][maxElement->event_owner]["event"][maxElement->event_title])
	//{
	//	std::cout << choice_info["choice_title"].get<std::string>() << std::endl;
	//}

	//for (json::iterator it = event_data_json["support_card"][maxElement->rare][maxElement->event_owner]["event"][maxElement->event_title].begin();
	//	it != event_data_json["support_card"][maxElement->rare][maxElement->event_owner]["event"][maxElement->event_title].end(); ++it)
	//{
	//	std::cout << it.key() << std::endl;

	//	//UmaChoice umaChoice;

	//	//umaEventData.similarity = maxElement->similarity;

	//	//umaEventData.event_owner = maxElement->event_owner;
	//	//umaEventData.sys_event_owner = utility::stdStr2system(umaEventData.event_owner);

	//	//umaEvent.event_title = maxElement->event_title;
	//	//umaEvent.sys_event_title = utility::stdStr2system(umaEvent.event_title);

	//	//for (const auto& choice_info : it.value())
	//	//{
	//	//	// choice_info["choice_title"]
	//	//	// choice_info["choice_effect"]

	//	//	
	//	//	umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
	//	//	umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);

	//	//	umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
	//	//	umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);

	//	//}

	//	//umaEvent.choice_list.push_back(umaChoice);
	//}

	


	return umaEventData;
}


//UmaEventData DataManager::GetSupportCardUmaEventData(std::string scanned_text)
//{
//	json event_data_json;
//
//	switch (global::config->GameServer)
//	{
//	case GameServerType::JP:
//		event_data_json = event_data_jp_json;
//		break;
//	case GameServerType::TW:
//		event_data_json = event_data_tw_json;
//	}
//
//
//	UmaEventData umaEventData;
//	float highestSimilarity = 0.0f;
//
//	std::thread* rStarThread = nullptr;
//	std::thread* srStarThread = nullptr;
//	std::thread* ssrStarThread = nullptr;
//
//
//
//	for (json::iterator it = event_data_json["support_card"].begin(); it != event_data_json["support_card"].end(); ++it)
//	{
//		// it == rare;
//		if (it.key() == "R")
//		{
//			rStarThread = new std::thread([=, &umaEventData, &highestSimilarity]()
//				{
//					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
//					{
//						// it2.key() == event_owner;
//
//						for (const auto& event : it2.value()["event"])
//						{
//							for (const auto& choice : event.items())
//							{
//								std::string event_title = choice.key();
//								float similarity = utility::GetSimilarity(scanned_text, event_title.c_str());
//
//								if (similarity < utility::SIMILAR_METRIC) continue;
//
//								highestSimilarity = std::max(similarity, highestSimilarity);
//
//								if (similarity < highestSimilarity) continue;
//
//								if (!umaEventData.event_list.empty())
//								{
//									for (auto _event : umaEventData.event_list)
//									{
//										_event.choice_list.clear();
//									}
//									umaEventData.event_list.clear();
//								}
//
//								umaEventData.similarity = similarity;
//								umaEventData.event_owner = it2.key();
//
//								UmaEvent umaEvent;
//								umaEvent.event_title = choice.key();
//
//								for (const auto& choice_info : choice.value())
//								{
//									UmaChoice umaChoice;
//									umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
//									umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
//
//									umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);
//									umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);
//
//									umaEvent.choice_list.push_back(umaChoice);
//								}
//
//								umaEventData.event_list.push_back(umaEvent);
//							}
//						}
//					}
//				});
//		}
//		else if (it.key() == "SR")
//		{
//			srStarThread = new std::thread([=, &umaEventData, &highestSimilarity]()
//				{
//					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
//					{
//						// it2.key() == event_owner;
//
//						for (const auto& event : it2.value()["event"])
//						{
//							for (const auto& choice : event.items())
//							{
//								std::string event_title = choice.key();
//								float similarity = utility::GetSimilarity(scanned_text, event_title.c_str());
//
//								if (similarity < utility::SIMILAR_METRIC) continue;
//
//								highestSimilarity = std::max(similarity, highestSimilarity);
//
//								if (similarity < highestSimilarity) continue;
//
//								if (!umaEventData.event_list.empty())
//								{
//									for (auto _event : umaEventData.event_list)
//									{
//										_event.choice_list.clear();
//									}
//									umaEventData.event_list.clear();
//								}
//
//								umaEventData.similarity = similarity;
//								umaEventData.event_owner = it2.key();
//
//								UmaEvent umaEvent;
//								umaEvent.event_title = choice.key();
//
//								for (const auto& choice_info : choice.value())
//								{
//									UmaChoice umaChoice;
//									umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
//									umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
//
//									umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);
//									umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);
//
//									umaEvent.choice_list.push_back(umaChoice);
//								}
//
//								umaEventData.event_list.push_back(umaEvent);
//							}
//						}
//					}
//				});
//		}
//		else if (it.key() == "SSR")
//		{
//			ssrStarThread = new std::thread([=, &umaEventData, &highestSimilarity]()
//				{
//					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
//					{
//						// it2.key() == event_owner;
//
//						for (const auto& event : it2.value()["event"])
//						{
//							for (const auto& choice : event.items())
//							{
//								std::string event_title = choice.key();
//								float similarity = utility::GetSimilarity(scanned_text, event_title.c_str());
//
//								if (similarity < utility::SIMILAR_METRIC) continue;
//
//								highestSimilarity = std::max(similarity, highestSimilarity);
//
//								if (similarity < highestSimilarity) continue;
//
//								if (!umaEventData.event_list.empty())
//								{
//									for (auto _event : umaEventData.event_list)
//									{
//										_event.choice_list.clear();
//									}
//									umaEventData.event_list.clear();
//								}
//
//								umaEventData.similarity = similarity;
//								umaEventData.event_owner = it2.key();
//
//								UmaEvent umaEvent;
//								umaEvent.event_title = choice.key();
//
//								for (const auto& choice_info : choice.value())
//								{
//									UmaChoice umaChoice;
//									umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
//									umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
//
//									umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);
//									umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);
//
//									umaEvent.choice_list.push_back(umaChoice);
//								}
//
//								umaEventData.event_list.push_back(umaEvent);
//							}
//						}
//					}
//				});
//		}
//	}
//
//
//	rStarThread->join();
//	srStarThread->join();
//	ssrStarThread->join();
//
//
//	delete rStarThread;
//	delete srStarThread;
//	delete ssrStarThread;
//
//	return umaEventData;
//}

//UmaEventData DataManager::GetUmaEventDataFromJson(std::string scanned_text)
//{
//#pragma region 變數
//	bool foundFirstEventTitle = false;
//	UmaEventData umaEventData;
//
//	FileManager* fileManager = FileManager::GetInstance();
//	json jsonData = fileManager->ReadJson(global::path::c_event_data_jp_json);
//	std::map<std::string, float> similarEventTitleList = {};
//#pragma endregion
//
//
//	//
//	// 獲取每個相似的 event_title
//	//
//
//	std::thread* characterThread = nullptr;
//	std::thread* oneStarThread = nullptr;
//	std::thread* twoStarThread = nullptr;
//	std::thread* threeStarThread = nullptr;
//
//
//	std::thread* supportCardThread = nullptr;
//
//	for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it)
//	{
//		if (it.key() == "character")
//		{
//			characterThread = new std::thread([=, &oneStarThread, &twoStarThread, &threeStarThread]()
//				{
//					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) // it.value() == characterRare
//					{
//
//						if (it2.key() == "1_star")
//						{
//							oneStarThread = new std::thread([=]()
//								{
//									for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) // it2.value() == article_id_list
//									{
//										std::string event_owner = it3.value()["event_owner"].get<std::string>();
//
//										if (utility::SIMILAR_METRIC > utility::GetCharacterNameSimilarity(scanned_text, event_owner)) continue;
//
//
//										//json event_list = it3.value()["event_list"];
//										//for (json::iterator it4 = event_list.begin(); it4 != event_list.end(); ++it4)
//										//{
//										//	std::string event_title = it4.value()["event_title"].get<std::string>();
//
//										//	//std::cout << event_title << std::endl;
//										//}
//									}
//								});
//
//						}
//						else if (it2.key() == "2_star")
//						{
//							twoStarThread = new std::thread([=]()
//								{
//									for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) // it2.value() == article_id_list
//									{
//										std::string event_owner = it3.value()["event_owner"].get<std::string>();
//
//										//std::cout << utility::GetCharacterNameSimilarity(scanned_text, event_owner) << std::endl;
//										//json event_list = it3.value()["event_list"];
//										//for (json::iterator it4 = event_list.begin(); it4 != event_list.end(); ++it4)
//										//{
//										//	std::string event_title = it4.value()["event_title"].get<std::string>();
//
//										//	//std::cout << event_title << std::endl;
//										//}
//									}
//								});
//						}
//						else if (it2.key() == "3_star")
//						{
//							threeStarThread = new std::thread([=]()
//								{
//									for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) // it2.value() == article_id_list
//									{
//										std::string event_owner = it3.value()["event_owner"].get<std::string>();
//
//										//std::cout << utility::GetCharacterNameSimilarity(scanned_text, event_owner) << std::endl;
//										//json event_list = it3.value()["event_list"];
//										//for (json::iterator it4 = event_list.begin(); it4 != event_list.end(); ++it4)
//										//{
//										//	std::string event_title = it4.value()["event_title"].get<std::string>();
//
//										//	//std::cout << event_title << std::endl;
//										//}
//									}
//								});
//						}
//					}
//				});
//		}
//		else
//		{
//			supportCardThread = new std::thread([=]()
//				{
//					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {}
//					{
//						std::cout << "character" << std::endl;
//					}
//				});
//		}
//	}
//
//	characterThread->join();
//	oneStarThread->join();
//	twoStarThread->join();
//	threeStarThread->join();
//
//
//	supportCardThread->join();
//
//	for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it) // article_id_table
//	{
//
//		//json event_list = it.value()["event_list"];
//		//for (json::iterator it2 = event_list.begin(); it2 != event_list.end(); ++it2)
//		//{
//		//	//if (!utility::IsSimilar(scanned_text, it2.value()["event_title"].get<std::string>())) continue;
//
//		//	float similarity = utility::GetSimilarity(scanned_text, it2.value()["event_title"].get<std::string>());
//
//		//	if (similarity >= utility::SIMILAR_METRIC)
//		//	{
//		//		similarEventTitleList.emplace(it2.value()["event_title"].get<std::string>(), similarity);
//		//	}
//
//		//	//similarEventTitleList.push_back(it2.value()["event_title"].get<std::string>());
//		//}
//	}
//
//
//	//auto maxElement = std::max_element(
//	//	similarEventTitleList.begin(), similarEventTitleList.end(),
//	//	[](const auto& p1, const auto& p2)
//	//	{
//	//		std::cout << "first: " << p1.first << "second: " << p1.second << std::endl;
//	//		return p1.second < p2.second;
//	//	}
//	//);
//
//	////////// 遍歷 json 物件
//	//for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it) // article_id_table
//	//{
//	//	if (foundFirstEventTitle) break;
//
//
//	//	json event_list = it.value()["event_list"];
//	//	for (json::iterator it2 = event_list.begin(); it2 != event_list.end(); ++it2)
//	//	{
//
//	//		if (maxElement != similarEventTitleList.end() && it2.value()["event_title"] == maxElement->first)
//	//		{
//
//
//	//			UmaEvent umaEvent;
//
//	//			umaEventData.event_owner = it.value()["event_owner"].get<std::string>();
//	//			umaEventData.sys_event_owner = utility::stdStr2system(umaEventData.event_owner);
//
//	//			std::cout << it.value()["event_owner"] << std::endl;
//
//
//	//			umaEvent.event_title = it2.value()["event_title"].get<std::string>();
//	//			umaEvent.sys_event_title = utility::stdStr2system(umaEvent.event_title);
//
//
//	//			json choice_list = it2.value()["choice_list"];
//	//			for (json::iterator it4 = choice_list.begin(); it4 != choice_list.end(); ++it4) // slot
//	//			{
//	//				foundFirstEventTitle = true;
//
//	//				UmaChoice umaChoice;
//
//	//				umaChoice.choice_title = it4.value()["choice_title"].get<std::string>();
//	//				umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);
//
//	//				umaChoice.choice_effect = it4.value()["choice_effect"].get<std::string>();
//	//				umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);
//
//	//				umaEvent.choice_list.push_back(umaChoice);
//	//			}
//	//			if (!umaEvent.choice_list.empty()) // 排除掉空 element
//	//				umaEventData.event_list.push_back(umaEvent);
//	//		}
//	//	}
//	//}
//
//
//
//	return umaEventData;
//}


