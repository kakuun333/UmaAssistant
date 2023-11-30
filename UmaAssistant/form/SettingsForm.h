#pragma once

#include "../class/LuaManager.h"

namespace UmaAssistant {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// SettingsForm 的摘要
	/// </summary>
	public ref class SettingsForm : public System::Windows::Forms::Form
	{
	public:
		SettingsForm(void);

		void FormClosingHandler(Object^ sender, FormClosingEventArgs^ e);

		void serverPortTextBox_KeyPress(Object^ sender, KeyPressEventArgs^ e);

		void serverPortTextBox_TextChanged(Object^ sender, EventArgs^ e);

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~SettingsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ update_event_data_jp_btn1;
	private: System::Windows::Forms::Button^ update_skill_data_jp_btn1;
	protected:


	protected:


	protected:


	protected:


	private: System::Windows::Forms::Button^ minimize_btn;
	private: System::Windows::Forms::Button^ close_form_btn;
	private: System::Windows::Forms::PictureBox^ icon_pictureBox;
	private: System::Windows::Forms::Label^ app_name_label;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;
		bool draggingForm = false;
	public: System::Windows::Forms::CheckBox^ debugMode_checkBox;
	private:



	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ serverPortTextBox;

	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::Label^ label2;
		   System::Drawing::Point dragOffset;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SettingsForm::typeid));
			this->update_event_data_jp_btn1 = (gcnew System::Windows::Forms::Button());
			this->update_skill_data_jp_btn1 = (gcnew System::Windows::Forms::Button());
			this->minimize_btn = (gcnew System::Windows::Forms::Button());
			this->close_form_btn = (gcnew System::Windows::Forms::Button());
			this->icon_pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->app_name_label = (gcnew System::Windows::Forms::Label());
			this->debugMode_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->serverPortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// update_event_data_jp_btn1
			// 
			this->update_event_data_jp_btn1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->update_event_data_jp_btn1->FlatAppearance->BorderSize = 0;
			this->update_event_data_jp_btn1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->update_event_data_jp_btn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->update_event_data_jp_btn1->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->update_event_data_jp_btn1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->update_event_data_jp_btn1->Location = System::Drawing::Point(8, 222);
			this->update_event_data_jp_btn1->Name = L"update_event_data_jp_btn1";
			this->update_event_data_jp_btn1->Size = System::Drawing::Size(360, 40);
			this->update_event_data_jp_btn1->TabIndex = 0;
			this->update_event_data_jp_btn1->Text = L"更新 event_data_jp.json";
			this->update_event_data_jp_btn1->UseVisualStyleBackColor = false;
			this->update_event_data_jp_btn1->Click += gcnew System::EventHandler(this, &SettingsForm::update_event_data_jp_btn_Click);
			// 
			// update_skill_data_jp_btn1
			// 
			this->update_skill_data_jp_btn1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->update_skill_data_jp_btn1->FlatAppearance->BorderSize = 0;
			this->update_skill_data_jp_btn1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->update_skill_data_jp_btn1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->update_skill_data_jp_btn1->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->update_skill_data_jp_btn1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->update_skill_data_jp_btn1->Location = System::Drawing::Point(8, 268);
			this->update_skill_data_jp_btn1->Name = L"update_skill_data_jp_btn1";
			this->update_skill_data_jp_btn1->Size = System::Drawing::Size(360, 40);
			this->update_skill_data_jp_btn1->TabIndex = 1;
			this->update_skill_data_jp_btn1->Text = L"更新 skill_data_jp.json";
			this->update_skill_data_jp_btn1->UseVisualStyleBackColor = false;
			this->update_skill_data_jp_btn1->Click += gcnew System::EventHandler(this, &SettingsForm::update_skill_data_jp_btn_Click);
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
			this->minimize_btn->Location = System::Drawing::Point(292, 0);
			this->minimize_btn->Name = L"minimize_btn";
			this->minimize_btn->Size = System::Drawing::Size(39, 32);
			this->minimize_btn->TabIndex = 12;
			this->minimize_btn->UseVisualStyleBackColor = false;
			this->minimize_btn->Click += gcnew System::EventHandler(this, &SettingsForm::minimize_btn_Click);
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
			this->close_form_btn->Location = System::Drawing::Point(337, 0);
			this->close_form_btn->Name = L"close_form_btn";
			this->close_form_btn->Size = System::Drawing::Size(40, 32);
			this->close_form_btn->TabIndex = 11;
			this->close_form_btn->UseVisualStyleBackColor = false;
			this->close_form_btn->Click += gcnew System::EventHandler(this, &SettingsForm::close_form_btn_Click);
			// 
			// icon_pictureBox
			// 
			this->icon_pictureBox->BackColor = System::Drawing::Color::Transparent;
			this->icon_pictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"icon_pictureBox.Image")));
			this->icon_pictureBox->Location = System::Drawing::Point(12, 5);
			this->icon_pictureBox->Name = L"icon_pictureBox";
			this->icon_pictureBox->Size = System::Drawing::Size(24, 24);
			this->icon_pictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->icon_pictureBox->TabIndex = 13;
			this->icon_pictureBox->TabStop = false;
			// 
			// app_name_label
			// 
			this->app_name_label->AutoSize = true;
			this->app_name_label->BackColor = System::Drawing::Color::Transparent;
			this->app_name_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->app_name_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->app_name_label->Location = System::Drawing::Point(42, 7);
			this->app_name_label->Name = L"app_name_label";
			this->app_name_label->Size = System::Drawing::Size(42, 24);
			this->app_name_label->TabIndex = 26;
			this->app_name_label->Text = L"設定";
			// 
			// debugMode_checkBox
			// 
			this->debugMode_checkBox->AutoSize = true;
			this->debugMode_checkBox->BackColor = System::Drawing::Color::Transparent;
			this->debugMode_checkBox->FlatAppearance->BorderSize = 0;
			this->debugMode_checkBox->FlatAppearance->CheckedBackColor = System::Drawing::Color::Black;
			this->debugMode_checkBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->debugMode_checkBox->Location = System::Drawing::Point(13, 177);
			this->debugMode_checkBox->Name = L"debugMode_checkBox";
			this->debugMode_checkBox->Size = System::Drawing::Size(121, 28);
			this->debugMode_checkBox->TabIndex = 27;
			this->debugMode_checkBox->Text = L"Debug 模式";
			this->debugMode_checkBox->UseVisualStyleBackColor = false;
			this->debugMode_checkBox->CheckedChanged += gcnew System::EventHandler(this, &SettingsForm::debugMode_checkBox_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label1->Location = System::Drawing::Point(9, 126);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(177, 24);
			this->label1->TabIndex = 28;
			this->label1->Text = L"本地伺服器埠口(Port)";
			// 
			// serverPortTextBox
			// 
			this->serverPortTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->serverPortTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->serverPortTextBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->serverPortTextBox->Location = System::Drawing::Point(192, 126);
			this->serverPortTextBox->MaxLength = 5;
			this->serverPortTextBox->Name = L"serverPortTextBox";
			this->serverPortTextBox->Size = System::Drawing::Size(63, 24);
			this->serverPortTextBox->TabIndex = 29;
			this->serverPortTextBox->Text = L"12345";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->BackColor = System::Drawing::Color::Transparent;
			this->radioButton1->Checked = true;
			this->radioButton1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->radioButton1->Location = System::Drawing::Point(12, 68);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(60, 28);
			this->radioButton1->TabIndex = 30;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"日文";
			this->radioButton1->UseVisualStyleBackColor = false;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->BackColor = System::Drawing::Color::Transparent;
			this->radioButton2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->radioButton2->Location = System::Drawing::Point(78, 68);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(92, 28);
			this->radioButton2->TabIndex = 31;
			this->radioButton2->Text = L"繁體中文";
			this->radioButton2->UseVisualStyleBackColor = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label2->Location = System::Drawing::Point(9, 38);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 24);
			this->label2->TabIndex = 32;
			this->label2->Text = L"辨識語言：";
			// 
			// SettingsForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(380, 320);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->serverPortTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->debugMode_checkBox);
			this->Controls->Add(this->app_name_label);
			this->Controls->Add(this->icon_pictureBox);
			this->Controls->Add(this->minimize_btn);
			this->Controls->Add(this->close_form_btn);
			this->Controls->Add(this->update_skill_data_jp_btn1);
			this->Controls->Add(this->update_event_data_jp_btn1);
			this->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"SettingsForm";
			this->Text = L"SettingsForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SettingsForm::SettingsFormMouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SettingsForm::SettingsFormMouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SettingsForm::SettingsFormMouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void update_event_data_jp_btn_Click(System::Object^ sender, System::EventArgs^ e);


	private: System::Void update_skill_data_jp_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void minimize_btn_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void close_form_btn_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void SettingsFormMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void SettingsFormMouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void SettingsFormMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void debugMode_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
};
}
