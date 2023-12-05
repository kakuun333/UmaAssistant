#pragma once
class ConsoleManager
{
private:
	ConsoleManager() {}

	static ConsoleManager* _instance;

	static bool _isExist;

	static BOOL _CtrlHandler(DWORD fdwCtrlType);
public:
	static ConsoleManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new ConsoleManager();
		}
		return _instance;
	}

	void Enable();

	void Disable();

	inline bool IsExist()
	{
		return _isExist;
	}
};

