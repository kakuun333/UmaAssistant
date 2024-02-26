#pragma once

namespace UmaAssistant {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// NotificationForm 的摘要
	/// </summary>
	public ref class NotificationForm : public System::Windows::Forms::Form
	{
	public:
		NotificationForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			this->Show();
			this->Hide();
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~NotificationForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: UmaCustomControl::RoundedButton^ closeForm_btn;
	public: System::Windows::Forms::Label^ raceSchedule_label;
	private: System::Windows::Forms::PictureBox^ icon_pictureBox;
	public: System::Windows::Forms::Label^ label1;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(NotificationForm::typeid));
			this->closeForm_btn = (gcnew UmaCustomControl::RoundedButton());
			this->raceSchedule_label = (gcnew System::Windows::Forms::Label());
			this->icon_pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->BeginInit();
			this->SuspendLayout();
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
			this->closeForm_btn->Location = System::Drawing::Point(433, 0);
			this->closeForm_btn->Name = L"closeForm_btn";
			this->closeForm_btn->Radius = 10;
			this->closeForm_btn->Size = System::Drawing::Size(40, 32);
			this->closeForm_btn->TabIndex = 28;
			this->closeForm_btn->TabStop = false;
			this->closeForm_btn->UseVisualStyleBackColor = false;
			this->closeForm_btn->Click += gcnew System::EventHandler(this, &NotificationForm::closeForm_btn_Click);
			// 
			// raceSchedule_label
			// 
			this->raceSchedule_label->AutoSize = true;
			this->raceSchedule_label->BackColor = System::Drawing::Color::Transparent;
			this->raceSchedule_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->raceSchedule_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->raceSchedule_label->Location = System::Drawing::Point(37, 9);
			this->raceSchedule_label->Name = L"raceSchedule_label";
			this->raceSchedule_label->Size = System::Drawing::Size(42, 24);
			this->raceSchedule_label->TabIndex = 30;
			this->raceSchedule_label->Text = L"通知";
			// 
			// icon_pictureBox
			// 
			this->icon_pictureBox->BackColor = System::Drawing::Color::Transparent;
			this->icon_pictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"icon_pictureBox.Image")));
			this->icon_pictureBox->Location = System::Drawing::Point(8, 7);
			this->icon_pictureBox->Name = L"icon_pictureBox";
			this->icon_pictureBox->Size = System::Drawing::Size(24, 24);
			this->icon_pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->icon_pictureBox->TabIndex = 29;
			this->icon_pictureBox->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label1->Location = System::Drawing::Point(160, 176);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(154, 24);
			this->label1->TabIndex = 31;
			this->label1->Text = L"偵測到已安排的賽事";
			// 
			// NotificationForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(473, 413);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->raceSchedule_label);
			this->Controls->Add(this->icon_pictureBox);
			this->Controls->Add(this->closeForm_btn);
			this->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(5);
			this->Name = L"NotificationForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"NotificationForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &NotificationForm::NotificationForm_FormClosing);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &NotificationForm::NotificationForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &NotificationForm::NotificationForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &NotificationForm::NotificationForm_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


#pragma region 私人變數
	private: bool _isDraggingForm = false;
	private: System::Drawing::Point _dragOffset;
#pragma endregion

	private: System::Void closeForm_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void NotificationForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void NotificationForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void NotificationForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void NotificationForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
};
}
