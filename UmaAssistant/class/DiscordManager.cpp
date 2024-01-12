#include "DiscordManager.h"

DiscordManager* DiscordManager::_instance = nullptr;

std::string DiscordManager::_jpAppKey = "1195236155709468752";

void DiscordManager::Init()
{
	DiscordEventHandlers Handler;
	memset(&Handler, 0, sizeof(Handler));
	Discord_Initialize(_jpAppKey.c_str(), &Handler, 1, NULL);
}

void DiscordManager::UpdateRPC()
{
	DiscordRichPresence rpc;
	memset(&rpc, 0, sizeof(rpc));
	rpc.state = "Example state";
	rpc.details = "Example details";
	rpc.startTimestamp = 0;
	rpc.largeImageText = "Example for largeImageText";
	rpc.smallImageText = "Example for smallImageText";

	//std::string largeImgPath = global::path::std_umaMisc + "\\Image\\DiscordRPC\\umamusume_icon.png";
	rpc.largeImageKey = "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaMisc/Image/Character/i_1.png";
	Discord_UpdatePresence(&rpc);
}