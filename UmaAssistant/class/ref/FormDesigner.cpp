#include "../../stdafx.h"


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

	std::cout << "result: " << result << std::endl;

	return result;
}
