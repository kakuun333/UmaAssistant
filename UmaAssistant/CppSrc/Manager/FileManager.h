#pragma once

// STL
#include <iostream>
#include <fstream>
#include <string>

// 3rdparty
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// include
#include <singleton_mutex.hpp>

#include <Util/CharacterConvert.h>

// .NET
using namespace System;
using namespace System::IO;


class FileManager : public SingletonMutex<FileManager>
{
public:
	nlohmann::json ReadJson(std::string path);

	void WriteJson(std::string path, std::string jsonString);

	System::String^ SysReadFile(System::String^ path);
};