#include "PreviewForm.h"

// STL
#include <map>
#include <string>

// class
#include "cppsrc/class/GameWindowFinder.h"

// global
//#include "global/global.h"

namespace UmaAssistant
{
	PreviewForm::PreviewForm(void)
	{
		InitializeComponent();
		//
		//TODO:  在此加入建構函式程式碼
		//

		// 更改 .resx 檔的路徑為 UmaAssistant/UmaAssistant/form
		/*System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(L"UmaAssistant.UmaAssistant.form.PreviewForm",
			System::Reflection::Assembly::GetExecutingAssembly());*/

			// 註冊 FormClosing 事件
		this->FormClosing += gcnew FormClosingEventHandler(this, &PreviewForm::FormClosingHandler);
		window_listbox->SelectedIndexChanged += gcnew EventHandler(this, &PreviewForm::OnSelectedIndexChanged);
	}

	void PreviewForm::OnSelectedIndexChanged(Object^ sender, EventArgs^ e)
	{
		// 處理選擇項目更改的邏輯
		if (window_listbox->SelectedIndex != -1)
		{
			System::String^ selectedItem = dynamic_cast<System::String^>(window_listbox->SelectedItem);

			GameWindowFinder* windowFinder = GameWindowFinder::GetInstance();

			std::map<std::string, HWND> windowDict = windowFinder->GetWindowDict();

			std::string windowName = util::systemStr2std(selectedItem);

			if (windowDict[windowName])
			{
				windowFinder->SetCurrentGameWindow(windowName);
				windowFinder->SetCurrentGameWindowName(windowName);

				Config::GetInstance()->GameWindowName = windowName;
				Config::GetInstance()->WriteToJson();
			}
		}
	}


	void PreviewForm::FormClosingHandler(Object^ sender, FormClosingEventArgs^ e)
	{
		// 取消關閉操作，避免 form 被自動釋放
		e->Cancel = true;

		// 隱藏視窗
		this->Hide();
	}


	System::Void PreviewForm::close_form_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
	System::Void PreviewForm::minimize_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
	}

	System::Void PreviewForm::previewForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		draggingForm = true;
		dragOffset.X = e->X;
		dragOffset.Y = e->Y;
	}

	System::Void PreviewForm::previewForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		draggingForm = false;
	}

	System::Void PreviewForm::previewForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (draggingForm)
		{
			System::Drawing::Point currentFormPos = PointToScreen(System::Drawing::Point(e->X, e->Y));
			this->Location = System::Drawing::Point(currentFormPos.X - dragOffset.X, currentFormPos.Y - dragOffset.Y);
		}
	}
}


