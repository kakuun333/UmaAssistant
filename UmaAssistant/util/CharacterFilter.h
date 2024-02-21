#pragma once

#include <string>
#include <regex>


// .NET
using namespace System::Text::RegularExpressions;

namespace util
{

	std::string RemoveSpace(std::string input);

	System::String^ RemoveSpace(System::String^ input);

	System::String^ FormNewLineFormat(System::String^ input);

	std::string ReplaceSpecialString(std::string input);
};
