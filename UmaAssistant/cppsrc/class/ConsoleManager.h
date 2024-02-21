#pragma once

// STL
#include <cstdio>

// Windows API
#include <Windows.h>
//#include <consoleapi.h>
//#include <consoleapi2.h>
//#include <wingdi.h>
//#include <WinNls.h>
//#include <processenv.h>
//#include <WinBase.h>

// util
#include "../util/CharacterConvert.h"

// global
#include "../global/form.h"
#include "../global/path.h"


class ConsoleManager
{
private:
	ConsoleManager() {}

	static ConsoleManager* _instance;

	static bool _isExist;

	static BOOL _CtrlHandler(DWORD fdwCtrlType);
public:
	static ConsoleManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new ConsoleManager();
		}
		return _instance;
	}

	void Enable();

	void Disable();

	inline bool IsExist()
	{
		return _isExist;
	}
};

