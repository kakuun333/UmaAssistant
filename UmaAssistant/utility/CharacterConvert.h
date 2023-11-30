#pragma once
#include <iostream>

namespace utility
{
	std::wstring string2wstring(const std::string& str);

	// �� System::String^ �ন std::string
	std::string systemStr2std(System::String^ systemStr);

	System::String^ stdStr2system(std::string stdStr);

	// �� char* �ন wchat_t*
	wchar_t* char2wchar(const char* str);

	// �� utf8 �ন utf16
	wchar_t* utf8to16(char* utf8);

	// �� utf16 �ন utf8
	char* utf16to8(wchar_t* utf16);

	// �� utf16 �ন utf8
	char* utf16to8(System::String^ sys_string);
}
