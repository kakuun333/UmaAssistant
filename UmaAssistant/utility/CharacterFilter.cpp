#include "CharacterFilter.h"

namespace utility
{
	System::String^ RemoveSpace(System::String^ str)
	{
		System::String^ removed_n = str->Replace("\n", "");
		System::String^ removed_space = removed_n->Replace(" ", "");
		System::String^ removed_widthspace = removed_space->Replace("¡@", "");
		return removed_widthspace;
	}
}