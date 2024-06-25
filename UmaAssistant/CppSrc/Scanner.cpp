#include "Scanner.h"

void Scanner::InitOcrJpn()
{
	std::thread initThread([=]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "jpn", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/); // 日文 "jpn"、繁體中文 "chi_tra"

			ocr->SetPageSegMode(tesseract::PSM_SINGLE_LINE/*tesseract::PSM_SINGLE_BLOCK*/);

			ocr->SetVariable("textord_tabfind_find_tables", "0"); // defulat: 1, run table detection
			ocr->SetVariable("textord_tabfind_vertical_text", "0"); // defulat: 1, Enable vertical detection
			ocr->SetVariable("textord_tabfind_vertical_horizontal_mix", "0"); // defulat: 1, find horizontal lines such as headers in vertical page mode

			m_OcrJpn = ocr;
		});

	initThread.detach();
}

void Scanner::InitOcrTw()
{
	std::thread initThread([=]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "chi_tra", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/); // 日文 "jpn"、繁體中文 "chi_tra"

			ocr->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);

			ocr->SetVariable("textord_tabfind_find_tables", "0"); // defulat: 1, run table detection
			ocr->SetVariable("textord_tabfind_vertical_text", "0"); // defulat: 1, Enable vertical detection
			ocr->SetVariable("textord_tabfind_vertical_horizontal_mix", "0"); // defulat: 1, find horizontal lines such as headers in vertical page mode

			m_OcrTw = ocr;
		});

	initThread.detach();
}

void Scanner::InitOcrEng()
{
	std::thread initThread([=]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "eng", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/);
			ocr->SetVariable("tessedit_char_whitelist", u8"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-!.");

			ocr->SetPageSegMode(/*tesseract::PSM_AUTO*/tesseract::PSM_SINGLE_LINE/*tesseract::PSM_SINGLE_BLOCK*/);

			ocr->SetVariable("textord_tabfind_find_tables", "0"); // defulat: 1, run table detection
			ocr->SetVariable("textord_tabfind_vertical_text", "0"); // defulat: 1, Enable vertical detection
			ocr->SetVariable("textord_tabfind_vertical_horizontal_mix", "0"); // defulat: 1, find horizontal lines such as headers in vertical page mode

			m_OcrEng = ocr;
		});

	initThread.detach();
}



#pragma region 私人函數
void Scanner::m_UpdateSapokaOrCharacterChoice(UmaEventData sapokaUmaEventData)
{
	WebViewManager::Instance->CleanChoiceTable();

	for (UmaChoice choice : sapokaUmaEventData.umaEvent.choice_list)
	{
		WebViewManager::Instance->CreateChoice(util::stdStr2system(choice.choice_name), util::stdStr2system(choice.choice_effect));
	}

	System::String^ sys_event_owner = util::stdStr2system(sapokaUmaEventData.Get<std::string>(UmaEventDataType::EVENT_OWNER));
	WebViewManager::Instance->ChangeEventOwner(sys_event_owner);

	System::String^ sys_event_title = util::stdStr2system(sapokaUmaEventData.Get<std::string>(UmaEventDataType::EVENT_TITLE));
	WebViewManager::Instance->ChangeEventName(sys_event_title);

	WebViewManager::Instance->HideSkillHintContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
	WebViewManager::Instance->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
}

void Scanner::m_UpdateScenarioChoice(ScenarioEventData scenarioEventData)
{
	WebViewManager::Instance->CleanChoiceTable();

	for (UmaChoice choice : scenarioEventData.choice_list)
	{
		WebViewManager::Instance->CreateChoice(util::stdStr2system(choice.choice_name), util::stdStr2system(choice.choice_effect));
	}

	System::String^ sys_event_title = util::stdStr2system(scenarioEventData.event_name);

	switch (Config::GetInstance()->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		WebViewManager::Instance->ChangeEventOwner(u8"メインシナリオイベント");
		break;
	case static_cast<int>(GameServerType::TW):
		WebViewManager::Instance->ChangeEventOwner(u8"主要劇情事件");
		break;
	}

	WebViewManager::Instance->ChangeEventName(sys_event_title);

	WebViewManager::Instance->HideSkillHintContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
	WebViewManager::Instance->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
}


std::string Scanner::m_GetScannedText(cv::Mat image, ImageType imgType, bool englishMode)
{
	std::unique_lock<std::mutex> lock(m_OcrMutex);

	UmaLog* umalog = UmaLog::GetInstance();

	int charCount = 0;
	char* utf8 = nullptr;

	switch (englishMode)
	{
	case true:
		// 設置圖片到 ocr
		m_OcrEng->SetImage(image.data, image.cols, image.rows, 1, image.step);

		// 進行文字辨識
		m_OcrEng->Recognize(0);

		utf8 = m_OcrEng->GetUTF8Text();
		break;
	case false:
		switch (Config::GetInstance()->GameServer)
		{
		case static_cast<int>(GameServerType::JP):
			switch (imgType)
			{
			case ImageType::IMG_EVENT_NAME:
				m_OcrJpn->SetVariable("tessedit_char_blacklist", u8"@$%^*_-+<>[]{}|\\`†;；=《》579"); // 有在事件名稱中出現的符號 0368:/#
				m_OcrJpn->SetVariable("tessedit_char_whitelist", u8"");
				m_OcrJpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
				break;
			case ImageType::IMG_HENSEI_CHARACTER_NAME:
				m_OcrJpn->SetVariable("tessedit_char_blacklist", u8"@#$%^*_+<>?()[]{}|\\`†.,;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
				m_OcrJpn->SetVariable("tessedit_char_whitelist", u8"");
				m_OcrJpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE/*PSM_SINGLE_BLOCK*/);
				break;
			case ImageType::IMG_DATE:
				m_OcrJpn->SetVariable("tessedit_char_blacklist", u8"");
				m_OcrJpn->SetVariable("tessedit_char_whitelist", u8"ジュニアクラシックシニア級0123456789０１２３４５６７８９月前後半");
				m_OcrJpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
				break;
			}

			// 設置圖片到 ocr
			m_OcrJpn->SetImage(image.data, image.cols, image.rows, 1, image.step);

			// 進行文字辨識
			m_OcrJpn->Recognize(0);

			utf8 = m_OcrJpn->GetUTF8Text();
			break;

		case static_cast<int>(GameServerType::TW):
			switch (imgType)
			{
			case ImageType::IMG_EVENT_NAME:
				m_OcrTw->SetVariable("tessedit_char_blacklist", u8"@$%^*_-+<>[]{}|\\`†;；=《》579"); // 有在事件名稱中出現的符號 0368:/#
				m_OcrTw->SetVariable("tessedit_char_whitelist", u8"");
				m_OcrTw->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
				break;
			case ImageType::IMG_HENSEI_CHARACTER_NAME:
				m_OcrTw->SetVariable("tessedit_char_blacklist", u8"@#$%^*_+<>?()[]{}|\\`†.,;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
				m_OcrTw->SetVariable("tessedit_char_whitelist", u8"");
				m_OcrTw->SetPageSegMode(tesseract::PSM_SINGLE_LINE/*PSM_SINGLE_BLOCK*/);
				break;
			case ImageType::IMG_DATE:
				m_OcrTw->SetVariable("tessedit_char_blacklist", u8"");
				m_OcrTw->SetVariable("tessedit_char_whitelist", u8"新手經典資深級0123456789０１２３４５６７８９月前後半");
				m_OcrTw->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
				break;
			}

			// 設置圖片到 ocr
			m_OcrTw->SetImage(image.data, image.cols, image.rows, 1, image.step);

			// 進行文字辨識
			m_OcrTw->Recognize(0);

			utf8 = m_OcrTw->GetUTF8Text();
			break;
		}
	}

	lock.unlock();


	std::string result = util::RemoveSpace(utf8);

#pragma region 釋放記憶體
	//ocr->End();
	delete[] utf8;
#pragma endregion

	// 替換某些特定的字串
	result = util::ReplaceSpecialString(result);

	if (util::IsRepeatingString(result, 4))
	{
		umalog->print(u8"[Scanner] 連續且重複的字符過多 result: ", result);
		return std::string();
	}

	if (util::HasBlackListedString(result))
	{
		umalog->print(u8"[Scanner] 檢查到含有黑名單字串 result: ", result);
		return std::string();
	}

	if (util::IsStringTooLong(result))
	{
		umalog->print(u8"[Scanner] 字串太長，超過 23 個 UTF8 Char 加起來的 Byte。 result: ", result);
		return std::string();
	}

	return result;
}




void Scanner::m_LookingForCurrentCharacter(Screenshot& ss, std::string& henseiCharNameText)
{
	DataManager* dataManager = DataManager::GetInstance();
	UmaLog* umalog = UmaLog::GetInstance();

#pragma region 尋找 Current Character

	if (!dataManager->IsCurrentCharacterInfoLocked())
	{
		try
		{
			std::string gray_another_name_text = this->m_GetScannedText(ss.hensei_character_another_name_gray, ImageType::IMG_HENSEI_CHARACTER_NAME);
			std::string gray_bin_another_name_text = this->m_GetScannedText(ss.hensei_character_another_name_gray_bin, ImageType::IMG_HENSEI_CHARACTER_NAME);
			std::string gray_bin_inv_another_name_text = this->m_GetScannedText(ss.hensei_character_another_name_gray_bin_inv, ImageType::IMG_HENSEI_CHARACTER_NAME);
			std::string eng_gray_bin_another_name_text = this->m_GetScannedText(ss.hensei_character_another_name_gray_bin, ImageType::IMG_HENSEI_CHARACTER_NAME, true);

			std::cout << "gray_another_name_text: " << gray_another_name_text << '\n';
			std::cout << "gray_bin_another_name_text: " << gray_bin_another_name_text << '\n';
			std::cout << "gray_bin_inv_another_name_text: " << gray_bin_inv_another_name_text << '\n';
			std::cout << "eng_gray_bin_another_name_text: " << eng_gray_bin_another_name_text << '\n';

			std::deque<std::string> scanned_text_list;
			scanned_text_list.push_back(gray_another_name_text);
			scanned_text_list.push_back(gray_bin_another_name_text);
			scanned_text_list.push_back(gray_bin_inv_another_name_text);
			scanned_text_list.push_back(eng_gray_bin_another_name_text);

			if (dataManager->TryGetCurrentCharacterByList(scanned_text_list))
			{
				std::cout << "[Scanner] 成功找到角色！\n";
			}
			else
			{
				std::cout << "[Scanner] 無法找到角色！\n";
			}
		}
		catch (const std::exception& e)
		{
			umalog->print("[std::exception] _LookingForCurrentCharacter:", e.what());
			this->Stop();
			umalog->print(u8"已終止 Scanner 運作");
		}
		catch (System::Exception^ ex)
		{
			umalog->print("[System::Exception] _LookingForCurrentCharacter: ", util::systemStr2std(ex->Message));
			this->Stop();
			umalog->print(u8"已終止 Scanner 運作");
		}
	}
	else
	{
		umalog->print("[Scanner] CURRENT CHARACTER LOCKED");
	}

#pragma endregion
}



void Scanner::m_Scan()
{
	DataManager* dataManager = DataManager::GetInstance();
	UmaLog* umalog = UmaLog::GetInstance();
	Config* config = Config::GetInstance();

	this->m_Scanning = true;
	while (global::umaswitch::Scanning)
	{
		std::unique_ptr<UmaTimer> timer = std::make_unique<UmaTimer>();
		timer->Start();

		Screenshot ss;

		if (!ss.IsDataComplete())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			continue;
		}

		
		umalog->print("[Scanner] ss._hasEventIcon:", ss.GetHasEventIcon() == true ? "true" : "false");
		umalog->print("[Scanner] ss._eventIconWhitePixelRatio:", ss.GetEventIconWhitePixelRatio());

		///
		/// 獲取圖片裡的文字
		/// 
		std::string gray_bin_event_text;
		std::string gray_event_text;
		std::string gray_bin_inv_event_text;
		std::string henseiCharNameText;

		// 如果是 EventTitle 才辨識 event_text
		if (ss.IsEventName())
		{
			gray_event_text = this->m_GetScannedText(ss.event_title_gray, ImageType::IMG_EVENT_NAME);
			gray_bin_event_text = this->m_GetScannedText(ss.event_title_gray_bin, ImageType::IMG_EVENT_NAME);
			gray_bin_inv_event_text = this->m_GetScannedText(ss.event_title_gray_bin_inv, ImageType::IMG_EVENT_NAME);

			// 檢查 eventText 是否都是空字串
			if (gray_event_text.empty() && gray_bin_event_text.empty() && gray_bin_inv_event_text.empty())
			{
				umalog->print(u8"[Scanner] 所有 eventText 都是空字串");
				this->m_PrintScanned(timer->Stop());
				std::this_thread::sleep_for(std::chrono::milliseconds(Config::GetInstance()->ScanInterval));
				continue;
			}
		}
		

		//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		//===================== 處理 date =======================
		//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		if (ss.IsDate())
		{
			std::string scanned_date = this->m_GetScannedText(ss.date_gray_bin, ImageType::IMG_DATE);
			umalog->print("[Scanner] scanned_date: ", scanned_date);
			umalog->print("[Scanner] TryFindScheduledRace: ", dataManager->TryFindScheduledRace(scanned_date) ? "true" : "false");

			// 更新 Discord RPC 狀態
			if (config->DiscordRPC)
			{
				dataManager->TryFindCurrentDate(scanned_date);
			}

			if (dataManager->TryFindScheduledRace(scanned_date) && !global::form::notificationForm->Visible)
			{
				umalog->print("[Scanner] 即將顯示 NotificationForm", scanned_date);
				FormController::Instance->ShowForm(global::form::notificationForm);
			}
		}


		// 尋找 CurrentCharacter
		this->m_LookingForCurrentCharacter(ss, henseiCharNameText);

#pragma region 尋找 character 或 sapoka 或 scenario 的事件
		if (m_PreviousEventText != gray_event_text &&
			m_PreviousEventText != gray_bin_event_text &&
			m_PreviousEventText != gray_bin_inv_event_text &&
			ss.IsEventName())
		{
			/*
			* 如果 m_PreviousEventText 都不一樣就重置 m_UpdatedChoice
			*/
			m_UpdatedChoice = false;


			umalog->print(u8"[Scanner] gray_event_text: ", gray_event_text);
			umalog->print(u8"[Scanner] gray_bin_event_text: ", gray_bin_event_text);
			umalog->print(u8"[Scanner] gray_bin_inv_event_text: ", gray_bin_inv_event_text);

			// 把所有辨識到的 event_text 都放入 list 中
			std::deque<std::string> scanned_text_list;
			scanned_text_list.push_back(gray_event_text);
			scanned_text_list.push_back(gray_bin_event_text);
			scanned_text_list.push_back(gray_bin_inv_event_text);

			// ---------------------------------------------------------------------------------------------------- //

			UmaEventNameData eventNameData = dataManager->GetMaxSimilarityUmaEventNameDataByList(scanned_text_list);

			if (eventNameData.event_type.empty())
			{
				umalog->print(u8"[Scanner] eventNameData.event_type.empty()");

				this->m_PrintScanned(timer->Stop());

				std::this_thread::sleep_for(std::chrono::milliseconds(Config::GetInstance()->ScanInterval));
				continue;
			}

			//std::cout << eventNameData.event_type << '\n';
			//std::cout << eventNameData.event_name << '\n';
			//std::cout << eventNameData.similarity << '\n';

			std::variant<UmaEventData, ScenarioEventData> variant = dataManager->GetEventDataByUmaEventNameData(eventNameData);

			if (std::holds_alternative<UmaEventData>(variant))
			{
				UmaEventData eventData = std::get<UmaEventData>(variant);

				if (eventData.IsDataComplete())
				{
					std::cout << "eventData.event_owner: " << eventData.event_owner << '\n';


					// 檢查是否與上次的 EventData 一致
					if (this->m_IsSameAsPreviousUpdatedEventData(eventNameData))
					{
						umalog->print(u8"[Scanner] 獲取到的 EventData 上次的 event_name 一致");

						this->m_PrintScanned(timer->Stop());

						std::this_thread::sleep_for(std::chrono::milliseconds(Config::GetInstance()->ScanInterval));
						continue;
					}


					this->m_UpdateSapokaOrCharacterChoice(eventData);
					m_PreviousEventText = eventNameData.matched_scanned_text;
					m_PreviousUpdatedUmaEventData = eventData;
					m_UpdatedChoice = true;
				}
			}
			else if (std::holds_alternative<ScenarioEventData>(variant))
			{
				ScenarioEventData eventData = std::get<ScenarioEventData>(variant);

				if (eventData.IsDataComplete())
				{
					// 檢查是否與上次的 EventData 一致
					if (this->m_IsSameAsPreviousUpdatedEventData(eventNameData))
					{
						umalog->print(u8"[Scanner] 獲取到的 EventData 上次的 event_name 一致");

						this->m_PrintScanned(timer->Stop());

						std::this_thread::sleep_for(std::chrono::milliseconds(Config::GetInstance()->ScanInterval));
						continue;
					}

					this->m_UpdateScenarioChoice(eventData);
					m_PreviousEventText = eventNameData.matched_scanned_text;
					m_PreviousUpdatedScenarioEventData = eventData;
					m_UpdatedChoice = true;
				}
			}
		}
		else
		{
			umalog->print(u8"[Scanner] eventText 偵測結果與上次一致");
		}
#pragma endregion


		// 預計會棄用
		// 如果有 tryCharThread 就等待它執行完畢
		//if (tryCharThread != nullptr && tryCharThread->joinable()) tryCharThread->join();

		//
		// 更新上次辨識到的文字
		//
		umalog->print(u8"[Scanner] _previousEventText: ", m_PreviousEventText);

		this->m_PrintScanned(timer->Stop());

		std::this_thread::sleep_for(std::chrono::milliseconds(Config::GetInstance()->ScanInterval));
	}
	this->m_Scanning = false;
}

#pragma endregion 私人函數




void Scanner::Start()
{
	if (global::umaswitch::Scanning)
	{
		std::cout << "[Scanner] 必須先停止掃描 Scanner::GetInstance()->Stop()" << std::endl;
		return;
	}

	global::umaswitch::Scanning = true;

	std::thread scanThread(&Scanner::m_Scan, this);

	scanThread.detach();


#pragma region 更新 UI
	UmaLog* umalog = UmaLog::GetInstance();
	switch (Config::GetInstance()->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		umalog->print("[Scanner] GameServer: JP");
		break;
	case static_cast<int>(GameServerType::TW):
		umalog->print("[Scanner] GameServer: TW");
		break;
	}

	switch (Config::GetInstance()->SoftwareLanguage)
	{
	case static_cast<int>(SoftwareLanguageType::JP):
		util::formctrl::Text(global::form::umaForm->scan_state_label, u8"起動状態：起動中");
		util::formctrl::Text(global::form::umaForm->scan_btn, u8"ストップ");
		break;
	case static_cast<int>(SoftwareLanguageType::TW):
		util::formctrl::Text(global::form::umaForm->scan_state_label, u8"運作狀態：運作中");
		util::formctrl::Text(global::form::umaForm->scan_btn, u8"停止");
		break;
	}
	util::formctrl::ForeColor(global::form::umaForm->scan_state_label, 0, 255, 0);
#pragma endregion
}

void Scanner::Stop()
{
	std::thread stopThread([=]()
		{
			bool stopped = false;

			do
			{
				if (m_Scanning)
				{
					global::umaswitch::Scanning = false;
					stopped = true;

#pragma region 更新 UI
					switch (Config::GetInstance()->SoftwareLanguage)
					{
					case static_cast<int>(SoftwareLanguageType::JP):						
						util::formctrl::Text(global::form::umaForm->scan_state_label, u8"起動状態：停止");
						util::formctrl::Text(global::form::umaForm->scan_btn, u8"スキャン");
						break;
					case static_cast<int>(SoftwareLanguageType::TW):
						util::formctrl::Text(global::form::umaForm->scan_state_label, u8"運作狀態：停止");
						util::formctrl::Text(global::form::umaForm->scan_btn, u8"啓動");
						break;
					}

					util::formctrl::ForeColor(global::form::umaForm->scan_state_label, 255, 0, 0);
#pragma endregion
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(300));
			} while (!stopped);
		});

	stopThread.detach();
}