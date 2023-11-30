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

	// 獲取標準輸出句柄
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 啟用處理 ANSI 轉譯碼的模式
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	// 重定向標準輸出
	if (freopen("CONOUT$", "w", stdout) == nullptr)
	{
		// 處理打開文件失敗的情況
		// 這裡可以加入錯誤處理邏輯，例如顯示一個錯誤消息或日誌
	}


	SetConsoleOutputCP(CP_UTF8); // 設定控制台輸出字碼頁為 UTF8 ，這樣日文字才不會變亂碼。
}

void ConsoleManager::Disable()
{
	if (!this->_isExist) return;
	//HWND consoleWindow = GetConsoleWindow();
	//PostMessage(consoleWindow, WM_CLOSE, 0, 0);


	FreeConsole();


	this->_isExist = false;
}