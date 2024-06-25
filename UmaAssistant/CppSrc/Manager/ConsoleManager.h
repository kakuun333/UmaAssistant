#pragma once

// STL
#include <cstdio>


// Windows API
#include <Windows.h>

// include
#include <singleton_mutex.hpp>


#include <Util/CharacterConvert.h>
#include <Global/form.h>
#include <Global/path.h>


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

