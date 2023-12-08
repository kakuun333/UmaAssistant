#include "../stdafx.h"





namespace UmaAssistant
{
	void SettingsForm::FormClosingHandler(Object^ sender, FormClosingEventArgs^ e)
	{
		// ���������ާ@�A�קK form �Q�۰�����
		e->Cancel = true;

		// ���õ���
		this->Hide();
	}

	void SettingsForm::serverPortTextBox_KeyPress(Object^ sender, KeyPressEventArgs^ e)
	{
		// ���\�Ʀr�B�h����M�R����
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 8 && e->KeyChar != 127)
		{
			e->Handled = true; // ������\���r�ſ�J
		}
	}

	void SettingsForm::serverPortTextBox_TextChanged(Object^ sender, EventArgs^ e)
	{
		String^ text = serverPortTextBox->Text;
		
		if (text->Length >= 4)
		{
			global::config->LocalServer["Port"] = utility::systemStr2std(text);

			global::config->WriteToJson();
		}

	}

	void SettingsForm::GameServerRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);

		WebManager* webManager = WebManager::GetInstance();

		if (radioButton != nullptr && radioButton->Checked)
		{
			// �p�G RadioButton �Q�襤
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
			// �p�G RadioButton �Q�襤
			if (radioButton == jpServerLang_tw_radioBtn)
			{
				global::config->JpServerLang = static_cast<int>(GameServerType::TW);
				webManager->ChangeJpServerLang(static_cast<int>(GameServerType::TW));
			}
			else if (radioButton == jpServerLang_jp_radioBtn)
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
			// �p�G RadioButton �Q�襤
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


	SettingsForm::SettingsForm(void)
	{
		InitializeComponent();
		//
		//TODO:  �b���[�J�غc�禡�{���X
		//

		// ��� .resx �ɪ����|�� UmaAssistant/UmaAssistant/form
		/*System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(L"UmaAssistant.UmaAssistant.form.SettingsForm",
			System::Reflection::Assembly::GetExecutingAssembly());*/

		// ���U FormClosing �ƥ�
		this->FormClosing += gcnew FormClosingEventHandler(this, &SettingsForm::FormClosingHandler);

		// ��l�� serverPortTextBox->Text

		serverPortTextBox->Text = utility::stdStr2system(global::config->LocalServer["Port"]);

		// ���U KeyPress �ƥ�
		serverPortTextBox->KeyPress += gcnew KeyPressEventHandler(this, &SettingsForm::serverPortTextBox_KeyPress);

		// ���U TextChanged �ƥ�
		serverPortTextBox->TextChanged += gcnew EventHandler(this, &SettingsForm::serverPortTextBox_TextChanged);

		//
		// ��l�� RadioButtons
		//
#pragma region ��l�� GameServerType
		// �q config ��l�� Checked
		switch (global::config->GameServer)
		{
		case static_cast<int>(GameServerType::JP):
			jp_server_radio_btn->Checked = true;
			break;
		case static_cast<int>(GameServerType::TW):
			tw_server_radio_btn->Checked = true;
			break;
		}

		// ���U CheckedChanged �ƥ�
		jp_server_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameServerRadioButtonChanged);
		tw_server_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameServerRadioButtonChanged);
#pragma endregion
#pragma region ��l�� GameWindow
		// �q config ��l�� Checked
		switch (global::config->GameWindow)
		{
		case static_cast<int>(GameWindowType::DMM):
			dmm_radio_btn->Checked = true;
			break;
		case static_cast<int>(GameWindowType::BLUE_STACKS):
			blue_stacks_radio_btn->Checked = true;
			break;
		}

		// ���U CheckedChanged �ƥ�
		dmm_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameWindowRadioButtonChanged);
		blue_stacks_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameWindowRadioButtonChanged);
#pragma endregion
#pragma region ��l�� JpServerLangType
		// �q config ��l�� Checked
		switch (global::config->JpServerLang)
		{
		case static_cast<int>(JpServerLangType::JP):
			jpServerLang_jp_radioBtn->Checked = true;
			break;
		case static_cast<int>(JpServerLangType::TW):
			jpServerLang_tw_radioBtn->Checked = true;
			break;
		}

		// ���U CheckedChanged �ƥ�
		jpServerLang_jp_radioBtn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::JpServerLangRadioButtonChanged);
		jpServerLang_tw_radioBtn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::JpServerLangRadioButtonChanged);
#pragma endregion

#pragma region ��l�� AutoMouseClick
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
	}

	System::Void SettingsForm::debugMode_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
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

	System::Void SettingsForm::alwaysOnTop_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
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
			global::config->AutoMouseClickKey["VK"] = 0x07; // �O�d
		
			//this->autoMouseClickKey_textBox->Text = "Unknown";
			break;
		}

		global::config->AutoMouseClickKey["WinFormButton"] = static_cast<int>(e->Button);


		// config
		global::config->WriteToJson();
	}

	System::Void SettingsForm::autoMouceClick_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
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
}