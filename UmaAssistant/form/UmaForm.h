#pragma once



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
		UmaForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//

			// 更改 .resx 檔的路徑為 UmaAssistant/UmaAssistant/form
			/*System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(L"UmaAssistant.UmaAssistant.form.UmaForm",
				System::Reflection::Assembly::GetExecutingAssembly());*/
		}

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

	public: System::Windows::Forms::TextBox^ event_title_textbox;


	private: System::Windows::Forms::Label^ label1;
	public: System::Windows::Forms::TextBox^ event_owner_textBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ icon_pictureBox;
	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>

		bool draggingForm = false;
	private: System::Windows::Forms::Button^ close_form_btn;
	private: System::Windows::Forms::Button^ minimize_btn;
	private: System::Windows::Forms::Button^ settings_btn;

	private: System::Windows::Forms::Button^ test_btn;
	private: System::Windows::Forms::Button^ screenshot_preview_btnd;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	public: System::Windows::Forms::FlowLayoutPanel^ choicePanel;
	private:




	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::TextBox^ textBox1;
	private:

	public:
	private: System::Windows::Forms::Label^ label4;
	public: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::Button^ button1;


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
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UmaForm::typeid));
			this->event_title_textbox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->event_owner_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->icon_pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->close_form_btn = (gcnew System::Windows::Forms::Button());
			this->minimize_btn = (gcnew System::Windows::Forms::Button());
			this->settings_btn = (gcnew System::Windows::Forms::Button());
			this->test_btn = (gcnew System::Windows::Forms::Button());
			this->screenshot_preview_btnd = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->choicePanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->choicePanel->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// event_title_textbox
			// 
			this->event_title_textbox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->event_title_textbox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->event_title_textbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->event_title_textbox->Cursor = System::Windows::Forms::Cursors::Default;
			this->event_title_textbox->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->event_title_textbox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->event_title_textbox->Location = System::Drawing::Point(140, 3);
			this->event_title_textbox->Multiline = true;
			this->event_title_textbox->Name = L"event_title_textbox";
			this->event_title_textbox->ReadOnly = true;
			this->event_title_textbox->Size = System::Drawing::Size(366, 20);
			this->event_title_textbox->TabIndex = 2;
			this->event_title_textbox->Text = L"名前はまだ無い。";
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label1->Location = System::Drawing::Point(3, 3);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(102, 20);
			this->label1->TabIndex = 5;
			this->label1->Text = L"event_title";
			// 
			// event_owner_textBox
			// 
			this->event_owner_textBox->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->event_owner_textBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->event_owner_textBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->event_owner_textBox->Cursor = System::Windows::Forms::Cursors::Default;
			this->event_owner_textBox->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->event_owner_textBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->event_owner_textBox->Location = System::Drawing::Point(141, 3);
			this->event_owner_textBox->Multiline = true;
			this->event_owner_textBox->Name = L"event_owner_textBox";
			this->event_owner_textBox->ReadOnly = true;
			this->event_owner_textBox->Size = System::Drawing::Size(366, 20);
			this->event_owner_textBox->TabIndex = 6;
			this->event_owner_textBox->Text = L"吾輩は猫である。";
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label2->Location = System::Drawing::Point(3, 3);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(116, 20);
			this->label2->TabIndex = 7;
			this->label2->Text = L"event_owner";
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
			this->close_form_btn->Location = System::Drawing::Point(501, 0);
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
			this->minimize_btn->Location = System::Drawing::Point(456, 0);
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
			this->settings_btn->Location = System::Drawing::Point(449, 40);
			this->settings_btn->Name = L"settings_btn";
			this->settings_btn->Size = System::Drawing::Size(75, 67);
			this->settings_btn->TabIndex = 11;
			this->settings_btn->Text = L"設定";
			this->settings_btn->UseVisualStyleBackColor = false;
			this->settings_btn->Click += gcnew System::EventHandler(this, &UmaForm::settings_btn_Click);
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
			this->test_btn->Location = System::Drawing::Point(243, 40);
			this->test_btn->Name = L"test_btn";
			this->test_btn->Size = System::Drawing::Size(97, 67);
			this->test_btn->TabIndex = 16;
			this->test_btn->Text = L"掃描";
			this->test_btn->UseVisualStyleBackColor = false;
			this->test_btn->Click += gcnew System::EventHandler(this, &UmaForm::test_btn_Click);
			// 
			// screenshot_preview_btnd
			// 
			this->screenshot_preview_btnd->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)),
				static_cast<System::Int32>(static_cast<System::Byte>(61)), static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->screenshot_preview_btnd->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"screenshot_preview_btnd.BackgroundImage")));
			this->screenshot_preview_btnd->FlatAppearance->BorderSize = 0;
			this->screenshot_preview_btnd->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->screenshot_preview_btnd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->screenshot_preview_btnd->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->screenshot_preview_btnd->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)),
				static_cast<System::Int32>(static_cast<System::Byte>(193)), static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->screenshot_preview_btnd->Location = System::Drawing::Point(346, 40);
			this->screenshot_preview_btnd->Name = L"screenshot_preview_btnd";
			this->screenshot_preview_btnd->Size = System::Drawing::Size(97, 67);
			this->screenshot_preview_btnd->TabIndex = 17;
			this->screenshot_preview_btnd->Text = L"截圖預覽";
			this->screenshot_preview_btnd->UseVisualStyleBackColor = false;
			this->screenshot_preview_btnd->Click += gcnew System::EventHandler(this, &UmaForm::screenshot_preview_btn_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				372)));
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->event_owner_textBox, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 129);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(510, 26);
			this->tableLayoutPanel1->TabIndex = 18;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				27.05882F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				72.94118F)));
			this->tableLayoutPanel2->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->event_title_textbox, 1, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(12, 161);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(510, 26);
			this->tableLayoutPanel2->TabIndex = 19;
			// 
			// choicePanel
			// 
			this->choicePanel->AutoScroll = true;
			this->choicePanel->BackColor = System::Drawing::Color::Transparent;
			this->choicePanel->Controls->Add(this->tableLayoutPanel3);
			this->choicePanel->Location = System::Drawing::Point(12, 224);
			this->choicePanel->Name = L"choicePanel";
			this->choicePanel->Size = System::Drawing::Size(513, 267);
			this->choicePanel->TabIndex = 20;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				26.39175F)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				73.60825F)));
			this->tableLayoutPanel3->Controls->Add(this->textBox2, 1, 1);
			this->tableLayoutPanel3->Controls->Add(this->label3, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->textBox1, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->label4, 0, 1);
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 2;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(485, 71);
			this->tableLayoutPanel3->TabIndex = 19;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->textBox2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->textBox2->Location = System::Drawing::Point(130, 28);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(352, 52);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"吾輩は猫であるるるるるるるるるるるるるるるるるるるるるる";
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label3->Location = System::Drawing::Point(3, 2);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(105, 20);
			this->label3->TabIndex = 7;
			this->label3->Text = L"choice_title";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->textBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->textBox1->Location = System::Drawing::Point(130, 3);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(352, 19);
			this->textBox1->TabIndex = 6;
			this->textBox1->Text = L"吾輩は猫である。";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 10));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->label4->Location = System::Drawing::Point(3, 25);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(114, 40);
			this->label4->TabIndex = 7;
			this->label4->Text = L"choice_effect";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(44)), static_cast<System::Int32>(static_cast<System::Byte>(61)),
				static_cast<System::Int32>(static_cast<System::Byte>(81)));
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Mochiy Pop One", 12));
			this->button1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(207)), static_cast<System::Int32>(static_cast<System::Byte>(193)),
				static_cast<System::Int32>(static_cast<System::Byte>(151)));
			this->button1->Location = System::Drawing::Point(15, 40);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(97, 67);
			this->button1->TabIndex = 21;
			this->button1->Text = L"測試";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &UmaForm::button1_Click);
			// 
			// UmaForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(540, 503);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->choicePanel);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->screenshot_preview_btnd);
			this->Controls->Add(this->test_btn);
			this->Controls->Add(this->settings_btn);
			this->Controls->Add(this->minimize_btn);
			this->Controls->Add(this->close_form_btn);
			this->Controls->Add(this->icon_pictureBox);
			this->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"UmaForm";
			this->Text = L"UmaForm";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UmaForm::UmaForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &UmaForm::UmaForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UmaForm::UmaForm_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->icon_pictureBox))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->choicePanel->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void test_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void settings_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void screenshot_preview_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void UmaForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void UmaForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void UmaForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void close_form_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void minimize_btn_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
};
}
