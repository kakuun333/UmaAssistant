#pragma once
#include <iostream>

namespace utility
{
	// 把 System::String^ 轉成 std::string
	std::string sys_str2std_str(System::String^ sys_str);

	// 把 char* 轉成 wchat_t*
	wchar_t* char2wchar(const char* str);

	// 把 utf8 轉成 utf16
	wchar_t* utf8to16(char* utf8);

	// 把 utf16 轉成 utf8
	char* utf16to8(wchar_t* utf16);

	// 把 utf16 轉成 utf8
	char* utf16to8(System::String^ sys_string);
}
