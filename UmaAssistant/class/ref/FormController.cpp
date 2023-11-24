#include "FormController.h"

using namespace System::Windows::Forms;

System::Void FormController::InvokeScript(WebBrowser^ webBrowser, System::String^ script, array<Object^>^ param)
{
    webBrowserTemp = webBrowser;

    if (webBrowser->InvokeRequired)
    {
        Action<String^, array<Object^>^>^ action = gcnew Action<String^, array<Object^>^>(this, &FormController::InvokeScriptInternal);
        webBrowser->Invoke(action, script, param);
    }
    //else
    //{
    //    webBrowser->Document->InvokeScript(script, param);
    //}
}

System::Void FormController::InvokeScriptInternal(String^ script, array<Object^>^ param)
{
    // ��ڪ��e�����
    // �i��P InvokeScript �ۦP���ާ@
    webBrowserTemp->Document->InvokeScript(script, param);
}