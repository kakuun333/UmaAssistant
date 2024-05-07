#pragma once

#include "cppsrc/enum/SoftwareLanguageType.h"

//#using "control/UmaCustomControl.RoundedButton.dll"

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
	
	public: SettingsForm(void);

	// 變數
	private: System::Drawing::Point dragOffset;
	private: bool draggingForm = false;
	private: bool _changingSoftwareLang = false;

	// Form
	private: void OnFormClosing(Object^ sender, FormClosingEventArgs^ e);

	// TextBox
	private: void DigitOnly_TextBox_KeyPress(Object^ sender, KeyPressEventArgs^ e);
	private: void serverPortTextBox_TextChanged(Object^ sender, EventArgs^ e);
	private: void scanInterval_textBox_TextChanged(Object^ sender, EventArgs^ e);

	// RadioButton
	private: void GameServerRadioButtonChanged(Object^ sender, EventArgs^ e);
	private: void GameWindowRadioButtonChanged(Object^ sender, EventArgs^ e);
	private: void JpServerLangRadioButtonChanged(Object^ sender, EventArgs^ e);
	private: void SoftwareLangRadioButtonChanged(Object^ sender, EventArgs^ e);

	// CheckBox
	private: void alwaysOnTop_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: void debugMode_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: void autoMouceClick_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: void outputLogFile_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: void discordRpc_checkBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e);

	// ProgramLanguage
	public: void ChangeSoftwareLanguage(SoftwareLanguageType langType);
	public: void TraverseControls(Control^ control, array<System::String^>^ sys_str_arr);

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

	private: System::ComponentModel::Container^ components;
	private: UmaCustomControl::RoundedButton^ minimize_btn;
	private: UmaCustomControl::RoundedButton^ close_form_btn;
	private: System::Windows::Forms::PictureBox^ icon_pictureBox;
	private: System::Windows::Forms::Label^ app_name_label;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
	public: System::Windows::Forms::CheckBox^ debugMode_checkBox;
	private: System::Windows::Forms::Label^ local_server_port_label;
	private: System::Windows::Forms::TextBox^ serverPortTextBox;
	private: System::Windows::Forms::RadioButton^ jp_server_radio_btn;
	private: System::Windows::Forms::Label^ game_server_type_label;
	private: System::Windows::Forms::RadioButton^ tw_server_radio_btn;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::RadioButton^ dmm_radio_btn;
	private: System::Windows::Forms::RadioButton^ emulator_radio_btn;
	private: System::Windows::Forms::Label^ window_type_label;
	public: System::Windows::Forms::CheckBox^ autoMouceClick_checkBox;
	public: System::Windows::Forms::CheckBox^ alwaysOnTop_checkBox;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::TextBox^ autoMouseClickKey_textBox;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel52;
	private: System::Windows::Forms::RadioButton^ jpServerLang_tw_radio_btn;
	private: System::Windows::Forms::RadioButton^ jpServerLang_jp_radio_btn;
	private: System::Windows::Forms::Label^ jp_server_lang_label;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel5;
	private: System::Windows::Forms::Label^ scan_interval_label;
	private: System::Windows::Forms::TextBox^ scanInterval_textBox;
	private: System::Windows::Forms::Label^ scan_interval_ms_label;
	public: System::Windows::Forms::CheckBox^ outputLogFile_checkBox;
	public: UmaCustomControl::RoundedButton^ default_btn;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel6;
	private: System::Windows::Forms::RadioButton^ software_lang_tw_radio_btn;
	private: System::Windows::Forms::RadioButton^ software_lang_jp_radio_btn;
	public: System::Windows::Forms::CheckBox^ discordRpc_checkBox;
	public: UmaCustomControl::RoundedButton^ test_btn;
	public: UmaCustomControl::RoundedButton^ screenshotPreview_btn;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SettingsForm::typeid));
			this->minimize_btn = (gcnew UmaCustomControl::RoundedButton());
			this->close_form_btn = (gcnew UmaCustomControl::RoundedButton());
			this->icon_pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->app_name_label = (gcnew System::Windows::Forms::Label());
			this->debugMode_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->local_server_port_label = (gcnew System::Windows::Forms::Label());
			this->serverPortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->jp_server_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->game_server_type_label = (gcnew System::Windows::Forms::Label());
			this->tw_server_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->dmm_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->emulator_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->window_type_label = (gcnew System::Windows::Forms::Label());
			this->autoMouceClick_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->alwaysOnTop_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->discordRpc_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->outputLogFile_checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->autoMouseClickKey_textBox = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel52 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->jpServerLang_jp_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->jpServerLang_tw_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->jp_server_lang_label = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->scan_interval_label = (gcnew System::Windows::Forms::Label());
			this->scanInterval_textBox = (gcnew System::Windows::Forms::TextBox());
			this->scan_interval_ms_label = (gcnew System::Windows::Forms::Label());
			this->default_btn = (gcnew UmaCustomControl::RoundedButton());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->software_lang_jp_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->software_lang_tw_radio_btn = (gcnew System::Windows::Forms::RadioButton());
			this->test_btn = (gcnew UmaCustomControl::RoundedButton());
			this->screenshotPreview_btn = (gcnew UmaCustomControl::RoundedButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->tableLayoutPanel52->SuspendLayout();
			this->tableLayoutPanel5->SuspendLayout();
			this->tableLayoutPanel6->SuspendLayout();
			this->SuspendLayout();
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
			this->minimize_btn->Radius = 10;
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
			this->close_form_btn->Radius = 10;
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
			this->debugMode_checkBox->Location = System::Drawing::Point(135, 3);
			this->debugMode_checkBox->Name = L"debugMode_checkBox";
			this->debugMode_checkBox->Size = System::Drawing::Size(108, 24);
			this->debugMode_checkBox->TabIndex = 27;
			this->debugMode_checkBox->Text = L"Debug 模式";
			this->debugMode_checkBox->UseVisualStyleBackColor = false;
			// 
			// local_server_port_label
			// 
			this->local_server_port_label->AutoSize = true;
			this->local_server_port_label->BackColor = System::Drawing::Color::Transparent;
			this->local_server_port_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->local_server_port_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																						static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->local_server_port_label->Location = System::Drawing::Point(3, 0);
			this->local_server_port_label->Name = L"local_server_port_label";
			this->local_server_port_label->Size = System::Drawing::Size(156, 20);
			this->local_server_port_label->TabIndex = 28;
			this->local_server_port_label->Text = L"本地伺服器埠口(Port)";
			// 
			// serverPortTextBox
			// 
			this->serverPortTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
																				  static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->serverPortTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->serverPortTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->serverPortTextBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																				  static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->serverPortTextBox->Location = System::Drawing::Point(234, 3);
			this->serverPortTextBox->MaxLength = 5;
			this->serverPortTextBox->Name = L"serverPortTextBox";
			this->serverPortTextBox->Size = System::Drawing::Size(122, 20);
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
			this->jp_server_radio_btn->Size = System::Drawing::Size(55, 24);
			this->jp_server_radio_btn->TabIndex = 30;
			this->jp_server_radio_btn->TabStop = true;
			this->jp_server_radio_btn->Text = L"日服";
			this->jp_server_radio_btn->UseVisualStyleBackColor = false;
			// 
			// game_server_type_label
			// 
			this->game_server_type_label->AutoSize = true;
			this->game_server_type_label->BackColor = System::Drawing::Color::Transparent;
			this->game_server_type_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->game_server_type_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					   static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->game_server_type_label->Location = System::Drawing::Point(12, 88);
			this->game_server_type_label->Name = L"game_server_type_label";
			this->game_server_type_label->Size = System::Drawing::Size(93, 20);
			this->game_server_type_label->TabIndex = 32;
			this->game_server_type_label->Text = L"遊戲伺服器：";
			// 
			// tw_server_radio_btn
			// 
			this->tw_server_radio_btn->AutoSize = true;
			this->tw_server_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->tw_server_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->tw_server_radio_btn->Location = System::Drawing::Point(145, 3);
			this->tw_server_radio_btn->Name = L"tw_server_radio_btn";
			this->tw_server_radio_btn->Size = System::Drawing::Size(69, 24);
			this->tw_server_radio_btn->TabIndex = 31;
			this->tw_server_radio_btn->Text = L"繁中服";
			this->tw_server_radio_btn->UseVisualStyleBackColor = false;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  39.88764F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  60.11236F)));
			this->tableLayoutPanel1->Controls->Add(this->jp_server_radio_btn, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tw_server_radio_btn, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 111);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(356, 34);
			this->tableLayoutPanel1->TabIndex = 33;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  40.16854F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  59.83146F)));
			this->tableLayoutPanel2->Controls->Add(this->dmm_radio_btn, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->emulator_radio_btn, 1, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(12, 171);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(356, 34);
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
			this->dmm_radio_btn->Size = System::Drawing::Size(66, 24);
			this->dmm_radio_btn->TabIndex = 30;
			this->dmm_radio_btn->TabStop = true;
			this->dmm_radio_btn->Text = L"DMM";
			this->dmm_radio_btn->UseVisualStyleBackColor = false;
			// 
			// emulator_radio_btn
			// 
			this->emulator_radio_btn->AutoSize = true;
			this->emulator_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->emulator_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																				   static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->emulator_radio_btn->Location = System::Drawing::Point(146, 3);
			this->emulator_radio_btn->Name = L"emulator_radio_btn";
			this->emulator_radio_btn->Size = System::Drawing::Size(69, 24);
			this->emulator_radio_btn->TabIndex = 31;
			this->emulator_radio_btn->Text = L"模擬器";
			this->emulator_radio_btn->UseVisualStyleBackColor = false;
			// 
			// window_type_label
			// 
			this->window_type_label->AutoSize = true;
			this->window_type_label->BackColor = System::Drawing::Color::Transparent;
			this->window_type_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->window_type_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																				  static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->window_type_label->Location = System::Drawing::Point(12, 148);
			this->window_type_label->Name = L"window_type_label";
			this->window_type_label->Size = System::Drawing::Size(79, 20);
			this->window_type_label->TabIndex = 34;
			this->window_type_label->Text = L"視窗類型：";
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
			this->autoMouceClick_checkBox->Size = System::Drawing::Size(84, 23);
			this->autoMouceClick_checkBox->TabIndex = 36;
			this->autoMouceClick_checkBox->Text = L"滑鼠連點";
			this->autoMouceClick_checkBox->UseVisualStyleBackColor = false;
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
			this->alwaysOnTop_checkBox->Size = System::Drawing::Size(112, 24);
			this->alwaysOnTop_checkBox->TabIndex = 37;
			this->alwaysOnTop_checkBox->Text = L"顯示在最上層";
			this->alwaysOnTop_checkBox->UseVisualStyleBackColor = false;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->BackColor = System::Drawing::Color::Transparent;
			this->flowLayoutPanel1->Controls->Add(this->alwaysOnTop_checkBox);
			this->flowLayoutPanel1->Controls->Add(this->discordRpc_checkBox);
			this->flowLayoutPanel1->Controls->Add(this->debugMode_checkBox);
			this->flowLayoutPanel1->Controls->Add(this->outputLogFile_checkBox);
			this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->flowLayoutPanel1->Location = System::Drawing::Point(9, 359);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(359, 63);
			this->flowLayoutPanel1->TabIndex = 39;
			// 
			// discordRpc_checkBox
			// 
			this->discordRpc_checkBox->AutoSize = true;
			this->discordRpc_checkBox->BackColor = System::Drawing::Color::Transparent;
			this->discordRpc_checkBox->FlatAppearance->BorderSize = 0;
			this->discordRpc_checkBox->FlatAppearance->CheckedBackColor = System::Drawing::Color::Black;
			this->discordRpc_checkBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->discordRpc_checkBox->Location = System::Drawing::Point(3, 33);
			this->discordRpc_checkBox->Name = L"discordRpc_checkBox";
			this->discordRpc_checkBox->Size = System::Drawing::Size(126, 24);
			this->discordRpc_checkBox->TabIndex = 48;
			this->discordRpc_checkBox->Text = L"Discord RPC";
			this->discordRpc_checkBox->UseVisualStyleBackColor = false;
			// 
			// outputLogFile_checkBox
			// 
			this->outputLogFile_checkBox->AutoSize = true;
			this->outputLogFile_checkBox->BackColor = System::Drawing::Color::Transparent;
			this->outputLogFile_checkBox->FlatAppearance->BorderSize = 0;
			this->outputLogFile_checkBox->FlatAppearance->CheckedBackColor = System::Drawing::Color::Black;
			this->outputLogFile_checkBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					   static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->outputLogFile_checkBox->Location = System::Drawing::Point(135, 33);
			this->outputLogFile_checkBox->Name = L"outputLogFile_checkBox";
			this->outputLogFile_checkBox->Size = System::Drawing::Size(112, 24);
			this->outputLogFile_checkBox->TabIndex = 38;
			this->outputLogFile_checkBox->Text = L"輸出偵錯日誌";
			this->outputLogFile_checkBox->UseVisualStyleBackColor = false;
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
			this->tableLayoutPanel3->Location = System::Drawing::Point(9, 327);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(359, 29);
			this->tableLayoutPanel3->TabIndex = 40;
			// 
			// autoMouseClickKey_textBox
			// 
			this->autoMouseClickKey_textBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
																						  static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->autoMouseClickKey_textBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->autoMouseClickKey_textBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->autoMouseClickKey_textBox->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->autoMouseClickKey_textBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																						  static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->autoMouseClickKey_textBox->Location = System::Drawing::Point(234, 3);
			this->autoMouseClickKey_textBox->Name = L"autoMouseClickKey_textBox";
			this->autoMouseClickKey_textBox->ReadOnly = true;
			this->autoMouseClickKey_textBox->Size = System::Drawing::Size(122, 20);
			this->autoMouseClickKey_textBox->TabIndex = 37;
			this->autoMouseClickKey_textBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SettingsForm::autoMouseClickKey_textBox_KeyDown);
			this->autoMouseClickKey_textBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SettingsForm::autoMouseClickKey_textBox_MouseDown);
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  50)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
																								  128)));
			this->tableLayoutPanel4->Controls->Add(this->local_server_port_label, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->serverPortTextBox, 1, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(9, 300);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(359, 23);
			this->tableLayoutPanel4->TabIndex = 41;
			// 
			// tableLayoutPanel52
			// 
			this->tableLayoutPanel52->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel52->ColumnCount = 2;
			this->tableLayoutPanel52->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								   40.28169F)));
			this->tableLayoutPanel52->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								   59.71831F)));
			this->tableLayoutPanel52->Controls->Add(this->jpServerLang_jp_radio_btn, 0, 0);
			this->tableLayoutPanel52->Controls->Add(this->jpServerLang_tw_radio_btn, 1, 0);
			this->tableLayoutPanel52->Location = System::Drawing::Point(13, 231);
			this->tableLayoutPanel52->Name = L"tableLayoutPanel52";
			this->tableLayoutPanel52->RowCount = 1;
			this->tableLayoutPanel52->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel52->Size = System::Drawing::Size(355, 34);
			this->tableLayoutPanel52->TabIndex = 43;
			// 
			// jpServerLang_jp_radio_btn
			// 
			this->jpServerLang_jp_radio_btn->AutoSize = true;
			this->jpServerLang_jp_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->jpServerLang_jp_radio_btn->Checked = true;
			this->jpServerLang_jp_radio_btn->Enabled = false;
			this->jpServerLang_jp_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																						  static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->jpServerLang_jp_radio_btn->Location = System::Drawing::Point(3, 3);
			this->jpServerLang_jp_radio_btn->Name = L"jpServerLang_jp_radio_btn";
			this->jpServerLang_jp_radio_btn->Size = System::Drawing::Size(55, 24);
			this->jpServerLang_jp_radio_btn->TabIndex = 30;
			this->jpServerLang_jp_radio_btn->TabStop = true;
			this->jpServerLang_jp_radio_btn->Text = L"日文";
			this->jpServerLang_jp_radio_btn->UseVisualStyleBackColor = false;
			// 
			// jpServerLang_tw_radio_btn
			// 
			this->jpServerLang_tw_radio_btn->AutoSize = true;
			this->jpServerLang_tw_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->jpServerLang_tw_radio_btn->Enabled = false;
			this->jpServerLang_tw_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																						  static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->jpServerLang_tw_radio_btn->Location = System::Drawing::Point(145, 3);
			this->jpServerLang_tw_radio_btn->Name = L"jpServerLang_tw_radio_btn";
			this->jpServerLang_tw_radio_btn->Size = System::Drawing::Size(83, 24);
			this->jpServerLang_tw_radio_btn->TabIndex = 31;
			this->jpServerLang_tw_radio_btn->Text = L"繁體中文";
			this->jpServerLang_tw_radio_btn->UseVisualStyleBackColor = false;
			// 
			// jp_server_lang_label
			// 
			this->jp_server_lang_label->AutoSize = true;
			this->jp_server_lang_label->BackColor = System::Drawing::Color::Transparent;
			this->jp_server_lang_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->jp_server_lang_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					 static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->jp_server_lang_label->Location = System::Drawing::Point(12, 208);
			this->jp_server_lang_label->Name = L"jp_server_lang_label";
			this->jp_server_lang_label->Size = System::Drawing::Size(107, 20);
			this->jp_server_lang_label->TabIndex = 42;
			this->jp_server_lang_label->Text = L"日服文本語言：";
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel5->ColumnCount = 3;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  75.81699F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  24.18301F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
																								  54)));
			this->tableLayoutPanel5->Controls->Add(this->scan_interval_label, 0, 0);
			this->tableLayoutPanel5->Controls->Add(this->scanInterval_textBox, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->scan_interval_ms_label, 2, 0);
			this->tableLayoutPanel5->Location = System::Drawing::Point(9, 271);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 1;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(359, 26);
			this->tableLayoutPanel5->TabIndex = 44;
			// 
			// scan_interval_label
			// 
			this->scan_interval_label->AutoSize = true;
			this->scan_interval_label->BackColor = System::Drawing::Color::Transparent;
			this->scan_interval_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->scan_interval_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->scan_interval_label->Location = System::Drawing::Point(3, 0);
			this->scan_interval_label->Name = L"scan_interval_label";
			this->scan_interval_label->Size = System::Drawing::Size(121, 20);
			this->scan_interval_label->TabIndex = 28;
			this->scan_interval_label->Text = L"辨識事件間隔時間";
			// 
			// scanInterval_textBox
			// 
			this->scanInterval_textBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
																					 static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->scanInterval_textBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->scanInterval_textBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->scanInterval_textBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					 static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->scanInterval_textBox->Location = System::Drawing::Point(234, 3);
			this->scanInterval_textBox->MaxLength = 4;
			this->scanInterval_textBox->Name = L"scanInterval_textBox";
			this->scanInterval_textBox->Size = System::Drawing::Size(67, 20);
			this->scanInterval_textBox->TabIndex = 29;
			this->scanInterval_textBox->Text = L"100";
			// 
			// scan_interval_ms_label
			// 
			this->scan_interval_ms_label->AutoSize = true;
			this->scan_interval_ms_label->BackColor = System::Drawing::Color::Transparent;
			this->scan_interval_ms_label->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->scan_interval_ms_label->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					   static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->scan_interval_ms_label->Location = System::Drawing::Point(307, 0);
			this->scan_interval_ms_label->Name = L"scan_interval_ms_label";
			this->scan_interval_ms_label->Size = System::Drawing::Size(37, 20);
			this->scan_interval_ms_label->TabIndex = 45;
			this->scan_interval_ms_label->Text = L"毫秒";
			// 
			// default_btn
			// 
			this->default_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
																			static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->default_btn->FlatAppearance->BorderSize = 0;
			this->default_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
																									 static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->default_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->default_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->default_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
																			static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->default_btn->Location = System::Drawing::Point(268, 428);
			this->default_btn->Name = L"default_btn";
			this->default_btn->Radius = 10;
			this->default_btn->Size = System::Drawing::Size(100, 65);
			this->default_btn->TabIndex = 45;
			this->default_btn->TabStop = false;
			this->default_btn->Text = L"恢復預設値";
			this->default_btn->UseVisualStyleBackColor = false;
			this->default_btn->Click += gcnew System::EventHandler(this, &SettingsForm::default_btn_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->label7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
																	   static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label7->Location = System::Drawing::Point(12, 32);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(163, 20);
			this->label7->TabIndex = 46;
			this->label7->Text = L"軟體語言／ソフト言語：";
			// 
			// tableLayoutPanel6
			// 
			this->tableLayoutPanel6->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel6->ColumnCount = 2;
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  38.99722F)));
			this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
																								  61.00278F)));
			this->tableLayoutPanel6->Controls->Add(this->software_lang_jp_radio_btn, 0, 0);
			this->tableLayoutPanel6->Controls->Add(this->software_lang_tw_radio_btn, 1, 0);
			this->tableLayoutPanel6->Location = System::Drawing::Point(12, 54);
			this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
			this->tableLayoutPanel6->RowCount = 1;
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel6->Size = System::Drawing::Size(359, 34);
			this->tableLayoutPanel6->TabIndex = 47;
			// 
			// software_lang_jp_radio_btn
			// 
			this->software_lang_jp_radio_btn->AutoSize = true;
			this->software_lang_jp_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->software_lang_jp_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																						   static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->software_lang_jp_radio_btn->Location = System::Drawing::Point(3, 3);
			this->software_lang_jp_radio_btn->Name = L"software_lang_jp_radio_btn";
			this->software_lang_jp_radio_btn->Size = System::Drawing::Size(69, 24);
			this->software_lang_jp_radio_btn->TabIndex = 30;
			this->software_lang_jp_radio_btn->Text = L"日本語";
			this->software_lang_jp_radio_btn->UseVisualStyleBackColor = false;
			// 
			// software_lang_tw_radio_btn
			// 
			this->software_lang_tw_radio_btn->AutoSize = true;
			this->software_lang_tw_radio_btn->BackColor = System::Drawing::Color::Transparent;
			this->software_lang_tw_radio_btn->Checked = true;
			this->software_lang_tw_radio_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																						   static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->software_lang_tw_radio_btn->Location = System::Drawing::Point(143, 3);
			this->software_lang_tw_radio_btn->Name = L"software_lang_tw_radio_btn";
			this->software_lang_tw_radio_btn->Size = System::Drawing::Size(83, 24);
			this->software_lang_tw_radio_btn->TabIndex = 31;
			this->software_lang_tw_radio_btn->TabStop = true;
			this->software_lang_tw_radio_btn->Text = L"繁體中文";
			this->software_lang_tw_radio_btn->UseVisualStyleBackColor = false;
			// 
			// test_btn
			// 
			this->test_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
																		 static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->test_btn->FlatAppearance->BorderSize = 0;
			this->test_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
																								  static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->test_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->test_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->test_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
																		 static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->test_btn->Location = System::Drawing::Point(110, 428);
			this->test_btn->Name = L"test_btn";
			this->test_btn->Radius = 10;
			this->test_btn->Size = System::Drawing::Size(95, 65);
			this->test_btn->TabIndex = 48;
			this->test_btn->TabStop = false;
			this->test_btn->Text = L"測試";
			this->test_btn->UseVisualStyleBackColor = false;
			this->test_btn->Click += gcnew System::EventHandler(this, &SettingsForm::test_btn_Click);
			// 
			// screenshotPreview_btn
			// 
			this->screenshotPreview_btn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
																					  static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->screenshotPreview_btn->FlatAppearance->BorderSize = 0;
			this->screenshotPreview_btn->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
																											   static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->screenshotPreview_btn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->screenshotPreview_btn->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->screenshotPreview_btn->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
																					  static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->screenshotPreview_btn->Location = System::Drawing::Point(9, 428);
			this->screenshotPreview_btn->Name = L"screenshotPreview_btn";
			this->screenshotPreview_btn->Radius = 10;
			this->screenshotPreview_btn->Size = System::Drawing::Size(95, 65);
			this->screenshotPreview_btn->TabIndex = 49;
			this->screenshotPreview_btn->TabStop = false;
			this->screenshotPreview_btn->Text = L"截圖預覽";
			this->screenshotPreview_btn->UseVisualStyleBackColor = false;
			this->screenshotPreview_btn->Click += gcnew System::EventHandler(this, &SettingsForm::screenshotPreview_btn_Click);
			// 
			// SettingsForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(380, 502);
			this->Controls->Add(this->screenshotPreview_btn);
			this->Controls->Add(this->test_btn);
			this->Controls->Add(this->tableLayoutPanel6);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->tableLayoutPanel5);
			this->Controls->Add(this->tableLayoutPanel52);
			this->Controls->Add(this->jp_server_lang_label);
			this->Controls->Add(this->default_btn);
			this->Controls->Add(this->tableLayoutPanel4);
			this->Controls->Add(this->tableLayoutPanel3);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->window_type_label);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->game_server_type_label);
			this->Controls->Add(this->app_name_label);
			this->Controls->Add(this->icon_pictureBox);
			this->Controls->Add(this->minimize_btn);
			this->Controls->Add(this->close_form_btn);
			this->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"SettingsForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
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
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->tableLayoutPanel52->ResumeLayout(false);
			this->tableLayoutPanel52->PerformLayout();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->tableLayoutPanel6->ResumeLayout(false);
			this->tableLayoutPanel6->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void minimize_btn_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void close_form_btn_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void SettingsFormMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void SettingsFormMouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void SettingsFormMouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void autoMouseClickKey_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
	private: System::Void autoMouseClickKey_textBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void default_btn_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void test_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void screenshotPreview_btn_Click(System::Object^ sender, System::EventArgs^ e);
};
}