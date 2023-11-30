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
			FileManager* fileManager = FileManager::GetInstance();

			json config = fileManager->ReadJson(global::path::std_config);

			config["LocalServer"]["Port"] = utility::systemStr2std(text);

			std::string jsonString = config.dump(2);

			fileManager->WriteJson(global::path::std_config, jsonString);
		}

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
		FileManager* fileManager = FileManager::GetInstance();
		json config = fileManager->ReadJson(global::path::std_config);
		serverPortTextBox->Text = utility::stdStr2system(config["LocalServer"]["Port"].get<std::string>());



		// ���U KeyPress �ƥ�
		serverPortTextBox->KeyPress += gcnew KeyPressEventHandler(this, &SettingsForm::serverPortTextBox_KeyPress);

		// ���U TextChanged �ƥ�
		serverPortTextBox->TextChanged += gcnew EventHandler(this, &SettingsForm::serverPortTextBox_TextChanged);
	}

	System::Void SettingsForm::debugMode_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		ConsoleManager* consoleManager = ConsoleManager::GetInstance();
		FileManager* fileManager = FileManager::GetInstance();
		json config = fileManager->ReadJson(global::path::std_config);
		if (debugMode_checkBox->Checked)
		{
			config["DebugMode"] = true;
			global::form::umaForm->test_btn->Visible = true;
			global::form::umaForm->screenshot_preview_btn->Visible = true;
			

			consoleManager->Enable();

		}
		else
		{
			config["DebugMode"] = false;
			global::form::umaForm->test_btn->Visible = false;
			global::form::umaForm->screenshot_preview_btn->Visible = false;


			consoleManager->Disable();

		}

		std::string jsonString = config.dump(2);

		fileManager->WriteJson(global::path::std_config, jsonString);
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