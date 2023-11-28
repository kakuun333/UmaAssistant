#pragma once
/*

讓跨執行緒操作 Form 更方便

*/

#include <vcclr.h>

using namespace System;
using namespace System::Windows::Forms;


namespace utility
{
	namespace formctrl
	{
		System::Void Add(Control^ parentControl, Control^ childControl);

		System::Void Text(Control^ control, System::String^ text);

		System::Void Clear(Control^ control);

		System::Void ForeColor(Control^ control, int r, int g, int b);
	}
};

