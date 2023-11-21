#include "FormControl.h"

using namespace System;

namespace utility
{
	namespace formctrl
	{
		void Add(Control^ parentControl, Control^ childControl)
		{
			if (parentControl->InvokeRequired)
			{
				// 如果不在 UI 執行緒上，則使用 Invoke 方法
				parentControl->Invoke(gcnew Action<Control^, Control^>(&Add), parentControl, childControl);
			}
			else
			{
				// 在 UI 執行緒上執行操作
				parentControl->Controls->Add(childControl);
			}
		}

		void Text(Control^ control, System::String^ text)
		{
			if (control->InvokeRequired)
			{
				control->Invoke(gcnew Action<Control^, String^>(&Text), control, text);
			}
			else
			{
				control->Text = text;
			}
		}

		void Clear(Control^ control)
		{
			if (control->InvokeRequired)
			{
				control->Invoke(gcnew Action<Control^>(&Clear), control);
			}
			else
			{
				control->Controls->Clear();
			}
		}
	}
};