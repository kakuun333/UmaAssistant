#include "../stdafx.h"

AutoMouseClicker* AutoMouseClicker::_instance = nullptr;

bool AutoMouseClicker::_starting = false;

void AutoMouseClicker::Start()
{
	// &global::config->AutoMouseClickKey;

	_starting = true;
	
	std::thread([=]()
		{
			while (_starting)
			{
				if (GetAsyncKeyState(global::config->AutoMouseClickKey["VK"]) & 0x8000)
				{
					INPUT input;
					input.type = INPUT_MOUSE;
					input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // ������U
					SendInput(1, &input, sizeof(INPUT));

					// ���ݤ@�q�ɶ�
					std::this_thread::sleep_for(std::chrono::milliseconds(10));

					input.mi.dwFlags = MOUSEEVENTF_LEFTUP; // ��������
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