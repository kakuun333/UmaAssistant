#pragma once

#include <map>
#include "../enum/GameWindowType.h"


class GameWindowFinder
{
private:
	GameWindowFinder() {}

	static GameWindowFinder* _instance;

	static HWND _currentGameWindow;

	static std::map<GameWindowType, LPCWSTR> _gameWindowDict;

public:
	static GameWindowFinder* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new GameWindowFinder();
		}
		return _instance;
	}

	void CreateFindGameWindowThread();

	inline HWND GetCurrentGameWindow()
	{
		return _currentGameWindow;
	}
};

