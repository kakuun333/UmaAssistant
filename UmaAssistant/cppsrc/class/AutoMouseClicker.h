#pragma once

// STL
#include <thread>

// Windows API
#include <Windows.h>

// class
#include "Config.h"

// global
//#include "../global/global.h"

class AutoMouseClicker
{
private:
	AutoMouseClicker() {}

	static AutoMouseClicker* _instance;

	static bool _starting;
public:
	static AutoMouseClicker* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new AutoMouseClicker();
		}
		return _instance;
	}

	void Start();

	void Stop();
};