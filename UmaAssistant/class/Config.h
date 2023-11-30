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
	int GameServer;
	int GameWindow;
	std::map<std::string, std::string> LocalServer;

	void Update();

	void WriteToJson();
};

