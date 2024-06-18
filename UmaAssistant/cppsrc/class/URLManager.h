#pragma once

#include <string>

class URLManager
{
private:
	URLManager() {}

	static URLManager* _instance;


	// 回調函數，用於處理接收到的數據
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

