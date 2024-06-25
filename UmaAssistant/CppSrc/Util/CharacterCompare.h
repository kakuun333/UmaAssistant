#pragma once

// STL
#include <string>
#include <vector>
#include <regex>

// 3rdparty
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "CharacterFilter.h"
#include "Constants.h"

#include <Manager/FileManager.h>
#include <Global/form.h>
#include <Global/path.h>

namespace util
{
	// 數 std::string 有幾個 UTF8 char，英文也可以數
	int CountUTF8Char(std::string input);

	std::vector<std::string> SplitJpnChar(std::string input);

	std::vector<int> GetNonSameIndexList(std::vector<std::string>& smaller_list, std::vector<std::string>& larger_list);

	int GetSameCount(std::vector<std::string>& smaller_list, std::vector<std::string>& larger_list);

	int GetSameCountByMoveIdx(std::vector<std::string>& smaller_list, std::vector<std::string>& larger_list, std::vector<int>& nonSameIdxList);

	float GetSimilarity(std::string str1, std::string str2);

	float GetCharacterNameSimilarity(std::string scannedName, std::string jsonDataName);

	bool IsRepeatingString(std::string scanned_text, int repeat_limit);

	bool HasBlackListedString(std::string scanned_text);

	bool IsStringTooLong(std::string scanned_text);

	int GetSameCountByMoveSmallerList(std::vector<std::string>& smaller_list, std::vector<std::string>& larger_list);

#pragma region 已棄用
	/// 從第一個 utf-8字 開始到 quantityInASet 的範圍的 utf-8字 拆分成一組，
	/// 只要分了 n 組就會跳過 n 個 utf-8字
	/// 例如：食いしん坊
	/// 預設四個 utf-8字 拆分成一組，所以第一組會是「食いしん」
	/// 基於「只要分了 n 組就會跳過 n 個 utf-8字」的規則
	/// 所以第二組會是「いしん坊」
	std::vector<std::string> SplitText(std::string input, int quantityInASet = 4);

	int GetSameCountBySimilarChar(std::vector<std::string> smaller_list, std::vector<std::string> larger_list);
	int GetSameCountByMoveIdxSimilarChar(std::vector<std::string> smaller_list, std::vector<std::string> larger_list, std::vector<int> nonSameIdxList);

	std::vector<std::string> GetSimilarCharList(std::string strChar);
	bool HasSimilarChar(std::string strChar);
#pragma endregion
}
