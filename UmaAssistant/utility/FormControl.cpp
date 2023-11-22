#include "FormControl.h"



namespace utility
{
	namespace formctrl
	{
		System::Void Add(Control^ parentControl, Control^ childControl)
		{
			if (parentControl->InvokeRequired)
			{
				// �p�G���b UI ������W�A�h�ϥ� Invoke ��k
				parentControl->Invoke(gcnew Action<Control^, Control^>(&Add), parentControl, childControl);
			}
			else
			{
				// �b UI ������W����ާ@
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
	}
};