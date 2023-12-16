#include "../stdafx.h"





namespace UmaAssistant
{

	SettingsForm::SettingsForm(void)
	{
		InitializeComponent();
		//
		//TODO:  在此加入建構函式程式碼
		//

		WebManager* webManager = WebManager::GetInstance();


		// 更改 .resx 檔的路徑為 UmaAssistant/UmaAssistant/form
		/*System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(L"UmaAssistant.UmaAssistant.form.SettingsForm",
			System::Reflection::Assembly::GetExecutingAssembly());*/

		// 註冊 FormClosing 事件
		this->FormClosing += gcnew FormClosingEventHandler(this, &SettingsForm::FormClosingHandler);

		// 初始化 TextBox 的 Text
		serverPortTextBox->Text = utility::stdStr2system(global::config->LocalServer["Port"]);
		scanInterval_textBox->Text = System::Convert::ToString(global::config->ScanInterval);

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
		switch (global::config->SoftwareLanguage)
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
		switch (global::config->GameServer)
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
		switch (global::config->GameWindow)
		{
		case static_cast<int>(GameWindowType::DMM):
			dmm_radio_btn->Checked = true;
			break;
		case static_cast<int>(GameWindowType::BLUE_STACKS):
			blue_stacks_radio_btn->Checked = true;
			break;
		}

		// 註冊 CheckedChanged 事件
		dmm_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameWindowRadioButtonChanged);
		blue_stacks_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameWindowRadioButtonChanged);
#pragma endregion
#pragma region 初始化 JpServerLangType
		// 從 config 初始化 Checked
		switch (global::config->JpServerLang)
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
		String^ buttonName = Enum::GetName(static_cast<System::Windows::Forms::MouseButtons>(global::config->AutoMouseClickKey["WinFormButton"]).GetType(),
			static_cast<System::Windows::Forms::MouseButtons>(global::config->AutoMouseClickKey["WinFormButton"]));

		autoMouseClickKey_textBox->Text = buttonName;


		AutoMouseClicker* autoMouseClicker = AutoMouseClicker::GetInstance();

		switch (global::config->AutoMouseClick)
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
#pragma endregion
	}


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
			global::config->LocalServer["Port"] = utility::systemStr2std(textbox->Text);

			global::config->WriteToJson();
		}
	}

	void SettingsForm::scanInterval_textBox_TextChanged(Object^ sender, EventArgs^ e)
	{
		TextBox^ textbox = dynamic_cast<TextBox^>(sender);

		if (textbox->Text->Length >= 1)
		{
			global::config->ScanInterval = System::Convert::ToInt32(textbox->Text);

			global::config->WriteToJson();
		}
	}

	void SettingsForm::GameServerRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);

		WebManager* webManager = WebManager::GetInstance();

		if (radioButton != nullptr && radioButton->Checked)
		{
			// 如果 RadioButton 被選中
			if (radioButton == tw_server_radio_btn)
			{
				global::config->GameServer = static_cast<int>(GameServerType::TW);
				webManager->ChangeSkillGameServer(static_cast<int>(GameServerType::TW));
			}
			else if (radioButton == jp_server_radio_btn)
			{
				global::config->GameServer = static_cast<int>(GameServerType::JP);
				webManager->ChangeSkillGameServer(static_cast<int>(GameServerType::JP));
			}
		}

		global::config->WriteToJson();
	}

	void SettingsForm::JpServerLangRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);

		WebManager* webManager = WebManager::GetInstance();

		if (radioButton != nullptr && radioButton->Checked)
		{
			// 如果 RadioButton 被選中
			if (radioButton == jpServerLang_tw_radio_btn)
			{
				global::config->JpServerLang = static_cast<int>(GameServerType::TW);
				webManager->ChangeJpServerLang(static_cast<int>(GameServerType::TW));
			}
			else if (radioButton == jpServerLang_jp_radio_btn)
			{
				global::config->JpServerLang = static_cast<int>(GameServerType::JP);
				webManager->ChangeJpServerLang(static_cast<int>(GameServerType::JP));
			}
		}

		global::config->WriteToJson();
	}

	void SettingsForm::GameWindowRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);

		if (radioButton != nullptr && radioButton->Checked)
		{
			// 如果 RadioButton 被選中
			if (radioButton == dmm_radio_btn)
			{
				global::config->GameWindow = static_cast<int>(GameWindowType::DMM);
			}
			else if (radioButton == blue_stacks_radio_btn)
			{
				global::config->GameWindow = static_cast<int>(GameWindowType::BLUE_STACKS);
			}
		}

		global::config->WriteToJson();
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
					utility::stdStr2system(form_obj_name),
					utility::stdStr2system(trans_name),
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
					utility::stdStr2system(form_obj_name),
					utility::stdStr2system(trans_name),
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
		

		WebManager* webManager = WebManager::GetInstance();


		if (radioButton != nullptr && radioButton->Checked)
		{
			// 如果 RadioButton 被選中
			if (radioButton == software_lang_jp_radio_btn)
			{
				global::config->SoftwareLanguage = static_cast<int>(SoftwareLanguageType::JP);

				this->ChangeSoftwareLanguage(SoftwareLanguageType::JP);

				webManager->ChangeCharacterNameBrowserLang(static_cast<int>(SoftwareLanguageType::JP));
				webManager->ChangeChoiceBrowserLang(static_cast<int>(SoftwareLanguageType::JP));
			}
			else if (radioButton == software_lang_tw_radio_btn)
			{
				global::config->SoftwareLanguage = static_cast<int>(SoftwareLanguageType::TW);

				this->ChangeSoftwareLanguage(SoftwareLanguageType::TW);

				webManager->ChangeCharacterNameBrowserLang(static_cast<int>(SoftwareLanguageType::TW));
				webManager->ChangeChoiceBrowserLang(static_cast<int>(SoftwareLanguageType::TW));
			}
		}

		_changingSoftwareLang = false;

		global::config->WriteToJson();
	}

	void SettingsForm::debugMode_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ConsoleManager* consoleManager = ConsoleManager::GetInstance();


		if (debugMode_checkBox->Checked)
		{
			global::config->DebugMode = true;
			global::form::umaForm->test_btn->Visible = true;
			global::form::umaForm->screenshot_preview_btn->Visible = true;
			update_event_data_jp_btn1->Visible = true;
			update_skill_data_jp_btn1->Visible = true;

			consoleManager->Enable();
		}
		else
		{
			global::config->DebugMode = false;
			global::form::umaForm->test_btn->Visible = false;
			global::form::umaForm->screenshot_preview_btn->Visible = false;

			update_event_data_jp_btn1->Visible = false;
			update_skill_data_jp_btn1->Visible = false;


			consoleManager->Disable();
		}


		global::config->WriteToJson();
	}

	void SettingsForm::autoMouceClick_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CheckBox^ checkbox = dynamic_cast<CheckBox^>(sender);
		AutoMouseClicker* autoMouseClicker = AutoMouseClicker::GetInstance();

		if (checkbox->Checked)
		{
			autoMouseClicker->Start();
			global::config->AutoMouseClick = checkbox->Checked;
		}
		else
		{
			autoMouseClicker->Stop();
			global::config->AutoMouseClick = checkbox->Checked;
		}

		// config
		global::config->WriteToJson();
	}

	void SettingsForm::alwaysOnTop_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CheckBox^ checkbox = dynamic_cast<CheckBox^>(sender);

		if (checkbox->Checked)
		{
			global::form::umaForm->TopMost = checkbox->Checked;
			this->TopMost = checkbox->Checked;

			// config
			global::config->AlwaysOnTop = checkbox->Checked;
		}
		else
		{
			global::form::umaForm->TopMost = checkbox->Checked;
			this->TopMost = checkbox->Checked;

			// config
			global::config->AlwaysOnTop = checkbox->Checked;
		}

		global::config->WriteToJson();
	}

	void SettingsForm::outputLogFile_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		CheckBox^ checkbox = dynamic_cast<CheckBox^>(sender);

		if (checkbox->Checked)
		{
			global::config->OutputLogFile = true;
			UmaLog::init(global::path::std_UmaTemp + "\\UmaLog.txt");
		}
		else
		{
			global::config->OutputLogFile = false;
			UmaLog::close();
		}

		global::config->WriteToJson();
	}

	System::Void SettingsForm::default_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->debugMode_checkBox->Checked = false;
		this->alwaysOnTop_checkBox->Checked = false;
		this->autoMouceClick_checkBox->Checked = false;
		this->outputLogFile_checkBox->Checked = false;

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
		global::config->AutoMouseClickKey["VK"] = VK_XBUTTON2;
		global::config->AutoMouseClickKey["WinFormButton"] = static_cast<int>(System::Windows::Forms::MouseButtons::XButton2);

		// ScanInterval
		this->scanInterval_textBox->Text = System::Convert::ToString(DEFAULT_SCAN_INTERVAL);

		// LocalServer
		this->serverPortTextBox->Text = utility::stdStr2system(DEFAULT_LOCAL_SERVER_PORT);

	}

	System::Void SettingsForm::update_event_data_jp_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LuaManager* luaManager = LuaManager::GetInstance();

		if (!luaManager->IsBusy())
			luaManager->DumpEventData();
	}

	System::Void SettingsForm::update_skill_data_jp_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LuaManager* luaManager = LuaManager::GetInstance();

		if (!luaManager->IsBusy())
			luaManager->DumpSkillData();
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

		//global::config->AutoMouseClickKey = (int)e->KeyCode;

		//global::config->WriteToJson();
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
			global::config->AutoMouseClickKey["VK"] = VK_LBUTTON;
			//this->autoMouseClickKey_textBox->Text = "Left";
			break;
		case Windows::Forms::MouseButtons::Right:
			global::config->AutoMouseClickKey["VK"] = VK_RBUTTON;
			//this->autoMouseClickKey_textBox->Text = "Right";
			break;
		case Windows::Forms::MouseButtons::Middle:
			global::config->AutoMouseClickKey["VK"] = VK_MBUTTON;
			//this->autoMouseClickKey_textBox->Text = "Middle";
			break;
		case Windows::Forms::MouseButtons::XButton1:
			global::config->AutoMouseClickKey["VK"] = VK_XBUTTON1;
			//this->autoMouseClickKey_textBox->Text = "XButton1";
			break;
		case Windows::Forms::MouseButtons::XButton2:
			global::config->AutoMouseClickKey["VK"] = VK_XBUTTON2;
			//this->autoMouseClickKey_textBox->Text = "XButton2";
			break;
		default:
			global::config->AutoMouseClickKey["VK"] = 0x07; // 保留
		
			//this->autoMouseClickKey_textBox->Text = "Unknown";
			break;
		}

		global::config->AutoMouseClickKey["WinFormButton"] = static_cast<int>(e->Button);


		// config
		global::config->WriteToJson();
	}
}