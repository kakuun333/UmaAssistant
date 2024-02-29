#pragma once

#include "FormController.h"
#include "../../global/form.h"

ref class WebViewManager
{
private:
	WebViewManager() {}
	WebViewManager(const WebViewManager%) { throw gcnew System::InvalidOperationException(u8"單一模式不可以有複製建構子。singleton cannot be copy-constructed"); }
	static WebViewManager _instance;

public:
	static property WebViewManager^ Instance { WebViewManager^ get() { return % _instance; } }

#pragma region choiceWebView2
	System::Void CreateChoice(System::String^ choice_name, System::String^ choice_effect);

	System::Void SetGameServer(int gameServer);
	System::Void SetJpServerLanguage(int jpServerLangType);
	System::Void ChangeEventOwner(System::String^ text);
	System::Void ChangeEventName(System::String^ text);
	System::Void ChangeChoiceHtmlLanguage(int softwareLangType);
	System::Void CleanChoiceTable();
	System::Void UpdateSkillContent();
	System::Void HideSkillHintContent();

	//void SetGameServer(int gameServer);
	//void SetJpServerLanguage(int jpServerLangType);
	//void ChangeEventOwner(System::String^ text);
	//void ChangeEventName(System::String^ text);
	//void ChangeChoiceHtmlLanguage(int softwareLangType);
	//void CleanChoiceTable();
	//void UpdateSkillContent();
	//void HideSkillContent();
#pragma endregion
#pragma region characterNameWebView2
	System::Void ChangeCharacterName(System::String^ characterName);
	System::Void ChangeCharacterNameHtmlLanguage(int softwareLangType);
#pragma endregion
#pragma region selectCharacterWebView2
	System::Void ChangeSelectCharacterHtmlLanguage(int softwareLangType);
#pragma endregion
};

