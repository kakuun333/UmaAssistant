﻿#pragma once

#include <memory>

namespace util
{
	std::unique_ptr<char[]> CombineConstChar(const char* str1, const char* str2);
};

