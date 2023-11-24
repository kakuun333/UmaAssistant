#pragma once

#include <string>

class FileManager
{
private:
	FileManager() {}

	static FileManager* _instance;

public:
	static FileManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new FileManager();
		}
		return _instance;
	}

	nlohmann::json ReadJson(std::string path);
};

