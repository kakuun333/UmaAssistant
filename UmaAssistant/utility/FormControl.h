#pragma once
/*

讓跨執行緒操作 Form 更方便

*/


using namespace System::Windows::Forms;


namespace utility
{
	namespace formctrl
	{
		void Add(Control^ parentControl, Control^ childControl);

		void Text(Control^ control, System::String^ text);

		void Clear(Control^ control);
	}
};

