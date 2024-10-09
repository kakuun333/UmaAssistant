#pragma once

// STL
#include <thread>

// Windows API
#include <Windows.h>

//
#include <Config.h>

// include
#include <singleton_mutex.hpp>


class MouseManager : public SingletonMutex<MouseManager>
{
private:
	bool m_Starting = false;
public:
	void Start();
	void Stop();
};