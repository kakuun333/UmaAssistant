#include "../stdafx.h"


namespace UmaAssistant
{
	System::Void UmaForm::test_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//std::cout << utility::IsSimilar(u8"食いしん坊は伊達じゃない", u8"食いじん坊は伊達じゃよない") << std::endl;

		//utility::IsSimilar(u8"灰簾石の瞳", u8"色雇五のだ睡");

		//std::cout << "Similarity: " << utility::GetSimilarity(u8"競賽獲勝!", u8"競賽獲勝！") << std::endl;

		//utility::GetCharacterNameSimilarity(u8"キセキの白星オグリキャップ", u8"オグリキャップ（キセキの白星）");

		/* UmaDataUpdater */
		//UmaDataUpdater::GetInstance()->Update();


		//global::config->WriteToJson();


		//std::cout << utility::IsStringTooLong(u8"あああああああああああああああああああああああ") << std::endl;

		//std::string test = u8"欸，我的打工......這麼糟嗎？";

		//test = utility::ReplaceSpecialString(test);

		//std::string boolean = utility::IsRepeatingString(test, 4) == true ? "true" : "false";

		//std::cout << test << std::endl;

		//std::cout << boolean << std::endl;
	}

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
			webManager->ChangeCharacterNameBrowserLang(static_cast<int>(SoftwareLanguageType::JP));
			webManager->ChangeChoiceBrowserLang(static_cast<int>(SoftwareLanguageType::JP));
			break;

		case static_cast<int>(GameServerType::TW):
			webManager->ChangeCharacterNameBrowserLang(static_cast<int>(SoftwareLanguageType::TW));
			webManager->ChangeChoiceBrowserLang(static_cast<int>(SoftwareLanguageType::TW));
			break;
		}
	}

	void UmaForm::OnSelectCharacterDocumentCompleted(Object^ sender, WebBrowserDocumentCompletedEventArgs^ e)
	{
		WebBrowser^ webBrowser = dynamic_cast<WebBrowser^>(sender);


	}

	void UmaForm::Character_IMG_Clicked(System::Object^ sender, System::Windows::Forms::HtmlElementEventArgs^ e)
	{
		DataManager* dataManager = DataManager::GetInstance();
		WebManager* webManager = WebManager::GetInstance();
		UmaLog* umalog = UmaLog::GetInstance();

		// 在這裡處理按鈕被點擊的邏輯
		HtmlElement^ element = safe_cast<HtmlElement^>(sender);
		System::String^ altValue = element->GetAttribute("alt");
		
		Regex^ jp_pattern = gcnew Regex("<jp_event_owner>(.+)</jp_event_owner>");
		Regex^ tw_pattern = gcnew Regex("<tw_event_owner>(.+)</tw_event_owner>");

		Match^ match;

		switch (global::config->GameServer)
		{
		case static_cast<int>(GameServerType::JP):
			match = jp_pattern->Match(altValue);
			if (match->Success)
			{
				dataManager->SetCurrentCharacterInfoLock(false);
				webManager->ChangeCharacterName("");
				
				System::String^ sys_event_owner = match->Groups[1]->Value;
				std::string std_event_owner = utility::systemStr2std(sys_event_owner);

				umalog->print("[UmaForm] matched: ", std_event_owner);

				if (dataManager->SetCurrentCharacterInfoDict(std_event_owner))
				{
					umalog->print("[UmaForm] FOUND SELECT CHARACTER");
					dataManager->SetCurrentCharacterInfoLock(true);
					webManager->ChangeCharacterName(sys_event_owner);
				}
				else
				{
					umalog->print("[UmaForm] NOT FOUND SELECT CHARACTER");
					std::cout << "FALSE" << std::endl;
				}
			}
			else
			{
				umalog->print("[UmaForm] NOT MATCHED SELECT CHARACTER NAME");
			}
			break;
		case static_cast<int>(GameServerType::TW):
			match = tw_pattern->Match(altValue);
			if (match->Success)
			{
				dataManager->SetCurrentCharacterInfoLock(false);
				webManager->ChangeCharacterName("");

				System::String^ sys_event_owner = match->Groups[1]->Value;
				std::string std_event_owner = utility::systemStr2std(sys_event_owner);

				umalog->print("[UmaForm] matched: ", std_event_owner);

				if (dataManager->SetCurrentCharacterInfoDict(std_event_owner))
				{
					umalog->print("[UmaForm] FOUND SELECT CHARACTER");
					dataManager->SetCurrentCharacterInfoLock(true);
					webManager->ChangeCharacterName(sys_event_owner);
				}
				else
				{
					umalog->print("[UmaForm] NOT FOUND SELECT CHARACTER");
					std::cout << "FALSE" << std::endl;
				}
			}
			else
			{
				umalog->print("[UmaForm] NOT MATCHED SELECT CHARACTER NAME");
			}
			break;
		}
	}

	void UmaForm::UpdateIMGClickEvent()
	{
		// 在 DocumentCompleted 事件中為 <img class="character_icon" /> 添加 Click 事件
		for each (HtmlElement^ element in this->select_character_webBrowser->Document->All)
		{
			/*
			HtmlElement->TagName 都是大寫
			要獲取 tag 的 class 需要用 "className"
			*/

			if (element->TagName == "IMG" && element->GetAttribute("className") == "character_icon")
			{
				element->Click -= gcnew HtmlElementEventHandler(this, &UmaForm::Character_IMG_Clicked);
				element->Click += gcnew HtmlElementEventHandler(this, &UmaForm::Character_IMG_Clicked);
			}
		}
	}

	System::Void UmaForm::close_select_character_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ button = dynamic_cast<Button^>(sender);

		_openedSelectCharacter = false;

		switch (global::config->SoftwareLanguage)
		{
		case static_cast<int>(SoftwareLanguageType::JP):
			this->select_character_btn->Text = u8"キャラ選択";
			break;
		case static_cast<int>(SoftwareLanguageType::TW):
			this->select_character_btn->Text = u8"選擇角色";
			break;
		}

		this->Size = System::Drawing::Size(560, this->Size.Height);

		this->minimize_btn->Location = System::Drawing::Point(476, 0);
		this->close_form_btn->Location = System::Drawing::Point(521, 0);
	}

	System::Void UmaForm::select_character_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ button = dynamic_cast<Button^>(sender);

		switch (_openedSelectCharacter)
		{
		case true:
			_openedSelectCharacter = false;

			switch (global::config->SoftwareLanguage)
			{
			case static_cast<int>(SoftwareLanguageType::JP):
				button->Text = u8"キャラ選択";
				break;
			case static_cast<int>(SoftwareLanguageType::TW):
				button->Text = u8"選擇角色";
				break;
			}
			


			this->Size = System::Drawing::Size(560, this->Size.Height);

			this->minimize_btn->Location = System::Drawing::Point(476, 0);
			this->close_form_btn->Location = System::Drawing::Point(521, 0);

			break;

		case false:
			_openedSelectCharacter = true;

			switch (global::config->SoftwareLanguage)
			{
			case static_cast<int>(SoftwareLanguageType::JP):
				button->Text = u8"折りたたむ";
				break;
			case static_cast<int>(SoftwareLanguageType::TW):
				button->Text = u8"收回";
				break;
			}
			

			this->Size = System::Drawing::Size(1060, this->Size.Height);

			this->minimize_btn->Location = System::Drawing::Point(476, 0);
			this->close_form_btn->Location = System::Drawing::Point(521, 0);


			this->UpdateIMGClickEvent();
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

		// choice.html
		choiceWebBrowser->DocumentCompleted += gcnew WebBrowserDocumentCompletedEventHandler(this, &UmaForm::OnChoiceDocumentCompleted);
		choiceWebBrowser->Navigate("http://localhost:" + port + "/choice.html");
		
		// character_name.html
		characterNameWebBrowser->Navigate("http://localhost:" + port + "/character_name.html");

		// select_character.html
		select_character_webBrowser->DocumentCompleted += gcnew WebBrowserDocumentCompletedEventHandler(this, &UmaForm::OnSelectCharacterDocumentCompleted);
		select_character_webBrowser->Navigate("http://localhost:" + port + "/select_character.html");
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