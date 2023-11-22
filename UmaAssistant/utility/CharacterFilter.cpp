#include "../stdafx.h"

/*
UTF-8 編碼
	全形空白鍵：\xE3\x80\x80


*/
namespace utility
{
	std::string RemoveSpace(std::string input)
	{
		std::regex pattern("\\s+|\n+|\xE3\x80\x80+");

		std::string result = std::regex_replace(input, pattern, "");
		return result;
	}

	System::String^ RemoveSpace(System::String^ input)
	{
		System::String^ removed_n = input->Replace("\n", "");
		System::String^ removed_space = removed_n->Replace(" ", "");
		System::String^ removed_widthspace = removed_space->Replace("　", "");
		return removed_widthspace;
	}

	System::String^ FormNewLineFormat(System::String^ input)
	{
		Regex^ regex = gcnew Regex("\n");
		String^ formattedStr = regex->Replace(input, Environment::NewLine);

		return formattedStr;
	}
}