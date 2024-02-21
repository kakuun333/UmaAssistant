#include "UmaTimer.h"


void UmaTimer::Start()
{
	_startTime = std::chrono::system_clock::now();
}

double UmaTimer::Stop()
{
	// 記錄結束時間
	std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();

	// 計算執行時間（毫秒）
	std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - _startTime);

	// 將時間差轉換為秒
	double seconds = duration.count() * 1.0f / 1000;

	return seconds;
}