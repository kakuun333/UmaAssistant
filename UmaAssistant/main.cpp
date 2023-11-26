//#include "form/UmaForm.h"
#include <Windows.h>

#include "global/Path.h"
#include "global/FormManager.h"
#include "class/Scanner.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThreadAttribute]
int main(array<String^>^ args)
{
	Scanner::InitOcrJpn();

	SetConsoleOutputCP(CP_UTF8); // 設定控制台輸出字碼頁為 UTF8 ，這樣日文字才不會變亂碼。

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

#pragma region 初始化 Form
	UmaAssistant::UmaForm^ umaForm = gcnew UmaAssistant::UmaForm();
	UmaAssistant::SettingsForm^ settingsForm = gcnew UmaAssistant::SettingsForm();
	UmaAssistant::PreviewForm^ previewForm = gcnew UmaAssistant::PreviewForm();

	// FormManager
	global::form::umaForm = umaForm;
	global::form::settingsForm = settingsForm;
	global::form::previewForm = previewForm;
#pragma endregion


	Application::Run(umaForm); // 啟動主要的 Form

	return 0;
}