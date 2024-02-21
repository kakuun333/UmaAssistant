#pragma once

// STL
#include <map>
#include <string>

// enum
#include "../enum/GameServerType.h"
#include "../enum/GameWindowType.h"
#include "../enum/SoftwareLanguageType.h"
#include "../enum/JpServerLangType.h"

// class
#include "FileManager.h"
#include "GameWindowFinder.h"

// 3rdparty
#include <nlohmann/json.hpp>
using json = nlohmann::json;

constexpr inline int DEFAULT_SCAN_INTERVAL = 100; // ²@¬í
const std::string DEFAULT_LOCAL_SERVER_PORT = "5854";
const std::string DEFAULT_PREVIOUS_CURRENT_CHARACTER_NAME = "DEFAULT_PREVIOUS_CURRENT_CHARACTER_NAME";

// global
#include "../global/path.h"

class Config
{
private:
	Config() {}
	static Config* _instance;

	std::map<std::string, int> InitGameWindowBoundOffset();
public:
	static Config* GetInstance()
	{
		if (_instance == nullptr) _instance = new Config();
		return _instance;
	}

	//bool ShowEnhanceSkill;
	bool DebugMode;
	bool AlwaysOnTop;
	bool AutoMouseClick;
	bool OutputLogFile;
	bool DiscordRPC;
	int SoftwareLanguage;
	int GameServer;
	int GameWindow;
	int JpServerLang;
	int ScanInterval;
	std::string GameWindowName;
	std::string PreviousCurrentCharacterName;
	std::map<std::string, int> AutoMouseClickKey;
	std::map<std::string, std::string> LocalServer;
	std::map<std::string, std::map<std::string, int>> GameWindowBoundOffset;

	void Update();

	void WriteToJson();


};

