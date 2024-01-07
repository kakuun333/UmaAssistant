#include "../stdafx.h"

namespace utility
{
	int CountUTF8Char(std::string input)
	{
		std::string currentChar;
		int count = 0;

		for (auto it = input.begin(); it != input.end(); ++it)
		{
			if ((*it & 0xC0) != 0x80)
			{
				// 檢查是否是多位元組字符的第一個位元組
				if (!currentChar.empty())
				{
					++count;
					currentChar.clear();
				}
			}
			currentChar += *it;
		}
		// 處理最後一個字符
		if (!currentChar.empty())
		{
			++count;
		}

		return count;
	}


	std::vector<std::string> SplitJpnChar(std::string input)
	{
		//const int MINIMUM_UTF8_CHAR_COUNT = 2;

		//// 文字大小不足 MINIMUM_CHAR_COUNT 個 utf-8
		//if (input.length() < UTF8_CHAR_BYTE * MINIMUM_UTF8_CHAR_COUNT)
		//{
		//	//std::cout << u8"文字大小不足 " << MINIMUM_UTF8_CHAR_COUNT << " 個 utf-8" << std::endl;
		//	return std::vector<std::string>();
		//}

		std::string currentChar;
		std::vector<std::string> char_list;

		for (auto it = input.begin(); it != input.end(); ++it)
		{
			if ((*it & 0xC0) != 0x80)
			{
				// 檢查是否是多位元組字符的第一個位元組
				if (!currentChar.empty())
				{
					char_list.push_back(currentChar);
					currentChar.clear();
				}
			}
			currentChar += *it;
		}

		// 處理最後一個字符
		if (!currentChar.empty())
		{
			char_list.push_back(currentChar);
		}


		return char_list;
	}

	std::vector<std::string> SplitText(std::string input, int quantityInASet)
	{
		//std::cout << "Text: " << input << "  size: " << input.size() << std::endl;

		int jpnchar_count = CountUTF8Char(input);
		std::vector<std::string> jpnchar_list = SplitJpnChar(input);

		std::vector<std::string> setStr_list;

		///
		/// jpnchar_count = 12
		/// 
		/// 3 個一組 loop 10 次
		/// 4 個一組 loop 9 次
		/// 5 個一組 loop 8 次

		for (int i = 0; i < (jpnchar_count - quantityInASet + 1); ++i)
		{
			int currentCharCount = 0;
			std::string aSetStr;

			int jpnchar_idx = 0;
			for (std::string jpnchar : jpnchar_list)
			{
				if (jpnchar_idx >= i)
				{
					if (currentCharCount < quantityInASet)
					{
						++currentCharCount;

						aSetStr.append(jpnchar);
					}
				}
				++jpnchar_idx;
			}

			setStr_list.push_back(aSetStr);
		}


		// 輸出一組組分割好的 string
		//int idx = 0;
		//for (std::string str : setStr_list)
		//{
		//	std::cout << "idx: " << idx << " str: " << str << " size: " << str.size() << std::endl;
		//	++idx;
		//}

		return setStr_list;
	}

	std::vector<int> GetNonSameIndexList(std::vector<std::string>& smaller_list, std::vector<std::string>& larger_list)
	{
		const size_t SMALLER_LIST_SIZE = smaller_list.size();

		std::vector<int> non_same_idx_list;

		int sameCount = 0;
		int char_idx = 0;

		for (const std::string& s1 : larger_list)
		{
			if (SMALLER_LIST_SIZE > char_idx)
			{
				if (s1 == smaller_list[char_idx])
				{
					++sameCount;
				}
				else
				{
					non_same_idx_list.push_back(char_idx);
				}
			}


			++char_idx;
		}

		return non_same_idx_list;
	}

	int GetSameCount(std::vector<std::string>& smaller_list, std::vector<std::string>& larger_list)
	{
		const size_t SMALLER_LIST_SIZE = smaller_list.size();

		int sameCount = 0;
		int char_idx = 0;


		for (const std::string& s1 : larger_list)
		{
			if (SMALLER_LIST_SIZE > char_idx)
			{
				if (s1 == smaller_list[char_idx]) ++sameCount;
			}
			//else
			//{
			//	std::cout << "sameCount: " << sameCount << std::endl;
			//}

			++char_idx;
		}

		return sameCount;
	}

	/// <summary>
	/// 獲取碰到不同字就 +1 Index 的 SameCount;
	/// </summary>
	/// <param name="smaller_list"></param>
	/// <param name="larger_list"></param>
	/// <param name="nonSameIdxList"></param>
	/// <returns></returns>
	int GetSameCountByMoveIdx(std::vector<std::string>& smaller_list, std::vector<std::string>& larger_list, std::vector<int>& nonSameIdxList)
	{
		int sameCount = 0;
		int char_idx = 0;
		for (std::string s1 : smaller_list)
		{
			if (s1 == larger_list[char_idx])
			{
				++sameCount;
			}
			else
			{
				for (int nonSameIdx : nonSameIdxList)
				{
					if (smaller_list[nonSameIdx] == larger_list[char_idx])
					{
						++sameCount;
					}
					//else
					//{
					//	if (HasSimilarChar(larger_list[char_idx]))
					//	{
					//		std::vector<std::string> similarCharList = GetSimilarCharList(larger_list[char_idx]);
					//	}
					//}
				}
			}

			++char_idx;
		}

		return sameCount;
	}

	int GetSameCountBySimilarChar(std::vector<std::string> smaller_list, std::vector<std::string> larger_list)
	{
		//
		// smaller_list 灰簾石の瞳
		// larger_list  色雇五の睡
		//

		float sameCount = 0;
		int char_idx = 0;

		for (std::string lStr : larger_list)
		{
			if (smaller_list.size() > char_idx)
			{
				if (lStr == smaller_list[char_idx])
				{
					++sameCount;
				}
				else
				{

					if (!HasSimilarChar(larger_list[char_idx])) continue;

					std::vector<std::string> similarCharList = GetSimilarCharList(smaller_list[char_idx]);

					for (std::string similarChar : similarCharList)
					{

						if (similarChar == lStr) ++sameCount;
					}

				}
			}
			++char_idx;
		}

		return sameCount;
	}

	int GetSameCountByMoveIdxSimilarChar(std::vector<std::string> smaller_list, std::vector<std::string> larger_list, std::vector<int> nonSameIdxList)
	{
		//
		// smaller_list 灰簾石の瞳
		// larger_list  色雇五のだ睡
		//

		int sameCount = 0;
		int similarCount = 0;
		int char_idx = 0;
		for (std::string sStr : smaller_list)
		{
			if (sStr == larger_list[char_idx])
			{
				++sameCount;
			}
			else
			{
				for (int nonSameIdx : nonSameIdxList)
				{
					if (smaller_list[nonSameIdx] == larger_list[char_idx])
					{
						++sameCount;
					}
					else
					{
						if (!HasSimilarChar(larger_list[nonSameIdx])) continue;

						std::vector<std::string> similarCharList = GetSimilarCharList(larger_list[nonSameIdx]);

						for (std::string similarChar : similarCharList)
						{
								
							if (similarChar == sStr) { /*std::cout << "sStr: " << sStr << "  similarChar: " << similarChar << std::endl;*/  ++similarCount; }
						}

					}
				}
			}

			++char_idx;
		}


		//std::cout << "sameCount: " << sameCount << std::endl;
		//std::cout << "similarCount: " << similarCount << std::endl;
		sameCount += similarCount;


		return sameCount;
	}

	bool HasSimilarChar(std::string strChar)
	{
		json json = FileManager::GetInstance()->ReadJson(global::path::std_similar_char_list_json);

		//std::cout << "========== Start ==========" << std::endl;
		for (const auto& similarCharArr : json)
		{
			for (const auto& element : similarCharArr)
			{
				std::string similarChar = element.get<std::string>();

				if (strChar == similarChar) return true;
			}
		}
		//std::cout << "==========  End  ==========" << std::endl;

		return false;
	}

	std::vector<std::string> GetSimilarCharList(std::string strChar)
	{
		json json = FileManager::GetInstance()->ReadJson(global::path::std_similar_char_list_json);

		std::vector<std::string> similarCharList = {};
		int trueArrIdx = -1;

		//std::cout << "========== Start ==========" << std::endl;

		//
		// 獲取 strChar 所在的 similarCharArrIdx
		//
		int similarCharArrIdx = 0;
		for (const auto& similarCharArr : json)
		{
			for (int i = 0; i < similarCharArr.size(); ++i)
			{
				std::string similarChar = similarCharArr[i].get<std::string>();

				if (strChar == similarChar) trueArrIdx = similarCharArrIdx;
			}
			++similarCharArrIdx;
		}

		//
		// 將 trueSimilarChar 放入 similarCharList;
		//
		for (const auto& trueSimilarChar : json[trueArrIdx])
		{
			
			if (trueSimilarChar != strChar) similarCharList.push_back(trueSimilarChar);
		}

		//for (std::string str : similarCharList)
		//{
		//	std::cout << "strChar: " << strChar << "  trueSimilarChar: " << str << std::endl;
		//}

		//std::cout << "==========  End  ==========" << std::endl;

		return similarCharList;
	}

	float GetSimilarity(std::string str1, std::string str2)
	{
		float similarity = NOT_SIMILAR;

		if (str1 == str2) return MAX_SIMIALARITY;

		int str1CharCount = CountUTF8Char(str1);
		int str2CharCount = CountUTF8Char(str2);

		///
		/// 如果兩個字數不同
		/// 情況：str1CharCount > str2CharCount
		/// 
		if (str1CharCount > str2CharCount)
		{
			/*
			食いじん坊は伊達じゃよない
			食いしん坊は伊達じゃない
			*/
			float totalCount = str1CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);

			if (jpnchar_list_1.empty() || jpnchar_list_2.empty()) return NOT_SIMILAR;

			int firstSameCount = GetSameCount(jpnchar_list_2, jpnchar_list_1);

			if (firstSameCount <= 0) return NOT_SIMILAR;

			//if ((firstSameCount / totalCount) * 100 < SIMILAR_METRIC) return NOT_SIMILAR;

			std::vector<int> nonSameIdxList = GetNonSameIndexList(jpnchar_list_2, jpnchar_list_1);
			int movedIdxCount = GetSameCountByMoveIdx(jpnchar_list_2, jpnchar_list_1, nonSameIdxList);
			//int movedIdxSimilarCharCount = GetSameCountByMoveIdxSimilarChar(jpnchar_list_2, jpnchar_list_1, nonSameIdxList);

			//if (movedIdxSimilarCharCount > movedIdxCount)
			//{
			//	similarity = (movedIdxSimilarCharCount / totalCount) * 100;

			//	std::cout << "similarity: " << similarity << "%" << std::endl;

			//	return similarity >= SIMILAR_METRIC;
			//}

			float similarity = (std::max(firstSameCount, movedIdxCount) / totalCount) * 100;

			if (similarity >= SIMILAR_METRIC) return similarity;

			//std::cout << "firstSameCount: " << firstSameCount << std::endl;
			//std::cout << "movedIdxCount: " << movedIdxCount << std::endl;
			//std::cout << "similarity: " << similarity << "%" << std::endl;

			return NOT_SIMILAR;
		}
		///
		/// 如果兩個字數不同
		/// 情況：str1CharCount < str2CharCount
		/// 
		else if (str1CharCount < str2CharCount)
		{
			/*
			食いしん坊は伊達じゃない
			食いじん坊は伊達じゃよない
			*/

			/*
			了史みんなのオグリキャップ
			みんなのオグリキャップ
			*/
			float totalCount = str2CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);

			if (jpnchar_list_1.empty() || jpnchar_list_2.empty()) return NOT_SIMILAR;

			int firstSameCount = GetSameCount(jpnchar_list_1, jpnchar_list_2);

			if (firstSameCount <= 0) return NOT_SIMILAR;
			//if ((firstSameCount / totalCount) * 100 < SIMILAR_METRIC) return NOT_SIMILAR;

			std::vector<int> nonSameIdxList = GetNonSameIndexList(jpnchar_list_1, jpnchar_list_2);
			int movedIdxCount = GetSameCountByMoveIdx(jpnchar_list_1, jpnchar_list_2, nonSameIdxList);

			//int movedIdxSimilarCharCount = GetSameCountByMoveIdxSimilarChar(jpnchar_list_1, jpnchar_list_2, nonSameIdxList);

			//if (movedIdxSimilarCharCount > movedIdxCount)
			//{
			//	similarity = (movedIdxSimilarCharCount / totalCount) * 100;

			//	std::cout << "similarity: " << similarity << "%" << std::endl;

			//	return similarity >= SIMILAR_METRIC;
			//}

			float similarity = (std::max(firstSameCount, movedIdxCount) / totalCount) * 100;

			if (similarity >= SIMILAR_METRIC) return similarity;


			//std::cout << "firstSameCount: " << firstSameCount << std::endl;
			//std::cout << "movedIdxCount: " << movedIdxCount << std::endl;
			//std::cout << "similarity: " << similarity << "%" << std::endl;
		}
		///
		/// 如果兩個字數一致
		/// 
		else if (str1CharCount == str2CharCount)
		{
			float totalCount = str1CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);

			if (jpnchar_list_1.empty() || jpnchar_list_2.empty()) return NOT_SIMILAR;

			int firstSameCount = GetSameCount(jpnchar_list_1, jpnchar_list_2);
			if (firstSameCount <= 0) return NOT_SIMILAR;

			std::vector<int> nonSameIdxList = GetNonSameIndexList(jpnchar_list_1, jpnchar_list_2);
			int movedIdxCount = GetSameCountByMoveIdx(jpnchar_list_1, jpnchar_list_2, nonSameIdxList);

			float similarity = (std::max(firstSameCount, movedIdxCount) / totalCount) * 100;

			if (similarity >= SIMILAR_METRIC) return similarity;

			return NOT_SIMILAR;
		}
	}

	float GetCharacterNameSimilarity(std::string scannedName, std::string jsonDataName)
	{
		/*

		scannedName				キセキの白星オグリキャップ
		jsonDataName			オグリキャップ（キセキの白星）
		json_replaced_name		キセキの白星オグリキャップ

		*/

		// 定義正規表達式 pattern，捕獲角色名稱和別名
		std::regex pattern(u8"(.+?)（(.+?)）");

		// 使用 std::regex_replace 來替換字符串
		std::string json_replaced_name = std::regex_replace(jsonDataName, pattern, "$2$1");

		float similarity = GetSimilarity(scannedName, json_replaced_name);

		/* 
		// 舊的程式碼，先保留起來

		int scanned_count = CountUTF8Char(scannedName);
		int replaced_count = CountUTF8Char(json_replaced_name);
		float totalCount = scanned_count > replaced_count ? scanned_count : replaced_count;

		std::vector<std::string> scanned_char_list = utility::SplitJpnChar(scannedName);
		std::vector<std::string> json_replaced_char_list = utility::SplitJpnChar(json_replaced_name);

		int firstSameCount = GetSameCount(scanned_char_list, json_replaced_char_list);

		if (firstSameCount <= 1) return NOT_SIMILAR;

		std::cout << "firstSameCount: " << firstSameCount << std::endl;
		std::cout << "totalCount: " << totalCount << std::endl;
		std::cout << "similarity: " << firstSameCount / totalCount * 100 << std::endl;
		std::cout << "SIMILAR_METRIC: " << SIMILAR_METRIC << std::endl;

		if ((firstSameCount / totalCount) * 100 >= SIMILAR_METRIC)
		{
			similarity = (firstSameCount / totalCount) * 100;

			std::cout << similarity << std::endl;
		}
		*/



		return similarity;
	}



	bool IsRepeatingString(std::string scanned_text, int repeat_limit = 3)
	{
		int repeat_count = 0;

		std::vector<std::string> text_list = SplitJpnChar(scanned_text);

		for (auto it = text_list.begin(); it != text_list.end(); ++it)
		{
			
			std::string std_char = *it;  // 獲取當前迭代的值
			std::string next_std_char;


			// 獲取下次迭代的值
			++it;
			if (it != text_list.end())
			{
				next_std_char = *it;
				//std::cout << "Current: " << std_char << ", Next: " << next_std_char << std::endl;
			}
			--it;  // 將迭代器回退到原本的位置

			if (std_char == next_std_char)
				++repeat_count;
			else
				repeat_count = 0;

			if (repeat_count >= repeat_limit)
			{
				return true;
			}
		}

		return false;
	}

	bool HasBlackListedString(std::string scanned_text)
	{
		json black_listed_string_arr = FileManager::GetInstance()->ReadJson(global::path::std_black_listed_string_json);

		for (const auto str : black_listed_string_arr)
		{
			std::regex pattern(str);
			std::smatch match;
			if (std::regex_search(scanned_text, match, pattern))
			{
				std::cout << u8"匹配到黑名單字串: " << match[0] << std::endl;
				return true;
			}
		}

		return false;
	}

	bool IsStringTooLong(std::string scanned_text)
	{
		return scanned_text.size() > UTF8_CHAR_BYTE * 22;
	}


}


