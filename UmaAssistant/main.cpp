// STL
#include <fstream>
#include <locale>
#include <codecvt>
#include <filesystem>
namespace fs = std::filesystem;

// Windows API
#include <Windows.h>

// 3rdparty
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// class
#include "class/DataManager.h"
#include "class/Scanner.h"
#include "class/GameWindowFinder.h"
#include "class/FileManager.h"
#include "class/ConsoleManager.h"
#include "class/Config.h"
#include "class/UmaLog.h"

// ref class
#include "class/ref/LocalServer.h"

// global
#include "global/form.h"

// singleton
//#include "test.h"	

// .NET
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Reflection;

[STAThreadAttribute]
int main(array<String^>^ args)
{
#pragma region 初始化 CSharp Runtime 路徑
	AppDomain^ currentDomain = AppDomain::CurrentDomain;
	currentDomain->AppendPrivatePath("CSharpRuntime");
#pragma endregion
#pragma region 初始化 config
	Config::GetInstance()->Update();
#pragma endregion
#pragma region 初始化 Console
	/*
	* 如果 DebugMode 有開啟就創建 Console
	*/
	if (Config::GetInstance()->DebugMode == true)
	{
		ConsoleManager::GetInstance()->Enable();
	}
#pragma endregion
#pragma region 初始化字型
	// 加載字型
	AddFontResourceW(util::string2wstring(global::path::std_MochiyPopOne).c_str());
#pragma endregion
#pragma region 初始化 Scanner
	Scanner::InitOcrJpn();
	Scanner::InitOcrTw();
	Scanner::InitOcrEng();
#pragma endregion
#pragma region 初始化 DataManager
	DataManager::GetInstance()->InitEventDataJson();
#pragma endregion
#pragma region 啟動本地伺服器
	System::String^ port = util::stdStr2system(Config::GetInstance()->LocalServer["Port"]);
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
#pragma region 初始化 CheckBox
	/*
	* 不知道為什麼放在 SettingsForm 的構造函數裡面 nlohmann::json 會報錯
	* 所以在這裡初始化
	*/
	// DebugMode
	switch (Config::GetInstance()->DebugMode)
	{
	case true:
		global::form::settingsForm->debugMode_checkBox->Checked = Config::GetInstance()->DebugMode;
		global::form::settingsForm->update_event_data_jp_btn1->Visible = Config::GetInstance()->DebugMode;
		global::form::settingsForm->update_skill_data_jp_btn1->Visible = Config::GetInstance()->DebugMode;
		break;
	case false:
		global::form::settingsForm->debugMode_checkBox->Checked = Config::GetInstance()->DebugMode;
		global::form::settingsForm->update_event_data_jp_btn1->Visible = Config::GetInstance()->DebugMode;
		global::form::settingsForm->update_skill_data_jp_btn1->Visible = Config::GetInstance()->DebugMode;
		break;
	}

	// AlwaysOnTop
	switch (Config::GetInstance()->AlwaysOnTop)
	{
	case true:
		global::form::settingsForm->alwaysOnTop_checkBox->Checked = Config::GetInstance()->AlwaysOnTop;
		break;
	case false:
		global::form::settingsForm->alwaysOnTop_checkBox->Checked = Config::GetInstance()->AlwaysOnTop;
		break;
	}

	// OutputLogFile
	switch (Config::GetInstance()->OutputLogFile)
	{
	case true:
		global::form::settingsForm->outputLogFile_checkBox->Checked = Config::GetInstance()->OutputLogFile;
		break;
	case false:
		global::form::settingsForm->outputLogFile_checkBox->Checked = Config::GetInstance()->OutputLogFile;
		break;
	}

	// DiscordRPC
	switch (Config::GetInstance()->DiscordRPC)
	{
	case true:
		global::form::settingsForm->discordRpc_checkBox->Checked = Config::GetInstance()->DiscordRPC;
		break;
	case false:
		global::form::settingsForm->discordRpc_checkBox->Checked = Config::GetInstance()->DiscordRPC;
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
	switch (Config::GetInstance()->SoftwareLanguage)
	{
	case static_cast<int>(GameServerType::JP):
		global::form::settingsForm->ChangeSoftwareLanguage(SoftwareLanguageType::JP);
		break;

	case static_cast<int>(GameServerType::TW):
		global::form::settingsForm->ChangeSoftwareLanguage(SoftwareLanguageType::TW);
		break;
	}
#pragma endregion
#pragma region 運行主要的 Form
	Application::Run(umaForm); // 啟動主要的 Form (UmaForm)
#pragma endregion
#pragma region 釋放資源
	// 中止 LocalServer
	LocalServer::Instance->Stop();
	ConsoleManager::GetInstance()->Disable();
	RemoveFontResourceW(util::string2wstring(global::path::std_MochiyPopOne).c_str());
#pragma endregion

	return 0;
}