#include "../stdafx.h"

GameWindowFinder* GameWindowFinder::_instance = nullptr;

HWND GameWindowFinder::_currentGameWindow = NULL;

std::map<std::string, HWND> GameWindowFinder::_windowDict = {};


/*
* �p�G�ΪŪ� std::string ���ܷ|���W�r�O�Ū� HWND
* �ҥH�ϥ� "NULL_GAME_WINDOW_NAME_UMA_ASSISTANT" ���N��
*/
std::string GameWindowFinder::_currentGameWindowName = NULL_GAME_WINDOW_NAME;


void GameWindowFinder::EnumWindow()
{
	this->_windowDict.clear();

	HWND window = GetTopWindow(GetDesktopWindow());
	do
	{
		// ���L�ݤ���������
		if (!IsWindowVisible(window))
			continue;

		wchar_t titleString[64];
		GetWindowTextW(window, titleString, 64);


		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::string utf8name = converter.to_bytes(titleString);

		if (utf8name.empty())
			continue;

		if (utf8name == u8"�]�w" ||
			utf8name == u8"�p��L" ||
			utf8name == u8"Program Manager" ||
			utf8name == u8"Microsoft Text Input Application")
			continue;

		System::String^ sys_string = utility::stdStr2system(utf8name);

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
				if (FindWindow(nullptr, utility::string2wstring(global::config->GameWindowName).c_str()))
				{
					_currentGameWindow = FindWindow(nullptr, utility::string2wstring(global::config->GameWindowName).c_str());
					//std::cout << u8"[GameWindowFinder] GameWindow: " << global::config->GameWindowName << std::endl;
					utility::formctrl::Text(global::form::umaForm->game_window_status_label, "�w���C������");
					utility::formctrl::ForeColor(global::form::umaForm->game_window_status_label, 0, 255, 0);
				}
				else
				{
					_currentGameWindow = NULL;
					_currentGameWindowName = NULL_GAME_WINDOW_NAME;
					//std::cout << u8"[GameWindowFinder] �����C������" << std::endl;
					utility::formctrl::Text(global::form::umaForm->game_window_status_label, "�����C������");
					utility::formctrl::ForeColor(global::form::umaForm->game_window_status_label, 255, 0, 0);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		});


	findGameWindowThread.detach();
}