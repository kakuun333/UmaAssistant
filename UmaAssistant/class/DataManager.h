#pragma once

#include <string>
#include "data/UmaEventData.h"

class DataManager
{
private:
	DataManager() {}

	static DataManager* _instance;

	static std::map<std::string, std::string> _currentCharacterInfoDict;

	static bool _currentCharacterInfoLocked;


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

	UmaEventData GetCurrentCharacterUmaEventData(std::string scanned_text);

	UmaEventData GetSupportCardUmaEventData(std::string scanned_text);

	bool TryGetCurrentCharacterName(std::string scanned_text);

	inline bool IsCurrentCharacterInfoLocked()
	{
		return _currentCharacterInfoLocked;
	}

	inline void SetCurrentCharacterInfo(bool value)
	{
		_currentCharacterInfoLocked = value;
	}

	inline std::map<std::string, std::string> GetCurrentCharacterInfoDict()
	{
		return _currentCharacterInfoDict;
	}
};

