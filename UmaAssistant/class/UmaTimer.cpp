#include "UmaTimer.h"


void UmaTimer::Start()
{
	_startTime = std::chrono::system_clock::now();
}

double UmaTimer::Stop()
{
	// �O�������ɶ�
	std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();

	// �p�����ɶ��]�@��^
	std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - _startTime);

	// �N�ɶ��t�ഫ����
	double seconds = duration.count() * 1.0f / 1000;

	return seconds;
}