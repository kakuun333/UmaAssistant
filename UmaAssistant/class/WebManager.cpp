#include "../stdafx.h"

WebManager* WebManager::_instance = nullptr;


// ========== СhoiceWebBrowser ========== //
void WebManager::CreateChoice(System::String^ choice_name, System::String^ choice_effect)
{
	array<Object^>^ param = gcnew array<Object^> { choice_name, choice_effect };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "createChoice", param);
}

void WebManager::ChangeEventOwner(System::String^ text)
{
	array<Object^>^ param = gcnew array<Object^> { text };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "changeEventOwner", param);
}
void WebManager::ChangeEventName(System::String^ text)
{
	array<Object^>^ param = gcnew array<Object^> { text };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "changeEventName", param);
}

void WebManager::CleanChoiceTable()
{
	array<Object^>^ param = gcnew array<Object^> { };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "cleanChoiceTable", param);
}

void WebManager::ChangeChoiceHtmlLanguage(int softwareLangType)
{
	array<Object^>^ param = gcnew array<Object^> { softwareLangType };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "changeChoiceHtmlLanguage", param);
}

void WebManager::UpdateSkillContent()
{
	array<Object^>^ param = gcnew array<Object^> { };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "updateSkillContent", param);
}

void WebManager::HideSkillContent()
{
	array<Object^>^ param = gcnew array<Object^> { };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "hideSkillHintContent", param);
}

void WebManager::SetGameServer(int gameServer)
{
	array<Object^>^ param = gcnew array<Object^> { gameServer };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "setGameServer", param);
}

void WebManager::SetJpServerLanguage(int jpServerLangType)
{
	array<Object^>^ param = gcnew array<Object^> { jpServerLangType };
	FormController::Instance->InvokeScript(global::form::umaForm->choiceWebBrowser, "setJpServerLanguage", param);
}

// ========== CharacterNameWebBrowser ========== //
void WebManager::ChangeCharacterName(System::String^ characterName)
{
	array<Object^>^ param = gcnew array<Object^> { characterName };
	FormController::Instance->InvokeScript(global::form::umaForm->characterNameWebBrowser, "changeCharacterName", param);
}

void WebManager::ChangeCharacterNameHtmlLanguage(int softwareLangType)
{
	array<Object^>^ param = gcnew array<Object^> { softwareLangType };
	FormController::Instance->InvokeScript(global::form::umaForm->characterNameWebBrowser, "changeCharacterNameHtmlLanguage", param);
}


// ========== select_character_webBrowser ========== //
void WebManager::ChangeSelectCharacterHtmlLanguage(int softwareLangType)
{
	array<Object^>^ param = gcnew array<Object^> { softwareLangType };
	FormController::Instance->InvokeScript(global::form::umaForm->select_character_webBrowser, "changeSelectCharacterHtmlLanguage", param);
}