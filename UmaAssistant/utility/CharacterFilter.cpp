#include "../stdafx.h"


namespace utility
{
	System::String^ RemoveSpace(System::String^ input)
	{
		System::String^ removed_n = input->Replace("\n", "");
		System::String^ removed_space = removed_n->Replace(" ", "");
		System::String^ removed_widthspace = removed_space->Replace("¡@", "");
		return removed_widthspace;
	}

	System::String^ FormNewLineFormat(System::String^ input)
	{
		Regex^ regex = gcnew Regex("\n");
		String^ formattedStr = regex->Replace(input, Environment::NewLine);

		return formattedStr;
	}
}