#pragma once

#include <string>
#include <vector>

#include <vcclr.h>

#include "../../enum/UmaEventDataType.h"

#include "../../utility/CharacterConvert.h"
//#include "../../utility/CharacterCompare.h"

constexpr inline int NONE_INDEX = -1;

/*


UmaEventData -> UmaEvent -> UmaChoice


*/


class UmaChoice
{
public:
	std::string choice_title;
	std::string choice_effect;

	//gcroot<System::String^> sys_choice_title;
	//gcroot<System::String^> sys_choice_effect;

};

class UmaEvent
{
public:
	std::string event_title;
	//gcroot<System::String^> sys_event_title;

	std::vector<UmaChoice> choice_list;
};

class UmaEventData
{
public:
	float similarity = -1;

	std::string event_owner;
	//gcroot<System::String^> sys_event_owner;

	std::vector<UmaEvent> event_list;

	// 如果資料完整返回 true，不完整返回 false
	bool IsDataComplete();

	template<typename T>
	T Get(UmaEventDataType dataType, int elementIndex = NONE_INDEX)
	{
		if constexpr (std::is_same_v<T, std::vector<UmaChoice>>)
		{
			if (dataType == UmaEventDataType::CHOICE_LIST)
			{
				for (const UmaEvent& _event : event_list)
				{
					if (_event.choice_list.empty()) continue;

					return _event.choice_list;
				}
				//return event_list[0].choice_list;
			}
		}
		else if constexpr (std::is_same_v <T, std::string>)
		{
			if (dataType == UmaEventDataType::EVENT_TITLE)
			{
				return event_list[0].event_title;
			}
			else if (dataType == UmaEventDataType::EVENT_OWNER)
			{
				return event_owner;
			}
		}
		//else if constexpr (std::is_same_v<T, System::String^>)
		//{
		//	if (dataType == UmaEventDataType::EVENT_TITLE)
		//	{
		//		//for (const UmaEvent& _event : event_list)
		//		//{
		//		//	if (_event.sys_event_title->Empty) continue;

		//		//	return _event.sys_event_title;
		//		//}
		//		return event_list[0].sys_event_title;
		//	}
		//	else if(dataType == UmaEventDataType::EVENT_OWNER)
		//	{
		//		return sys_event_owner;
		//	}
		//}
	}
};

