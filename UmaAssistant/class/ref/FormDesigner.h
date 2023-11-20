#pragma once

using namespace System::Windows::Forms;


constexpr inline unsigned int NEW_LINE_BYTE = 52;
constexpr inline unsigned int NEW_LINE_SIZE = 20;

public ref class FormDesigner
{
private:
	FormDesigner() {}
	FormDesigner(const FormDesigner%) { throw gcnew System::InvalidOperationException(u8"��@�Ҧ����i�H���ƻs�غc�l�Csingleton cannot be copy-constructed"); }
	static FormDesigner _instance;

public:
	static property FormDesigner^ Instance { FormDesigner^ get() { return % _instance; } }
	
	// �ǤJ textbox ��p��X table_layout �����һݪ�����
	int CalcChoiceTableVerticalSize(TextBox^ choice_effect_textbox);
};