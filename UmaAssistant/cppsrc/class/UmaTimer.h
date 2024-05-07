#pragma once

// STL
#include <chrono>

class UmaTimer
{
private:
	std::chrono::system_clock::time_point _startTime;

public:
	UmaTimer() {}

	// 開始計時
	void Start();

	// 停止計時，並回傳經過的時間
	double Stop();
};

