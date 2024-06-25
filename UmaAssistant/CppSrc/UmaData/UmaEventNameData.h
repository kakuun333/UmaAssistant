#pragma once

#include <string>
#include <Util/Constants.h>

class UmaEventNameData
{
public:
	std::string event_type;
	std::string event_name;
	std::string matched_scanned_text;
	float similarity = util::NOT_SIMILAR;
};

