#pragma once
/*

���������ާ@ Form ���K

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

