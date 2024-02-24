#include "RaceScheduleForm.h"

// class
#include "cppsrc/class/Config.h"

// util
#include "cppsrc/util/CharacterConvert.h"


using namespace System::Collections::Generic;


namespace UmaAssistant
{
#pragma region EventHandler 函式
	System::Void RaceScheduleForm::OnWebMessageReceived(System::Object^ sender, CoreWebView2WebMessageReceivedEventArgs^ e)
	{

	}

	System::Void RaceScheduleForm::OnNavigationCompleted(System::Object^ sender, CoreWebView2NavigationCompletedEventArgs^ e)
	{
		
	}
#pragma endregion

	RaceScheduleForm::RaceScheduleForm(void)
	{
		InitializeComponent();
		//
		//TODO:  在此加入建構函式程式碼
		//

		// 提取 config 資料
		System::String^ port = util::stdStr2system(Config::GetInstance()->LocalServer["Port"]);

		raceScheduleWebView2->WebMessageReceived += gcnew System::EventHandler<CoreWebView2WebMessageReceivedEventArgs^>(this, &RaceScheduleForm::OnWebMessageReceived);
		raceScheduleWebView2->NavigationCompleted += gcnew System::EventHandler<CoreWebView2NavigationCompletedEventArgs^>(this, &RaceScheduleForm::OnNavigationCompleted);
		raceScheduleWebView2->Source = gcnew System::Uri(System::String::Format("http://localhost:{0}/race_schedule.html", port), System::UriKind::Absolute);
	}

#pragma region Button Click
	System::Void RaceScheduleForm::minimize_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
	}
	System::Void RaceScheduleForm::closeForm_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
#pragma endregion

#pragma region Mouse Event
	System::Void RaceScheduleForm::RaceScheduleForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		_isDraggingForm = true;
		_dragOffset.X = e->X;
		_dragOffset.Y = e->Y;
	}
	System::Void RaceScheduleForm::RaceScheduleForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		_isDraggingForm = false;
	}
	System::Void RaceScheduleForm::RaceScheduleForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (_isDraggingForm)
		{
			System::Drawing::Point currentFormPos = PointToScreen(System::Drawing::Point(e->X, e->Y));
			this->Location = System::Drawing::Point(currentFormPos.X - _dragOffset.X, currentFormPos.Y - _dragOffset.Y);
		}
	}
#pragma endregion
}