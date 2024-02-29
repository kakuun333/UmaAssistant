#pragma once

// STL
#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <codecvt>

// MS
#include <Windows.h>

// enum
#include "../enum/GameWindowType.h"
#include "../enum/SoftwareLanguageType.h"

// util
#include "../util/FormControl.h"

// class
#include "Config.h"
#include "DataManager.h"
#include <singleton_mutex.hpp>

// global
#include "../global/form.h"

const std::string NULL_GAME_WINDOW_NAME = "NULL_GAME_WINDOW_NAME_UMA_ASSISTANT";

class GameWindowFinder : public SingletonMutex<GameWindowFinder>
{
private:
	static HWND _currentGameWindow;
	static std::string _currentGameWindowName;

	static std::map<std::string, HWND> _windowDict;

	bool _foundGameWindow = false;

	//bool _previousFoundGameWindow = false;

public:
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

	inline bool GetFoundGameWindow()
	{
		return _foundGameWindow;
	}

	inline void SetFoundGameWindow(bool value)
	{
		_foundGameWindow = value;
	}
};

