#include "ScenarioEventData.h"
#include <iostream>
bool ScenarioEventData::IsDataComplete()
{
	if (this->event_title.empty()) return false;

	for (ScenarioChoice _event : this->event_list)
	{
		if (_event.choice_title.empty()) return false;
		if (_event.choice_effect.empty()) return false;
	}


	return true;
}