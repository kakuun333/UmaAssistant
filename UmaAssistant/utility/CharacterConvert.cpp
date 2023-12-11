#include "../stdafx.h"

namespace utility
{
	std::wstring string2wstring(const std::string& str)
	{
		int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
		std::wstring result(size, L'\0');
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &result[0], size);
		return result;
	}

	std::string systemStr2std(System::String^ systemStr)
	{
		marshal_context context;

		const wchar_t* c_utf16 = context.marshal_as<const wchar_t*>(systemStr);

		char* c_utf8 = utf16to8(const_cast<wchar_t*>(c_utf16));

		std::string std_string(c_utf8);

		delete[] c_utf8;

		return std_string;
	}

	System::String^ stdStr2system(std::string stdStr)
	{
		marshal_context context;

		char* utf8 = const_cast<char*>(stdStr.c_str());

		wchar_t* c_utf16 = utf8to16(utf8);

		System::String^ sys_str = msclr::interop::marshal_as<System::String^>(c_utf16);

		delete[] c_utf16;

		return sys_str;
	}

	wchar_t* char2wchar(const char* str)
	{
		// 獲取需要的緩衝區大小
		int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

		// 分配緩衝區
		wchar_t* wideStr = new wchar_t[len];

		// 執行轉換
		MultiByteToWideChar(CP_UTF8, 0, str, -1, wideStr, len);

		return wideStr;
	}

	wchar_t* utf8to16(char* utf8)
	{
		// 獲取需要的緩衝區大小
		int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);

		// 分配緩衝區
		wchar_t* utf16Buffer = new wchar_t[len];

		// 執行轉換
		MultiByteToWideChar(CP_UTF8, 0, utf8, -1, utf16Buffer, len);

		// 返回
		return utf16Buffer;
	}

	char* utf16to8(wchar_t* utf16)
	{
		// 獲取需要的緩衝區大小
		int len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, NULL, NULL);

		// 分配緩衝區
		char* utf8Buffer = new char[len];

		// 執行轉換
		WideCharToMultiByte(CP_UTF8, 0, utf16, -1, utf8Buffer, len, NULL, NULL);

		// 返回
		return utf8Buffer;
	}

	char* utf16to8(System::String^ sys_string)
	{
		marshal_context context;

		// 把 System::String^ 轉成 const char*
		const char* c_str = context.marshal_as<const char*>(sys_string);

		// 把 char 轉成 wchar_t
		wchar_t* utf16 = char2wchar(c_str);

		// 獲取需要的緩衝區大小
		int len = WideCharToMultiByte(CP_UTF8, 0, utf16, -1, NULL, 0, NULL, NULL);

		// 分配緩衝區
		char* utf8Buffer = new char[len];

		// 執行轉換
		WideCharToMultiByte(CP_UTF8, 0, utf16, -1, utf8Buffer, len, NULL, NULL);

		delete[] utf16;

		// 返回
		return utf8Buffer;
	}
}
