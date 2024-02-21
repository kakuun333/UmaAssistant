#pragma once

// STL
#include <iostream>
#include <fstream>
#include <string>

// 3rdparty
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// util
#include "../util/CharacterConvert.h"

// .NET
using namespace System;
using namespace System::IO;


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

	void WriteJson(std::string path, std::string jsonString);

	System::String^ SysReadFile(System::String^ path);
};