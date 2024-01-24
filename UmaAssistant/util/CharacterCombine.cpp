#include "../stdafx.h"

namespace util
{
	/// <summary>
	/// 將兩個 const char* 合在一起變成一個 std::unique_ptr<char[]>
	/// </summary>
	/// <param name="str1"></param>
	/// <param name="str2"></param>
	/// <returns></returns>
	std::unique_ptr<char[]> CombineConstChar(const char* str1, const char* str2)
	{
        // 合併後的長度
        rsize_t len = strlen(str1) + strlen(str2) + 1;
        
		std::unique_ptr<char[]> result = std::make_unique<char[]>(len);

        // 複製 str1 到 result
        strncpy_s(result.get(), len, str1, strlen(str1));

        // 把 str2 連接到 result
        strcat_s(result.get(), len, str2);

        return result;
	}
};