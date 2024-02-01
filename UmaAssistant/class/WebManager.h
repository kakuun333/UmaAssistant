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
	void ChangeEventName(System::String^ text);
	void CleanChoiceTable();
	void UpdateSkillContent();
	void HideSkillContent();

	void ChangeCharacterName(System::String^ characterName);

	void SetGameServer(int gameServer);

	void SetJpServerLanguage(int jpServerLangType);

	void ChangeCharacterNameHtmlLanguage(int softwareLangType);
	void ChangeChoiceHtmlLanguage(int softwareLangType);
	void ChangeSelectCharacterHtmlLanguage(int softwareLangType);

	//void ChangeShowEnhanceSkillData(bool boolean);
};

