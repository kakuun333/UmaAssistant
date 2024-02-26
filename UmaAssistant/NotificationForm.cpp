#include "NotificationForm.h"


namespace UmaAssistant
{
	System::Void NotificationForm::closeForm_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}

#pragma region Form Event
	System::Void NotificationForm::NotificationForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		_isDraggingForm = true;
		_dragOffset.X = e->X;
		_dragOffset.Y = e->Y;
	}
	System::Void NotificationForm::NotificationForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (_isDraggingForm)
		{
			System::Drawing::Point currentFormPos = PointToScreen(System::Drawing::Point(e->X, e->Y));
			this->Location = System::Drawing::Point(currentFormPos.X - _dragOffset.X, currentFormPos.Y - _dragOffset.Y);
		}
	}
	System::Void NotificationForm::NotificationForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		_isDraggingForm = false;
	}

	System::Void NotificationForm::NotificationForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
	{
		// 取消關閉操作，避免 form 被自動釋放
		e->Cancel = true;
		// 隱藏視窗
		this->Hide();
	}
#pragma endregion
}
