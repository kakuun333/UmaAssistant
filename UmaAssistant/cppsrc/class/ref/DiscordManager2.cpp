#include "DiscordManager2.h"

#include <string>

Void DiscordManager2::Shutdown()
{
	//try
	//{
	//	Discord_Shutdown();
	//	this->IsShutdown = true;
	//	UmaLog::GetInstance()->print(u8"[DiscordManager] 已終結 Discord RPC");
	//}
	//catch (std::exception e)
	//{
	//	UmaLog::GetInstance()->print(u8"[DiscordManager][Shutdown][std::exception]", e.what());
	//}
}

Void DiscordManager2::UpdateRPC()
{
	//if (!Config::GetInstance()->DiscordRPC) return;

	//try
	//{
	//	IsBusy = true;
	//	// ================ DiscordEventHandlers ================ //
	//	DiscordEventHandlers* Handler = new DiscordEventHandlers();
	//	memset((DiscordEventHandlers*)Handler, 0, sizeof(Handler));

	//	switch (Config::GetInstance()->GameServer)
	//	{
	//	case static_cast<int>(SoftwareLanguageType::JP):
	//		Discord_Initialize(util::systemStr2std(_jpAppClientId).c_str(), (DiscordEventHandlers*)Handler, 1, NULL);
	//		break;

	//	case static_cast<int>(SoftwareLanguageType::TW):
	//		Discord_Initialize(util::systemStr2std(_twAppClientId).c_str(), (DiscordEventHandlers*)Handler, 1, NULL);
	//		break;
	//	}

	//	// ================ DiscordRichPresence ================ //
	//	DiscordRichPresence rpc;
	//	memset(&rpc, 0, sizeof(rpc));

	//	std::string details, state, largeImageText, smallImageText;

	//	std::string characterName = this->_GetCurrentCharacterName();
	//	std::string iconName = this->_GetCurrentCharacterIconName(characterName);
	//	std::string smallImageUrl = CHARACTER_ICON_URL + iconName;

	//	rpc.startTimestamp = time(0);
	//	rpc.largeImageKey = "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaAssistant/UmaMisc/Image/DiscordRPC/umamusume_icon.png";
	//	rpc.smallImageKey = smallImageUrl == CHARACTER_ICON_URL ? "" : smallImageUrl.c_str();

	//	// ------------- 更新 largeImageText ------------- //
	//	switch (Config::GetInstance()->GameServer)
	//	{
	//	case static_cast<int>(SoftwareLanguageType::JP):
	//		largeImageText = u8"ウマ娘 プリティーダービー";
	//		rpc.largeImageText = largeImageText.c_str();
	//		break;

	//	case static_cast<int>(SoftwareLanguageType::TW):
	//		largeImageText = u8"賽馬娘 Pretty Derby";
	//		rpc.largeImageText = largeImageText.c_str();
	//		break;
	//	}

	//	switch (Config::GetInstance()->SoftwareLanguage)
	//	{
	//	case static_cast<int>(SoftwareLanguageType::JP):
	//		// ---------------------------------------------- //
	//		details = characterName.empty() ? "" : characterName + u8" を育成している";
	//		rpc.details = details.c_str();
	//		// ---------------------------------------------- //
	//		state = u8"待機中";
	//		rpc.state = state.c_str();
	//		// ---------------------------------------------- //
	//		smallImageText = characterName.empty() ? "" : characterName;
	//		rpc.smallImageText = smallImageText.c_str();
	//		// ---------------------------------------------- //
	//		break;
	//	case static_cast<int>(SoftwareLanguageType::TW):
	//		// ---------------------------------------------- //
	//		details = characterName.empty() ? u8"閒置狀態" : u8"正在培育 " + characterName;
	//		rpc.details = details.c_str();
	//		// ---------------------------------------------- //
	//		state = u8"閒置中";
	//		rpc.state = state.c_str();
	//		// ---------------------------------------------- //
	//		smallImageText = characterName.empty() ? "" : characterName;
	//		rpc.smallImageText = smallImageText.c_str();
	//		// ---------------------------------------------- //
	//		break;
	//	}

	//	Discord_UpdatePresence(&rpc);

	//	this->IsShutdown = false;

	//	UmaLog::GetInstance()->print(u8"[DiscordManager] 已更新 Discord RPC");

	//	IsBusy = false;
	//}
	//catch (std::exception e)
	//{
	//	IsBusy = false;
	//	UmaLog::GetInstance()->print(u8"[DiscordManager][UpdateRPC][std::exception]", e.what());
	//}
}



std::string DiscordManager2::_GetCurrentCharacterName()
{
	return DataManager::GetInstance()->GetCurrentCharacterInfoDict()["event_owner"];
}

std::string DiscordManager2::_GetCurrentCharacterIconName(std::string currentCharName)
{
	std::string iconName;

	FileManager* fileManager = FileManager::GetInstance();

	// arr == array == 陣列
	json arrJsonData = fileManager->ReadJson(global::path::std_UmaData + "\\select_character_data.json");

	for (const auto& entry : arrJsonData)
	{
		if (currentCharName == entry["jp_event_owner"] || currentCharName == entry["tw_event_owner"])
		{
			iconName = entry["icon"];
			break;
		}

		/*std::cout << "Icon: " << entry["icon"] << std::endl;
		std::cout << "JP Event Owner: " << entry["jp_event_owner"] << std::endl;
		std::cout << "TW Event Owner: " << entry["tw_event_owner"] << std::endl;*/
	}

	return iconName;
}