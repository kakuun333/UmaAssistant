#pragma once
class LuaManager
{
private:
	LuaManager() {}

	static LuaManager* _instance;

	static bool _busy;

public:
	static LuaManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new LuaManager();
		}
		return _instance;
	}

	inline void SetBusy(bool value)
	{
		_busy = value;
	}

	inline bool IsBusy()
	{
		return _busy;
	}


	void DumpEventData();

	void DumpSkillData();
};

