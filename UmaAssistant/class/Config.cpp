#include "../stdafx.h"


Config::Config() {};

std::map<std::string, int> Config::InitGameWindowBoundOffset()
{
	std::map<std::string, int> tmp =
	{
		{ "Width", 0 },
		{ "Height", 0},
		{ "X", 0 },
		{ "Y", 0 },
	};

	return tmp;
}

void Config::Update()
{
	FileManager* fileManager = FileManager::GetInstance();
	json json_config = fileManager->ReadJson(global::path::std_config);

	// bool
	//ShowEnhanceSkill = json_config["ShowEnhanceSkill"].empty() ? true : json_config["ShowEnhanceSkill"].get<bool>();
	DebugMode = json_config["DebugMode"].empty() ? false : json_config["DebugMode"].get<bool>();
	AlwaysOnTop = json_config["AlwaysOnTop"].empty() ? false : json_config["AlwaysOnTop"].get<bool>();
	AutoMouseClick = json_config["AutoMouseClick"].empty() ? false : json_config["AutoMouseClick"].get<bool>();
	OutputLogFile = json_config["OutputLogFile"].empty() ? false : json_config["OutputLogFile"].get<bool>();

	// int
	SoftwareLanguage = json_config["SoftwareLanguage"].empty() ? static_cast<int>(SoftwareLanguageType::TW) : json_config["SoftwareLanguage"].get<int>();
	GameServer = json_config["GameServer"].empty() ? static_cast<int>(GameServerType::JP) : json_config["GameServer"].get<int>();
	GameWindow = json_config["GameWindow"].empty() ? static_cast<int>(GameWindowType::DMM) : json_config["GameWindow"].get<int>();
	JpServerLang = json_config["JpServerLang"].empty() ? static_cast<int>(JpServerLangType::JP) : json_config["JpServerLang"].get<int>();
	ScanInterval = json_config["ScanInterval"].empty() ? DEFAULT_SCAN_INTERVAL : json_config["ScanInterval"].get<int>();

	// std::string
	GameWindowName = json_config["GameWindowName"].empty() ? NULL_GAME_WINDOW_NAME : json_config["GameWindowName"].get<std::string>();
	PreviousCurrentCharacterName = json_config["PreviousCurrentCharacterName"].empty() ? DEFAULT_PREVIOUS_CURRENT_CHARACTER_NAME : json_config["PreviousCurrentCharacterName"].get<std::string>();

	// std::map
	AutoMouseClickKey["VK"] = json_config["AutoMouseClickKey"]["VK"].empty() ? VK_XBUTTON2 : json_config["AutoMouseClickKey"]["VK"].get<int>();
	AutoMouseClickKey["WinFormButton"] = json_config["AutoMouseClickKey"]["WinFormButton"].empty() ? (int)System::Windows::Forms::MouseButtons::XButton2 : json_config["AutoMouseClickKey"]["WinFormButton"].get<int>();

	LocalServer["Port"] = json_config["LocalServer"]["Port"].empty() ? DEFAULT_LOCAL_SERVER_PORT : json_config["LocalServer"]["Port"].get<std::string>();

	GameWindowBoundOffset["DMM"] = json_config["GameWindowBoundOffset"]["DMM"].empty() ? this->InitGameWindowBoundOffset() : json_config["GameWindowBoundOffset"]["DMM"].get<std::map<std::string, int>>();
	GameWindowBoundOffset["Emulator"] = json_config["GameWindowBoundOffset"]["Emulator"].empty() ? this->InitGameWindowBoundOffset() : json_config["GameWindowBoundOffset"]["Emulator"].get<std::map<std::string, int>>();
}

void Config::WriteToJson()
{
	FileManager* fileManager = FileManager::GetInstance();

	json json_config = fileManager->ReadJson(global::path::std_config);

	// bool
	//json_config["ShowEnhanceSkill"] = this->ShowEnhanceSkill;
	json_config["DebugMode"] = this->DebugMode;
	json_config["AlwaysOnTop"] = this->AlwaysOnTop;
	json_config["AutoMouseClick"] = this->AutoMouseClick;
	json_config["OutputLogFile"] = this->OutputLogFile;

	// int
	json_config["SoftwareLanguage"] = this->SoftwareLanguage;
	json_config["GameServer"] = this->GameServer;
	json_config["GameWindow"] = this->GameWindow;
	json_config["JpServerLang"] = this->JpServerLang;
	json_config["ScanInterval"] = this->ScanInterval;

	// std::string
	json_config["GameWindowName"] = this->GameWindowName;
	json_config["PreviousCurrentCharacterName"] = this->PreviousCurrentCharacterName;

	// std::map
	json_config["AutoMouseClickKey"]["VK"] = this->AutoMouseClickKey["VK"];
	json_config["AutoMouseClickKey"]["WinFormButton"] = this->AutoMouseClickKey["WinFormButton"];
	json_config["LocalServer"]["Port"] = this->LocalServer["Port"];

	json_config["GameWindowBoundOffset"]["DMM"] = this->GameWindowBoundOffset["DMM"];
	json_config["GameWindowBoundOffset"]["Emulator"] = this->GameWindowBoundOffset["Emulator"];

	std::string jsonString = json_config.dump(2);

	fileManager->WriteJson(global::path::std_config, jsonString);
}