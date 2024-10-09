#pragma once

// STL
#include <map>
#include <string>

// Enum
#include <Enum/GameServerType.h>
#include <Enum/GameWindowType.h>
#include <Enum/SoftwareLanguageType.h>
#include <Enum/JpServerLangType.h>

// Manager
#include <Manager/FileManager.h>
#include <Manager/GameWindowManager.h>

// include
#include <singleton_mutex.hpp>

// 3rdparty
#include <nlohmann/json.hpp>
using json = nlohmann::json;

constexpr inline int DEFAULT_SCAN_INTERVAL = 100;
const std::string DEFAULT_LOCAL_SERVER_PORT = "58541";
const std::string DEFAULT_PREVIOUS_CURRENT_CHARACTER_NAME = "DEFAULT_PREVIOUS_CURRENT_CHARACTER_NAME";

// Global
#include <Global/path.h>

class Config : public SingletonMutex<Config>
{
public:
	void Update();
	void WriteToJson();
public:
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
private:
	std::map<std::string, int> m_InitGameWindowBoundOffset();
};

