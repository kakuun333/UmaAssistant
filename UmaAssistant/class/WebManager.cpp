#include "../stdafx.h"

WebManager* WebManager::_instance = nullptr;

void WebManager::CreateChoice(System::String^ title, System::String^ effect)
{
	array<Object^>^ param = gcnew array<Object^> { title, effect };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "createChoice", param);
}

void WebManager::ChangeEventOwner(System::String^ text)
{
	array<Object^>^ param = gcnew array<Object^> { text };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "changeEventOwner", param);
}
void WebManager::ChangeEventTitle(System::String^ text)
{
	array<Object^>^ param = gcnew array<Object^> { text };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "changeEventTitle", param);
}

void WebManager::CleanChoiceTable()
{
	array<Object^>^ param = gcnew array<Object^> { };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "cleanChoiceTable", param);
}

void WebManager::ChangeCharacterName(System::String^ characterName)
{
	array<Object^>^ param = gcnew array<Object^> { characterName };
	FormController::Instance->InvokeScript(global::form::umaForm->characterNameWebBrowser, "changeCharacterName", param);
}

void WebManager::UpdateSkillContent()
{
	array<Object^>^ param = gcnew array<Object^> { };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "updateSkillContent", param);
}

void WebManager::HiddenSkillContent()
{
	array<Object^>^ param = gcnew array<Object^> { };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "hiddenSkillHintContent", param);
}

void WebManager::ChangeSkillGameServer(int gameServer)
{
	array<Object^>^ param = gcnew array<Object^> { gameServer };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "changeSkillGameServer", param);
}

void WebManager::ChangeJpServerLang(int jpServerLangType)
{
	array<Object^>^ param = gcnew array<Object^> { jpServerLangType };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "changeJpServerLang", param);
}

void WebManager::ChangeCharacterNameBrowserLang(int softwareLangType)
{
	array<Object^>^ param = gcnew array<Object^> { softwareLangType };
	FormController::Instance->InvokeScript(global::form::umaForm->characterNameWebBrowser, "changeCharacterNameBrowserLang", param);
}

void WebManager::ChangeChoiceBrowserLang(int softwareLangType)
{
	array<Object^>^ param = gcnew array<Object^> { softwareLangType };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "changeChoiceBrowserLang", param);
}