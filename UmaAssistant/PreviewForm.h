#pragma once

namespace UmaAssistant {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// PreviewForm 的摘要
	/// </summary>
	public ref class PreviewForm : public System::Windows::Forms::Form
	{
	public:
		PreviewForm(void);

		void FormClosingHandler(Object^ sender, FormClosingEventArgs^ e);


		void OnSelectedIndexChanged(Object^ sender, EventArgs^ e);

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~PreviewForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::ListBox^ window_listbox;
	private: System::Windows::Forms::Label^ select_window_label;
	public:

	private: System::Windows::Forms::PictureBox^ icon_pictureBox;
	private: System::Windows::Forms::Button^ minimize_btn;
	private: System::Windows::Forms::Button^ close_form_btn;
	private: System::Windows::Forms::Label^ title_select_window_label;


	public:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;
		bool draggingForm = false;
		System::Drawing::Point dragOffset;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(PreviewForm::typeid));
			this->window_listbox = (gcnew System::Windows::Forms::ListBox());
			this->select_window_label = (gcnew System::Windows::Forms::Label());
			this->icon_pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->minimize_btn = (gcnew System::Windows::Forms::Button());
			this->close_form_btn = (gcnew System::Windows::Forms::Button());
			this->title_select_window_label = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// window_listbox
			// 
			this->window_listbox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->window_listbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->window_listbox->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 9));
			this->window_listbox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->window_listbox->FormattingEnabled = true;
			this->window_listbox->ItemHeight = 17;
			this->window_listbox->Location = System::Drawing::Point(12, 77);
			this->window_listbox->Name = L"window_listbox";
			this->window_listbox->Size = System::Drawing::Size(410, 374);
			this->window_listbox->TabIndex = 0;
			// 
			// select_window_label
			// 
			this->select_window_label->AutoSize = true;
			this->select_window_label->BackColor = System::Drawing::Color::Transparent;
			this->select_window_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->select_window_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->select_window_label->Location = System::Drawing::Point(8, 50);
			this->select_window_label->Name = L"select_window_label";
			this->select_window_label->Size = System::Drawing::Size(138, 24);
			this->select_window_label->TabIndex = 33;
			this->select_window_label->Text = L"請選擇遊戲視窗：";
			// 
			// icon_pictureBox
			// 
			this->icon_pictureBox->BackColor = System::Drawing::Color::Transparent;
			this->icon_pictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"icon_pictureBox.Image")));
			this->icon_pictureBox->Location = System::Drawing::Point(12, 7);
			this->icon_pictureBox->Name = L"icon_pictureBox";
			this->icon_pictureBox->Size = System::Drawing::Size(24, 24);
			this->icon_pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->icon_pictureBox->TabIndex = 36;
			this->icon_pictureBox->TabStop = false;
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
			this->minimize_btn->Location = System::Drawing::Point(348, 0);
			this->minimize_btn->Name = L"minimize_btn";
			this->minimize_btn->Size = System::Drawing::Size(39, 32);
			this->minimize_btn->TabIndex = 35;
			this->minimize_btn->UseVisualStyleBackColor = false;
			this->minimize_btn->Click += gcnew System::EventHandler(this, &PreviewForm::minimize_btn_Click);
			// 
			// close_form_btn
			// 
			this->close_form_btn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->close_form_btn->BackColor = System::Drawing::Color::Transparent;
			this->close_form_btn->FlatAppearance->BorderSize = 0;
			this->close_form_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(125)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->close_form_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->close_form_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->close_form_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->close_form_btn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"close_form_btn.Image")));
			this->close_form_btn->Location = System::Drawing::Point(393, 0);
			this->close_form_btn->Name = L"close_form_btn";
			this->close_form_btn->Size = System::Drawing::Size(40, 32);
			this->close_form_btn->TabIndex = 34;
			this->close_form_btn->UseVisualStyleBackColor = false;
			this->close_form_btn->Click += gcnew System::EventHandler(this, &PreviewForm::close_form_btn_Click);
			// 
			// title_select_window_label
			// 
			this->title_select_window_label->AutoSize = true;
			this->title_select_window_label->BackColor = System::Drawing::Color::Transparent;
			this->title_select_window_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->title_select_window_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->title_select_window_label->Location = System::Drawing::Point(42, 9);
			this->title_select_window_label->Name = L"title_select_window_label";
			this->title_select_window_label->Size = System::Drawing::Size(74, 24);
			this->title_select_window_label->TabIndex = 37;
			this->title_select_window_label->Text = L"選取視窗";
			// 
			// PreviewForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(434, 461);
			this->Controls->Add(this->title_select_window_label);
			this->Controls->Add(this->icon_pictureBox);
			this->Controls->Add(this->minimize_btn);
			this->Controls->Add(this->close_form_btn);
			this->Controls->Add(this->select_window_label);
			this->Controls->Add(this->window_listbox);
			this->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(6);
			this->Name = L"PreviewForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PreviewForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PreviewForm::previewForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &PreviewForm::previewForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &PreviewForm::previewForm_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void close_form_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void minimize_btn_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void previewForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void previewForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void previewForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

};
}
