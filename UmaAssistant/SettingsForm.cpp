#include "SettingsForm.h"

// enum
#include "cppsrc/enum/SoftwareLanguageType.h"
#include "cppsrc/enum/GameServerType.h"

// class
#include "cppsrc/class/AutoMouseClicker.h"
#include "cppsrc/class/Screenshot.h"

#include "cppsrc/class/Config.h"
#include "cppsrc/class/ConsoleManager.h"
#include "cppsrc/class/DataManager.h"

// global
#include "cppsrc/global/form.h"


#using "CSharpRuntime/UmaCSharpLibrary.dll"

namespace UmaAssistant
{
	SettingsForm::SettingsForm(void)
	{
		InitializeComponent();
		//
		//TODO:  在此加入建構函式程式碼
		//

		// 註冊 FormClosing 事件
		this->FormClosing += gcnew FormClosingEventHandler(this, &SettingsForm::FormClosingHandler);

		// 初始化 TextBox 的 Text
		serverPortTextBox->Text = util::stdStr2system(Config::GetInstance()->LocalServer["Port"]);
		scanInterval_textBox->Text = System::Convert::ToString(Config::GetInstance()->ScanInterval);

		// 註冊 KeyPress 事件
		serverPortTextBox->KeyPress += gcnew KeyPressEventHandler(this, &SettingsForm::DigitOnly_TextBox_KeyPress);
		scanInterval_textBox->KeyPress += gcnew KeyPressEventHandler(this, &SettingsForm::DigitOnly_TextBox_KeyPress);

		// 註冊 TextChanged 事件
		serverPortTextBox->TextChanged += gcnew EventHandler(this, &SettingsForm::serverPortTextBox_TextChanged);
		scanInterval_textBox->TextChanged += gcnew EventHandler(this, &SettingsForm::scanInterval_textBox_TextChanged);

		//
		// 初始化 RadioButtons
		//
#pragma region 初始化 SoftwareLanguage
		switch (Config::GetInstance()->SoftwareLanguage)
		{
		case static_cast<int>(GameServerType::JP):
			software_lang_jp_radio_btn->Checked = true;
			break;

		case static_cast<int>(GameServerType::TW):
			software_lang_tw_radio_btn->Checked = true;
			break;
		}

		software_lang_jp_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::SoftwareLangRadioButtonChanged);
		software_lang_tw_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::SoftwareLangRadioButtonChanged);
#pragma endregion
#pragma region 初始化 GameServerType
		// 從 config 初始化 Checked
		switch (Config::GetInstance()->GameServer)
		{
		case static_cast<int>(GameServerType::JP):
			jp_server_radio_btn->Checked = true;
			break;
		case static_cast<int>(GameServerType::TW):
			tw_server_radio_btn->Checked = true;
			break;
		}

		// 註冊 CheckedChanged 事件
		jp_server_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameServerRadioButtonChanged);
		tw_server_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameServerRadioButtonChanged);
#pragma endregion
#pragma region 初始化 GameWindow
		// 從 config 初始化 Checked
		switch (Config::GetInstance()->GameWindow)
		{
		case static_cast<int>(GameWindowType::DMM):
			dmm_radio_btn->Checked = true;
			break;
		case static_cast<int>(GameWindowType::EMULATOR):
			emulator_radio_btn->Checked = true;
			break;
		}

		// 註冊 CheckedChanged 事件
		dmm_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameWindowRadioButtonChanged);
		emulator_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameWindowRadioButtonChanged);
#pragma endregion
#pragma region 初始化 JpServerLangType
		// 從 config 初始化 Checked
		switch (Config::GetInstance()->JpServerLang)
		{
		case static_cast<int>(JpServerLangType::JP):
			jpServerLang_jp_radio_btn->Checked = true;
			break;
		case static_cast<int>(JpServerLangType::TW):
			jpServerLang_tw_radio_btn->Checked = true;
			break;
		}

		// 註冊 CheckedChanged 事件
		jpServerLang_jp_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::JpServerLangRadioButtonChanged);
		jpServerLang_tw_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::JpServerLangRadioButtonChanged);
#pragma endregion

#pragma region 初始化 AutoMouseClick
		String^ buttonName = Enum::GetName(static_cast<System::Windows::Forms::MouseButtons>(Config::GetInstance()->AutoMouseClickKey["WinFormButton"]).GetType(),
			static_cast<System::Windows::Forms::MouseButtons>(Config::GetInstance()->AutoMouseClickKey["WinFormButton"]));

		autoMouseClickKey_textBox->Text = buttonName;


		AutoMouseClicker* autoMouseClicker = AutoMouseClicker::GetInstance();

		switch (Config::GetInstance()->AutoMouseClick)
		{
		case true:
			autoMouceClick_checkBox->Checked = true;
			autoMouseClicker->Start();
			break;
		case false:
			autoMouceClick_checkBox->Checked = false;
			autoMouseClicker->Stop();
			break;
		}
#pragma endregion
#pragma region 初始化 checkBox
		this->alwaysOnTop_checkBox->CheckedChanged += gcnew System::EventHandler(this, &SettingsForm::alwaysOnTop_checkBox_CheckedChanged);
		this->autoMouceClick_checkBox->CheckedChanged += gcnew System::EventHandler(this, &SettingsForm::autoMouceClick_checkBox_CheckedChanged);
		this->debugMode_checkBox->CheckedChanged += gcnew System::EventHandler(this, &SettingsForm::debugMode_checkBox_CheckedChanged);
		this->outputLogFile_checkBox->CheckedChanged += gcnew System::EventHandler(this, &SettingsForm::outputLogFile_checkBox_CheckedChanged);
		this->discordRpc_checkBox->CheckedChanged += gcnew System::EventHandler(this, &SettingsForm::discordRpc_checkBox_CheckedChanged);
#pragma endregion
#pragma region 初始化 DebugMode 啟動時該顯示的按鈕
		switch (Config::GetInstance()->DebugMode)
		{
		case true:
			this->test_btn->Visible = true;
			this->screenshotPreview_btn->Visible = true;
			break;
		case false:
			this->test_btn->Visible = false;
			this->screenshotPreview_btn->Visible = false;
			break;
		}
#pragma endregion
	}

#pragma region Button Click
	System::Void SettingsForm::test_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DataManager* dataManager = DataManager::GetInstance();

		/* UmaDataUpdater */
		//UmaDataUpdater::GetInstance()->Update();
		//Config::GetInstance()->WriteToJson();

		std::cout << "CLICKED TEST BUTTON" << std::endl;
	}
	System::Void SettingsForm::screenshotPreview_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Screenshot::ShowImage();
	}
	System::Void SettingsForm::default_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//this->showEnhanceSkill_checkBox->Checked = true;
		this->debugMode_checkBox->Checked = false;
		this->alwaysOnTop_checkBox->Checked = false;
		this->autoMouceClick_checkBox->Checked = false;
		this->outputLogFile_checkBox->Checked = false;
		this->discordRpc_checkBox->Checked = false;

		// SoftwareLanguage
		this->software_lang_tw_radio_btn->Checked = true;

		// GameServer
		this->jp_server_radio_btn->Checked = true;

		// GameWindow
		this->dmm_radio_btn->Checked = true;

		// JpServerLang
		this->jpServerLang_jp_radio_btn->Checked = true;

		// AutoMouseClickKey
		this->autoMouseClickKey_textBox->Text = "XButton2";
		Config::GetInstance()->AutoMouseClickKey["VK"] = VK_XBUTTON2;
		Config::GetInstance()->AutoMouseClickKey["WinFormButton"] = static_cast<int>(System::Windows::Forms::MouseButtons::XButton2);

		// ScanInterval
		this->scanInterval_textBox->Text = System::Convert::ToString(DEFAULT_SCAN_INTERVAL);

		// LocalServer
		this->serverPortTextBox->Text = util::stdStr2system(DEFAULT_LOCAL_SERVER_PORT);

		// GameWindowName
		Config::GetInstance()->GameWindowName = NULL_GAME_WINDOW_NAME;
		Config::GetInstance()->PreviousCurrentCharacterName = DEFAULT_PREVIOUS_CURRENT_CHARACTER_NAME;

		Config::GetInstance()->WriteToJson();
	}
#pragma endregion

	void SettingsForm::FormClosingHandler(Object^ sender, FormClosingEventArgs^ e)
	{
		// 取消關閉操作，避免 form 被自動釋放
		e->Cancel = true;

		// 隱藏視窗
		this->Hide();
	}

	void SettingsForm::DigitOnly_TextBox_KeyPress(Object^ sender, KeyPressEventArgs^ e)
	{
		// 允許數字、退格鍵和刪除鍵
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 8 && e->KeyChar != 127)
		{
			e->Handled = true; // 阻止不允許的字符輸入
		}
	}

	void SettingsForm::serverPortTextBox_TextChanged(Object^ sender, EventArgs^ e)
	{
		TextBox^ textbox = dynamic_cast<TextBox^>(sender);

		if (textbox->Text->Length >= 4)
		{
			Config::GetInstance()->LocalServer["Port"] = util::systemStr2std(textbox->Text);

			Config::GetInstance()->WriteToJson();
		}
	}

	void SettingsForm::scanInterval_textBox_TextChanged(Object^ sender, EventArgs^ e)
	{
		TextBox^ textbox = dynamic_cast<TextBox^>(sender);

		if (textbox->Text->Length >= 1)
		{
			Config::GetInstance()->ScanInterval = System::Convert::ToInt32(textbox->Text);

			Config::GetInstance()->WriteToJson();
		}
	}

	void SettingsForm::GameServerRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);


		if (radioButton != nullptr && radioButton->Checked)
		{
			// 如果 RadioButton 被選中
			if (radioButton == tw_server_radio_btn)
			{
				Config::GetInstance()->GameServer = static_cast<int>(GameServerType::TW);
				WebViewManager::Instance->SetGameServer(static_cast<int>(GameServerType::TW));
			}
			else if (radioButton == jp_server_radio_btn)
			{
				Config::GetInstance()->GameServer = static_cast<int>(GameServerType::JP);
				WebViewManager::Instance->SetGameServer(static_cast<int>(GameServerType::JP));
			}
		}

		Config::GetInstance()->WriteToJson();
	}

	void SettingsForm::JpServerLangRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);


		if (radioButton != nullptr && radioButton->Checked)
		{
			// 如果 RadioButton 被選中
			if (radioButton == jpServerLang_tw_radio_btn)
			{
				Config::GetInstance()->JpServerLang = static_cast<int>(GameServerType::TW);
				WebViewManager::Instance->SetJpServerLanguage(static_cast<int>(GameServerType::TW));
			}
			else if (radioButton == jpServerLang_jp_radio_btn)
			{
				Config::GetInstance()->JpServerLang = static_cast<int>(GameServerType::JP);
				WebViewManager::Instance->SetJpServerLanguage(static_cast<int>(GameServerType::JP));
			}
		}

		Config::GetInstance()->WriteToJson();
	}

	void SettingsForm::GameWindowRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);

		if (radioButton != nullptr && radioButton->Checked)
		{
			// 如果 RadioButton 被選中
			if (radioButton == dmm_radio_btn)
			{
				Config::GetInstance()->GameWindow = static_cast<int>(GameWindowType::DMM);
			}
			else if (radioButton == emulator_radio_btn)
			{
				Config::GetInstance()->GameWindow = static_cast<int>(GameWindowType::EMULATOR);
			}
		}

		Config::GetInstance()->WriteToJson();
	}

	void SettingsForm::TraverseControls(Control^ control, array<System::String^>^ sys_str_arr)
	{
		System::String^ controlName = sys_str_arr[0];
		System::String^ controlTransText = sys_str_arr[1];

		for each (Control^ childControl in control->Controls)
		{
			if (controlName == childControl->Name)
			{
				childControl->Text = controlTransText;
			}

			// 如果控制元件還有子控制元件，遞迴遍歷
			if (childControl->Controls->Count > 0)
			{
				this->TraverseControls(childControl, sys_str_arr);
			}
		}
	}

	void SettingsForm::ChangeSoftwareLanguage(SoftwareLanguageType langType)
	{
		FileManager* fileManager = FileManager::GetInstance();
		json langData = fileManager->ReadJson(global::path::std_umaMisc + "\\software_lang.json");

		switch (static_cast<int>(langType))
		{
		case static_cast<int>(SoftwareLanguageType::JP):
			for (json::iterator it = langData["jp"].begin(); it != langData["jp"].end(); ++it)
			{
				std::string form_obj_name = it.key();
				std::string trans_name = it.value().get<std::string>();

				array<System::String^>^ sys_str_arr =
				{
					util::stdStr2system(form_obj_name),
					util::stdStr2system(trans_name),
				};

				this->TraverseControls(this, sys_str_arr);
				this->TraverseControls(global::form::umaForm, sys_str_arr);
				this->TraverseControls(global::form::previewForm, sys_str_arr);
			}
			break;
		case static_cast<int>(SoftwareLanguageType::TW):
			for (json::iterator it = langData["tw"].begin(); it != langData["tw"].end(); ++it)
			{
				std::string form_obj_name = it.key();
				std::string trans_name = it.value().get<std::string>();

				array<System::String^>^ sys_str_arr =
				{
					util::stdStr2system(form_obj_name),
					util::stdStr2system(trans_name),
				};

				this->TraverseControls(this, sys_str_arr);
				this->TraverseControls(global::form::umaForm, sys_str_arr);
				this->TraverseControls(global::form::previewForm, sys_str_arr);
			}
			break;
		}
	}

	void SettingsForm::SoftwareLangRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);

		if (_changingSoftwareLang)
		{
			radioButton->Checked = !radioButton->Checked;
			return;
		}
		else
		{
			_changingSoftwareLang = true;
		}
		
		if (radioButton != nullptr && radioButton->Checked)
		{
			// 如果 RadioButton 被選中
			if (radioButton == software_lang_jp_radio_btn)
			{
				Config::GetInstance()->SoftwareLanguage = static_cast<int>(SoftwareLanguageType::JP);

				this->ChangeSoftwareLanguage(SoftwareLanguageType::JP);

				WebViewManager::Instance->ChangeCharacterNameHtmlLanguage(static_cast<int>(SoftwareLanguageType::JP));
				WebViewManager::Instance->ChangeChoiceHtmlLanguage(static_cast<int>(SoftwareLanguageType::JP));
				WebViewManager::Instance->ChangeSelectCharacterHtmlLanguage(static_cast<int>(SoftwareLanguageType::JP));
			}
			else if (radioButton == software_lang_tw_radio_btn)
			{
				Config::GetInstance()->SoftwareLanguage = static_cast<int>(SoftwareLanguageType::TW);

				this->ChangeSoftwareLanguage(SoftwareLanguageType::TW);

				WebViewManager::Instance->ChangeCharacterNameHtmlLanguage(static_cast<int>(SoftwareLanguageType::TW));
				WebViewManager::Instance->ChangeChoiceHtmlLanguage(static_cast<int>(SoftwareLanguageType::TW));
				WebViewManager::Instance->ChangeSelectCharacterHtmlLanguage(static_cast<int>(SoftwareLanguageType::TW));
			}
		}

		_changingSoftwareLang = false;

		Config::GetInstance()->WriteToJson();
	}

	void SettingsForm::debugMode_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ConsoleManager* consoleManager = ConsoleManager::GetInstance();


		if (debugMode_checkBox->Checked)
		{
			Config::GetInstance()->DebugMode = true;
			global::form::settingsForm->test_btn->Visible = true;
			global::form::settingsForm->screenshotPreview_btn->Visible = true;

			consoleManager->Enable();
		}
		else
		{
			Config::GetInstance()->DebugMode = false;
			global::form::settingsForm->test_btn->Visible = false;
			global::form::settingsForm->screenshotPreview_btn->Visible = false;

			consoleManager->Disable();
		}


		Config::GetInstance()->WriteToJson();
	}

	void SettingsForm::autoMouceClick_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CheckBox^ checkbox = dynamic_cast<CheckBox^>(sender);
		AutoMouseClicker* autoMouseClicker = AutoMouseClicker::GetInstance();

		if (checkbox->Checked)
		{
			autoMouseClicker->Start();
			Config::GetInstance()->AutoMouseClick = checkbox->Checked;
		}
		else
		{
			autoMouseClicker->Stop();
			Config::GetInstance()->AutoMouseClick = checkbox->Checked;
		}

		// config
		Config::GetInstance()->WriteToJson();
	}

	void SettingsForm::alwaysOnTop_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CheckBox^ checkbox = dynamic_cast<CheckBox^>(sender);

		if (checkbox->Checked)
		{
			global::form::umaForm->TopMost = checkbox->Checked;
			global::form::previewForm->TopMost = checkbox->Checked;
			this->TopMost = checkbox->Checked;

			// config
			Config::GetInstance()->AlwaysOnTop = checkbox->Checked;
		}
		else
		{
			global::form::umaForm->TopMost = checkbox->Checked;
			global::form::previewForm->TopMost = checkbox->Checked;
			this->TopMost = checkbox->Checked;

			// config
			Config::GetInstance()->AlwaysOnTop = checkbox->Checked;
		}

		Config::GetInstance()->WriteToJson();
	}

	void SettingsForm::outputLogFile_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CheckBox^ checkbox = dynamic_cast<CheckBox^>(sender);

		if (checkbox->Checked)
		{
			Config::GetInstance()->OutputLogFile = true;
			UmaLog::init(global::path::std_UmaTemp + "\\UmaLog.txt");
		}
		else
		{
			Config::GetInstance()->OutputLogFile = false;
			UmaLog::close();
		}

		Config::GetInstance()->WriteToJson();
	}

	void SettingsForm::discordRpc_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CheckBox^ checkbox = dynamic_cast<CheckBox^>(sender);

		if (checkbox->Checked)
		{
			Config::GetInstance()->DiscordRPC = true;

			// 更新 DiscordRPC
			UmaCSharp::UmaDiscordManager::Instance->SetPresence(
				Config::GetInstance()->GameServer,
				Config::GetInstance()->SoftwareLanguage,
				util::stdStr2system(DataManager::GetInstance()->GetCurrentCharacter())
			);
			
		}
		else
		{
			Config::GetInstance()->DiscordRPC = false;

			// 更新 DiscordRPC
			UmaCSharp::UmaDiscordManager::Instance->Deinitialize();
		}

		Config::GetInstance()->WriteToJson();
	}

	System::Void SettingsForm::update_event_data_jp_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//LuaManager* luaManager = LuaManager::GetInstance();

		//if (!luaManager->IsBusy())
		//	luaManager->DumpEventData();
	}

	System::Void SettingsForm::update_skill_data_jp_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//LuaManager* luaManager = LuaManager::GetInstance();

		//if (!luaManager->IsBusy())
		//	luaManager->DumpSkillData();
	}

	System::Void SettingsForm::minimize_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
	}

	System::Void SettingsForm::close_form_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}

	System::Void SettingsForm::SettingsFormMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		draggingForm = true;
		dragOffset.X = e->X;
		dragOffset.Y = e->Y;
	}

	System::Void SettingsForm::SettingsFormMouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		draggingForm = false;
	}

	System::Void SettingsForm::SettingsFormMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (draggingForm)
		{
			System::Drawing::Point currentFormPos = PointToScreen(System::Drawing::Point(e->X, e->Y));
			this->Location = System::Drawing::Point(currentFormPos.X - dragOffset.X, currentFormPos.Y - dragOffset.Y);
		}
	}

	System::Void SettingsForm::autoMouseClickKey_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
	{
		//String^ buttonName = Enum::GetName(e->KeyCode.GetType(), e->KeyCode);

		//this->autoMouseClickKey_textBox->Text = buttonName;

		//Config::GetInstance()->AutoMouseClickKey = (int)e->KeyCode;

		//Config::GetInstance()->WriteToJson();
	}

	System::Void SettingsForm::autoMouseClickKey_textBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		String^ buttonName = Enum::GetName(e->Button.GetType(), e->Button);
		this->autoMouseClickKey_textBox->Text = buttonName;

		//
		// https://learn.microsoft.com/zh-tw/windows/win32/inputdev/virtual-key-codes
		//
		switch (e->Button)
		{
		case Windows::Forms::MouseButtons::Left:
			Config::GetInstance()->AutoMouseClickKey["VK"] = VK_LBUTTON;
			//this->autoMouseClickKey_textBox->Text = "Left";
			break;
		case Windows::Forms::MouseButtons::Right:
			Config::GetInstance()->AutoMouseClickKey["VK"] = VK_RBUTTON;
			//this->autoMouseClickKey_textBox->Text = "Right";
			break;
		case Windows::Forms::MouseButtons::Middle:
			Config::GetInstance()->AutoMouseClickKey["VK"] = VK_MBUTTON;
			//this->autoMouseClickKey_textBox->Text = "Middle";
			break;
		case Windows::Forms::MouseButtons::XButton1:
			Config::GetInstance()->AutoMouseClickKey["VK"] = VK_XBUTTON1;
			//this->autoMouseClickKey_textBox->Text = "XButton1";
			break;
		case Windows::Forms::MouseButtons::XButton2:
			Config::GetInstance()->AutoMouseClickKey["VK"] = VK_XBUTTON2;
			//this->autoMouseClickKey_textBox->Text = "XButton2";
			break;
		default:
			Config::GetInstance()->AutoMouseClickKey["VK"] = 0x07; // 保留
		
			//this->autoMouseClickKey_textBox->Text = "Unknown";
			break;
		}

		Config::GetInstance()->AutoMouseClickKey["WinFormButton"] = static_cast<int>(e->Button);

		// config
		Config::GetInstance()->WriteToJson();
	}
}