#pragma once

#include <chrono>

class UmaTimer
{
private:
	std::chrono::system_clock::time_point _startTime;

public:
	UmaTimer() {}

	void Start();

	double Stop();
};

