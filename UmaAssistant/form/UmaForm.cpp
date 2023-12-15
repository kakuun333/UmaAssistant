#include "../stdafx.h"

//#using <System.dll>
//#using <System.Net.dll>






namespace UmaAssistant
{
	void UmaForm::OnChoiceDocumentCompleted(System::Object^ sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^ e)
	{
		// 初始化 skill_displayer.js 中的 let GameServer 變數
		WebManager* webManager = WebManager::GetInstance();


		// GameServer
		switch (global::config->GameServer)
		{
		case static_cast<int>(GameServerType::JP):
			webManager->ChangeSkillGameServer(static_cast<int>(GameServerType::JP));
			break;

		case static_cast<int>(GameServerType::TW):
			webManager->ChangeSkillGameServer(static_cast<int>(GameServerType::TW));
			break;
		}

		// JpServerLang
		switch (global::config->JpServerLang)
		{
		case static_cast<int>(GameServerType::JP):
			webManager->ChangeJpServerLang(static_cast<int>(GameServerType::JP));
			break;

		case static_cast<int>(GameServerType::TW):
			webManager->ChangeJpServerLang(static_cast<int>(GameServerType::TW));
			break;
		}


		// SoftwareLanguage
		switch (global::config->SoftwareLanguage)
		{
		case static_cast<int>(GameServerType::JP):
			webManager->ChangeCharacterNameTitleLang(static_cast<int>(SoftwareLanguageType::JP));
			webManager->ChangeTableHeaderLang(static_cast<int>(SoftwareLanguageType::JP));
			break;

		case static_cast<int>(GameServerType::TW):
			webManager->ChangeCharacterNameTitleLang(static_cast<int>(SoftwareLanguageType::TW));
			webManager->ChangeTableHeaderLang(static_cast<int>(SoftwareLanguageType::TW));
			break;
		}

	}

	UmaForm::UmaForm(void) // UmaForm 的建構函數
	{
		InitializeComponent();
		//
		//TODO:  在此加入建構函式程式碼
		//


#pragma region WebBrowser
		// 提取 config 資料
		System::String^ port = utility::stdStr2system(global::config->LocalServer["Port"]);
		//json config = FileManager::GetInstance()->ReadJson(global::path::std_config);

		//System::String^ port = utility::stdStr2system(config["LocalServer"]["Port"].get<std::string>());

		choiceWebBrowser->DocumentCompleted += gcnew WebBrowserDocumentCompletedEventHandler(this, &UmaForm::OnChoiceDocumentCompleted);
		choiceWebBrowser->Navigate("http://localhost:" + port + "/choice.html");
		characterNameWebBrowser->Navigate("http://localhost:" + port + "/character_name.html");
#pragma endregion

#pragma region DebugMode
		if (global::config->DebugMode == true)
		{
			test_btn->Visible = true;
			screenshot_preview_btn->Visible = true;
		}
		else
		{
			test_btn->Visible = false;
			screenshot_preview_btn->Visible = false;
		}
#pragma endregion

	}


	System::Void UmaForm::test_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//std::cout << utility::IsSimilar(u8"食いしん坊は伊達じゃない", u8"食いじん坊は伊達じゃよない") << std::endl;

		//utility::IsSimilar(u8"灰簾石の瞳", u8"色雇五のだ睡");

		//std::cout << "Similarity: " << utility::GetSimilarity(u8"競賽獲勝!", u8"競賽獲勝！") << std::endl;

		//utility::GetCharacterNameSimilarity(u8"キセキの白星オグリキャップ", u8"オグリキャップ（キセキの白星）");
	}

	System::Void UmaForm::scan_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Scanner* scanner = Scanner::GetInstance();
		FileManager* fileManager = FileManager::GetInstance();
		UmaLog* umalog = UmaLog::GetInstance();

		json config = fileManager->ReadJson(global::path::std_config);
		if (!global::umaswitch::Scanning)
		{
			switch (config["GameServer"].get<int>())
			{
			case static_cast<int>(GameServerType::JP):
				scanner->Start("jpn");
				umalog->print("[Scanner] GameServer: JP");
				break;
			case static_cast<int>(GameServerType::TW):
				scanner->Start("chi_tra");
				umalog->print("[Scanner] GameServer: TW");
				break;
			}
			
			switch (global::config->SoftwareLanguage)
			{
			case static_cast<int>(SoftwareLanguageType::JP):
				this->scan_btn->Text = u8"ストップ";
				break;
			case static_cast<int>(SoftwareLanguageType::TW):
				this->scan_btn->Text = u8"停止";
				break;
			}
		}
		else
		{
			scanner->Stop();

			switch (global::config->SoftwareLanguage)
			{
			case static_cast<int>(SoftwareLanguageType::JP):
				this->scan_btn->Text = u8"スキャン";
				break;
			case static_cast<int>(SoftwareLanguageType::TW):
				this->scan_btn->Text = u8"啓動";
				break;
			}
		}
	}

	System::Void UmaForm::settings_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		global::form::settingsForm->Show();
	}

	System::Void UmaForm::screenshot_preview_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Screenshot::ShowImage();


		//global::form::previewForm->Show();
	}


	System::Void UmaForm::UmaForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		draggingForm = true;
		dragOffset.X = e->X;
		dragOffset.Y = e->Y;
	}
	System::Void UmaForm::UmaForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		draggingForm = false;
	}

	System::Void UmaForm::UmaForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (draggingForm)
		{
			System::Drawing::Point currentFormPos = PointToScreen(System::Drawing::Point(e->X, e->Y));
			this->Location = System::Drawing::Point(currentFormPos.X  - dragOffset.X, currentFormPos.Y - dragOffset.Y);
		}
	}

	System::Void UmaForm::close_form_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}

	System::Void UmaForm::minimize_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
	}

	System::Void UmaForm::clean_current_character_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DataManager::GetInstance()->SetCurrentCharacterInfoLock(false);
		WebManager::GetInstance()->ChangeCharacterName("");
	}

	System::Void UmaForm::select_window_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		global::form::previewForm->window_listbox->Items->Clear();
		GameWindowFinder::GetInstance()->EnumWindow();
		global::form::previewForm->Show();
	}
}