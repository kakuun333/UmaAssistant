#include "UmaForm.h"

// util
#include "cppsrc/util/CharacterConvert.h"

// class
#include "cppsrc/class/Config.h"
#include "cppsrc/class/Scanner.h"
#include "cppsrc/class/DataManager.h"
#include "cppsrc/class/ConsoleManager.h"
#include "cppsrc/class/ref/WebViewManager.h"
#include "cppsrc/class/ref/LocalServer.h"

// global
#include "cppsrc/global/umaswitch.h"

#using "CSharpRuntime/UmaCSharpLibrary.dll"

using namespace Microsoft::Web::WebView2::Core;
using namespace Microsoft::Web::WebView2::WinForms;

namespace UmaAssistant
{
#pragma region EventHandler 函式
	System::Void UmaForm::OnNavigationCompleted(System::Object^ sender, CoreWebView2NavigationCompletedEventArgs^ e)
	{
		WebView2^ webview = dynamic_cast<WebView2^>(sender);
		
		DataManager* dataManager = DataManager::GetInstance();

		if (webview->Name == choiceWebView2->Name)
		{
			// 初始化 skill_displayer.js 中的 let GameServer 變數

			// GameServer
			switch (Config::GetInstance()->GameServer)
			{
			case static_cast<int>(GameServerType::JP):
				WebViewManager::Instance->SetGameServer(static_cast<int>(GameServerType::JP));
				break;

			case static_cast<int>(GameServerType::TW):
				WebViewManager::Instance->SetGameServer(static_cast<int>(GameServerType::TW));
				break;
			}

			// JpServerLang
			switch (Config::GetInstance()->JpServerLang)
			{
			case static_cast<int>(GameServerType::JP):
				WebViewManager::Instance->SetJpServerLanguage(static_cast<int>(GameServerType::JP));
				break;

			case static_cast<int>(GameServerType::TW):
				WebViewManager::Instance->SetJpServerLanguage(static_cast<int>(GameServerType::TW));
				break;
			}


			// SoftwareLanguage
			switch (Config::GetInstance()->SoftwareLanguage)
			{
			case static_cast<int>(GameServerType::JP):
				WebViewManager::Instance->ChangeCharacterNameHtmlLanguage(static_cast<int>(SoftwareLanguageType::JP));
				WebViewManager::Instance->ChangeChoiceHtmlLanguage(static_cast<int>(SoftwareLanguageType::JP));
				break;

			case static_cast<int>(GameServerType::TW):
				WebViewManager::Instance->ChangeCharacterNameHtmlLanguage(static_cast<int>(SoftwareLanguageType::TW));
				WebViewManager::Instance->ChangeChoiceHtmlLanguage(static_cast<int>(SoftwareLanguageType::TW));
				break;
			}
		}
		else if (webview->Name == characterNameWebView2->Name)
		{
			#pragma region 初始化上次選擇的角色
			if (dataManager->SetCurrentCharacterInfoDict(Config::GetInstance()->PreviousCurrentCharacterName))
			{
				std::cout << u8"成功初始化上次培育的角色！ PreviousCurrentCharacterName: " << Config::GetInstance()->PreviousCurrentCharacterName << std::endl;
				dataManager->SetCurrentCharacterInfoLock(true);

				System::String^ sys_currentCharName = util::stdStr2system(Config::GetInstance()->PreviousCurrentCharacterName);
				WebViewManager::Instance->ChangeCharacterName(sys_currentCharName);

				// 更新 Discord RPC
				UmaCSharp::UmaDiscordManager::Instance->SetPresence(
					Config::GetInstance()->GameServer,
					Config::GetInstance()->SoftwareLanguage,
					util::stdStr2system(DataManager::GetInstance()->GetCurrentCharacter())
				);
				UmaCSharp::UmaDiscordManager::Instance->Update();
			}
			else
			{
				std::cout << u8"初始化上次培育的角色失敗！ PreviousCurrentCharacterName: " << Config::GetInstance()->PreviousCurrentCharacterName << std::endl;
			}
			#pragma endregion
		}
		else if (webview->Name == selectCharacterWebView2->Name)
		{
			// 切換 select_character.html 語言
			WebViewManager::Instance->ChangeSelectCharacterHtmlLanguage(Config::GetInstance()->SoftwareLanguage);
		}
	}

	System::Void UmaForm::OnWebMessageReceived(System::Object^ sender, CoreWebView2WebMessageReceivedEventArgs^ e)
	{
		WebView2^ webview = dynamic_cast<WebView2^>(sender);

		// 當 Web 內容發送消息時觸發此事件
		System::String^ message = e->TryGetWebMessageAsString();

		if (System::String::IsNullOrEmpty(message))
		{
			std::cout << u8"[UmaForm] WebMessage 是空的:" << util::systemStr2std(message) << std::endl;
			return;
		}


		if (webview->Name == selectCharacterWebView2->Name)
		{
			json j_msg = json::parse(util::systemStr2std(message));

			if (j_msg["messageName"] == "charImgClick")
			{

				//std::cout << u8"收到消息:" << util::systemStr2std(message) << std::endl;

				DataManager* dataManager = DataManager::GetInstance();
				UmaLog* umalog = UmaLog::GetInstance();

				System::String^ altValue = util::stdStr2system(j_msg["alt"].get<std::string>());

				Regex^ jp_pattern = gcnew Regex("<jp_event_owner>(.+)</jp_event_owner>");
				Regex^ tw_pattern = gcnew Regex("<tw_event_owner>(.+)</tw_event_owner>");

				Match^ match;

				switch (Config::GetInstance()->GameServer)
				{
				case static_cast<int>(GameServerType::JP):
					match = jp_pattern->Match(altValue);
					if (match->Success)
					{
						dataManager->SetCurrentCharacterInfoLock(false);
						WebViewManager::Instance->ChangeCharacterName("");
							
						System::String^ sys_event_owner = match->Groups[1]->Value;
						std::string std_event_owner = util::systemStr2std(sys_event_owner);

						umalog->print("[UmaForm] CHARACTER MATCHED: ", std_event_owner);

						if (dataManager->SetCurrentCharacterInfoDict(std_event_owner))
						{
							umalog->print(u8"[UmaForm] 已找到選擇的角色");
							dataManager->SetCurrentCharacterInfoLock(true);
							WebViewManager::Instance->ChangeCharacterName(sys_event_owner);

							// 更新 Discord RPC
							UmaCSharp::UmaDiscordManager::Instance->SetPresence(
								Config::GetInstance()->GameServer,
								Config::GetInstance()->SoftwareLanguage,
								util::stdStr2system(DataManager::GetInstance()->GetCurrentCharacter())
							);
							UmaCSharp::UmaDiscordManager::Instance->Update();
						}
						else
						{
							umalog->print("[UmaForm] CAN NOT FOUND SELECT CHARACTER");
						}
					}
					else
					{
						umalog->print("[UmaForm] NOT MATCHED SELECT CHARACTER NAME");
					}
					break;
				case static_cast<int>(GameServerType::TW):
					match = tw_pattern->Match(altValue);
					if (match->Success)
					{
						dataManager->SetCurrentCharacterInfoLock(false);
						WebViewManager::Instance->ChangeCharacterName("");

						System::String^ sys_event_owner = match->Groups[1]->Value;
						std::string std_event_owner = util::systemStr2std(sys_event_owner);

						umalog->print("[UmaForm] CHARACTER MATCHED: ", std_event_owner);

						if (dataManager->SetCurrentCharacterInfoDict(std_event_owner))
						{
							umalog->print(u8"[UmaForm] 已找到選擇的角色");
							dataManager->SetCurrentCharacterInfoLock(true);
							WebViewManager::Instance->ChangeCharacterName(sys_event_owner);

							// 更新 Discord RPC
							UmaCSharp::UmaDiscordManager::Instance->SetPresence(
								Config::GetInstance()->GameServer,
								Config::GetInstance()->SoftwareLanguage,
								util::stdStr2system(DataManager::GetInstance()->GetCurrentCharacter())
							);
							UmaCSharp::UmaDiscordManager::Instance->Update();
						}
						else
						{
							umalog->print("[UmaForm] CAN NOT FOUND SELECT CHARACTER");
						}
					}
					else
					{
						umalog->print("[UmaForm] NOT MATCHED SELECT CHARACTER NAME");
					}
					break;
				}
			}
		}
	
	}

	System::Void UmaForm::OnApplicationExit(System::Object^ sender, EventArgs^ e)
	{
		// 中止 LocalServer
		LocalServer::Instance->Stop();

		// 關閉 Console
		ConsoleManager::GetInstance()->Disable();

		// 卸載字型
		RemoveFontResourceW(util::string2wstring(global::path::std_MochiyPopOne).c_str());

		// 去初始化 Discord RPC
		UmaCSharp::UmaDiscordManager::Instance->Deinitialize();
	}
#pragma endregion

#pragma region Button Click
	System::Void UmaForm::scan_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Scanner* scanner = Scanner::GetInstance();
		FileManager* fileManager = FileManager::GetInstance();
		UmaLog* umalog = UmaLog::GetInstance();

		if (!global::umaswitch::Scanning)
		{
			if (!Scanner::IsInited())
			{
				umalog->print("[UmaForm] Scanner 尚未完成初始化！");
				return;
			}

			scanner->Start();
		}
		else
		{
			scanner->Stop();
		}
	}

	System::Void UmaForm::settings_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		global::form::settingsForm->Show();
	}

	System::Void UmaForm::close_form_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}

	System::Void UmaForm::minimize_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
	}

	System::Void UmaForm::clean_current_character_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DataManager::GetInstance()->SetCurrentCharacterInfoLock(false);
		WebViewManager::Instance->ChangeCharacterName("");
	}

	System::Void UmaForm::select_window_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		global::form::previewForm->window_listbox->Items->Clear();
		GameWindowFinder::GetInstance()->EnumWindow();
		global::form::previewForm->Show();
	}

	System::Void UmaForm::close_select_character_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ button = dynamic_cast<Button^>(sender);

		_openedSelectCharacter = false;

		switch (Config::GetInstance()->SoftwareLanguage)
		{
		case static_cast<int>(SoftwareLanguageType::JP):
			this->select_character_btn->Text = u8"キャラ選択";
			break;
		case static_cast<int>(SoftwareLanguageType::TW):
			this->select_character_btn->Text = u8"選擇角色";
			break;
		}

		this->Size = System::Drawing::Size(560, this->Size.Height);

		this->minimize_btn->Location = System::Drawing::Point(476, 0);
		this->close_form_btn->Location = System::Drawing::Point(521, 0);
	}

	System::Void UmaForm::select_character_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ button = dynamic_cast<Button^>(sender);

		switch (_openedSelectCharacter)
		{
		case true:
			_openedSelectCharacter = false;

			switch (Config::GetInstance()->SoftwareLanguage)
			{
			case static_cast<int>(SoftwareLanguageType::JP):
				button->Text = u8"キャラ選択";
				break;
			case static_cast<int>(SoftwareLanguageType::TW):
				button->Text = u8"選擇角色";
				break;
			}


			this->Size = System::Drawing::Size(560, this->Size.Height);
			this->minimize_btn->Location = System::Drawing::Point(476, 0);
			this->close_form_btn->Location = System::Drawing::Point(521, 0);

			break;

		case false:
			_openedSelectCharacter = true;

			switch (Config::GetInstance()->SoftwareLanguage)
			{
			case static_cast<int>(SoftwareLanguageType::JP):
				button->Text = u8"折りたたむ";
				break;
			case static_cast<int>(SoftwareLanguageType::TW):
				button->Text = u8"收回";
				break;
			}

			this->Size = System::Drawing::Size(1060, this->Size.Height);

			this->minimize_btn->Location = System::Drawing::Point(476, 0);
			this->close_form_btn->Location = System::Drawing::Point(521, 0);
			break;
		}
	}


#pragma endregion

	UmaForm::UmaForm(void) // UmaForm 的建構函數
	{
		InitializeComponent();
		//
		//TODO:  在此加入建構函式程式碼
		//

		Application::ApplicationExit += gcnew EventHandler(this, &UmaForm::OnApplicationExit);

		#pragma region 初始化 WebBrowser
		// 提取 config 資料
		System::String^ port = util::stdStr2system(Config::GetInstance()->LocalServer["Port"]);

		// choice.html
		choiceWebView2->WebMessageReceived += gcnew System::EventHandler<CoreWebView2WebMessageReceivedEventArgs^>(this, &UmaForm::OnWebMessageReceived);
		choiceWebView2->NavigationCompleted += gcnew System::EventHandler<CoreWebView2NavigationCompletedEventArgs^>(this, &UmaForm::OnNavigationCompleted);
		choiceWebView2->Source = gcnew System::Uri(System::String::Format("http://localhost:{0}/choice.html", port), System::UriKind::Absolute);

		// character_name.html
		characterNameWebView2->NavigationCompleted += gcnew System::EventHandler<CoreWebView2NavigationCompletedEventArgs^>(this, &UmaForm::OnNavigationCompleted);
		characterNameWebView2->Source = gcnew System::Uri(System::String::Format("http://localhost:{0}/character_name.html", port), System::UriKind::Absolute);

		// select_character.html
		selectCharacterWebView2->WebMessageReceived += gcnew System::EventHandler<CoreWebView2WebMessageReceivedEventArgs^>(this, &UmaForm::OnWebMessageReceived);
		selectCharacterWebView2->NavigationCompleted += gcnew System::EventHandler<CoreWebView2NavigationCompletedEventArgs^>(this, &UmaForm::OnNavigationCompleted);
		selectCharacterWebView2->Source = gcnew System::Uri(System::String::Format("http://localhost:{0}/select_character.html", port), System::UriKind::Absolute);
		#pragma endregion
	}

	System::Void UmaForm::UmaForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		draggingForm = true;
		dragOffset.X = e->X;
		dragOffset.Y = e->Y;
	}
	System::Void UmaForm::UmaForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		draggingForm = false;
	}

	System::Void UmaForm::UmaForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
		if (draggingForm)
		{
			System::Drawing::Point currentFormPos = PointToScreen(System::Drawing::Point(e->X, e->Y));
			this->Location = System::Drawing::Point(currentFormPos.X  - dragOffset.X, currentFormPos.Y - dragOffset.Y);
		}
	}
}