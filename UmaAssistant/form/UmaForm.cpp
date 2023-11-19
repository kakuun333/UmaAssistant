#include "../stdafx.h"

namespace UmaAssistant
{

	System::Void UmaForm::test_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{

		std::unique_ptr<Screenshot>ss(new Screenshot());
		global::form::previewForm->pictureBox1->Image = ss->bmp_window;
		
		System::String^ scanned_text = Scanner::Scan(global::path::c_screenshot_event, "jpn");

		//global::form::umaForm->textBox1->Text = scanned_text;
		//-------------------------------------------------------------------------

		FileManager::LuaTableToJson(utility::sys_str2std_str(scanned_text));
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
		//std::cout << e->X << std::endl;
		//std::cout << e->Y << std::endl;
		
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

