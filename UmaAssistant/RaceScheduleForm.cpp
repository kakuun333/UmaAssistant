#include "RaceScheduleForm.h"

// class
#include "cppsrc/class/Config.h"

// util
#include "cppsrc/util/CharacterConvert.h"



#using "CSharpRuntime/UmaCSharpLibrary.dll"

using namespace System::Collections::Generic;


namespace UmaAssistant
{
#pragma region EventHandler 函式
	System::Void RaceScheduleForm::OnWebMessageReceived(System::Object^ sender, CoreWebView2WebMessageReceivedEventArgs^ e)
	{
		System::String^ message = e->TryGetWebMessageAsString();

		if (System::String::IsNullOrEmpty(message))
		{
			std::cout << u8"[UmaForm] WebMessage 是空的:" << util::systemStr2std(message) << std::endl;
			return;
		}

		json j_msg = json::parse(util::systemStr2std(message));

		//UmaCSharp::FileManager::Instance

		FileManager* fileManager = FileManager::GetInstance();
		

		if (j_msg["messageType"] == "saveRaceScheduleData")
		{
			//for (const auto& raceObj : j_msg["messageContent"]["raceObjectList"])
			//{
			//	std::string race_name = raceObj["race_name"].get<std::string>();
			//	//std::string race_grade = raceObj["race_grade"].get<std::string>();
			//	//std::string race_track = raceObj["race_track"].get<std::string>();
			//	//std::string racecourse = raceObj["racecourse"].get<std::string>();
			//	//std::string race_distance = raceObj["race_distance"].get<std::string>();
			//	//std::string race_distance_type = raceObj["race_distance_type"].get<std::string>();
			//	//std::string race_direction = raceObj["race_direction"].get<std::string>();
			//	//std::string race_date_grade = raceObj["race_date_grade"].get<std::string>();
			//	//std::string race_date_day = raceObj["race_date_day"].get<std::string>();
			//}

			std::string fileName = j_msg["messageContent"]["fileName"].get<std::string>();
			fileManager->WriteJson(global::path::std_UmaTemp + "\\" + fileName, j_msg["messageContent"]["raceObjectList"].dump(2));
		}
		else if (j_msg["messageType"] == "loadRaceScheduleData")
		{
			DataManager::GetInstance()->SetRaceScheduleJson(json::parse(j_msg["messageContent"].get<std::string>()));

			UmaCSharp::UmaLog::d("RaceScheduleForm", "已載入比賽排程！");
		}
	}

	System::Void RaceScheduleForm::OnNavigationCompleted(System::Object^ sender, CoreWebView2NavigationCompletedEventArgs^ e)
	{

	}

	System::Void RaceScheduleForm::RaceScheduleForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
	{
		// 取消關閉操作，避免 form 被自動釋放
		e->Cancel = true;
		// 隱藏視窗
		this->Hide();
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