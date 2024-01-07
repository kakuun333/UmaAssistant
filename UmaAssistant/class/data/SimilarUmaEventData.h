#pragma once

#include <string>

class SimilarUmaEventData
{
public:
	float similarity;

	std::string rare;
	std::string event_title;
	std::string event_owner;

	std::string matched_scanned_text;
};