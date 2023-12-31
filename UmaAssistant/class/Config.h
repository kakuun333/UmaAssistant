#pragma once
#include <map>
#include <string>
#include "../enum/GameServerType.h"
#include "../enum/GameWindowType.h"

constexpr inline int DEFAULT_SCAN_INTERVAL = 100; // ²@¬í

const std::string DEFAULT_LOCAL_SERVER_PORT = "5854";


class Config
{
private:

	std::map<std::string, int> InitGameWindowBoundOffset();

public:
	Config();

	//bool ShowEnhanceSkill;
	bool DebugMode;
	bool AlwaysOnTop;
	bool AutoMouseClick;
	bool OutputLogFile;
	int SoftwareLanguage;
	int GameServer;
	int GameWindow;
	int JpServerLang;
	int ScanInterval;
	std::string GameWindowName;
	std::map<std::string, int> AutoMouseClickKey;
	std::map<std::string, std::string> LocalServer;
	std::map<std::string, std::map<std::string, int>> GameWindowBoundOffset;

	void Update();

	void WriteToJson();


};

