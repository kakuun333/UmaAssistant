#include "GameWindowFinder.h"



GameWindowFinder* GameWindowFinder::_instance = nullptr;

HWND GameWindowFinder::_currentGameWindow = NULL;

std::map<std::string, HWND> GameWindowFinder::_windowDict = {};


/*
* 如果用空的 std::string 的話會找到名字是空的 HWND
* 所以使用 "NULL_GAME_WINDOW_NAME_UMA_ASSISTANT" 做代替
*/
std::string GameWindowFinder::_currentGameWindowName = NULL_GAME_WINDOW_NAME;


void GameWindowFinder::EnumWindow()
{
	this->_windowDict.clear();

	HWND window = GetTopWindow(GetDesktopWindow());
	do
	{
		// 跳過看不見的視窗
		if (!IsWindowVisible(window))
			continue;

		wchar_t titleString[64];
		GetWindowTextW(window, titleString, 64);


		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::string utf8name = converter.to_bytes(titleString);

		if (utf8name.empty())
			continue;

		if (utf8name == u8"設定" ||
			utf8name == u8"小算盤" ||
			utf8name == u8"Program Manager" ||
			utf8name == u8"Microsoft Text Input Application")
			continue;

		System::String^ sys_string = util::stdStr2system(utf8name);

		global::form::previewForm->window_listbox->Items->Add(sys_string);

		this->_windowDict.emplace(utf8name, window);

		std::cout << "utf8: " << utf8name << std::endl;

	} while (window = GetWindow(window, GW_HWNDNEXT));
}

void GameWindowFinder::CreateFindGameWindowThread()
{
	std::thread findGameWindowThread([=]()
		{
			while (true)
			{
				//if (FindWindow(nullptr, utility::string2wstring(GetCurrentGameWindowName()).c_str()))
				if (FindWindow(nullptr, util::string2wstring(Config::GetInstance()->GameWindowName).c_str()))
				{
					_currentGameWindow = FindWindow(nullptr, util::string2wstring(Config::GetInstance()->GameWindowName).c_str());
					//std::cout << u8"[GameWindowFinder] GameWindow: " << Config::GetInstance()->GameWindowName << std::endl;

					switch (Config::GetInstance()->SoftwareLanguage)
					{
					case static_cast<int>(SoftwareLanguageType::JP):
						util::formctrl::Text(global::form::umaForm->game_window_status_label, u8"ゲームウィンドウが見つけました");
						break;
					case static_cast<int>(SoftwareLanguageType::TW):
						util::formctrl::Text(global::form::umaForm->game_window_status_label, u8"已找到遊戲視窗");
						break;
					}
					
					util::formctrl::ForeColor(global::form::umaForm->game_window_status_label, 0, 255, 0);

					if (!this->GetFoundGameWindow())
					{
						//DiscordManager2::Instance->UpdateRPC();
					}


					this->SetFoundGameWindow(true);
				}
				else
				{
					_currentGameWindow = NULL;
					_currentGameWindowName = NULL_GAME_WINDOW_NAME;
					//std::cout << u8"[GameWindowFinder] 未找到遊戲視窗" << std::endl;

					switch (Config::GetInstance()->SoftwareLanguage)
					{
					case static_cast<int>(SoftwareLanguageType::JP):
						util::formctrl::Text(global::form::umaForm->game_window_status_label, u8"ゲームウィンドウが見つかりません");
						break;
					case static_cast<int>(SoftwareLanguageType::TW):
						util::formctrl::Text(global::form::umaForm->game_window_status_label, u8"未找到遊戲視窗");
						break;
					}
					
					util::formctrl::ForeColor(global::form::umaForm->game_window_status_label, 255, 0, 0);

					this->SetFoundGameWindow(false);

					//if (Config::GetInstance()->DiscordRPC && !DiscordManager2::Instance->IsShutdown)
					//{
					//	DiscordManager2::Instance->Shutdown();
					//}
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		});


	findGameWindowThread.detach();
}