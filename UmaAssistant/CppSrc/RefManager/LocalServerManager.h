#pragma once

// Enum
#include <Enum/FileType.h>
#include <Enum/FilePathType.h>

// Global
#include <Global/form.h>
#include <Global/path.h>

// .NET
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Threading;

public ref class LocalServerManager
{

private:
	LocalServerManager() {}
	LocalServerManager(const LocalServerManager%) { throw gcnew System::InvalidOperationException(u8"單一模式不可以有複製建構子。singleton cannot be copy-constructed"); }
	static LocalServerManager m_Instance;

	static HttpListener^ m_Listener;

	void StartLocalServer(Object^ port);

	void HandleUmaWebRequest(Object^ obj);
public:
	static property LocalServerManager^ Instance { LocalServerManager^ get() { return % m_Instance; } }

	void Start(System::String^ port);

	void Stop();
};
