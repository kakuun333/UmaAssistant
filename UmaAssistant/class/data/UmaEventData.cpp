#include "../../stdafx.h"

bool UmaEventData::IsDataComplete()
{
	//std::cout << "1" << std::endl;
	if (this->event_owner.empty()) return false;
	//std::cout << "2" << std::endl;
	//if (System::String::IsNullOrEmpty(this->sys_event_owner)) return false;

	//std::cout << "3" << std::endl;
	if (this->event_list.empty()) return false;

	for (UmaEvent _event : this->event_list)
	{
		//std::cout << "4" << std::endl;
		if (_event.event_title.empty()) return false;
		//std::cout << "5" << std::endl;
		//if (System::String::IsNullOrEmpty(_event.sys_event_title)) return false;
		//std::cout << "6" << std::endl;
		if (_event.choice_list.empty()) return false;

		for (UmaChoice choice : _event.choice_list)
		{
			//std::cout << "7" << std::endl;
			if (choice.choice_title.empty()) return false;
			//std::cout << "8" << std::endl;
			//if (System::String::IsNullOrEmpty(choice.sys_choice_title)) return false;
			//std::cout << "9" << std::endl;
			if (choice.choice_effect.empty()) return false;
			//std::cout << "10" << std::endl;
			//if (System::String::IsNullOrEmpty(choice.sys_choice_effect)) return false;
			//std::cout << "11" << std::endl;
		}
	}


	return true;
}