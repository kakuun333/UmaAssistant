#include "../stdafx.h"
//#using <System.dll>
//#using <System.Net.dll>






namespace UmaAssistant
{
	UmaForm::UmaForm(void) // UmaForm 的建構函數
	{
		InitializeComponent();
		//
		//TODO:  在此加入建構函式程式碼
		//

#pragma region WebBrowser
		//choiceWebBrowser->DocumentCompleted += gcnew WebBrowserDocumentCompletedEventHandler(&OnDocumentCompleted);

		System::String^ port = "1234";

		LocalServer::Instance->Start(port);


		choiceWebBrowser->Navigate("http://localhost:" + port + "/choice.html");
		//characterNameWebBrowser->Navigate(global::path::character_name_html);




		//json skill_data_jp = FileManager::GetInstance()->ReadJson(global::path::std_skill_data_jp_json);
		//// 要插入的 json
		//std::string insertJson = skill_data_jp.dump();
		//// 正規表達式模式
		//std::regex pattern("(<pre id=\"skill_json_jp\">)(</pre>)");
		//// 替換字符串
		//std::string insertedJsonHtml = std::regex_replace(utility::systemStr2std(choiceWebBrowser->DocumentText), pattern, "$1" + insertJson + "$2");
		//choiceWebBrowser->DocumentText = utility::stdStr2system(insertedJsonHtml);
		//std::cout << insertedJsonHtml << std::endl;
#pragma endregion
	}





	System::Void UmaForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//std::cout << utility::IsSimilar(u8"食いしん坊は伊達じゃない", u8"食いじん坊は伊達じゃよない") << std::endl;

		//utility::IsSimilar(u8"灰簾石の瞳", u8"色雇五のだ睡");

		utility::GetCharacterNameSimilarity(u8"キセキの白星オグリキャップ", u8"オグリキャップ（キセキの白星）");
	}

	System::Void UmaForm::scan_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Scanner* scanner = Scanner::GetInstance();

		if (!global::umaswitch::Scanning)
		{
			scanner->Start("jpn");

			this->scan_btn->Text = "停止";
		}
		else
		{
			scanner->Stop();

			this->scan_btn->Text = "起動";
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
}