//#include "form/UmaForm.h"
#include <Windows.h>
#include <fstream>

#include "global/Path.h"
#include "global/FormManager.h"
#include "global/Others.h"

#include "class/DataManager.h"
#include "class/Scanner.h"
#include "class/GameWindowFinder.h"
#include "class/FileManager.h"
#include "class/ConsoleManager.h"
#include "class/LocalServer.h"
#include "class/WebManager.h"
//#include "class/PyManager.h"
#include "class/UmaLog.h"


#include <nlohmann/json.hpp>
using json = nlohmann::json;


#include <locale>
#include <codecvt>


using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Reflection;



[STAThreadAttribute]
int main(array<String^>^ args)
{
	// 初始化 config
	global::config->Update();


#pragma region 初始化 Console
	/*
	* 如果 DebugMode 有開啟就創建 Console
	*/
	if (global::config->DebugMode == true)
	{
		ConsoleManager::GetInstance()->Enable();
	}
#pragma endregion
#pragma region 初始化字型
	// 加載字型
	AddFontResourceW(utility::string2wstring(global::path::std_MochiyPopOne).c_str());
#pragma endregion


	// 初始化 Scanner
	Scanner::InitOcrJpn();
	Scanner::InitOcrTw();
	Scanner::InitOcrEng();

	// 初始化 DataManager
	DataManager::InitEventDataJson();

	// 初始化 python
	//PyManager::GetInstance()->Init();


#pragma region 啟動本地伺服器
	System::String^ port = utility::stdStr2system(global::config->LocalServer["Port"]);
	LocalServer::Instance->Start(port);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
#pragma endregion
#pragma region 初始化 Form
	UmaAssistant::UmaForm^ umaForm = gcnew UmaAssistant::UmaForm();
	UmaAssistant::PreviewForm^ previewForm = gcnew UmaAssistant::PreviewForm();
	UmaAssistant::SettingsForm^ settingsForm = gcnew UmaAssistant::SettingsForm();

	// FormManager
	global::form::umaForm = umaForm;
	global::form::previewForm = previewForm;
	global::form::settingsForm = settingsForm;
#pragma endregion
#pragma region 初始化 checkBox
	/*
	* 不知道為什麼放在 SettingsForm 的構造函數裡面 nlohmann::json 會報錯
	* 所以在這裡初始化
	*/

	/*
	*  初始化 CheckBox
	*/

	switch (global::config->DebugMode)
	{
	case true:
		global::form::settingsForm->debugMode_checkBox->Checked = global::config->DebugMode;
		global::form::settingsForm->update_event_data_jp_btn1->Visible = global::config->DebugMode;
		global::form::settingsForm->update_skill_data_jp_btn1->Visible = global::config->DebugMode;
		break;
	case false:
		global::form::settingsForm->debugMode_checkBox->Checked = global::config->DebugMode;
		global::form::settingsForm->update_event_data_jp_btn1->Visible = global::config->DebugMode;
		global::form::settingsForm->update_skill_data_jp_btn1->Visible = global::config->DebugMode;
		break;
	}

	switch (global::config->AlwaysOnTop)
	{
	case true:
		global::form::settingsForm->alwaysOnTop_checkBox->Checked = global::config->AlwaysOnTop;
		break;
	case false:
		global::form::settingsForm->alwaysOnTop_checkBox->Checked = global::config->AlwaysOnTop;
		break;
	}

	switch (global::config->OutputLogFile)
	{
	case true:
		global::form::settingsForm->outputLogFile_checkBox->Checked = global::config->OutputLogFile;
		break;
	case false:
		global::form::settingsForm->outputLogFile_checkBox->Checked = global::config->OutputLogFile;
		break;
	}
#pragma endregion

#pragma region 初始化 GameWindowFinder
	/*
	* 初始化 UmaForm 之後才可以初始化 GameWindowFinder
	* 因為 WindowFinder 需要與 UmaForm 的物件互動
	*/
	GameWindowFinder::GetInstance()->CreateFindGameWindowThread();
#pragma endregion

#pragma region 初始化語言
	switch (global::config->SoftwareLanguage)
	{
	case static_cast<int>(GameServerType::JP):
		global::form::settingsForm->ChangeSoftwareLanguage(SoftwareLanguageType::JP);
		break;

	case static_cast<int>(GameServerType::TW):
		global::form::settingsForm->ChangeSoftwareLanguage(SoftwareLanguageType::TW);
		break;
	}
#pragma endregion


	Application::Run(umaForm); // 啟動主要的 Form (UmaForm)


#pragma region 釋放資源
	// 中止 LocalServer
	LocalServer::Instance->Stop();

	ConsoleManager::GetInstance()->Disable();

	RemoveFontResourceW(utility::string2wstring(global::path::std_MochiyPopOne).c_str());


#pragma endregion
	return 0;
}