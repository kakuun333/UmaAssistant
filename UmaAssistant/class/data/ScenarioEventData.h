#pragma once

#include <string>
#include <vector>

class ScenarioChoice
{
public:
	std::string choice_title;
	std::string choice_effect;
};

class ScenarioEventData
{

public:
	std::string event_title;
	std::vector<ScenarioChoice> event_list;

	bool IsDataComplete();
};

