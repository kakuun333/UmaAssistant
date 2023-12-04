#pragma once

#include "../class/LuaManager.h"

namespace UmaAssistant
{

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

		void GameServerRadioButtonChanged(Object^ sender, EventArgs^ e);

		void GameWindowRadioButtonChanged(Object^ sender, EventArgs^ e);

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

	private: System::Windows::Forms::Button^ minimize_btn;
	private: System::Windows::Forms::Button^ close_form_btn;
	private: System::Windows::Forms::PictureBox^ icon_pictureBox;
	private: System::Windows::Forms::Label^ app_name_label;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container^ components;
		bool draggingForm = false;
	public: System::Windows::Forms::CheckBox^ debugMode_checkBox;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ serverPortTextBox;
	private: System::Windows::Forms::RadioButton^ jp_server_radio_btn;



	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RadioButton^ tw_server_radio_btn;

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::RadioButton^ dmm_radio_btn;
	private: System::Windows::Forms::RadioButton^ blue_stacks_radio_btn;


	private: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::CheckBox^ autoMouceClick_checkBox;
	private:

	public: System::Windows::Forms::CheckBox^ alwaysOnTop_checkBox;

	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::TextBox^ autoMouseClickKey_textBox;

	public:
	private:
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
			this->jp_server_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tw_server_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->dmm_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->blue_stacks_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->autoMouceClick_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->alwaysOnTop_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->autoMouseClickKey_textBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
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
			this->update_event_data_jp_btn1->Location = System::Drawing::Point(3, 71);
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
			this->update_skill_data_jp_btn1->Location = System::Drawing::Point(3, 117);
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
			this->debugMode_checkBox->Location = System::Drawing::Point(3, 37);
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
			this->label1->Location = System::Drawing::Point(11, 173);
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
			this->serverPortTextBox->Location = System::Drawing::Point(194, 173);
			this->serverPortTextBox->MaxLength = 5;
			this->serverPortTextBox->Name = L"serverPortTextBox";
			this->serverPortTextBox->Size = System::Drawing::Size(63, 24);
			this->serverPortTextBox->TabIndex = 29;
			this->serverPortTextBox->Text = L"12345";
			// 
			// jp_server_radio_btn
			// 
			this->jp_server_radio_btn->AutoSize = true;
			this->jp_server_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->jp_server_radio_btn->Checked = true;
			this->jp_server_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->jp_server_radio_btn->Location = System::Drawing::Point(3, 3);
			this->jp_server_radio_btn->Name = L"jp_server_radio_btn";
			this->jp_server_radio_btn->Size = System::Drawing::Size(60, 28);
			this->jp_server_radio_btn->TabIndex = 30;
			this->jp_server_radio_btn->TabStop = true;
			this->jp_server_radio_btn->Text = L"日服";
			this->jp_server_radio_btn->UseVisualStyleBackColor = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label2->Location = System::Drawing::Point(12, 38);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(74, 24);
			this->label2->TabIndex = 32;
			this->label2->Text = L"伺服器：";
			// 
			// tw_server_radio_btn
			// 
			this->tw_server_radio_btn->AutoSize = true;
			this->tw_server_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->tw_server_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->tw_server_radio_btn->Location = System::Drawing::Point(84, 3);
			this->tw_server_radio_btn->Name = L"tw_server_radio_btn";
			this->tw_server_radio_btn->Size = System::Drawing::Size(76, 28);
			this->tw_server_radio_btn->TabIndex = 31;
			this->tw_server_radio_btn->Text = L"繁中服";
			this->tw_server_radio_btn->UseVisualStyleBackColor = false;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				36)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				64)));
			this->tableLayoutPanel1->Controls->Add(this->jp_server_radio_btn, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tw_server_radio_btn, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 65);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(225, 34);
			this->tableLayoutPanel1->TabIndex = 33;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				36)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				64)));
			this->tableLayoutPanel2->Controls->Add(this->dmm_radio_btn, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->blue_stacks_radio_btn, 1, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(12, 129);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(225, 34);
			this->tableLayoutPanel2->TabIndex = 35;
			// 
			// dmm_radio_btn
			// 
			this->dmm_radio_btn->AutoSize = true;
			this->dmm_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->dmm_radio_btn->Checked = true;
			this->dmm_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->dmm_radio_btn->Location = System::Drawing::Point(3, 3);
			this->dmm_radio_btn->Name = L"dmm_radio_btn";
			this->dmm_radio_btn->Size = System::Drawing::Size(73, 28);
			this->dmm_radio_btn->TabIndex = 30;
			this->dmm_radio_btn->TabStop = true;
			this->dmm_radio_btn->Text = L"DMM";
			this->dmm_radio_btn->UseVisualStyleBackColor = false;
			// 
			// blue_stacks_radio_btn
			// 
			this->blue_stacks_radio_btn->AutoSize = true;
			this->blue_stacks_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->blue_stacks_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->blue_stacks_radio_btn->Location = System::Drawing::Point(84, 3);
			this->blue_stacks_radio_btn->Name = L"blue_stacks_radio_btn";
			this->blue_stacks_radio_btn->Size = System::Drawing::Size(136, 28);
			this->blue_stacks_radio_btn->TabIndex = 31;
			this->blue_stacks_radio_btn->Text = L"BlueStacks";
			this->blue_stacks_radio_btn->UseVisualStyleBackColor = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label3->Location = System::Drawing::Point(12, 102);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(90, 24);
			this->label3->TabIndex = 34;
			this->label3->Text = L"視窗類型：";
			// 
			// autoMouceClick_checkBox
			// 
			this->autoMouceClick_checkBox->AutoSize = true;
			this->autoMouceClick_checkBox->BackColor = System::Drawing::Color::Transparent;
			this->autoMouceClick_checkBox->FlatAppearance->BorderSize = 0;
			this->autoMouceClick_checkBox->FlatAppearance->CheckedBackColor = System::Drawing::Color::Black;
			this->autoMouceClick_checkBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->autoMouceClick_checkBox->Location = System::Drawing::Point(3, 3);
			this->autoMouceClick_checkBox->Name = L"autoMouceClick_checkBox";
			this->autoMouceClick_checkBox->Size = System::Drawing::Size(93, 28);
			this->autoMouceClick_checkBox->TabIndex = 36;
			this->autoMouceClick_checkBox->Text = L"滑鼠連點";
			this->autoMouceClick_checkBox->UseVisualStyleBackColor = false;
			this->autoMouceClick_checkBox->CheckedChanged += gcnew System::EventHandler(this, &SettingsForm::autoMouceClick_checkBox_CheckedChanged);
			// 
			// alwaysOnTop_checkBox
			// 
			this->alwaysOnTop_checkBox->AutoSize = true;
			this->alwaysOnTop_checkBox->BackColor = System::Drawing::Color::Transparent;
			this->alwaysOnTop_checkBox->FlatAppearance->BorderSize = 0;
			this->alwaysOnTop_checkBox->FlatAppearance->CheckedBackColor = System::Drawing::Color::Black;
			this->alwaysOnTop_checkBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->alwaysOnTop_checkBox->Location = System::Drawing::Point(3, 3);
			this->alwaysOnTop_checkBox->Name = L"alwaysOnTop_checkBox";
			this->alwaysOnTop_checkBox->Size = System::Drawing::Size(125, 28);
			this->alwaysOnTop_checkBox->TabIndex = 37;
			this->alwaysOnTop_checkBox->Text = L"顯示在最上層";
			this->alwaysOnTop_checkBox->UseVisualStyleBackColor = false;
			this->alwaysOnTop_checkBox->CheckedChanged += gcnew System::EventHandler(this, &SettingsForm::alwaysOnTop_checkBox_CheckedChanged);
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->BackColor = System::Drawing::Color::Transparent;
			this->flowLayoutPanel1->Controls->Add(this->alwaysOnTop_checkBox);
			this->flowLayoutPanel1->Controls->Add(this->debugMode_checkBox);
			this->flowLayoutPanel1->Controls->Add(this->update_event_data_jp_btn1);
			this->flowLayoutPanel1->Controls->Add(this->update_skill_data_jp_btn1);
			this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->flowLayoutPanel1->Location = System::Drawing::Point(9, 250);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(368, 164);
			this->flowLayoutPanel1->TabIndex = 39;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				128)));
			this->tableLayoutPanel3->Controls->Add(this->autoMouceClick_checkBox, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->autoMouseClickKey_textBox, 1, 0);
			this->tableLayoutPanel3->Location = System::Drawing::Point(9, 207);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(260, 37);
			this->tableLayoutPanel3->TabIndex = 40;
			// 
			// autoMouseClickKey_textBox
			// 
			this->autoMouseClickKey_textBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->autoMouseClickKey_textBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->autoMouseClickKey_textBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->autoMouseClickKey_textBox->Location = System::Drawing::Point(135, 3);
			this->autoMouseClickKey_textBox->Name = L"autoMouseClickKey_textBox";
			this->autoMouseClickKey_textBox->ReadOnly = true;
			this->autoMouseClickKey_textBox->Size = System::Drawing::Size(122, 31);
			this->autoMouseClickKey_textBox->TabIndex = 37;
			this->autoMouseClickKey_textBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SettingsForm::autoMouseClickKey_textBox_KeyDown);
			this->autoMouseClickKey_textBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SettingsForm::autoMouseClickKey_textBox_MouseDown);
			// 
			// SettingsForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(380, 420);
			this->Controls->Add(this->tableLayoutPanel3);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->serverPortTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->app_name_label);
			this->Controls->Add(this->icon_pictureBox);
			this->Controls->Add(this->minimize_btn);
			this->Controls->Add(this->close_form_btn);
			this->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"SettingsForm";
			this->Text = L"SettingsForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SettingsForm::SettingsFormMouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SettingsForm::SettingsFormMouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SettingsForm::SettingsFormMouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
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

	private: System::Void alwaysOnTop_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);

	private: System::Void autoMouseClickKey_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

	private: System::Void autoMouseClickKey_textBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void autoMouceClick_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
};
}