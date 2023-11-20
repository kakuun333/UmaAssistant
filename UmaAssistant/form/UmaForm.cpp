#include "../stdafx.h"

namespace UmaAssistant
{

	System::Void UmaForm::test_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{

		std::unique_ptr<Screenshot>ss(new Screenshot());
		global::form::previewForm->pictureBox1->Image = ss->bmp_window;
		
		Scanner& scanner = Scanner::GetInstance();
		System::String^ scanned_text = scanner.Scan(global::path::c_screenshot_event, "jpn");


		//global::form::umaForm->textBox1->Text = scanned_text;
		//-------------------------------------------------------------------------

		DataManager& dataManager = DataManager::GetInstance();
		UmaEventData event_data = dataManager.GetUmaEventDataFromJson(utility::systemStr2std(scanned_text));

		choicePanel->Controls->Clear();

		for (UmaChoice choice : event_data.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
		{
			std::cout << "choice_title: " << choice.choice_title << std::endl;
			std::cout << "choice_effect: " << choice.choice_effect << std::endl;
			
			// ------------------------------------------------------------------------------- //
			Label^ choice_title_label = gcnew Label();

			//choice_title_label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			choice_title_label->AutoSize = true;
			choice_title_label->BackColor = System::Drawing::Color::Transparent;
			choice_title_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			choice_title_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			choice_title_label->Text = "choice_title";

			// ------------------------------------------------------------------------------- //
			Label^ choice_effect_label = gcnew Label();


			//choice_effect_label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			choice_effect_label->AutoSize = true;
			choice_effect_label->BackColor = System::Drawing::Color::Transparent;
			choice_effect_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			choice_effect_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			choice_effect_label->Text = "choice_effect";

			// ------------------------------------------------------------------------------- //

			TextBox^ choice_title_textbox = gcnew TextBox();
			choice_title_textbox->Anchor = System::Windows::Forms::AnchorStyles::None;
			choice_title_textbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			choice_title_textbox->Cursor = System::Windows::Forms::Cursors::Default;
			choice_title_textbox->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));

			choice_title_textbox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			choice_title_textbox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));

			//choice_title_textbox->Location = System::Drawing::Point(141, 4);
			choice_title_textbox->Multiline = true;
			choice_title_textbox->ReadOnly = true;

			choice_title_textbox->Text = utility::FormNewLineFormat(choice.sys_choice_title); // utility::stdStr2system(choice.choice_title);

			choice_title_textbox->Size = System::Drawing::Size(366, 25);

			choice_title_textbox->Dock = System::Windows::Forms::DockStyle::Fill;


			// ------------------------------------------------------------------------------- //

			TextBox^ choice_effect_textbox = gcnew TextBox();

			choice_effect_textbox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			choice_effect_textbox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));

			choice_effect_textbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			choice_effect_textbox->Cursor = System::Windows::Forms::Cursors::Default;
			choice_effect_textbox->Dock = System::Windows::Forms::DockStyle::Fill;
			choice_effect_textbox->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));

			//choice_effect_textbox->Location = System::Drawing::Point(141, 36);
			choice_effect_textbox->Multiline = true;
			choice_effect_textbox->ReadOnly = true;

			choice_effect_textbox->Text = utility::FormNewLineFormat(choice.sys_choice_effect); //"\r\n" + utility::stdStr2system(choice.choice_effect);

			choice_effect_textbox->Size = System::Drawing::Size(373, 50);

			// ------------------------------------------------------------------------------- //

			TableLayoutPanel^ chocie_title_table = gcnew TableLayoutPanel();

			chocie_title_table->BackColor = System::Drawing::Color::Transparent;
			chocie_title_table->ColumnCount = 2;

			chocie_title_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				27.0F)));
			chocie_title_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				73.0F)));


			chocie_title_table->RowCount = 1;
			chocie_title_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

			chocie_title_table->Location = System::Drawing::Point(3, 3);
			chocie_title_table->Size = System::Drawing::Size(485, FormDesigner::Instance->CalcChoiceTableVerticalSize(choice_title_textbox));
			

			chocie_title_table->Controls->Add(choice_title_label, 0, 0);
			chocie_title_table->Controls->Add(choice_title_textbox, 1, 0);
			// ------------------------------------------------------------------------------- //

			TableLayoutPanel^ chocie_effect_table = gcnew TableLayoutPanel();

			chocie_effect_table->BackColor = System::Drawing::Color::Transparent;
			chocie_effect_table->ColumnCount = 2;

			chocie_effect_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				27.0F)));
			chocie_effect_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				73.0F)));


			chocie_effect_table->RowCount = 1;
			chocie_effect_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

			chocie_effect_table->Location = System::Drawing::Point(3, 3);
			chocie_effect_table->Size = System::Drawing::Size(485, FormDesigner::Instance->CalcChoiceTableVerticalSize(choice_effect_textbox));


			chocie_effect_table->Controls->Add(choice_effect_label, 0, 0);
			chocie_effect_table->Controls->Add(choice_effect_textbox, 1, 0);

			choicePanel->Controls->Add(chocie_title_table);
			choicePanel->Controls->Add(chocie_effect_table);
		}

		System::String^ sys_event_owner = event_data.Get<System::String^>(UmaEventDataType::EVENT_OWNER);
		event_owner_textBox->Text = sys_event_owner;
		//std::cout << "event_owner: " << event_owner << std::endl;

		System::String^ sys_event_title = event_data.Get<System::String^>(UmaEventDataType::EVENT_TITLE);
		event_title_textbox->Text = sys_event_title;
		//std::cout << "event_title: " << event_title << std::endl;
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