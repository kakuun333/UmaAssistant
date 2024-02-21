#pragma once

// util
#include "../../util/CharacterFilter.h"
#include "../../util/CharacterConvert.h"

// class
#include "../data/UmaEventData.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Text::RegularExpressions;


constexpr inline unsigned int NEW_LINE_BYTE = 52;
constexpr inline unsigned int NEW_LINE_SIZE = 20;

ref class FormDesigner
{
private:
	FormDesigner() {}
	FormDesigner(const FormDesigner%) { throw gcnew System::InvalidOperationException(u8"��@�Ҧ����i�H���ƻs�غc�l�Csingleton cannot be copy-constructed"); }
	static FormDesigner _instance;

public:
	static property FormDesigner^ Instance { FormDesigner^ get() { return %_instance; } }
	
	System::Void CreateChoiceTable(UmaChoice choice);

	// �ǤJ textbox ��p��X table_layout �����һݪ�����
	int CalcChoiceTableVerticalSize(TextBox^ choice_effect_textbox);
};