#include "FormDesigner.h"






System::Void FormDesigner::CreateChoiceTable(UmaChoice choice)
{
	//std::cout << "choice_title: " << choice.choice_title << std::endl;
	//std::cout << "choice_effect: " << choice.choice_effect << std::endl;

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

	choice_title_textbox->Text = util::FormNewLineFormat(util::stdStr2system(choice.choice_name));

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

	choice_effect_textbox->Text = util::FormNewLineFormat(util::stdStr2system(choice.choice_name)); //"\r\n" + utility::stdStr2system(choice.choice_effect);

	choice_effect_textbox->Size = System::Drawing::Size(373, 50);

	// ------------------------------------------------------------------------------- //

	TableLayoutPanel^ choice_title_table = gcnew TableLayoutPanel();

	choice_title_table->BackColor = System::Drawing::Color::Transparent;
	choice_title_table->ColumnCount = 2;

	choice_title_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
		27.0F)));
	choice_title_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
		73.0F)));


	choice_title_table->RowCount = 1;
	choice_title_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

	choice_title_table->Location = System::Drawing::Point(3, 3);
	choice_title_table->Size = System::Drawing::Size(485, FormDesigner::Instance->CalcChoiceTableVerticalSize(choice_title_textbox));


	choice_title_table->Controls->Add(choice_title_label, 0, 0);
	choice_title_table->Controls->Add(choice_title_textbox, 1, 0);
	// ------------------------------------------------------------------------------- //

	TableLayoutPanel^ choice_effect_table = gcnew TableLayoutPanel();

	choice_effect_table->BackColor = System::Drawing::Color::Transparent;
	choice_effect_table->ColumnCount = 2;

	choice_effect_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
		27.0F)));
	choice_effect_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
		73.0F)));


	choice_effect_table->RowCount = 1;
	choice_effect_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));

	choice_effect_table->Location = System::Drawing::Point(3, 3);
	choice_effect_table->Size = System::Drawing::Size(485, FormDesigner::Instance->CalcChoiceTableVerticalSize(choice_effect_textbox));


	choice_effect_table->Controls->Add(choice_effect_label, 0, 0);
	choice_effect_table->Controls->Add(choice_effect_textbox, 1, 0);



	//if (global::form::umaForm->choicePanel->InvokeRequired)
	//{
	//	global::form::umaForm->choicePanel->Invoke(gcnew Action<Control^, Control^>());
	//}
	//else
	//{
	//	global::form::umaForm->choicePanel->Controls->Add(choice_title_table);
	//	global::form::umaForm->choicePanel->Controls->Add(choice_effect_table);
	//}
}




int FormDesigner::CalcChoiceTableVerticalSize(TextBox^ choice_effect_textbox)
{
	System::String^ text = choice_effect_textbox->Text;

	Regex^ regex = gcnew Regex(Environment::NewLine);
	array<String^>^ str_arr = regex->Split(text);

	unsigned int newLineCount = 0;

	for each (String^ line in str_arr)
	{
		newLineCount++;

		unsigned int lineByteCount = line->Length * sizeof(wchar_t);

		if (lineByteCount > NEW_LINE_BYTE)
		{
			newLineCount++;
		}
	}


	int result = newLineCount * NEW_LINE_SIZE;

	//std::cout << "result: " << result << std::endl;

	return result;
}
