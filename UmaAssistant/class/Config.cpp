#include "../stdafx.h"


Config::Config() {};

void Config::Update()
{
	FileManager* fileManager = FileManager::GetInstance();
	json json_config = fileManager->ReadJson(global::path::std_config);

	DebugMode = json_config["DebugMode"].empty() ? false : json_config["DebugMode"].get<bool>();

	AlwaysOnTop = json_config["AlwaysOnTop"].empty() ? false : json_config["AlwaysOnTop"].get<bool>();

	AutoMouseClick = json_config["AutoMouseClick"].empty() ? false : json_config["AutoMouseClick"].get<bool>();

	GameServer = json_config["GameServer"].empty() ? static_cast<int>(GameServerType::JP) : json_config["GameServer"].get<int>();

	GameWindow = json_config["GameWindow"].empty() ? static_cast<int>(GameWindowType::DMM) : json_config["GameWindow"].get<int>();

	JpServerLang = json_config["JpServerLang"].empty() ? static_cast<int>(JpServerLangType::JP) : json_config["JpServerLang"].get<int>();

	ScanInterval = json_config["ScanInterval"].empty() ? DEFAULT_SCAN_INTERVAL : json_config["ScanInterval"].get<int>();

	GameWindowName = json_config["GameWindowName"].empty() ? NULL_GAME_WINDOW_NAME : json_config["GameWindowName"].get<std::string>();

	AutoMouseClickKey["VK"] = json_config["AutoMouseClickKey"]["VK"].empty() ? VK_XBUTTON2 : json_config["AutoMouseClickKey"]["VK"].get<int>();
	AutoMouseClickKey["WinFormButton"] = json_config["AutoMouseClickKey"]["WinFormButton"].empty() ? (int)System::Windows::Forms::MouseButtons::XButton2 : json_config["AutoMouseClickKey"]["WinFormButton"].get<int>();

	LocalServer["Port"] = json_config["LocalServer"]["Port"].empty() ? "7777" : json_config["LocalServer"]["Port"].get<std::string>();
}

void Config::WriteToJson()
{
	FileManager* fileManager = FileManager::GetInstance();

	json json_config = fileManager->ReadJson(global::path::std_config);

	json_config["DebugMode"] = this->DebugMode;
	json_config["AlwaysOnTop"] = this->AlwaysOnTop;
	json_config["AutoMouseClick"] = this->AutoMouseClick;
	json_config["GameServer"] = this->GameServer;
	json_config["GameWindow"] = this->GameWindow;
	json_config["JpServerLang"] = this->JpServerLang;
	json_config["ScanInterval"] = this->ScanInterval;
	json_config["GameWindowName"] = this->GameWindowName;
	json_config["AutoMouseClickKey"]["VK"] = this->AutoMouseClickKey["VK"];
	json_config["AutoMouseClickKey"]["WinFormButton"] = this->AutoMouseClickKey["WinFormButton"];
	json_config["LocalServer"]["Port"] = this->LocalServer["Port"];

	std::string jsonString = json_config.dump(2);

	fileManager->WriteJson(global::path::std_config, jsonString);
}