#pragma once



using namespace System;
using namespace System::Windows::Forms;

/// <summary>
/// �� Windows Form �h��������ާ@�ܱo��e��
/// </summary>
ref class FormController
{
private:
	FormController() {}
	FormController(const FormController%) { throw gcnew System::InvalidOperationException(u8"��@�Ҧ����i�H���ƻs�غc�l�Csingleton cannot be copy-constructed"); }
	static FormController _instance;


	System::Void FormController::InvokeScriptInternal(String^ script, array<Object^>^ param);

public:
	static property FormController^ Instance { FormController^ get() { return % _instance; } }

	static WebBrowser^ webBrowserTemp;

	System::Void FormController::InvokeScript(WebBrowser^ webBrowser, System::String^ script, array<Object^>^ param);

	

};

