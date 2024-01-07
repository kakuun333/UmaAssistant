#pragma once



namespace utility
{
	constexpr inline uint UTF8_CHAR_BYTE = 0x3; // 一個 utf8 文字佔的 Byte 數量
	constexpr inline float SIMILAR_METRIC = 50; // 相似度標準，大於 n 才算是相似;
	constexpr inline float JP_CHAR_SIMILAR_METRIC = 65;
	constexpr inline int MAX_SIMIALARITY = 100;
	constexpr inline int NOT_SIMILAR = -1;

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
