#pragma once

// STL
#include <cstdio>

// class
#include <singleton_mutex.hpp>

// Windows API
#include <Windows.h>

// util
#include "../util/CharacterConvert.h"

// global
#include "../global/form.h"
#include "../global/path.h"


class ConsoleManager : public SingletonMutex<ConsoleManager>
{
private:
	static bool _isExist;

	static BOOL _CtrlHandler(DWORD fdwCtrlType);
public:
	void Enable();

	void Disable();

	inline bool IsExist() { return _isExist; }
};

