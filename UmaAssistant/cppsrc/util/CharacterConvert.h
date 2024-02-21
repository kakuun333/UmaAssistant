#pragma once

// STL
#include <iostream>
#include <string>

// Windows API
#include <Windows.h>
#include <msclr/marshal.h>
using namespace msclr::interop;


namespace util
{
	std::wstring string2wstring(const std::string& str);

	// 把 System::String^ 轉成 std::string
	std::string systemStr2std(System::String^ systemStr);

	// 把 std::string 轉成 System::String^
	System::String^ stdStr2system(std::string stdStr);

	// 把 char* 轉成 wchat_t*
	// 必須使用 delete[] 釋放記憶體
	wchar_t* char2wchar(const char* str);

	// 把 utf8 轉成 utf16
	// 必須使用 delete[] 釋放記憶體
	wchar_t* utf8to16(char* utf8);

	// 把 utf16 轉成 utf8
	// 必須使用 delete[] 釋放記憶體
	char* utf16to8(wchar_t* utf16);
	char* utf16to8(System::String^ sys_string);
}
