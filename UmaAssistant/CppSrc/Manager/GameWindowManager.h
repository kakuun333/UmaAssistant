#pragma once

// STL
#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <codecvt>

// MS
#include <Windows.h>

// Enum
#include <Enum/GameWindowType.h>
#include <Enum/SoftwareLanguageType.h>

// Util
#include <Util/FormControl.h>


#include <Config.h>

// Manager
#include <Manager/DataManager.h>

// include
#include <singleton_mutex.hpp>

// Global
#include <Global/form.h>

#using "CSharpDLL/UmaCSharpLibrary.dll"

const std::string NULL_GAME_WINDOW_NAME = "NULL_GAME_WINDOW_NAME_UMA_ASSISTANT";

class GameWindowManager : public SingletonMutex<GameWindowManager>
{
public:
	void EnumWindow();

	void CreateFindGameWindowThread();
public:
	// WindowDict
	inline std::map<std::string, HWND> GetWindowDict() { return m_WindowDict; } const

	// CurrentGameWindow
	inline HWND GetCurrentGameWindow() { return m_CurrentGameWindow; } const
	inline void SetCurrentGameWindow(const std::string& windowName) { m_CurrentGameWindow = m_WindowDict[windowName]; }

	// CurrentGameWindowName
	inline std::string GetCurrentGameWindowName() {	return m_CurrentGameWindowName;	} const
	inline void SetCurrentGameWindowName(const std::string& windowName) { m_CurrentGameWindowName = windowName; }

	// FoundGameWindow
	inline bool GetFoundGameWindow() { return m_FoundGameWindow; } const
	inline void SetFoundGameWindow(const bool& value) { m_FoundGameWindow = value; }
private:
	std::map<std::string, HWND> m_WindowDict = {};
	HWND m_CurrentGameWindow = NULL;

	/*
	* 如果用空的 std::string 的話會找到名字是空的 HWND
	* 所以使用 "NULL_GAME_WINDOW_NAME_UMA_ASSISTANT" 做代替
	*/
	std::string m_CurrentGameWindowName = NULL_GAME_WINDOW_NAME;

	bool m_FoundGameWindow = false;
};

