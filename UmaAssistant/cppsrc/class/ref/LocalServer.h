#pragma once

// enum
#include "../../enum/FileType.h"
#include "../../enum/FilePathType.h"

// global
#include "../../global/form.h"
#include "../../global/path.h"

// .NET
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Threading;

public ref class LocalServer
{

private:
	LocalServer() {}
	LocalServer(const LocalServer%) { throw gcnew System::InvalidOperationException(u8"單一模式不可以有複製建構子。singleton cannot be copy-constructed"); }
	static LocalServer _instance;

	static HttpListener^ _listener;

	void StartLocalServer(Object^ port);

	void HandleUmaWebRequest(Object^ obj);
public:
	static property LocalServer^ Instance { LocalServer^ get() { return % _instance; } }

	void Start(System::String^ port);

	void Stop();
};
