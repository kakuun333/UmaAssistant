#pragma once



namespace UmaAssistant {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// PreviewForm ���K�n
	/// </summary>
	public ref class PreviewForm : public System::Windows::Forms::Form
	{
	public:
		PreviewForm(void)
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
		}

		void FormClosingHandler(Object^ sender, FormClosingEventArgs^ e)
		{
			// ���������ާ@�A�קK form �Q�۰�����
			e->Cancel = true;

			// ���õ���
			this->Hide();
		}

		System::Windows::Forms::PictureBox^ GetPictureBox()
		{
			return pictureBox1;
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
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
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
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
