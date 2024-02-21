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
	FormDesigner(const FormDesigner%) { throw gcnew System::InvalidOperationException(u8"單一模式不可以有複製建構子。singleton cannot be copy-constructed"); }
	static FormDesigner _instance;

public:
	static property FormDesigner^ Instance { FormDesigner^ get() { return %_instance; } }
	
	System::Void CreateChoiceTable(UmaChoice choice);

	// 傳入 textbox 後計算出 table_layout 垂直所需的高度
	int CalcChoiceTableVerticalSize(TextBox^ choice_effect_textbox);
};