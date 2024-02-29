#include "WebViewManager.h"


#pragma region choiceWebView2
System::Void WebViewManager::CreateChoice(System::String^ choice_name, System::String^ choice_effect)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"createChoice", gcnew array<System::Object^>{choice_name, choice_effect});
}
System::Void WebViewManager::SetGameServer(int gameServer)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"setGameServer", gcnew array<System::Object^>{gameServer});
}
System::Void WebViewManager::SetJpServerLanguage(int jpServerLangType)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"setJpServerLanguage", gcnew array<System::Object^>{jpServerLangType});
}
System::Void WebViewManager::ChangeEventOwner(System::String^ text)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"changeEventOwner", gcnew array<System::Object^>{text});
}
System::Void WebViewManager::ChangeEventName(System::String^ text)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"changeEventName", gcnew array<System::Object^>{text});
}
System::Void WebViewManager::ChangeChoiceHtmlLanguage(int softwareLangType)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"changeChoiceHtmlLanguage", gcnew array<System::Object^>{softwareLangType});
}
System::Void WebViewManager::CleanChoiceTable()
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"cleanChoiceTable", gcnew array<System::Object^>{});
}
System::Void WebViewManager::UpdateSkillContent()
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"updateSkillContent", gcnew array<System::Object^>{});
}
System::Void WebViewManager::HideSkillHintContent()
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->choiceWebView2,
		"hideSkillHintContent", gcnew array<System::Object^>{});
}
#pragma endregion

#pragma region characterNameWebView2
System::Void WebViewManager::ChangeCharacterName(System::String^ characterName)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->characterNameWebView2,
		"changeCharacterName", gcnew array<System::Object^>{characterName});
}

System::Void WebViewManager::ChangeCharacterNameHtmlLanguage(int softwareLangType)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->characterNameWebView2,
		"changeCharacterNameHtmlLanguage", gcnew array<System::Object^>{softwareLangType});
}
#pragma endregion


#pragma region selectCharacterWebView2
System::Void WebViewManager::ChangeSelectCharacterHtmlLanguage(int softwareLangType)
{
	FormController::Instance->ExecuteFunctionAsync(global::form::umaForm->selectCharacterWebView2,
		"changeSelectCharacterHtmlLanguage", gcnew array<System::Object^>{softwareLangType});
}
#pragma endregion