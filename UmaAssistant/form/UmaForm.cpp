#include "../stdafx.h"

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
		choiceWebBrowser->Navigate(global::path::choiceWebBrowser);
		characterNameWebBrowser->Navigate(global::path::characterNameWebBrowser);
#pragma endregion WebBrowser
	}

	System::Void UmaForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//std::cout << utility::IsSimilar(u8"食いしん坊は伊達じゃない", u8"食いじん坊は伊達じゃよない") << std::endl;

		//utility::IsSimilar(u8"灰簾石の瞳", u8"色雇五のだ睡");

		utility::GetCharacterNameSimilarity(u8"キセキの白星オグリキャップ", u8"オグリキャップ（キセキの白星）");
	}

	System::Void UmaForm::test_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Scanner* scanner = Scanner::GetInstance();

		if (!global::umaswitch::Scanning)
		{
			//scanner->Start("jpn");
			scanner->Start("jpn");

			test_btn->Text = "Stop";
		}
		else
		{
			scanner->Stop();

			test_btn->Text = "Start";
		}
	}

	System::Void UmaForm::settings_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		global::form::settingsForm->Show();
	}

	System::Void UmaForm::screenshot_preview_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		global::form::previewForm->Show();
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
}