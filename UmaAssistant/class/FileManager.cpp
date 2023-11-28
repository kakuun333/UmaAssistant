#include "../stdafx.h"

FileManager* FileManager::_instance = nullptr;


nlohmann::json FileManager::ReadJson(std::string path)
{
	std::ifstream inputFile(path);
	if (inputFile.is_open())
	{
		nlohmann::json jsonInput;
		inputFile >> jsonInput;
		inputFile.close();


		return jsonInput;

	}
	else
	{
		std::cerr << u8"讀取失敗：" << path << std::endl;
	}
}


System::String^ FileManager::SysReadFile(System::String^ path)
{
    System::String^ fileContent;

    try
    {
        // 使用 StreamReader 打開檔案
        StreamReader^ sr = gcnew StreamReader(path);

        // 讀取檔案內容
        fileContent = sr->ReadToEnd();

        // 關閉 StreamReader
        sr->Close();
    }
    catch (Exception^ e)
    {
        // 處理可能的異常
        Console::WriteLine("Error: " + e->Message);
    }

    return fileContent;
}