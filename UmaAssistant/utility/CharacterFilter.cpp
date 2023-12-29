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

	std::string ReplaceSpecialString(std::string input)
	{
		//if (input.empty()) return std::string();

		/*
		[Scanner] event_title_gray_bin_inv:  全.力.肌.肉!!
		*/

		std::string result;

		std::string inputStr;

		std::regex exclamationMark_pattern(R"(\!)");

		std::regex questionMark_pattern(R"(\?)");

		std::regex three_dot_pattern(R"(\.\.\.)");
		
		std::regex dot_pattern(R"(\.)");
		
		std::regex left_parenthesis_pattern(R"(\()");
		std::regex right_parenthesis_pattern(R"(\))");

		// 3rd演唱會,結束！
		// , -> ，
		std::regex comma_pattern(R"(,)");

		result = std::regex_replace(input, exclamationMark_pattern, u8"！");

		result = result.empty() ? inputStr = input : inputStr = result;
		result = std::regex_replace(inputStr, questionMark_pattern, u8"？");

		result = result.empty() ? inputStr = input : inputStr = result;
		result = std::regex_replace(inputStr, three_dot_pattern, u8"…");

		result = result.empty() ? inputStr = input : inputStr = result;
		result = std::regex_replace(inputStr, dot_pattern, u8"．");

		result = result.empty() ? inputStr = input : inputStr = result;
		result = std::regex_replace(inputStr, left_parenthesis_pattern, u8"（");

		result = result.empty() ? inputStr = input : inputStr = result;
		result = std::regex_replace(inputStr, right_parenthesis_pattern, u8"）");

		result = result.empty() ? inputStr = input : inputStr = result;
		result = std::regex_replace(inputStr, comma_pattern, u8"，");

		return result;
	}
}