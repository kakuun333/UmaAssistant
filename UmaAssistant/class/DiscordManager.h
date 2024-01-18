#pragma once


#include <string>
#include <cstring>

#include <discord_register.h>
#include <discord_rpc.h>

const std::string CHARACTER_ICON_URL = "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaMisc/Image/Character/";

class DiscordManager
{
private:
	DiscordManager() {}

	static DiscordManager* _instance;
	static std::string _jpAppClientId;
	static std::string _twAppClientId;

	bool _inited = false;

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

#pragma region ¤º´O¨ç¦¡
	inline void SetInited(bool value)
	{
		_inited = value;
	}
	
	inline bool GetInited()
	{
		return _inited;
	}
#pragma endregion

};