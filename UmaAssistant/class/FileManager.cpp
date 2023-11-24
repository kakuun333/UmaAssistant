#include "../stdafx.h"

FileManager* FileManager::_instance = nullptr;


nlohmann::json FileManager::ReadJson(std::string path)
{
	std::ifstream inputFile(path);
	if (inputFile.is_open())
	{
		nlohmann::json jsonInput;
		inputFile >> jsonInput;
		inputFile.close();


		return jsonInput;

	}
	else
	{
		std::cerr << u8"讀取 " << path << " 失敗。" << std::endl;
	}
}