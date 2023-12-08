#include "../stdafx.h"

//#using <System.dll>
//#using <System.Net.dll>






namespace UmaAssistant
{
	void UmaForm::OnChoiceDocumentCompleted(System::Object^ sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^ e)
	{
		// 初始化 skill_displayer.js 中的 let GameServer 變數
		WebManager* webManager = WebManager::GetInstance();
		if (global::config->GameServer == static_cast<int>(GameServerType::JP))
		{
			webManager->ChangeSkillGameServer(static_cast<int>(GameServerType::JP));
		}
		else if (global::config->GameServer == static_cast<int>(GameServerType::TW))
		{
			webManager->ChangeSkillGameServer(static_cast<int>(GameServerType::TW));
		}
		// 初始化 skill_displayer.js 中的 let JpServerLang 變數
		if (global::config->JpServerLang == static_cast<int>(JpServerLangType::JP))
		{
			webManager->ChangeJpServerLang(static_cast<int>(JpServerLangType::JP));
		}
		else if (global::config->JpServerLang == static_cast<int>(JpServerLangType::TW))
		{
			webManager->ChangeJpServerLang(static_cast<int>(JpServerLangType::TW));
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

		std::cout << "Similarity: " << utility::GetSimilarity(u8"競賽獲勝!", u8"競賽獲勝！") << std::endl;

		//utility::GetCharacterNameSimilarity(u8"キセキの白星オグリキャップ", u8"オグリキャップ（キセキの白星）");
	}

	System::Void UmaForm::scan_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Scanner* scanner = Scanner::GetInstance();

		FileManager* fileManager = FileManager::GetInstance();
		json config = fileManager->ReadJson(global::path::std_config);
		if (!global::umaswitch::Scanning)
		{
			switch (config["GameServer"].get<int>())
			{
			case static_cast<int>(GameServerType::JP):
				scanner->Start("jpn");
				
				std::cout << "scanner GameServer: JP" << std::endl;
				break;
			case static_cast<int>(GameServerType::TW):
				scanner->Start("chi_tra");
				std::cout << "scanner GameServer: TW" << std::endl;
				break;
			}
			

			this->scan_btn->Text = u8"停止";
		}
		else
		{
			scanner->Stop();

			this->scan_btn->Text = u8"啓動";
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