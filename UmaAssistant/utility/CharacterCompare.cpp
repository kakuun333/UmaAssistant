﻿#include "../stdafx.h"

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
		//if (input.size() < UTF8_CHAR_SIZE * 1)
		//{
		//	std::cout << u8"文字長度不足一個字" << std::endl;
		//	return std::vector<std::string>::;
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

	std::vector<int> GetNonSameIndexList(std::vector<std::string> smaller_list, std::vector<std::string> larger_list)
	{
		std::vector<int> non_same_idx_list;

		float sameCount = 0;
		int char_idx = 0;

		for (std::string s1 : larger_list)
		{
			if (smaller_list.size() > char_idx)
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

	int GetSameCount(std::vector<std::string> smaller_list, std::vector<std::string> larger_list)
	{
		float sameCount = 0;
		int char_idx = 0;
		for (std::string s1 : larger_list)
		{
			if (smaller_list.size() > char_idx)
				if (s1 == smaller_list[char_idx]) ++sameCount;

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
	int GetSameCountByMoveIdx(std::vector<std::string> smaller_list, std::vector<std::string> larger_list, std::vector<int> nonSameIdxList)
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
		json json = FileManager::GetInstance()->ReadJson(global::path::c_similar_char_list_json);

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
		json json = FileManager::GetInstance()->ReadJson(global::path::c_similar_char_list_json);

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



	/// <summary>
	/// 比較兩個字串是否相似
	/// </summary>
	/// <param name="str1"></param>
	/// <param name="str2"></param>
	/// <returns></returns>
	bool IsSimilar(std::string str1, std::string str2)
	{
#ifdef UMA_DEBUG
		std::cout << "================= TEST =================" << std::endl;
		std::cout << "str1: " << str1 << std::endl;
		std::cout << "str2: " << str2 << std::endl;
#endif

		int str1CharCount = CountUTF8Char(str1);
		int str2CharCount = CountUTF8Char(str2);

		float similarity = 0;


		///
		/// 如果兩個字數一致
		/// 
		if (str1CharCount == str2CharCount)
		{
			float totalCount = str1CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);


			int firstSameCount = GetSameCount(jpnchar_list_1, jpnchar_list_2);
			if (firstSameCount <= 0) return false;
			if ((firstSameCount / totalCount) * 100 < SIMILAR_METRIC) return false;



			//int sameCountBySimilarChar = GetSameCountBySimilarChar(jpnchar_list_1, jpnchar_list_2);
			//if (sameCountBySimilarChar > firstSameCount)
			//{
			//	
			//	similarity = (sameCountBySimilarChar / totalCount) * 100;

			//	std::cout << "sameCountBySimilarChar: " << sameCountBySimilarChar << std::endl;
			//	std::cout << "similarity: " << similarity << "%" << std::endl;

			//	return similarity > SIMILAR_METRIC;
			//}
			
			similarity = (firstSameCount / totalCount) * 100;

			std::cout << "similarity: " << similarity << "%" << std::endl;



			return (similarity == SIMIALAR_MAX) || (similarity > SIMILAR_METRIC);
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
			float totalCount = str2CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);

			int firstSameCount = GetSameCount(jpnchar_list_1, jpnchar_list_2);

			if (firstSameCount <= 0) return false;
			if ((firstSameCount / totalCount) * 100 < SIMILAR_METRIC) return false;

			std::vector<int> nonSameIdxList = GetNonSameIndexList(jpnchar_list_1, jpnchar_list_2);
			int movedIdxCount = GetSameCountByMoveIdx(jpnchar_list_1, jpnchar_list_2, nonSameIdxList);
			//int movedIdxSimilarCharCount = GetSameCountByMoveIdxSimilarChar(jpnchar_list_1, jpnchar_list_2, nonSameIdxList);

#ifdef UMA_DEBUG
			std::cout << "firstSameCount: " << firstSameCount << std::endl;
			std::cout << "movedIdxCount: " << movedIdxCount << std::endl;
#endif

			//if (movedIdxSimilarCharCount > movedIdxCount)
			//{
			//	similarity = (movedIdxSimilarCharCount / totalCount) * 100;

			//	std::cout << "similarity: " << similarity << "%" << std::endl;

			//	return similarity >= SIMILAR_METRIC;
			//}

			if (movedIdxCount > firstSameCount)
			{
				similarity = (movedIdxCount / totalCount) * 100;

				std::cout << "similarity: " << similarity << "%" << std::endl;

				return similarity >= SIMILAR_METRIC;
			}
		}
		///
		/// 如果兩個字數不同
		/// 情況：str1CharCount > str2CharCount
		/// 
		else if (str1CharCount > str2CharCount)
		{
			/*
			食いじん坊は伊達じゃよない
			食いしん坊は伊達じゃない
			*/
			float totalCount = str1CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);

			int firstSameCount = GetSameCount(jpnchar_list_2, jpnchar_list_1);

			if (firstSameCount <= 0) return false;
			if ((firstSameCount / totalCount) * 100 < SIMILAR_METRIC) return false;

			std::vector<int> nonSameIdxList = GetNonSameIndexList(jpnchar_list_2, jpnchar_list_1);
			int movedIdxCount = GetSameCountByMoveIdx(jpnchar_list_2, jpnchar_list_1, nonSameIdxList);
			//int movedIdxSimilarCharCount = GetSameCountByMoveIdxSimilarChar(jpnchar_list_2, jpnchar_list_1, nonSameIdxList);


#ifdef UMA_DEBUG
			std::cout << "firstSameCount: " << firstSameCount << std::endl;
			std::cout << "movedIdxCount: " << movedIdxCount << std::endl;
#endif
			//if (movedIdxSimilarCharCount > movedIdxCount)
			//{
			//	similarity = (movedIdxSimilarCharCount / totalCount) * 100;

			//	std::cout << "similarity: " << similarity << "%" << std::endl;

			//	return similarity >= SIMILAR_METRIC;
			//}


			if (movedIdxCount > firstSameCount)
			{
				similarity = (movedIdxCount / totalCount) * 100;

				std::cout << "similarity: " << similarity << "%" << std::endl;

				return similarity >= SIMILAR_METRIC;
			}

			return false;
		}
	}



	float GetSimilarity(std::string str1, std::string str2)
	{
		int str1CharCount = CountUTF8Char(str1);
		int str2CharCount = CountUTF8Char(str2);

		float similarity = 0;


		///
		/// 如果兩個字數一致
		/// 
		if (str1CharCount == str2CharCount)
		{
			float totalCount = str1CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);


			int firstSameCount = GetSameCount(jpnchar_list_1, jpnchar_list_2);
			if (firstSameCount <= 0) return NOT_SIMILAR;
			if ((firstSameCount / totalCount) * 100 < SIMILAR_METRIC) return NOT_SIMILAR;
			if (firstSameCount == totalCount) return (firstSameCount / totalCount) * 100;

			//int sameCountBySimilarChar = GetSameCountBySimilarChar(jpnchar_list_1, jpnchar_list_2);
			//if (sameCountBySimilarChar > firstSameCount)
			//{
	
			//	similarity = (sameCountBySimilarChar / totalCount) * 100;

			//	std::cout << "sameCountBySimilarChar: " << sameCountBySimilarChar << std::endl;
			//	std::cout << "similarity: " << similarity << "%" << std::endl;

			//	if (similarity >= SIMILAR_METRIC)
			//	{
			//		return similarity;
			//	}
			//}


			similarity = (firstSameCount / totalCount) * 100;

			std::cout << "similarity: " << similarity << "%" << std::endl;


			if (similarity >= SIMILAR_METRIC)
			{
				return similarity;
			}

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

			if (firstSameCount >= movedIdxCount)
			{
				similarity = (firstSameCount / totalCount) * 100;

				if (similarity < SIMILAR_METRIC) return NOT_SIMILAR;

				std::cout << "similarity: " << similarity << "%" << std::endl;

				return similarity;
			}
			else if (firstSameCount < movedIdxCount)
			{
				similarity = (movedIdxCount / totalCount) * 100;

				if (similarity < SIMILAR_METRIC) return NOT_SIMILAR;

				std::cout << "similarity: " << similarity << "%" << std::endl;

				return similarity;
			}

			//std::cout << "firstSameCount: " << firstSameCount << std::endl;
			//std::cout << "movedIdxCount: " << movedIdxCount << std::endl;
			//std::cout << "similarity: " << similarity << "%" << std::endl;
		}
		///
		/// 如果兩個字數不同
		/// 情況：str1CharCount > str2CharCount
		/// 
		else if (str1CharCount > str2CharCount)
		{
			/*
			食いじん坊は伊達じゃよない
			食いしん坊は伊達じゃない
			*/
			float totalCount = str1CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);

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

			if (firstSameCount >= movedIdxCount)
			{
				similarity = (firstSameCount / totalCount) * 100;

				if (similarity < SIMILAR_METRIC) return NOT_SIMILAR;

				std::cout << "similarity: " << similarity << "%" << std::endl;

				return similarity;
			}
			else if (firstSameCount < movedIdxCount)
			{
				similarity = (movedIdxCount / totalCount) * 100;

				if (similarity < SIMILAR_METRIC) return NOT_SIMILAR;

				std::cout << "similarity: " << similarity << "%" << std::endl;

				return similarity;
			}

			//std::cout << "firstSameCount: " << firstSameCount << std::endl;
			//std::cout << "movedIdxCount: " << movedIdxCount << std::endl;
			//std::cout << "similarity: " << similarity << "%" << std::endl;

			return NOT_SIMILAR;
		}
	}

	float GetCharacterNameSimilarity(std::string scannedName, std::string jsonDataName)
	{
		//
		// scannedName  キセキの白星オグリキャップ
		// jsonDataName オグリキャップ（キセキの白星）

		float similarity = NOT_SIMILAR;

		// 定義正規表達式模式，使用捕獲組
		std::regex pattern(u8"(.+?)（(.+?)）");

		// 使用 std::regex_replace 來替換字符串
		std::string replaced_name = std::regex_replace(jsonDataName, pattern, "$2$1");

		int scanned_count = CountUTF8Char(scannedName);
		int replaced_count = CountUTF8Char(replaced_name);
		float totalCount = scanned_count > replaced_count ? scanned_count : replaced_count;

		std::vector<std::string> scanned_char_list = utility::SplitJpnChar(scannedName);
		std::vector<std::string> replaced_char_list = utility::SplitJpnChar(replaced_name);

		int firstSameCount = GetSameCount(scanned_char_list, replaced_char_list);


		if (firstSameCount <= 1) return NOT_SIMILAR;


		//std::cout << 111 << std::endl;

		std::cout << "firstSameCount: " << firstSameCount << std::endl;
		std::cout << "totalCount: " << totalCount << std::endl;
		std::cout << "similarity: " << firstSameCount / totalCount * 100 << std::endl;
		std::cout << "SIMILAR_METRIC: " << SIMILAR_METRIC << std::endl;
		if ((firstSameCount / totalCount) * 100 >= SIMILAR_METRIC)
		{
			//std::cout << 222 << std::endl;
			similarity = (firstSameCount / totalCount) * 100;

			std::cout << similarity << std::endl;
		}
		//std::cout << 333 << std::endl;

		return similarity;
	}










}

