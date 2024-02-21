#include "FormControl.h"



namespace util
{
	namespace formctrl
	{
		System::Void Add(Control^ parentControl, Control^ childControl)
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

		System::Void Text(Control^ control, System::String^ text)
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

		System::Void Clear(Control^ control)
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

		System::Void ForeColor(Control^ control, int r = 255, int g = 255, int b = 255)
		{
			if (control->InvokeRequired)
			{
				control->Invoke(gcnew Action<Control^, int, int, int>(&ForeColor), control, r, g, b);
			}
			else
			{
				control->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(r)),
					static_cast<System::Int32>(static_cast<System::Byte>(g)), static_cast<System::Int32>(static_cast<System::Byte>(b)));
			}
		}
	}
};