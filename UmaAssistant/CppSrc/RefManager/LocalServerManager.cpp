﻿#include "LocalServerManager.h"



void LocalServerManager::HandleUmaWebRequest(System::Object^ obj)
{
	array<System::Object^>^ paramsArray = static_cast<array<System::Object^>^>(obj);

	// 處理請求的實際邏輯
	HttpListenerContext^ context = dynamic_cast<HttpListenerContext^>(paramsArray[0]);
	HttpListenerRequest^ request = context->Request;
	HttpListenerResponse^ response = context->Response;

	// 檔案類型
	FileType fileType = static_cast<FileType>(safe_cast<System::Int32>(paramsArray[1]));

	// 檔案路徑類型
	FilePathType filePathType = static_cast<FilePathType>(safe_cast<System::Int32>(paramsArray[2]));

	// 檔案路徑
	System::String^ filePath;

	switch (filePathType)
	{
	case FilePathType::UMA_WEB:
		filePath = global::path::umaWeb + request->Url->AbsolutePath;
		break;
	case FilePathType::UMA_MISC:
		filePath = global::path::currentDir + request->Url->AbsolutePath;
		break;
	case FilePathType::UMA_DATA:
		filePath = global::path::currentDir + request->Url->AbsolutePath;
		break;
	}

	try
	{
		// 讀取檔案
		array<System::Byte>^ fileData = File::ReadAllBytes(filePath);


		if (System::IO::File::Exists(filePath))
		{
			array<System::Byte>^ fileData = System::IO::File::ReadAllBytes(filePath);

			// 設定回應標頭
			switch (fileType)
			{
			case FileType::HTML:
				response->ContentType = "text/html";
				break;
			case FileType::CSS:
				response->ContentType = "text/css";
				break;
			case FileType::JSON:
				response->ContentType = "application/json";
				break;
			case FileType::JAVASCRIPT:
				response->ContentType = "text/javascript";
				break;
			case FileType::TTF:
				response->ContentType = "application/font-sfnt";
				break;
			case FileType::PNG:
				response->ContentType = "image/png";
				break;
			}

			response->ContentLength64 = fileData->Length;

			try
			{
				// 寫入回應數據
				response->OutputStream->Write(fileData, 0, fileData->Length);
			}
			catch (System::Net::HttpListenerException^ ex)
			{
				std::cout << u8"[LocalServer] 處理 HTTP 請求時發生例外\n";
			}
		}
		else
		{
			// 檔案不存在的處理邏輯
			response->StatusCode = (int)HttpStatusCode::NotFound;
			response->StatusDescription = "File not found.";
			response->OutputStream->Close();
		}
	}
	catch (FileNotFoundException^)
	{
		// 檔案不存在的處理邏輯
		response->StatusCode = (int)HttpStatusCode::NotFound;
	}

	// 關閉回應流
	response->OutputStream->Close();
}



void LocalServerManager::StartLocalServer(Object^ port)
{
	System::String^ port_str = dynamic_cast<System::String^>(port);

	// 創建 HttpListener 物件
	HttpListener^ listener = gcnew HttpListener();

	m_Listener = listener;

	// 添加要聽取的前綴（URL）
	listener->Prefixes->Add(System::String::Format("{0}{1}/", "http://localhost:", port_str));

	try
	{
		// 開始監聽請求
		listener->Start();

		std::cout << u8"正在監聽本地伺服器... Port: " << util::systemStr2std(port_str) << std::endl;

		while (true)
		{

			// 等待請求
			HttpListenerContext^ context = listener->GetContext();

			String^ requestUrl = context->Request->Url->AbsolutePath;

			//Console::WriteLine(requestUrl);

			if (requestUrl->EndsWith(".html"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^> {
					context,
					static_cast<Object^>(safe_cast<Int32>(FileType::HTML)),
					static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_WEB))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServerManager::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".css"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
					static_cast<Object^>(safe_cast<Int32>(FileType::CSS)),
					static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_WEB))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServerManager::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".json"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
					static_cast<Object^>(safe_cast<Int32>(FileType::JSON)),
					static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_DATA))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServerManager::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".js"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
					static_cast<Object^>(safe_cast<Int32>(FileType::JAVASCRIPT)),
					static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_WEB))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServerManager::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".ttf"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
						static_cast<Object^>(safe_cast<Int32>(FileType::TTF)),
						static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_MISC))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServerManager::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".png"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
					static_cast<Object^>(safe_cast<Int32>(FileType::PNG)),
					static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_MISC))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServerManager::HandleUmaWebRequest), paramsArray);
			}
		}
	}
	catch (Exception^ ex)
	{
		std::cout << u8"Local Server Error: " << util::systemStr2std(ex->Message) << std::endl;
	}
	finally
	{
		// 關閉伺服器
		listener->Close();
		//listener->Stop();
	}
}

void LocalServerManager::Start(System::String^ port)
{
	Thread^ localHostThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &LocalServerManager::StartLocalServer));

	localHostThread->Start(port);
}

void LocalServerManager::Stop()
{
	m_Listener->Close();
	//_listener->Stop();
}