#include "PreviewForm.h"
#include "../stdafx.h"


namespace UmaAssistant
{
	PreviewForm::PreviewForm(void)
	{
		InitializeComponent();
		//
		//TODO:  �b���[�J�غc�禡�{���X
		//

		// ��� .resx �ɪ����|�� UmaAssistant/UmaAssistant/form
		/*System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(L"UmaAssistant.UmaAssistant.form.PreviewForm",
			System::Reflection::Assembly::GetExecutingAssembly());*/

			// ���U FormClosing �ƥ�
		this->FormClosing += gcnew FormClosingEventHandler(this, &PreviewForm::FormClosingHandler);
		window_listbox->SelectedIndexChanged += gcnew EventHandler(this, &PreviewForm::OnSelectedIndexChanged);
	}

	void PreviewForm::OnSelectedIndexChanged(Object^ sender, EventArgs^ e)
	{
		// �B�z��ܶ��ا�諸�޿�
		if (window_listbox->SelectedIndex != -1)
		{
			System::String^ selectedItem = dynamic_cast<System::String^>(window_listbox->SelectedItem);

			GameWindowFinder* windowFinder = GameWindowFinder::GetInstance();

			std::map<std::string, HWND> windowDict = windowFinder->GetWindowDict();

			std::string windowName = utility::systemStr2std(selectedItem);

			if (windowDict[windowName])
			{
				windowFinder->SetCurrentGameWindow(windowName);
				windowFinder->SetCurrentGameWindowName(windowName);

				global::config->GameWindowName = windowName;
				global::config->WriteToJson();
			}
		}
	}


	void PreviewForm::FormClosingHandler(Object^ sender, FormClosingEventArgs^ e)
	{
		// ���������ާ@�A�קK form �Q�۰�����
		e->Cancel = true;

		// ���õ���
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


