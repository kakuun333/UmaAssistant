#include "../stdafx.h"

ConsoleManager* ConsoleManager::_instance = nullptr;

bool ConsoleManager::_isExist = false;

void ConsoleManager::Enable()
{
	if (this->_isExist) return;
	this->_isExist = true;

	if (!AttachConsole(ATTACH_PARENT_PROCESS))
	{
		AllocConsole();
	}

	SetConsoleOutputCP(CP_UTF8); // 設定控制台輸出字碼頁為 UTF8 ，這樣日文字才不會變亂碼。

	// 獲取標準輸出句柄
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 啟用處理 ANSI 轉譯碼的模式
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);


	FILE* newStdout;
	// 重定向標準輸出
	if (freopen_s(&newStdout, "CONOUT$", "w", stdout) == 0)
	{
		// 現在 stdout 被重新導向到 CONOUT$
		printf("New console\n");

		// 恢復標準輸出到控制台
		freopen_s(&newStdout, "CONOUT$", "w", stdout);
		printf("Back to the console.\n");
	}
	else
	{
		// 處理錯誤
		perror("freopen_s");
	}
	//if (freopen("CONOUT$", "w", stdout) == nullptr)
	//{
	//	// 處理打開文件失敗的情況
	//}


	
}

void ConsoleManager::Disable()
{
	if (!this->_isExist) return;
	//HWND consoleWindow = GetConsoleWindow();
	//PostMessage(consoleWindow, WM_CLOSE, 0, 0);


	FreeConsole();


	this->_isExist = false;
}