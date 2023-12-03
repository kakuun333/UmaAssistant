#pragma once

#include "../global/Path.h"

namespace UmaAssistant {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// UmaForm 的摘要
	/// </summary>
	public ref class UmaForm : public System::Windows::Forms::Form
	{
	public:
		UmaForm(void);


		void OnChoiceDocumentCompleted(Object^ sender, WebBrowserDocumentCompletedEventArgs^ e);

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~UmaForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^ icon_pictureBox;
	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		bool draggingForm = false;
		System::Drawing::Point dragOffset;


	private: System::Windows::Forms::Button^ close_form_btn;
	private: System::Windows::Forms::Button^ minimize_btn;
	private: System::Windows::Forms::Button^ settings_btn;
	private: System::Windows::Forms::Button^ scan_btn;
	public: System::Windows::Forms::Button^ screenshot_preview_btn;



	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	public: System::Windows::Forms::Button^ test_btn;

	public: System::Windows::Forms::WebBrowser^ characterNameWebBrowser;
	private: System::Windows::Forms::Button^ clean_current_character_btn;
	public: System::Windows::Forms::Label^ game_window_status_label;


	private: System::Windows::Forms::Label^ app_name_label;
	private: System::Windows::Forms::Button^ select_window_btn;



	public: System::Windows::Forms::WebBrowser^ choiceWebBrowser;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UmaForm::typeid));
			this->icon_pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->close_form_btn = (gcnew System::Windows::Forms::Button());
			this->minimize_btn = (gcnew System::Windows::Forms::Button());
			this->settings_btn = (gcnew System::Windows::Forms::Button());
			this->scan_btn = (gcnew System::Windows::Forms::Button());
			this->screenshot_preview_btn = (gcnew System::Windows::Forms::Button());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->test_btn = (gcnew System::Windows::Forms::Button());
			this->choiceWebBrowser = (gcnew System::Windows::Forms::WebBrowser());
			this->characterNameWebBrowser = (gcnew System::Windows::Forms::WebBrowser());
			this->clean_current_character_btn = (gcnew System::Windows::Forms::Button());
			this->game_window_status_label = (gcnew System::Windows::Forms::Label());
			this->app_name_label = (gcnew System::Windows::Forms::Label());
			this->select_window_btn = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// icon_pictureBox
			// 
			this->icon_pictureBox->BackColor = System::Drawing::Color::Transparent;
			this->icon_pictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"icon_pictureBox.Image")));
			this->icon_pictureBox->Location = System::Drawing::Point(9, 8);
			this->icon_pictureBox->Name = L"icon_pictureBox";
			this->icon_pictureBox->Size = System::Drawing::Size(24, 24);
			this->icon_pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->icon_pictureBox->TabIndex = 8;
			this->icon_pictureBox->TabStop = false;
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
			this->close_form_btn->Location = System::Drawing::Point(521, 0);
			this->close_form_btn->Name = L"close_form_btn";
			this->close_form_btn->Size = System::Drawing::Size(40, 32);
			this->close_form_btn->TabIndex = 9;
			this->close_form_btn->UseVisualStyleBackColor = false;
			this->close_form_btn->Click += gcnew System::EventHandler(this, &UmaForm::close_form_btn_Click);
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
			this->minimize_btn->Location = System::Drawing::Point(476, 0);
			this->minimize_btn->Name = L"minimize_btn";
			this->minimize_btn->Size = System::Drawing::Size(39, 32);
			this->minimize_btn->TabIndex = 10;
			this->minimize_btn->UseVisualStyleBackColor = false;
			this->minimize_btn->Click += gcnew System::EventHandler(this, &UmaForm::minimize_btn_Click);
			// 
			// settings_btn
			// 
			this->settings_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->settings_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"settings_btn.BackgroundImage")));
			this->settings_btn->FlatAppearance->BorderSize = 0;
			this->settings_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->settings_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->settings_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->settings_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->settings_btn->Location = System::Drawing::Point(211, 42);
			this->settings_btn->Name = L"settings_btn";
			this->settings_btn->Size = System::Drawing::Size(95, 65);
			this->settings_btn->TabIndex = 11;
			this->settings_btn->Text = L"設定";
			this->settings_btn->UseVisualStyleBackColor = false;
			this->settings_btn->Click += gcnew System::EventHandler(this, &UmaForm::settings_btn_Click);
			// 
			// scan_btn
			// 
			this->scan_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->scan_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"scan_btn.BackgroundImage")));
			this->scan_btn->FlatAppearance->BorderSize = 0;
			this->scan_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->scan_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->scan_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->scan_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->scan_btn->Location = System::Drawing::Point(9, 42);
			this->scan_btn->Name = L"scan_btn";
			this->scan_btn->Size = System::Drawing::Size(95, 65);
			this->scan_btn->TabIndex = 16;
			this->scan_btn->Text = L"啓動";
			this->scan_btn->UseVisualStyleBackColor = false;
			this->scan_btn->Click += gcnew System::EventHandler(this, &UmaForm::scan_btn_Click);
			// 
			// screenshot_preview_btn
			// 
			this->screenshot_preview_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->screenshot_preview_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"screenshot_preview_btn.BackgroundImage")));
			this->screenshot_preview_btn->FlatAppearance->BorderSize = 0;
			this->screenshot_preview_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->screenshot_preview_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->screenshot_preview_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->screenshot_preview_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->screenshot_preview_btn->Location = System::Drawing::Point(357, 42);
			this->screenshot_preview_btn->Name = L"screenshot_preview_btn";
			this->screenshot_preview_btn->Size = System::Drawing::Size(95, 65);
			this->screenshot_preview_btn->TabIndex = 17;
			this->screenshot_preview_btn->Text = L"截圖預覽";
			this->screenshot_preview_btn->UseVisualStyleBackColor = false;
			this->screenshot_preview_btn->Click += gcnew System::EventHandler(this, &UmaForm::screenshot_preview_btn_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// test_btn
			// 
			this->test_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->test_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"test_btn.BackgroundImage")));
			this->test_btn->FlatAppearance->BorderSize = 0;
			this->test_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->test_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->test_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->test_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->test_btn->Location = System::Drawing::Point(458, 42);
			this->test_btn->Name = L"test_btn";
			this->test_btn->Size = System::Drawing::Size(95, 65);
			this->test_btn->TabIndex = 21;
			this->test_btn->Text = L"測試";
			this->test_btn->UseVisualStyleBackColor = false;
			this->test_btn->Click += gcnew System::EventHandler(this, &UmaForm::test_btn_Click);
			// 
			// choiceWebBrowser
			// 
			this->choiceWebBrowser->Location = System::Drawing::Point(9, 164);
			this->choiceWebBrowser->MinimumSize = System::Drawing::Size(20, 20);
			this->choiceWebBrowser->Name = L"choiceWebBrowser";
			this->choiceWebBrowser->Size = System::Drawing::Size(544, 374);
			this->choiceWebBrowser->TabIndex = 22;
			// 
			// characterNameWebBrowser
			// 
			this->characterNameWebBrowser->Location = System::Drawing::Point(9, 113);
			this->characterNameWebBrowser->MinimumSize = System::Drawing::Size(20, 20);
			this->characterNameWebBrowser->Name = L"characterNameWebBrowser";
			this->characterNameWebBrowser->Size = System::Drawing::Size(463, 45);
			this->characterNameWebBrowser->TabIndex = 23;
			// 
			// clean_current_character_btn
			// 
			this->clean_current_character_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->clean_current_character_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"clean_current_character_btn.BackgroundImage")));
			this->clean_current_character_btn->FlatAppearance->BorderSize = 0;
			this->clean_current_character_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->clean_current_character_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->clean_current_character_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->clean_current_character_btn->Location = System::Drawing::Point(478, 113);
			this->clean_current_character_btn->Name = L"clean_current_character_btn";
			this->clean_current_character_btn->Size = System::Drawing::Size(75, 45);
			this->clean_current_character_btn->TabIndex = 24;
			this->clean_current_character_btn->Text = L"清除角色";
			this->clean_current_character_btn->UseVisualStyleBackColor = false;
			this->clean_current_character_btn->Click += gcnew System::EventHandler(this, &UmaForm::clean_current_character_Click);
			// 
			// game_window_status_label
			// 
			this->game_window_status_label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->game_window_status_label->AutoSize = true;
			this->game_window_status_label->BackColor = System::Drawing::Color::Transparent;
			this->game_window_status_label->ForeColor = System::Drawing::Color::Red;
			this->game_window_status_label->Location = System::Drawing::Point(164, 10);
			this->game_window_status_label->Name = L"game_window_status_label";
			this->game_window_status_label->Size = System::Drawing::Size(107, 20);
			this->game_window_status_label->TabIndex = 8;
			this->game_window_status_label->Text = L"未找到遊戲視窗";
			// 
			// app_name_label
			// 
			this->app_name_label->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->app_name_label->AutoSize = true;
			this->app_name_label->BackColor = System::Drawing::Color::Transparent;
			this->app_name_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->app_name_label->Location = System::Drawing::Point(39, 9);
			this->app_name_label->Name = L"app_name_label";
			this->app_name_label->Size = System::Drawing::Size(123, 20);
			this->app_name_label->TabIndex = 25;
			this->app_name_label->Text = L"UmaAssistant";
			// 
			// select_window_btn
			// 
			this->select_window_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->select_window_btn->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"select_window_btn.BackgroundImage")));
			this->select_window_btn->FlatAppearance->BorderSize = 0;
			this->select_window_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->select_window_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->select_window_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->select_window_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->select_window_btn->Location = System::Drawing::Point(110, 42);
			this->select_window_btn->Name = L"select_window_btn";
			this->select_window_btn->Size = System::Drawing::Size(95, 65);
			this->select_window_btn->TabIndex = 26;
			this->select_window_btn->Text = L"選取視窗";
			this->select_window_btn->UseVisualStyleBackColor = false;
			this->select_window_btn->Click += gcnew System::EventHandler(this, &UmaForm::select_window_btn_Click);
			// 
			// UmaForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(560, 550);
			this->Controls->Add(this->select_window_btn);
			this->Controls->Add(this->app_name_label);
			this->Controls->Add(this->game_window_status_label);
			this->Controls->Add(this->clean_current_character_btn);
			this->Controls->Add(this->characterNameWebBrowser);
			this->Controls->Add(this->choiceWebBrowser);
			this->Controls->Add(this->test_btn);
			this->Controls->Add(this->screenshot_preview_btn);
			this->Controls->Add(this->scan_btn);
			this->Controls->Add(this->settings_btn);
			this->Controls->Add(this->minimize_btn);
			this->Controls->Add(this->close_form_btn);
			this->Controls->Add(this->icon_pictureBox);
			this->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"UmaForm";
			this->Text = L"UmaForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UmaForm::UmaForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &UmaForm::UmaForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UmaForm::UmaForm_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void scan_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void settings_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void screenshot_preview_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void UmaForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void UmaForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void UmaForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void close_form_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void minimize_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void test_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void clean_current_character_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void select_window_btn_Click(System::Object^ sender, System::EventArgs^ e);
};
}
