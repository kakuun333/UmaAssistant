#pragma once

#using "CSharpRuntime/Newtonsoft.Json.dll"
using namespace Newtonsoft::Json;
using namespace Microsoft::Web::WebView2::WinForms;

using namespace System;
using namespace System::Windows::Forms;


/// <summary>
/// �� Windows Form �b�h��������ާ@�ܱo���K
/// </summary>
ref class FormController
{
private:
	FormController() {}
	FormController(const FormController%) { throw gcnew System::InvalidOperationException(u8"��@�Ҧ����i�H���ƻs�غc�l�Csingleton cannot be copy-constructed"); }
	static FormController _instance;

	//static WebBrowser^ webBrowserTemp;
	WebBrowser^ _webBrowserTemp;
	WebView2^ _webView2Temp;

	System::Void _InvokeScriptInternal(String^ script, array<Object^>^ param);

	System::Void _ExecuteFunctionAsyncInternal(String^ functionName, array<Object^>^ param);

	System::Void _ExecuteFunctionAsync(WebView2^ webView2, String^ functionName, array<Object^>^ param);
public:
	static property FormController^ Instance { FormController^ get() { return %_instance; } }


	System::Void InvokeScript(WebBrowser^ webBrowser, String^ script, array<Object^>^ param);


	System::Void ExecuteFunctionAsync(WebView2^ webView2, String^ functionName, array<Object^>^ param);
};

