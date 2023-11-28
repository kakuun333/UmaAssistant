#pragma once

#include <map>
#include "../enum/GameWindowType.h"


class WindowFinder
{
private:
	WindowFinder() {}

	static WindowFinder* _instance;

	static HWND _currentGameWindow;

	static std::map<GameWindowType, LPCWSTR> _gameWindowDict;

public:
	static WindowFinder* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new WindowFinder();
		}
		return _instance;
	}

	void CreateFindGameWindowThread();

	inline HWND GetCurrentGameWindow()
	{
		return _currentGameWindow;
	}
};

