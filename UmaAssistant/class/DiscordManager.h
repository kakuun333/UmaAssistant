#pragma once


#include <string>
#include <cstring>

#include <discord_register.h>
#include <discord_rpc.h>

class DiscordManager
{
private:
	DiscordManager() {}

	static DiscordManager* _instance;
	static std::string _jpAppKey;



public:
	static DiscordManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new DiscordManager();
		}

		return _instance;
	}

	void Init();

	void UpdateRPC();
};