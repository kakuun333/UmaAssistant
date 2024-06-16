#pragma once

#include <string>
#include "../../util/Constants.h"

class UmaEventNameData
{
public:
	std::string event_type;
	std::string event_name;
	std::string matched_scanned_text;
	float similarity = util::NOT_SIMILAR;
};

