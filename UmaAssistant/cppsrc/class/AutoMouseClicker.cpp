#include "AutoMouseClicker.h"

AutoMouseClicker* AutoMouseClicker::_instance = nullptr;
bool AutoMouseClicker::_starting = false;

void AutoMouseClicker::Start()
{
	_starting = true;
	
	std::thread([=]()
		{
			while (_starting)
			{
				if (GetAsyncKeyState(Config::GetInstance()->AutoMouseClickKey["VK"]) & 0x8000)
				{
					INPUT input;
					input.type = INPUT_MOUSE;
					input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // 左鍵按下
					SendInput(1, &input, sizeof(INPUT));

					// 等待一段時間
					std::this_thread::sleep_for(std::chrono::milliseconds(1/*10*/));

					input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // 左鍵釋放
					SendInput(1, &input, sizeof(INPUT));
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}).detach();
}

void AutoMouseClicker::Stop()
{
	_starting = false;
}