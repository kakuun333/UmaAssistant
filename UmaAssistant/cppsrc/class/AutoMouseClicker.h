#pragma once

// STL
#include <thread>

// Windows API
#include <Windows.h>

// class
#include "Config.h"
#include <singleton_mutex.hpp>

class AutoMouseClicker : public SingletonMutex<AutoMouseClicker>
{
private:
	static bool _starting;
public:
	void Start();
	void Stop();
};