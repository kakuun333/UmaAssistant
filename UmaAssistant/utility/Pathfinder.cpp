#include "../stdafx.h"


namespace utility
{
	// 獲取專案位置
	const char* GetCurrentDir()
	{
		System::String^ currentDir = Directory::GetCurrentDirectory();

		const char* c_currentDir = utility::utf16to8(currentDir);

		return c_currentDir;
	}
}