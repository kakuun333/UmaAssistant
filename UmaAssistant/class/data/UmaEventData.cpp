#include "../../stdafx.h"

bool UmaEventData::IsDataComplete()
{
	//std::cout << "1" << std::endl;
	if (this->event_owner.empty()) return false;

	//std::cout << "2" << std::endl;

	if (this->umaEvent.empty()) return false;

	//std::cout << "3" << std::endl;

	if (this->umaEvent.event_title.empty()) return false;
	//std::cout << "4" << std::endl;

	if (this->umaEvent.choice_list.empty()) return false;

	//std::cout << "5" << std::endl;

	for (UmaChoice choice : this->umaEvent.choice_list)
	{
		//std::cout << "6" << std::endl;
		if (choice.choice_title.empty()) return false;
		//std::cout << "7" << std::endl;
		if (choice.choice_effect.empty()) return false;
		//std::cout << "8" << std::endl;
	}



	return true;
}