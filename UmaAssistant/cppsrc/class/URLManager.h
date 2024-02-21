#pragma once

#include <string>

class URLManager
{
private:
	URLManager() {}

	static URLManager* _instance;


	// �^�ը�ơA�Ω�B�z�����쪺�ƾ�
	static size_t _WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);

public:
	static URLManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new URLManager();
		}

		return _instance;
	}


	std::string GetResponseByUrl(std::string url);

};

