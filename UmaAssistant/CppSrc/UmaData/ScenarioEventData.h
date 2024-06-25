#pragma once

#include <string>
#include <vector>


#include <Util/Constants.h>
#include <UmaData/UmaEventData.h>

class ScenarioEventData
{

public:
	float similarity = util::NOT_SIMILAR;

	std::string event_name;

	std::vector<UmaChoice> choice_list;

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

