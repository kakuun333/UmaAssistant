#pragma once

#include <string>
#include <vector>

#include "UmaEventData.h"



class ScenarioEventData
{

public:
	float similarity = -1;

	std::string event_name;

	std::vector<UmaChoice> choice_list;

	std::string matched_scanned_text;

	inline bool IsDataComplete()
	{
		if (this->event_name.empty()) return false;

		for (UmaChoice _event : this->choice_list)
		{
			if (_event.choice_name.empty()) return false;
			if (_event.choice_effect.empty()) return false;
		}

		return true;
	}
};

