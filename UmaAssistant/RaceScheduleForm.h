#pragma once

#using "control/Microsoft.Web.WebView2.Core.dll"
#using "control/Microsoft.Web.WebView2.WinForms.dll"
using namespace Microsoft::Web::WebView2::Core;
using namespace Microsoft::Web::WebView2::WinForms;

namespace UmaAssistant {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// RaceScheduleForm 的摘要
	/// </summary>
	public ref class RaceScheduleForm : public System::Windows::Forms::Form
	{
	public:
		RaceScheduleForm(void);
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~RaceScheduleForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ icon_pictureBox;
	public: System::Windows::Forms::Label^ raceSchedule_label;
	private: UmaCustomControl::RoundedButton^ minimize_btn;
	private: UmaCustomControl::RoundedButton^ closeForm_btn;
	public: Microsoft::Web::WebView2::WinForms::WebView2^ raceScheduleWebView2;
	private:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RaceScheduleForm::typeid));
			this->icon_pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->raceSchedule_label = (gcnew System::Windows::Forms::Label());
			this->minimize_btn = (gcnew UmaCustomControl::RoundedButton());
			this->closeForm_btn = (gcnew UmaCustomControl::RoundedButton());
			this->raceScheduleWebView2 = (gcnew Microsoft::Web::WebView2::WinForms::WebView2());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->raceScheduleWebView2))->BeginInit();
			this->SuspendLayout();
			// 
			// icon_pictureBox
			// 
			this->icon_pictureBox->BackColor = System::Drawing::Color::Transparent;
			this->icon_pictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"icon_pictureBox.Image")));
			this->icon_pictureBox->Location = System::Drawing::Point(10, 5);
			this->icon_pictureBox->Name = L"icon_pictureBox";
			this->icon_pictureBox->Size = System::Drawing::Size(24, 24);
			this->icon_pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->icon_pictureBox->TabIndex = 9;
			this->icon_pictureBox->TabStop = false;
			// 
			// raceSchedule_label
			// 
			this->raceSchedule_label->AutoSize = true;
			this->raceSchedule_label->BackColor = System::Drawing::Color::Transparent;
			this->raceSchedule_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->raceSchedule_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->raceSchedule_label->Location = System::Drawing::Point(39, 7);
			this->raceSchedule_label->Name = L"raceSchedule_label";
			this->raceSchedule_label->Size = System::Drawing::Size(74, 24);
			this->raceSchedule_label->TabIndex = 26;
			this->raceSchedule_label->Text = L"比賽排程";
			// 
			// minimize_btn
			// 
			this->minimize_btn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->minimize_btn->BackColor = System::Drawing::Color::Transparent;
			this->minimize_btn->FlatAppearance->BorderSize = 0;
			this->minimize_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->minimize_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->minimize_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->minimize_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->minimize_btn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"minimize_btn.Image")));
			this->minimize_btn->Location = System::Drawing::Point(620, 1);
			this->minimize_btn->Name = L"minimize_btn";
			this->minimize_btn->Radius = 10;
			this->minimize_btn->Size = System::Drawing::Size(39, 32);
			this->minimize_btn->TabIndex = 28;
			this->minimize_btn->TabStop = false;
			this->minimize_btn->UseVisualStyleBackColor = false;
			this->minimize_btn->Click += gcnew System::EventHandler(this, &RaceScheduleForm::minimize_btn_Click);
			// 
			// closeForm_btn
			// 
			this->closeForm_btn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->closeForm_btn->BackColor = System::Drawing::Color::Transparent;
			this->closeForm_btn->FlatAppearance->BorderSize = 0;
			this->closeForm_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(125)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->closeForm_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->closeForm_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->closeForm_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->closeForm_btn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"closeForm_btn.Image")));
			this->closeForm_btn->Location = System::Drawing::Point(664, 1);
			this->closeForm_btn->Name = L"closeForm_btn";
			this->closeForm_btn->Radius = 10;
			this->closeForm_btn->Size = System::Drawing::Size(40, 32);
			this->closeForm_btn->TabIndex = 27;
			this->closeForm_btn->TabStop = false;
			this->closeForm_btn->UseVisualStyleBackColor = false;
			this->closeForm_btn->Click += gcnew System::EventHandler(this, &RaceScheduleForm::closeForm_btn_Click);
			// 
			// raceScheduleWebView2
			// 
			this->raceScheduleWebView2->AllowExternalDrop = true;
			this->raceScheduleWebView2->CreationProperties = nullptr;
			this->raceScheduleWebView2->DefaultBackgroundColor = System::Drawing::Color::White;
			this->raceScheduleWebView2->Location = System::Drawing::Point(12, 34);
			this->raceScheduleWebView2->Name = L"raceScheduleWebView2";
			this->raceScheduleWebView2->Size = System::Drawing::Size(681, 504);
			this->raceScheduleWebView2->TabIndex = 29;
			this->raceScheduleWebView2->ZoomFactor = 1;
			// 
			// RaceScheduleForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(705, 550);
			this->Controls->Add(this->raceScheduleWebView2);
			this->Controls->Add(this->minimize_btn);
			this->Controls->Add(this->closeForm_btn);
			this->Controls->Add(this->raceSchedule_label);
			this->Controls->Add(this->icon_pictureBox);
			this->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"RaceScheduleForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"RaceScheduleForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &RaceScheduleForm::RaceScheduleForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &RaceScheduleForm::RaceScheduleForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &RaceScheduleForm::RaceScheduleForm_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->raceScheduleWebView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


#pragma region 私人變數
	private: bool _isDraggingForm = false;
	private: System::Drawing::Point _dragOffset;
#pragma endregion

#pragma region EventHandler 函式
	public: System::Void OnWebMessageReceived(System::Object^ sender, CoreWebView2WebMessageReceivedEventArgs^ e);
	public: System::Void OnNavigationCompleted(System::Object^ sender, CoreWebView2NavigationCompletedEventArgs^ e);
#pragma endregion

#pragma region Button Click
	private: System::Void minimize_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void closeForm_btn_Click(System::Object^ sender, System::EventArgs^ e);
#pragma endregion

#pragma region Mouse Event
	private: System::Void RaceScheduleForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void RaceScheduleForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void RaceScheduleForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
#pragma endregion
};
}
