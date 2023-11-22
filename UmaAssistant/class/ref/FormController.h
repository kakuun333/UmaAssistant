#pragma once



using namespace System;
using namespace System::Windows::Forms;

/// <summary>
/// 讓 Windows Form 多執行緒的操作變得更容易
/// </summary>
ref class FormController
{
private:
	FormController() {}
	FormController(const FormController%) { throw gcnew System::InvalidOperationException(u8"單一模式不可以有複製建構子。singleton cannot be copy-constructed"); }
	static FormController _instance;


	System::Void FormController::InvokeScriptInternal(String^ script, array<Object^>^ param);

public:
	static property FormController^ Instance { FormController^ get() { return % _instance; } }

	static WebBrowser^ webBrowserTemp;

	System::Void FormController::InvokeScript(WebBrowser^ webBrowser, System::String^ script, array<Object^>^ param);

	

};

