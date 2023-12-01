#include "../stdafx.h"


Config::Config() {};

void Config::Update()
{
	FileManager* fileManager = FileManager::GetInstance();
	json json_config = fileManager->ReadJson(global::path::std_config);

	DebugMode = json_config["DebugMode"].empty() ? false : json_config["DebugMode"].get<bool>();

	GameServer = json_config["GameServer"].empty() ? GameServerType::JP : json_config["GameServer"].get<int>();

	GameWindow = json_config["GameWindow"].empty() ? GameWindowType::DMM : json_config["GameWindow"].get<int>();

	GameWindowName = json_config["GameWindowName"].empty() ? NULL_GAME_WINDOW_NAME : json_config["GameWindowName"].get<std::string>();

	LocalServer["Port"] = json_config["LocalServer"]["Port"].empty() ? "7777" : json_config["LocalServer"]["Port"].get<std::string>();
}

void Config::WriteToJson()
{
	FileManager* fileManager = FileManager::GetInstance();

	json json_config = fileManager->ReadJson(global::path::std_config);

	json_config["DebugMode"] = this->DebugMode;
	json_config["GameServer"] = this->GameServer;
	json_config["GameWindow"] = this->GameWindow;
	json_config["GameWindowName"] = this->GameWindowName;
	json_config["LocalServer"]["Port"] = this->LocalServer["Port"];

	std::string jsonString = json_config.dump(2);

	fileManager->WriteJson(global::path::std_config, jsonString);
}