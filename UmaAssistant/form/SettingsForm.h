#pragma once

#include "../lua/luaTest.h"

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
		SettingsForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//

			// 更改 .resx 檔的路徑為 UmaAssistant/UmaAssistant/form
			/*System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(L"UmaAssistant.UmaAssistant.form.SettingsForm",
				System::Reflection::Assembly::GetExecutingAssembly());*/

			// 註冊 FormClosing 事件
			this->FormClosing += gcnew FormClosingEventHandler(this, &SettingsForm::FormClosingHandler);
		}

		void FormClosingHandler(Object^ sender, FormClosingEventArgs^ e)
		{
			// 取消關閉操作，避免 form 被自動釋放
			e->Cancel = true;

			// 隱藏視窗
			this->Hide();
		}

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
	private: System::Windows::Forms::Button^ button1;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"新細明體", 11));
			this->button1->Location = System::Drawing::Point(66, 84);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(139, 86);
			this->button1->TabIndex = 0;
			this->button1->Text = L"更新 event_data_jp.json";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SettingsForm::button1_Click);
			// 
			// SettingsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->button1);
			this->Name = L"SettingsForm";
			this->Text = L"SettingsForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		testlua();
	}
	};
}
