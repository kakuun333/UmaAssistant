#pragma once

#include <string>
#include "data/UmaEventData.h"

class DataManager
{
private:
	DataManager() {}

	static DataManager* _instance;

public:
	static DataManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new DataManager();
		}
		return _instance;
	}

	UmaEventData GetUmaEventDataFromJson(std::string scanned_text);
};

