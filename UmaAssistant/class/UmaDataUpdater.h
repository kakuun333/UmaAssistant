#pragma once

#include <string>

class UmaDataUpdater
{
private:
	UmaDataUpdater() {};

	static UmaDataUpdater* _instance;

	bool _updating = false;

	void _UpdateFileFormUrl(std::string filePath, std::string url);

	//std::string _RemoveHTMLTag(std::string html);
public:
	static UmaDataUpdater* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new UmaDataUpdater();
		}

		return _instance;
	}

	void Update();
};

