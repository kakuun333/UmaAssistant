#pragma once

// STL
#include <iostream>
#include <string>

// Discord API
#include <discord_register.h>
#include <discord_rpc.h>

#include "RefSingleton.h"

#include "../UmaLog.h"
#include "../DataManager.h"

using namespace System;

const std::string CHARACTER_ICON_URL = "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaAssistant/UmaMisc/Image/Character/";

ref class DiscordManager2 : public RefSingleton<DiscordManager2^>
{
private:
	String^ _jpAppClientId = "1195236155709468752";
	String^ _twAppClientId = "1195259431106138132";

	Boolean^ _isShutdown = true;
	Boolean^ _isbusy = false;

	std::string _GetCurrentCharacterName();
	std::string _GetCurrentCharacterIconName(std::string currentCharName);
public:
	property Boolean^ IsShutdown
	{
		Boolean^ get() { return _isShutdown; }
		Void set(Boolean^ value) { _isShutdown = value; }
	}

	property Boolean^ IsBusy
	{
		Boolean^ get() { return _isbusy; }
		Void set(Boolean^ value) { _isbusy = value; }
	}

	Void Shutdown();

	Void UpdateRPC();
};

