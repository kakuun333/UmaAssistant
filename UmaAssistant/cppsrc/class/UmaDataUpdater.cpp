#include "../stdafx.h"

UmaDataUpdater* UmaDataUpdater::_instance = nullptr;

//std::string UmaDataUpdater::_RemoveHTMLTag(std::string html)
//{
//    std::string removedHtmlTagJsonData;
//
//    std::regex pattern("<pre.*>(.+)</pre>");
//
//    std::smatch matches;
//
//    std::cout << "remove tag " << std::endl;
//
//    if (std::regex_search(html, matches, pattern))
//    {
//        removedHtmlTagJsonData = matches[0];
//        // matches[0] 存儲整個匹配的字串
//        std::cout << "Full match: " << matches[0] << std::endl;
//
//    }
//    else
//    {
//        std::cout << "No match found." << std::endl;
//    }
//
//    return removedHtmlTagJsonData;
//}

void UmaDataUpdater::_UpdateFileFormUrl(std::string filePath, std::string url)
{
    FileManager* fileManager = FileManager::GetInstance();
	URLManager* urlManager = URLManager::GetInstance();

	std::string jsonData = urlManager->GetResponseByUrl(url);

    fileManager->WriteJson(filePath, jsonData); // 把 html 寫入 .json 裡面。
	std::cout << u8"[UmaDataUpdater] 成功更新 " << filePath << std::endl;
}


void UmaDataUpdater::Update()
{
	if (_updating) return;
	_updating = true;

	// event_data
    this->_UpdateFileFormUrl(global::path::std_event_data_jp_json, "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaData/event_data_jp.json");
	this->_UpdateFileFormUrl(global::path::std_event_data_tw_json, "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaData/event_data_tw.json");
	this->_UpdateFileFormUrl(global::path::std_event_data_jp_trans_tw_json, "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaData/event_data_jp_trans_tw.json");

	// skill_data
	this->_UpdateFileFormUrl(global::path::std_skill_data_jp_json, "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaData/skill_data_jp.json");
	this->_UpdateFileFormUrl(global::path::std_skill_data_tw_json, "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaData/skill_data_tw.json");
	this->_UpdateFileFormUrl(global::path::std_UmaData + "\\skill_data_jp_trans_tw.json", "https://raw.githubusercontent.com/kakuun333/UmaAssistant/main/UmaData/skill_data_jp_trans_tw.json");

	_updating = false;
}