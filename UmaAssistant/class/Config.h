#pragma once
#include <map>
#include <string>
#include "../enum/GameServerType.h"
#include "../enum/GameWindowType.h"

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
	std::string GameWindowName;
	std::map<std::string, int> AutoMouseClickKey;
	std::map<std::string, std::string> LocalServer;

	void Update();

	void WriteToJson();
};
