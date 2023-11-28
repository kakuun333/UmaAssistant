#include "../stdafx.h"


void LocalServer::HandleUmaWebRequest(Object^ obj)
{
	array<Object^>^ paramsArray = static_cast<array<Object^>^>(obj);

	// �B�z�ШD������޿�
	HttpListenerContext^ context = dynamic_cast<HttpListenerContext^>(paramsArray[0]);
	HttpListenerRequest^ request = context->Request;
	HttpListenerResponse^ response = context->Response;

	// �ɮ�����
	FileType fileType = static_cast<FileType>(safe_cast<Int32>(paramsArray[1]));

	// �ɮ׸��|����
	FilePathType filePathType = static_cast<FilePathType>(safe_cast<Int32>(paramsArray[2]));

	// �ɮ׸��|
	String^ filePath;

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

	//Console::WriteLine("filePath = " + filePath);


	try
	{
		// Ū���ɮ�
		array<Byte>^ fileData = File::ReadAllBytes(filePath);

		// �]�w�^�����Y
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

		// �g�J�^���ƾ�
		response->OutputStream->Write(fileData, 0, fileData->Length);
	}
	catch (FileNotFoundException^)
	{
		// �ɮפ��s�b���B�z�޿�
		response->StatusCode = (int)HttpStatusCode::NotFound;
	}

	// �����^���y
	response->OutputStream->Close();
}



void LocalServer::StartLocalServer(Object^ port)
{
	System::String^ port_str = dynamic_cast<System::String^>(port);

	// �Ы� HttpListener ����
	HttpListener^ listener = gcnew HttpListener();

	// �K�[�nť�����e��]URL�^
	listener->Prefixes->Add("http://localhost:" + port_str + "/");

	try
	{
		// �}�l��ť�ШD
		listener->Start();

		Console::WriteLine("���b��ť���a���A��..."/*"Local Server listening..."*/);

		while (true)
		{

			// ���ݽШD
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
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServer::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".css"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
					static_cast<Object^>(safe_cast<Int32>(FileType::CSS)),
					static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_WEB))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServer::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".json"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
						static_cast<Object^>(safe_cast<Int32>(FileType::JSON)),
						static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_DATA))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServer::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".js"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
						static_cast<Object^>(safe_cast<Int32>(FileType::JAVASCRIPT)),
						static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_WEB))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServer::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".ttf"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
						static_cast<Object^>(safe_cast<Int32>(FileType::TTF)),
						static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_MISC))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServer::HandleUmaWebRequest), paramsArray);
			}
			else if (requestUrl->EndsWith(".png"))
			{
				array<Object^>^ paramsArray = gcnew array<Object^>
				{
					context,
					static_cast<Object^>(safe_cast<Int32>(FileType::PNG)),
					static_cast<Object^>(safe_cast<Int32>(FilePathType::UMA_MISC))
				};
				ThreadPool::QueueUserWorkItem(gcnew WaitCallback(this, &LocalServer::HandleUmaWebRequest), paramsArray);
			}



			//if (requestUrl == "/choice.html")
			//{
			//	// ��^ choice.html �����e
			//	String^ responseString = FileManager::GetInstance()->SysReadFile(global::path::choice_html);
			//	array<Byte>^ buffer = Encoding::UTF8->GetBytes(responseString);

			//	System::IO::Stream^ output = context->Response->OutputStream;
			//	output->Write(buffer, 0, buffer->Length);
			//}
			//else if (requestUrl == "/choice_style.css")
			//{
			//	String^ responseString = FileManager::GetInstance()->SysReadFile(global::path::choice_style_css);
			//	array<Byte>^ buffer = Encoding::UTF8->GetBytes(responseString);

			//	System::IO::Stream^ output = context->Response->OutputStream;
			//	output->Write(buffer, 0, buffer->Length);
			//}
			//else if (requestUrl == "/choice_displayer.js")
			//{
			//	String^ responseString = FileManager::GetInstance()->SysReadFile(global::path::choice_displayer_js);
			//	array<Byte>^ buffer = Encoding::UTF8->GetBytes(responseString);

			//	System::IO::Stream^ output = context->Response->OutputStream;
			//	output->Write(buffer, 0, buffer->Length);
			//}
			//else if (requestUrl == "/skill_displayer.js")
			//{
			//	String^ responseString = FileManager::GetInstance()->SysReadFile(global::path::skill_displayer_js);
			//	array<Byte>^ buffer = Encoding::UTF8->GetBytes(responseString);

			//	System::IO::Stream^ output = context->Response->OutputStream;
			//	output->Write(buffer, 0, buffer->Length);
			//}


			// ������X�y�M�W�U��
			//context->Response->Close();
		}
	}
	catch (Exception^ ex)
	{
		Console::WriteLine("Local Server Error: " + ex->Message);
	}
	finally
	{
		// �������A��
		listener->Close();
	}
}

void LocalServer::Start(System::String^ port)
{
	Thread^ localHostThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &LocalServer::StartLocalServer));

	localHostThread->Start(port);
}