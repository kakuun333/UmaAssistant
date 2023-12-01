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

		if (radioButton != nullptr && radioButton->Checked)
		{
			// �p�G RadioButton �Q�襤
			if (radioButton == tw_server_radio_btn)
			{
				global::config->GameServer = GameServerType::TW;
				//Console::WriteLine("RadioButton Checked: " + radioButton->Text);
			}
			else if (radioButton == jp_server_radio_btn)
			{
				global::config->GameServer = GameServerType::JP;
				//Console::WriteLine("RadioButton Checked: " + radioButton->Text);
			}
		}

		global::config->WriteToJson();
	}

	void SettingsForm::GameWindowRadioButtonChanged(Object^ sender, EventArgs^ e)
	{
		RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);

		FileManager* fileManager = FileManager::GetInstance();
		json config = fileManager->ReadJson(global::path::std_config);

		if (radioButton != nullptr && radioButton->Checked)
		{
			// �p�G RadioButton �Q�襤
			if (radioButton == dmm_radio_btn)
			{
				global::config->GameWindow = GameWindowType::DMM;
				//Console::WriteLine("RadioButton Checked: " + radioButton->Text);
			}
			else if (radioButton == blue_stacks_radio_btn)
			{
				global::config->GameWindow = GameWindowType::BLUE_STACKS;
				//Console::WriteLine("RadioButton Checked: " + radioButton->Text);
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
		// RadioButtons
		//
#pragma region GameServerType
		// �q config ��l�� Checked
		switch (global::config->GameServer)
		{
		case GameServerType::JP:
			jp_server_radio_btn->Checked = true;
			break;
		case GameServerType::TW:
			tw_server_radio_btn->Checked = true;
			break;
		}

		// ���U CheckedChanged �ƥ�
		jp_server_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameServerRadioButtonChanged);
		tw_server_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameServerRadioButtonChanged);
#pragma endregion
#pragma region GameWindow
		// �q config ��l�� Checked
		switch (global::config->GameWindow)
		{
		case GameWindowType::DMM:
			dmm_radio_btn->Checked = true;
			break;
		case GameWindowType::BLUE_STACKS:
			blue_stacks_radio_btn->Checked = true;
			break;
		}

		// ���U CheckedChanged �ƥ�
		dmm_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameWindowRadioButtonChanged);
		blue_stacks_radio_btn->CheckedChanged += gcnew EventHandler(this, &SettingsForm::GameWindowRadioButtonChanged);
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
			

			consoleManager->Enable();
		}
		else
		{
			global::config->DebugMode = false;
			global::form::umaForm->test_btn->Visible = false;
			global::form::umaForm->screenshot_preview_btn->Visible = false;


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
}