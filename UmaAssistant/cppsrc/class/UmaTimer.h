#pragma once

// STL
#include <chrono>

class UmaTimer
{
private:
	std::chrono::system_clock::time_point _startTime;

public:
	UmaTimer() {}

	// �}�l�p��
	void Start();

	// ����p�ɡA�æ^�Ǹg�L���ɶ�
	double Stop();
};

