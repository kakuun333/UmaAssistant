#pragma once

#include <string>
#include <vector>

#include <vcclr.h>

#include "../../enum/UmaEventDataType.h"

#include "../../utility/CharacterConvert.h"

constexpr inline int NONE_INDEX = -1;

/*


UmaEventData -> UmaEvent -> UmaChoice


*/


class UmaChoice
{
public:
	std::string choice_title;
	std::string choice_effect;

	gcroot<System::String^> sys_choice_title;
	gcroot<System::String^> sys_choice_effect;

};

class UmaEvent
{
public:
	std::string event_title;
	gcroot<System::String^> sys_event_title;

	std::vector<UmaChoice> choice_list;
};

class UmaEventData
{
public:
	unsigned int article_id;

	std::string event_owner;
	gcroot<System::String^> sys_event_owner;

	std::vector<UmaEvent> event_list;

	template<typename T>
	T Get(UmaEventDataType dataType, int elementIndex = NONE_INDEX)
	{
		if constexpr (std::is_same_v<T, std::vector<UmaChoice>>)
		{
			if (dataType == UmaEventDataType::CHOICE_LIST)
			{
				return event_list[0].choice_list;
			}
		}
		else if constexpr (std::is_same_v<T, System::String^>)
		{
			if (dataType == UmaEventDataType::EVENT_TITLE)
			{
				return event_list[0].sys_event_title;
			}
			else if(dataType == UmaEventDataType::EVENT_OWNER)
			{
				return sys_event_owner;
			}
		}
	}
};

