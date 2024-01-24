#pragma once

#include <string>
#include <vector>

#include <vcclr.h>


#include "../../util/CharacterConvert.h"
#include "../../util/Constants.h"

#include "../../enum/UmaEventDataType.h"
#include "../../enum/UmaDataType.h"


constexpr inline int NONE_INDEX = -1;

/*


UmaEventData -> UmaEvent -> UmaChoice


*/


class UmaChoice
{
public:
	std::string choice_name;
	std::string choice_effect;
};

class UmaEvent
{
public:
	std::string event_name;

	std::vector<UmaChoice> choice_list;

	inline bool empty()
	{
		if (event_name.empty() && choice_list.empty()) return true;

		return false;
	}
};

class UmaEventData
{
public:
	float similarity = util::NOT_SIMILAR;

	std::string event_owner;
	std::string rare;

	std::string matched_scanned_text;

	UmaEvent umaEvent;

	UmaDataType umaDataType;

	// 如果資料完整返回 true，不完整返回 false
	inline bool UmaEventData::IsDataComplete()
	{
		//std::cout << "1" << std::endl;
		if (this->event_owner.empty()) return false;

		//std::cout << "2" << std::endl;

		if (this->umaEvent.empty()) return false;

		//std::cout << "3" << std::endl;

		if (this->umaEvent.event_name.empty()) return false;
		//std::cout << "4" << std::endl;

		if (this->umaEvent.choice_list.empty()) return false;

		//std::cout << "5" << std::endl;

		for (UmaChoice choice : this->umaEvent.choice_list)
		{
			//std::cout << "6" << std::endl;
			if (choice.choice_name.empty()) return false;
			//std::cout << "7" << std::endl;
			if (choice.choice_effect.empty()) return false;
			//std::cout << "8" << std::endl;
		}

		return true;
	}

	template<typename T>
	T Get(UmaEventDataType dataType)
	{
		if constexpr (std::is_same_v<T, std::vector<UmaChoice>>)
		{
			if (dataType == UmaEventDataType::CHOICE_LIST)
			{
				return umaEvent.choice_list;
			}
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			if (dataType == UmaEventDataType::EVENT_TITLE)
			{
				return umaEvent.event_name;
			}
			else if (dataType == UmaEventDataType::EVENT_OWNER)
			{
				return event_owner;
			}
		}
	}
};

