#pragma once



namespace utility
{
	constexpr inline unsigned int UTF8_CHAR_SIZE = 3;
	constexpr inline float SIMILAR_METRIC = 50; // 相似度標準，大於 n 才算是相似;
	constexpr inline int SIMIALAR_MAX = 100;
	constexpr inline int NOT_SIMILAR = -1;

	int CountUTF8Char(std::string input);

	std::vector<std::string> SplitJpnChar(std::string input);

	/// 從第一個 utf-8字 開始到 quantityInASet 的範圍的 utf-8字 拆分成一組，
	/// 只要分了 n 組就會跳過 n 個 utf-8字
	/// 例如：食いしん坊
	/// 預設四個 utf-8字 拆分成一組，所以第一組會是「食いしん」
	/// 基於「只要分了 n 組就會跳過 n 個 utf-8字」的規則
	/// 所以第二組會是「いしん坊」
	std::vector<std::string> SplitText(std::string input, int quantityInASet = 4);

	std::vector<int> GetNonSameIndexList(std::vector<std::string> smaller_list, std::vector<std::string> larger_list);

	int GetSameCount(std::vector<std::string> smaller_list, std::vector<std::string> larger_list);

	int GetSameCountByMoveIdx(std::vector<std::string> smaller_list, std::vector<std::string> larger_list, std::vector<int> nonSameIdxList);

	int GetSameCountBySimilarChar(std::vector<std::string> smaller_list, std::vector<std::string> larger_list);

	int GetSameCountByMoveIdxSimilarChar(std::vector<std::string> smaller_list, std::vector<std::string> larger_list, std::vector<int> nonSameIdxList);

	bool HasSimilarChar(std::string strChar);

	std::vector<std::string> GetSimilarCharList(std::string strChar);

	bool IsSimilar(std::string str1, std::string str2);

	float GetSimilarity(std::string str1, std::string str2);

	float GetCharacterNameSimilarity(std::string scannedName, std::string jsonDataName);
}
