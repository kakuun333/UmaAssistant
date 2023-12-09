#pragma once
#include <map>
#include <string>
#include "../enum/GameServerType.h"
#include "../enum/GameWindowType.h"

constexpr inline int DEFAULT_SCAN_INTERVAL = 100; // ²@¬í

class Config
{
private:

public:
	Config();

	bool DebugMode;
	bool AlwaysOnTop;
	bool AutoMouseClick;
	int GameServer;
	int GameWindow;
	int JpServerLang;
	int ScanInterval;
	std::string GameWindowName;
	std::map<std::string, int> AutoMouseClickKey;
	std::map<std::string, std::string> LocalServer;

	void Update();

	void WriteToJson();
};

