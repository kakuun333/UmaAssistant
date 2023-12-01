#pragma once

#include <string>

class WebManager
{
private:
	WebManager() {}

	static WebManager* _instance;

public:
	static WebManager* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new WebManager();
		}
		return _instance;
	}

	void CreateChoice(System::String^ title, System::String^ effect);
	void ChangeEventOwner(System::String^ text);
	void ChangeEventTitle(System::String^ text);
	void CleanChoiceTable();
	void UpdateSkillContent();
	void HiddenSkillContent();

	void ChangeCharacterName(System::String^ characterName);

	void ChangeSkillGameServer(System::String^ gameServer);
};

