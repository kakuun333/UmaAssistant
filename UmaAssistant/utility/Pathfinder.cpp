#include "../stdafx.h"


namespace utility
{
	// ����M�צ�m
	const char* GetCurrentDir()
	{
		System::String^ currentDir = Directory::GetCurrentDirectory();

		const char* c_currentDir = utility::utf16to8(currentDir);

		return c_currentDir;
	}
}