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