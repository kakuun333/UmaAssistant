#pragma once
class PyManager
{
private:
	PyManager() {}

	static PyManager* _instance;

	static bool _inited;

	static bool _busy;

public:
	static PyManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new PyManager();
		}
		return _instance;
	}

	void Init();

	inline void SetBusy(bool value)
	{
		_busy = value;
	}

	inline bool IsBusy()
	{
		return _busy;
	}

	void event_data_jp2tw();
};

