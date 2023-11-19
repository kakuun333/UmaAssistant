#include "../stdafx.h"

void FileManager::LuaTableToJson(std::string scanned_text)
{
	json jsonData;

	bool foundFirstEventTitle = false;

	// 打開 JSON 檔
	std::ifstream jsonFile(global::path::event_data_jp_json);
	if (jsonFile.is_open())
	{
		// 讀取 JSON 檔的內容到 json 物件
		jsonFile >> jsonData;

		jsonFile.close();
	}

	std::string event_owner;
	std::string event_title;

	std::string choice_title;
	std::string choice_effect;

	// 遍歷 json 物件
	for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it) // article_id_table
	{
		event_owner = it.value()["event_owner"];
		json event_slot = it.value()["event_slot"];

		if (foundFirstEventTitle) break;

		for (json::iterator it2 = event_slot.begin(); it2 != event_slot.end(); ++it2)
		{
			std::string event_slot_idx = it2.key();

			

			event_title = it2.value()["event_title"];
			json event_choice = it2.value()["event_choice"];
			for (json::iterator it4 = event_choice.begin(); it4 != event_choice.end(); ++it4) // slot
			{
				if (event_title == scanned_text)
				{
					foundFirstEventTitle = true;
					std::string choiceEffect = it4.value()["choice_effect"];
					std::string choiceTitle = it4.value()["choice_title"];
					//std::cout << "event_slot_idx: \n" << event_slot_idx << std::endl;
					//std::cout << "event_title: \n" << event_title << std::endl;
					std::cout << "choiceEffect: \n" << choiceEffect << std::endl;
					std::cout << "choiceTitle: " << choiceTitle << std::endl;
				}
			}

		}
	}
}