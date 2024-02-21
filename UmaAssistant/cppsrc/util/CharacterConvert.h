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

	// �� System::String^ �ন std::string
	std::string systemStr2std(System::String^ systemStr);

	// �� std::string �ন System::String^
	System::String^ stdStr2system(std::string stdStr);

	// �� char* �ন wchat_t*
	// �����ϥ� delete[] ����O����
	wchar_t* char2wchar(const char* str);

	// �� utf8 �ন utf16
	// �����ϥ� delete[] ����O����
	wchar_t* utf8to16(char* utf8);

	// �� utf16 �ন utf8
	// �����ϥ� delete[] ����O����
	char* utf16to8(wchar_t* utf16);
	char* utf16to8(System::String^ sys_string);
}
