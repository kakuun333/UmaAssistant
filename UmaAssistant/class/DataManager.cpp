#include "../stdafx.h"

#pragma region 靜態變數
DataManager* DataManager::_instance = nullptr;

bool DataManager::_currentCharacterInfoLocked = false;

nlohmann::json DataManager::event_data_json;

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
	event_data_json = fileManager->ReadJson(global::path::c_event_data_jp_json);
}

bool DataManager::TryGetCurrentCharacterName(std::string scanned_text)
{
	WebManager* webManager = WebManager::GetInstance();

	std::thread* oneStarThread = nullptr;
	std::thread* twoStarThread = nullptr;
	std::thread* threeStarThread = nullptr;


	for (json::iterator it = event_data_json["character"].begin(); it != event_data_json["character"].end(); ++it) // it.value() == characterRare
	{
		if (it.key() == "1_star")
		{
			oneStarThread = new std::thread([=]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						std::string event_owner = it2.key();
						if (utility::SIMILAR_METRIC > utility::GetCharacterNameSimilarity(scanned_text, event_owner)) continue;

						_currentCharacterInfoDict["rare"] = it.key();
						_currentCharacterInfoDict["event_owner"] = event_owner;
						_currentCharacterInfoLocked = true;

						webManager->ChangeCharacterName(utility::stdStr2system(event_owner));
					}
				});

		}
		else if (it.key() == "2_star")
		{
			twoStarThread = new std::thread([=]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						std::string event_owner = it2.key();
						if (utility::SIMILAR_METRIC > utility::GetCharacterNameSimilarity(scanned_text, event_owner)) continue;

						_currentCharacterInfoDict["rare"] = it.key();
						_currentCharacterInfoDict["event_owner"] = event_owner;
						_currentCharacterInfoLocked = true;

						webManager->ChangeCharacterName(utility::stdStr2system(event_owner));
					}
				});
		}
		else if (it.key() == "3_star")
		{
			threeStarThread = new std::thread([=]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
					{
						// it2.key() == event_owner;

						std::string event_owner = it2.key();
						if (utility::SIMILAR_METRIC > utility::GetCharacterNameSimilarity(scanned_text, event_owner)) continue;

						_currentCharacterInfoDict["rare"] = it.key();
						_currentCharacterInfoDict["event_owner"] = event_owner;
						_currentCharacterInfoLocked = true;

						webManager->ChangeCharacterName(utility::stdStr2system(event_owner));
					}
				});
		}
	}

	oneStarThread->join();
	twoStarThread->join();
	threeStarThread->join();

	delete oneStarThread;
	delete twoStarThread;
	delete threeStarThread;

	return true;
	//return !_currentCharacterInfoDict["event_owner"].empty();
}

UmaEventData DataManager::GetCurrentCharacterUmaEventData(std::string scanned_text)
{
	UmaEventData umaEventData;


	umaEventData.event_owner = _currentCharacterInfoDict["event_owner"];
	umaEventData.sys_event_owner = utility::stdStr2system(_currentCharacterInfoDict["event_owner"]);

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

				umaEventData.event_owner = _currentCharacterInfoDict["event_owner"];
				umaEventData.sys_event_owner = utility::stdStr2system(umaEventData.event_owner);

				UmaEvent umaEvent;
				umaEvent.event_title = choice.key();
				umaEvent.sys_event_title = utility::stdStr2system(umaEvent.event_title);

				for (const auto& choice_info : choice.value())
				{
					// choice_info["choice_title"]
					// choice_info["choice_effect"]

					UmaChoice umaChoice;
					umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
					umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);

					umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
					umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);

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
	UmaEventData umaEventData;

	std::map<std::string, float> similarEventTitleList = {};


	std::thread* rStarThread = nullptr;
	std::thread* srStarThread = nullptr;
	std::thread* ssrStarThread = nullptr;


	for (json::iterator it = event_data_json["support_card"].begin(); it != event_data_json["support_card"].end(); ++it)
	{
		// it == rare;
		if (it.key() == "R")
		{
			rStarThread = new std::thread([=, &similarEventTitleList]()
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
									similarEventTitleList.emplace(choice.key(), similarity);
								}
							}
						}
					}
				});
		}
		else if (it.key() == "SR")
		{
			srStarThread = new std::thread([=, &similarEventTitleList]()
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
									similarEventTitleList.emplace(choice.key(), similarity);
								}
							}
						}
					}
				});
		}
		else if (it.key() == "SSR")
		{
			ssrStarThread = new std::thread([=, &similarEventTitleList]()
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
									similarEventTitleList.emplace(choice.key(), similarity);
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

	if (similarEventTitleList.empty()) return umaEventData;

	auto maxElement = std::max_element(
		similarEventTitleList.begin(), similarEventTitleList.end(),
		[](const auto& p1, const auto& p2)
		{
			//std::cout << "first: " << p1.first << "second: " << p1.second << std::endl;
			return p1.second < p2.second;
		}
	);

	for (json::iterator it = event_data_json["support_card"].begin(); it != event_data_json["support_card"].end(); ++it)
	{
		// it == rare;

		for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2)
		{
			// it2 == event_owner;

			for (const auto& event : it2.value()["event"])
			{
				for (const auto& choice : event.items())
				{
					// choice.key() == event_title
					if (choice.key() != maxElement->first) continue;

					umaEventData.event_owner = it2.key();
					umaEventData.sys_event_owner = utility::stdStr2system(umaEventData.event_owner);

					UmaEvent umaEvent;
					umaEvent.event_title = choice.key();
					umaEvent.sys_event_title = utility::stdStr2system(umaEvent.event_title);

					for (const auto& choice_info : choice.value())
					{
						// choice_info["choice_title"]
						// choice_info["choice_effect"]

						UmaChoice umaChoice;
						umaChoice.choice_title = choice_info["choice_title"].get<std::string>();
						umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);

						umaChoice.choice_effect = choice_info["choice_effect"].get<std::string>();
						umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);

						umaEvent.choice_list.push_back(umaChoice);
					}

					umaEventData.event_list.push_back(umaEvent);
				}
			}
		}
	}

	delete rStarThread;
	delete srStarThread;
	delete ssrStarThread;

	return umaEventData;
}

UmaEventData DataManager::GetUmaEventDataFromJson(std::string scanned_text)
{
#pragma region 變數
	bool foundFirstEventTitle = false;
	UmaEventData umaEventData;

	FileManager* fileManager = FileManager::GetInstance();
	json jsonData = fileManager->ReadJson(global::path::c_event_data_jp_json);
	std::map<std::string, float> similarEventTitleList = {};
#pragma endregion


	//
	// 獲取每個相似的 event_title
	//

	std::thread* characterThread = nullptr;
	std::thread* oneStarThread = nullptr;
	std::thread* twoStarThread = nullptr;
	std::thread* threeStarThread = nullptr;


	std::thread* supportCardThread = nullptr;

	for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it)
	{
		if (it.key() == "character")
		{
			characterThread = new std::thread([=, &oneStarThread, &twoStarThread, &threeStarThread]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) // it.value() == characterRare
					{

						if (it2.key() == "1_star")
						{
							oneStarThread = new std::thread([=]()
								{
									for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) // it2.value() == article_id_list
									{
										std::string event_owner = it3.value()["event_owner"].get<std::string>();

										if (utility::SIMILAR_METRIC > utility::GetCharacterNameSimilarity(scanned_text, event_owner)) continue;


										//json event_list = it3.value()["event_list"];
										//for (json::iterator it4 = event_list.begin(); it4 != event_list.end(); ++it4)
										//{
										//	std::string event_title = it4.value()["event_title"].get<std::string>();

										//	//std::cout << event_title << std::endl;
										//}
									}
								});

						}
						else if (it2.key() == "2_star")
						{
							twoStarThread = new std::thread([=]()
								{
									for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) // it2.value() == article_id_list
									{
										std::string event_owner = it3.value()["event_owner"].get<std::string>();

										//std::cout << utility::GetCharacterNameSimilarity(scanned_text, event_owner) << std::endl;
										//json event_list = it3.value()["event_list"];
										//for (json::iterator it4 = event_list.begin(); it4 != event_list.end(); ++it4)
										//{
										//	std::string event_title = it4.value()["event_title"].get<std::string>();

										//	//std::cout << event_title << std::endl;
										//}
									}
								});
						}
						else if (it2.key() == "3_star")
						{
							threeStarThread = new std::thread([=]()
								{
									for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) // it2.value() == article_id_list
									{
										std::string event_owner = it3.value()["event_owner"].get<std::string>();

										//std::cout << utility::GetCharacterNameSimilarity(scanned_text, event_owner) << std::endl;
										//json event_list = it3.value()["event_list"];
										//for (json::iterator it4 = event_list.begin(); it4 != event_list.end(); ++it4)
										//{
										//	std::string event_title = it4.value()["event_title"].get<std::string>();

										//	//std::cout << event_title << std::endl;
										//}
									}
								});
						}
					}
				});
		}
		else
		{
			supportCardThread = new std::thread([=]()
				{
					for (json::iterator it2 = it.value().begin(); it2 != it.value().end(); ++it2) {}
					{
						std::cout << "character" << std::endl;
					}
				});
		}
	}

	characterThread->join();
	oneStarThread->join();
	twoStarThread->join();
	threeStarThread->join();


	supportCardThread->join();

	for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it) // article_id_table
	{

		//json event_list = it.value()["event_list"];
		//for (json::iterator it2 = event_list.begin(); it2 != event_list.end(); ++it2)
		//{
		//	//if (!utility::IsSimilar(scanned_text, it2.value()["event_title"].get<std::string>())) continue;

		//	float similarity = utility::GetSimilarity(scanned_text, it2.value()["event_title"].get<std::string>());

		//	if (similarity >= utility::SIMILAR_METRIC)
		//	{
		//		similarEventTitleList.emplace(it2.value()["event_title"].get<std::string>(), similarity);
		//	}

		//	//similarEventTitleList.push_back(it2.value()["event_title"].get<std::string>());
		//}
	}


	//auto maxElement = std::max_element(
	//	similarEventTitleList.begin(), similarEventTitleList.end(),
	//	[](const auto& p1, const auto& p2)
	//	{
	//		std::cout << "first: " << p1.first << "second: " << p1.second << std::endl;
	//		return p1.second < p2.second;
	//	}
	//);

	////////// 遍歷 json 物件
	//for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it) // article_id_table
	//{
	//	if (foundFirstEventTitle) break;


	//	json event_list = it.value()["event_list"];
	//	for (json::iterator it2 = event_list.begin(); it2 != event_list.end(); ++it2)
	//	{

	//		if (maxElement != similarEventTitleList.end() && it2.value()["event_title"] == maxElement->first)
	//		{


	//			UmaEvent umaEvent;

	//			umaEventData.event_owner = it.value()["event_owner"].get<std::string>();
	//			umaEventData.sys_event_owner = utility::stdStr2system(umaEventData.event_owner);

	//			std::cout << it.value()["event_owner"] << std::endl;


	//			umaEvent.event_title = it2.value()["event_title"].get<std::string>();
	//			umaEvent.sys_event_title = utility::stdStr2system(umaEvent.event_title);


	//			json choice_list = it2.value()["choice_list"];
	//			for (json::iterator it4 = choice_list.begin(); it4 != choice_list.end(); ++it4) // slot
	//			{
	//				foundFirstEventTitle = true;

	//				UmaChoice umaChoice;

	//				umaChoice.choice_title = it4.value()["choice_title"].get<std::string>();
	//				umaChoice.sys_choice_title = utility::stdStr2system(umaChoice.choice_title);

	//				umaChoice.choice_effect = it4.value()["choice_effect"].get<std::string>();
	//				umaChoice.sys_choice_effect = utility::stdStr2system(umaChoice.choice_effect);

	//				umaEvent.choice_list.push_back(umaChoice);
	//			}
	//			if (!umaEvent.choice_list.empty()) // 排除掉空 element
	//				umaEventData.event_list.push_back(umaEvent);
	//		}
	//	}
	//}



	return umaEventData;
}


