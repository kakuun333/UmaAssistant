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
		//std::vector<std::string> larger_list = jpnchar_list_1.size() > jpnchar_list_2.size() ? jpnchar_list_1 : jpnchar_list_2;
		//std::vector<std::string> smaller_list = larger_list == jpnchar_list_1 ? jpnchar_list_2 : jpnchar_list_1;

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
		//std::vector<std::string> larger_list = jpnchar_list_1.size() > jpnchar_list_2.size() ? jpnchar_list_1 : jpnchar_list_2;
		//std::vector<std::string> smaller_list = larger_list == jpnchar_list_1 ? jpnchar_list_2 : jpnchar_list_1;

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


	bool IsSimilar(std::string str1, std::string str2)
	{
#ifdef UMA_DEBUG
		std::cout << "================= TEST =================" << std::endl;
		std::cout << "str1: " << str1 << std::endl;
		std::cout << "str2: " << str2 << std::endl;
#endif

		int str1CharCount = CountUTF8Char(str1);
		int str2CharCount = CountUTF8Char(str2);
		///
		/// 如果兩個字數一致
		/// 
		if (str1CharCount == str2CharCount)
		{
			float totalCount = str1CharCount;

			std::vector<std::string> jpnchar_list_1 = utility::SplitJpnChar(str1);
			std::vector<std::string> jpnchar_list_2 = utility::SplitJpnChar(str2);

			float sameCount = 0;

			int char_idx = 0;
			for (std::string s1 : jpnchar_list_1)
			{
				if (s1 == jpnchar_list_2[char_idx]) ++sameCount;

				++char_idx;
			}
			//std::cout << "same_count: " << sameCount << std::endl;
			//std::cout << "similarity: " << (sameCount / totalCount) * 100 << "%" << std::endl;

			float similarity = (sameCount / totalCount) * 100;

			return similarity > SIMILAR_METRIC;
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
			
			std::vector<int> nonSameIdxList = GetNonSameIndexList(jpnchar_list_1, jpnchar_list_2);

			int secondSameCount = 0;
			int char_idx = 0;
			for (std::string s1 : jpnchar_list_1)
			{
				if (s1 == jpnchar_list_2[char_idx])
				{
					++secondSameCount;
				}
				else
				{
					for (int nonSameIdx : nonSameIdxList)
					{
						if (jpnchar_list_1[nonSameIdx] == jpnchar_list_2[char_idx]) ++secondSameCount;
					}
				}

				++char_idx;
			}

#ifdef UMA_DEBUG
			std::cout << "firstSameCount: " << firstSameCount << std::endl;
			std::cout << "secondSameCount: " << secondSameCount << std::endl;
#endif

			if (secondSameCount > firstSameCount)
			{
				float similarity = (secondSameCount / totalCount) * 100;
				std::cout << "similarity: " << (secondSameCount / totalCount) * 100 << "%" << std::endl;

				return similarity > SIMILAR_METRIC;
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

			std::vector<int> nonSameIdxList = GetNonSameIndexList(jpnchar_list_2, jpnchar_list_1);

			int secondSameCount = 0;
			int char_idx = 0;
			for (std::string s1 : jpnchar_list_2)
			{
				if (s1 == jpnchar_list_1[char_idx])
				{
					++secondSameCount;
				}
				else
				{
					for (int nonSameIdx : nonSameIdxList)
					{
						if (jpnchar_list_2[nonSameIdx] == jpnchar_list_1[char_idx]) ++secondSameCount;
					}
				}

				++char_idx;
			}

#ifdef UMA_DEBUG
			std::cout << "firstSameCount: " << firstSameCount << std::endl;
			std::cout << "secondSameCount: " << secondSameCount << std::endl;
#endif

			if (secondSameCount > firstSameCount)
			{
				float similarity = (secondSameCount / totalCount) * 100;

				std::cout << "similarity: " << (secondSameCount / totalCount) * 100 << "%" << std::endl;

				return similarity > SIMILAR_METRIC;
			}
		}

#ifdef UMA_DEBUG
		std::cout << "================= TEST END =================" << std::endl;
#endif
		return false;
	}
}