#include "FormController.h"

System::Void FormController::_InvokeScriptInternal(String^ script, array<Object^>^ param)
{
    // ��ڪ��e�����
    // �i��P InvokeScript �ۦP���ާ@
    _webBrowserTemp->Document->InvokeScript(script, param);
}


System::Void FormController::InvokeScript(WebBrowser^ webBrowser, System::String^ script, array<Object^>^ param)
{
    _webBrowserTemp = webBrowser;

    if (webBrowser->InvokeRequired)
    {
        Action<String^, array<Object^>^>^ action = gcnew Action<String^, array<Object^>^>(this, &FormController::_InvokeScriptInternal);
        webBrowser->Invoke(action, script, param);
    }
    else
    {
        webBrowser->Document->InvokeScript(script, param);
    }
}

// =============================================================================================================== //

System::Void FormController::_ExecuteFunctionAsyncInternal(String^ functionName, array<Object^>^ param)
{
    _ExecuteFunctionAsync(_webView2Temp, functionName, param);
}

System::Void FormController::_ExecuteFunctionAsync(WebView2^ webView2, String^ functionName, array<Object^>^ param)
{
    // https://stackoverflow.com/questions/62835549/equivalent-of-webbrowser-invokescriptstring-object-in-webview2
    System::String^ script = functionName + "(";
    for (int i = 0; i < param->Length; i++)
    {
        script += JsonConvert::SerializeObject(param[i]);
        if (i < param->Length - 1)
        {
            script += ", ";
        }
    }
    script += ");";

    webView2->ExecuteScriptAsync(script);
}



System::Void FormController::ExecuteFunctionAsync(WebView2^ webView2, String^ functionName, array<Object^>^ param)
{
    _webView2Temp = webView2;

    if (webView2->InvokeRequired)
    {
        Action<String^, array<Object^>^>^ action = gcnew Action<String^, array<Object^>^>(this, &FormController::_ExecuteFunctionAsyncInternal);
        webView2->Invoke(action, functionName, param);
    }
    else
    {
        _ExecuteFunctionAsync(_webView2Temp, functionName, param);
    }
}