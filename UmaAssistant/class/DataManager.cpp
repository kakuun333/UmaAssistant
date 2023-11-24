#include "../stdafx.h"

//DataManager::DataManager() {}
DataManager* DataManager::_instance = nullptr;


UmaEventData DataManager::GetUmaEventDataFromJson(std::string scanned_text)
{
#pragma region 變數
	bool foundFirstEventTitle = false;
	json jsonData;

	UmaEventData umaEventData;
#pragma endregion


	// 打開 JSON 檔
	std::ifstream jsonFile(global::path::c_event_data_jp_json);
	if (jsonFile.is_open())
	{
		// 讀取 JSON 檔的內容到 json 物件
		jsonFile >> jsonData;

		jsonFile.close();
	}


	//std::cout << "scanned_text: " << scanned_text << std::endl;





	// 遍歷 json 物件
	for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it) // article_id_table
	{
		if (foundFirstEventTitle) break;
		/*event_data.event_owner = it.value()["event_owner"];*/

		json event_list = it.value()["event_list"];
		for (json::iterator it2 = event_list.begin(); it2 != event_list.end(); ++it2)
		{
			//for (std::string splitted_json_text : utility::SplitText(it2.value()["event_title"], 6))
			//{
			//	bool notThis = false;
			//	for (std::string splitted_scanned_text : utility::SplitText(scanned_text))
			//	{
			//		if (splitted_json_text != splitted_scanned_text)
			//		{
			//			notThis = true;
			//		}
			//	}

			//	if (notThis) continue;
			//}

			if (!utility::IsSimilar(scanned_text, it2.value()["event_title"])) continue;

			//if (it2.value()["event_title"] != scanned_text) continue;


			//std::string event_idx = it2.key();

			UmaEvent umaEvent;

			umaEventData.event_owner = it.value()["event_owner"];
			umaEventData.sys_event_owner = utility::stdStr2system(it.value()["event_owner"]);

			std::cout << it.value()["event_owner"] << std::endl;


			umaEvent.event_title = it2.value()["event_title"];
			umaEvent.sys_event_title = utility::stdStr2system(it2.value()["event_title"]);
			
			
			json choice_list = it2.value()["choice_list"];
			for (json::iterator it4 = choice_list.begin(); it4 != choice_list.end(); ++it4) // slot
			{
				foundFirstEventTitle = true;

				UmaChoice umaChoice;

				umaChoice.choice_title = it4.value()["choice_title"];
				umaChoice.sys_choice_title = utility::stdStr2system(it4.value()["choice_title"]);

				umaChoice.choice_effect = it4.value()["choice_effect"];
				umaChoice.sys_choice_effect = utility::stdStr2system(it4.value()["choice_effect"]);

				umaEvent.choice_list.push_back(umaChoice);
				//std::cout << "event_idx: \n" << event_idx << std::endl;
				//std::cout << "event_title: \n" << event_title << std::endl;
				//std::cout << "choiceTitle: " << choice_title << std::endl;
				//std::cout << "choiceEffect: \n" << choice_effect << std::endl;
			}

			if (!umaEvent.choice_list.empty()) // 排除掉空 element
				umaEventData.event_list.push_back(umaEvent);

			//std::cout << umaEventData.event_owner << std::endl;
			//std::cout << umaEvent.event_title << std::endl;
			//std::cout << umaEvent.choice_list[0].choice_title << std::endl;
			//std::cout << umaEvent.choice_list[0].choice_effect << std::endl;
			//std::cout << umaEvent.choice_list[1].choice_title << std::endl;
			//std::cout << umaEvent.choice_list[1].choice_effect << std::endl;
		}

		//if (!event_list.event_title.empty() && !event_list.event_choice_list.empty()) // 排除掉空 element
		//	event_data.event_list.push_back(event_list);

	}



	return umaEventData;
}