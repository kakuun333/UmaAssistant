#include "../stdafx.h"

GameWindowFinder* GameWindowFinder::_instance = nullptr;

HWND GameWindowFinder::_currentGameWindow = NULL;

std::map<GameWindowType, LPCWSTR> GameWindowFinder::_gameWindowDict =
{
	{ GameWindowType::DMM,		   L"umamusume" },
	{ GameWindowType::BLUE_STACKS, L"umamusume" },

};

void GameWindowFinder::CreateFindGameWindowThread()
{
	std::thread findGameWindowThread([=]()
		{
			while (true)
			{
				if (FindWindow(nullptr, _gameWindowDict[GameWindowType::DMM]))
				{
					_currentGameWindow = FindWindow(nullptr, L"umamusume");
					//std::cout << u8"[WindowFinder] GameWindow: umamusume" << std::endl;
					utility::formctrl::Text(global::form::umaForm->game_window_status_label, "已找到遊戲視窗");
					utility::formctrl::ForeColor(global::form::umaForm->game_window_status_label, 0, 255, 0);
				}
				//else if (FindWindow(nullptr, _gameWindowDict[GameWindowType::BLUE_STACKS]))
				//{

				//}
				else
				{
					_currentGameWindow = NULL;
					//std::cout << u8"[WindowFinder] 未找到遊戲視窗" << std::endl;
					utility::formctrl::Text(global::form::umaForm->game_window_status_label, "未找到遊戲視窗");
					utility::formctrl::ForeColor(global::form::umaForm->game_window_status_label, 255, 0, 0);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
		});


	findGameWindowThread.detach();
}