#pragma once

// STL
#include <string>
#include <cstring>

// Discord API
#include <discord_register.h>
#include <discord_rpc.h>

// enum
#include "../enum/SoftwareLanguageType.h"

// class
#include "Config.h"
#include "DataManager.h"
#include "UmaLog.h"

// global
#include "../global/form.h"

const std::string CHARACTER_ICON_URL = "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaMisc/Image/Character/";

class DiscordManager
{
private:
	DiscordManager() {}

	static DiscordManager* _instance;
	static std::string _jpAppClientId;
	static std::string _twAppClientId;

	bool _isShutdown = true;

	std::string _GetCurrentCharacterName();

	std::string _GetCurrentCharacterIconName(std::string currentCharName);
public:
	static DiscordManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new DiscordManager();
		}

		return _instance;
	}

	void UpdateRPC();

	void Shutdown();

	inline void SetIsShutdown(bool value)
	{
		_isShutdown = value;
	}
	
	inline bool GetIsShutdown()
	{
		return _isShutdown;
	}
};