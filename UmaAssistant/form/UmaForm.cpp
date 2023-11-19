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


		///
		///	TODO: 好像與擷取的到一個選項而已
		/// 

		json jsonData;
		bool found_event_effect = false;

		// 打開 JSON 檔
		std::ifstream jsonFile(global::path::event_data_jp_json);
		if (jsonFile.is_open())
		{
			// 讀取 JSON 檔的內容到 json 物件
			jsonFile >> jsonData;

			jsonFile.close();
		}

		std::string event_owner;
		std::string event_title;

		std::string choice_title;
		std::string choice_effect;

		// 遍歷 json 物件
		for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it) // article_id_table
		{
			event_owner = it.value()["event_owner"];
			json event_slot = it.value()["event_slot"];

			for (json::iterator it2 = event_slot.begin(); it2 != event_slot.end(); ++it2)
			{
				std::string event_slot_idx = it2.key();

				event_title = it2.value()["event_title"];
				json event_choice = it2.value()["event_choice"];
				for (json::iterator it4 = event_choice.begin(); it4 != event_choice.end(); ++it4) // slot
				{
					if (!found_event_effect && event_title == utility::sys_str2std_str(scanned_text))
					{

						std::string choiceEffect = it4.value()["choice_effect"];
						std::string choiceTitle = it4.value()["choice_title"];
						std::cout << "event_slot_idx: \n" << event_slot_idx << std::endl;
						std::cout << "event_title: \n" << event_title << std::endl;
						std::cout << "choiceEffect: \n" << choiceEffect << std::endl;
						std::cout << "choiceTitle: \n" << choiceTitle << std::endl;

						found_event_effect = true;
						break;
					}
				}
			}
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

