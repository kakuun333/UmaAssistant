//#include "form/UmaForm.h"
#include <Windows.h>

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


#include <nlohmann/json.hpp>
using json = nlohmann::json;


#include <locale>
#include <codecvt>

using namespace System;
using namespace System::Windows::Forms;




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

	// 加載字型
	AddFontResourceW(utility::string2wstring(global::path::std_MochiyPopOne).c_str());



	// 初始化 Scanner
	Scanner::InitOcrJpn();
	Scanner::InitOcrTw();

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
	UmaAssistant::SettingsForm^ settingsForm = gcnew UmaAssistant::SettingsForm();
	UmaAssistant::PreviewForm^ previewForm = gcnew UmaAssistant::PreviewForm();

	// FormManager
	global::form::umaForm = umaForm;
	global::form::settingsForm = settingsForm;
	global::form::previewForm = previewForm;
#pragma endregion
#pragma region 初始化 SettingsForm 的 debugMode_checkBox
	/*
	* 不知道為什麼放在 SettingsForm 的構造函數裡面 nlohmann::json 會報錯
	* 所以在這裡初始化
	*/
	if (global::config->DebugMode == true)
		global::form::settingsForm->debugMode_checkBox->Checked = true;
	else
		global::form::settingsForm->debugMode_checkBox->Checked = false;
#pragma endregion

#pragma region 初始化 GameWindowFinder
	/*
	* 初始化 UmaForm 之後才可以初始化 GameWindowFinder
	* 因為 WindowFinder 需要與 UmaForm 的物件互動
	*/
	GameWindowFinder::GetInstance()->CreateFindGameWindowThread();
#pragma endregion


	Application::Run(umaForm); // 啟動主要的 Form (UmaForm)



#pragma region 釋放資源
	// 中止 LocalServer
	LocalServer::Instance->Stop();

	// 卸載字型
	RemoveFontResourceW(utility::string2wstring(global::path::std_MochiyPopOne).c_str());
#pragma endregion
	return 0;
}