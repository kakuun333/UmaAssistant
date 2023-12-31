#pragma once

#include <map>
#include "../enum/GameWindowType.h"


const std::string NULL_GAME_WINDOW_NAME = "NULL_GAME_WINDOW_NAME_UMA_ASSISTANT";

class GameWindowFinder
{
private:
	GameWindowFinder() {}

	static GameWindowFinder* _instance;

	static HWND _currentGameWindow;
	static std::string _currentGameWindowName;

	static std::map<std::string, HWND> _windowDict;

public:
	static GameWindowFinder* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new GameWindowFinder();
		}
		return _instance;
	}

	void EnumWindow();

	void CreateFindGameWindowThread();

	inline std::map<std::string, HWND> GetWindowDict()
	{
		return _windowDict;
	}

	inline void SetCurrentGameWindow(std::string windowName)
	{
		_currentGameWindow = _windowDict[windowName];
	}

	inline HWND GetCurrentGameWindow()
	{
		return _currentGameWindow;
	}

	inline void SetCurrentGameWindowName(std::string windowName)
	{
		_currentGameWindowName = windowName;
	}

	inline std::string GetCurrentGameWindowName()
	{
		return _currentGameWindowName;
	}
};

