#include "../stdafx.h"

namespace utility
{
	/// <summary>
	/// 將兩個 const char* 合在一起變成一個 const char*
	/// </summary>
	/// <param name="str1"></param>
	/// <param name="str2"></param>
	/// <returns></returns>
	const char* CombineChar(const char* str1, const char* str2)
	{
        // 合併後的長度
        rsize_t len = strlen(str1) + strlen(str2) + 1;
            
        char* result = new char[len];

        // 複製 str1 到 result
        strncpy_s(result, len, str1, strlen(str1));

        // 把 str2 連接到 result
        strcat_s(result, len, str2);

        return result;

        // 釋放記憶體
        delete[] result;
	}
};