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
        std::cout << "Error: " << utility::systemStr2std(e->Message)<< std::endl;
    }

    return fileContent;
}

void FileManager::WriteJson(std::string path, std::string jsonString)
{
    // 寫入 json
    std::ofstream outputFile(path);
    if (outputFile.is_open())
    {
        outputFile << jsonString << std::endl;
        outputFile.close();
        std::cout << "[FileManager] " << path << u8" 成功創建並寫入！" << std::endl;
    }
    else
    {
        std::cout << "[FileManager] " << path << u8" 寫入失敗" << std::endl;
    }
}