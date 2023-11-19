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
		PreviewForm(void)
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
		}

		void FormClosingHandler(Object^ sender, FormClosingEventArgs^ e)
		{
			// 取消關閉操作，避免 form 被自動釋放
			e->Cancel = true;

			// 隱藏視窗
			this->Hide();
		}

		System::Windows::Forms::PictureBox^ GetPictureBox()
		{
			return pictureBox1;
		}

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
	public: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:

	protected:

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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(484, 811);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// PreviewForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(484, 811);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"PreviewForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PreviewForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
