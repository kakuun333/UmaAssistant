#include "../stdafx.h"
#include <tesseract/baseapi.h> // Tesseract OCR Version: 5.3.3


# pragma region 初始化靜態變數
Scanner* Scanner::_instance = nullptr;
bool Scanner::_scanning = false;
tesseract::TessBaseAPI* Scanner::ocr_jpn = nullptr;
tesseract::TessBaseAPI* Scanner::ocr_tw = nullptr;
tesseract::TessBaseAPI* Scanner::ocr_eng = nullptr;
#pragma endregion



void Scanner::InitOcrJpn()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "jpn", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/); // 日文 "jpn"、繁體中文 "chi_tra"

			ocr->SetPageSegMode(tesseract::PSM_SINGLE_LINE/*tesseract::PSM_SINGLE_BLOCK*/);

			ocr->SetVariable("textord_tabfind_find_tables", "0"); // 禁用 vertical script
			ocr->SetVariable("textord_orientation", "0"); // 禁用旋轉

			ocr_jpn = ocr;
		});

	initThread.detach();
}

void Scanner::InitOcrTw()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "chi_tra", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/); // 日文 "jpn"、繁體中文 "chi_tra"

			ocr->SetPageSegMode(tesseract::PSM_AUTO/*PSM_SINGLE_LINE*//*tesseract::PSM_SINGLE_BLOCK*/);

			ocr->SetVariable("textord_tabfind_find_tables", "0"); // 禁用 vertical script
			ocr->SetVariable("textord_orientation", "0"); // 禁用旋轉

			ocr_tw = ocr;
		});

	initThread.detach();
}

void Scanner::InitOcrEng()
{
	std::thread initThread([]()
		{
			tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); // 初始化 Tesseract

			ocr->Init(global::path::std_tessdata_best.c_str(), "eng", tesseract::OEM_LSTM_ONLY/*OEM_DEFAULT*/);
			ocr->SetVariable("tessedit_char_whitelist", u8"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-!.");

			ocr->SetPageSegMode(/*tesseract::PSM_AUTO*/tesseract::PSM_SINGLE_LINE/*tesseract::PSM_SINGLE_BLOCK*/);

			ocr->SetVariable("textord_tabfind_find_tables", "0"); // 禁用 vertical script
			ocr->SetVariable("textord_orientation", "0"); // 禁用旋轉

			ocr_eng = ocr;
		});

	initThread.detach();
}



#pragma region 私人函數
void Scanner::_UpdateSapokaChoice(WebManager* webManager, UmaEventData sapokaUmaEventData)
{
	webManager->CleanChoiceTable();

	for (UmaChoice choice : sapokaUmaEventData.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
	{
		webManager->CreateChoice(utility::stdStr2system(choice.choice_title), utility::stdStr2system(choice.choice_effect));
	}

	System::String^ sys_event_owner = utility::stdStr2system(sapokaUmaEventData.Get<std::string>(UmaEventDataType::EVENT_OWNER));
	webManager->ChangeEventOwner(sys_event_owner);

	System::String^ sys_event_title = utility::stdStr2system(sapokaUmaEventData.Get<std::string>(UmaEventDataType::EVENT_TITLE));
	webManager->ChangeEventTitle(sys_event_title);

	webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
	webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
}

void Scanner::_UpdateCharChoice(WebManager* webManager, UmaEventData charUmaEventData)
{
	// 這裡更新 UI
	webManager->CleanChoiceTable();

	for (UmaChoice choice : charUmaEventData.Get<std::vector<UmaChoice>>(UmaEventDataType::CHOICE_LIST))
	{
		webManager->CreateChoice(utility::stdStr2system(choice.choice_title), utility::stdStr2system(choice.choice_effect));
	}

	System::String^ sys_event_owner = utility::stdStr2system(charUmaEventData.Get<std::string>(UmaEventDataType::EVENT_OWNER));
	webManager->ChangeEventOwner(sys_event_owner);

	System::String^ sys_event_title = utility::stdStr2system(charUmaEventData.Get<std::string>(UmaEventDataType::EVENT_TITLE));
	webManager->ChangeEventTitle(sys_event_title);

	webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
	webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
}

void Scanner::_UpdateScenarioChoice(WebManager* webManager, ScenarioEventData scenarioEventData)
{
	webManager->CleanChoiceTable();

	for (ScenarioChoice choice : scenarioEventData.event_list)
	{
		webManager->CreateChoice(utility::stdStr2system(choice.choice_title), utility::stdStr2system(choice.choice_effect));
	}

	System::String^ sys_event_title = utility::stdStr2system(scenarioEventData.event_title);

	switch (global::config->GameServer)
	{
	case static_cast<int>(GameServerType::JP):
		webManager->ChangeEventOwner(u8"メインシナリオイベント");
		break;
	case static_cast<int>(GameServerType::TW):
		webManager->ChangeEventOwner(u8"主要劇情事件");
		break;
	}

	webManager->ChangeEventTitle(sys_event_title);

	webManager->HiddenSkillContent(); // 隱藏 skill_hint_content 避免更新 ChoiceTable 時 skill_hint_content 無法再隱藏
	webManager->UpdateSkillContent(); // 重新尋找 skill_hint 再監聽
}


std::string Scanner::_GetScannedText(cv::Mat image, ImageType imgType, bool englishMode)
{
	std::unique_lock<std::mutex> lock(ocrMutex);

	UmaLog* umalog = UmaLog::GetInstance();

	int charCount = 0;
	char* utf8 = nullptr;

	switch (englishMode)
	{
	case true:
		// 設置圖片到 ocr
		ocr_eng->SetImage(image.data, image.cols, image.rows, 1, image.step);

		// 進行文字辨識
		ocr_eng->Recognize(0);

		utf8 = ocr_eng->GetUTF8Text();
		break;
	case false:
		switch (global::config->GameServer)
		{
		case static_cast<int>(GameServerType::JP):
			switch (imgType)
			{
			case ImageType::IMG_EVENT_TITLE:
				ocr_jpn->SetVariable("tessedit_char_blacklist", u8"@$%^*_-+<>[]{}|/\\`†;；=《》579"); // 有在事件名稱中出現的符號 0368:/#
				ocr_jpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
				break;
			case ImageType::IMG_HENSEI_CHARACTER_NAME:
				ocr_jpn->SetVariable("tessedit_char_blacklist", u8"@#$%^*_+<>?()[]{}|\\`†.,;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
				ocr_jpn->SetPageSegMode(tesseract::PSM_SINGLE_LINE/*PSM_SINGLE_BLOCK*/);
				break;
			}

			// 設置圖片到 ocr
			ocr_jpn->SetImage(image.data, image.cols, image.rows, 1, image.step);

			// 進行文字辨識
			ocr_jpn->Recognize(0);

			utf8 = ocr_jpn->GetUTF8Text();
			break;

		case static_cast<int>(GameServerType::TW):
			switch (imgType)
			{
			case ImageType::IMG_EVENT_TITLE:
				ocr_tw->SetVariable("tessedit_char_blacklist", u8"@$%^*_-+<>[]{}|/\\`†;；=《》579"); // 有在事件名稱中出現的符號 0368:/#
				ocr_tw->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
				break;
			case ImageType::IMG_HENSEI_CHARACTER_NAME:
				ocr_tw->SetVariable("tessedit_char_blacklist", u8"@#$%^*_+<>?()[]{}|\\`†.,;；=「」【】『』〈〉［］〔〕≪≫（）〔〕");
				ocr_tw->SetPageSegMode(tesseract::PSM_SINGLE_LINE/*PSM_SINGLE_BLOCK*/);
				break;
			}

			// 設置圖片到 ocr
			ocr_tw->SetImage(image.data, image.cols, image.rows, 1, image.step);

			// 進行文字辨識
			ocr_tw->Recognize(0);

			utf8 = ocr_tw->GetUTF8Text();
			break;
		}
	}

	lock.unlock();


	std::string result = utility::RemoveSpace(utf8);

#pragma region 釋放記憶體
	//ocr->End();
	delete[] utf8;
#pragma endregion

	// 替換某些特定的字串
	result = utility::ReplaceSpecialString(result);

	if (utility::IsRepeatingString(result, 4))
	{
		umalog->print(u8"[Scanner] 連續且重複的字符過多 result: ", result);
		return std::string();
	}

	if (utility::HasBlackListedString(result))
	{
		umalog->print(u8"[Scanner] 檢查到含有黑名單字串 result: ", result);
		return std::string();
	}

	if (utility::IsStringTooLong(result))
	{
		umalog->print(u8"[Scanner] 字串太長，超過 23 個 UTF8 Char 加起來的 Byte。 result: ", result);
		return std::string();
	}

	return result;
}




void Scanner::_LookingForCurrentCharacter(Screenshot& ss, std::string& henseiCharNameText)
{
	DataManager* dataManager = DataManager::GetInstance();
	UmaLog* umalog = UmaLog::GetInstance();

#pragma region 尋找 Current Character

	if (!dataManager->IsCurrentCharacterInfoLocked())
	{
		try
		{
			std::string gray_another_name_text = this->_GetScannedText(ss.hensei_character_another_name_gray, ImageType::IMG_HENSEI_CHARACTER_NAME);
			std::string gray_bin_another_name_text = this->_GetScannedText(ss.hensei_character_another_name_gray_bin, ImageType::IMG_HENSEI_CHARACTER_NAME);
			std::string gray_bin_inv_another_name_text = this->_GetScannedText(ss.hensei_character_another_name_gray_bin_inv, ImageType::IMG_HENSEI_CHARACTER_NAME);
			std::string eng_gray_bin_another_name_text = this->_GetScannedText(ss.hensei_character_another_name_gray_bin, ImageType::IMG_HENSEI_CHARACTER_NAME, true);

			std::cout << "gray_another_name_text: " << gray_another_name_text << std::endl;
			std::cout << "gray_bin_another_name_text: " << gray_bin_another_name_text << std::endl;
			std::cout << "gray_bin_inv_another_name_text: " << gray_bin_inv_another_name_text << std::endl;
			std::cout << "eng_gray_bin_another_name_text: " << eng_gray_bin_another_name_text << std::endl;

			std::deque<std::string> scanned_text_list;
			scanned_text_list.push_back(gray_another_name_text);
			scanned_text_list.push_back(gray_bin_another_name_text);
			scanned_text_list.push_back(gray_bin_inv_another_name_text);
			scanned_text_list.push_back(eng_gray_bin_another_name_text);

			if (dataManager->TryGetCurrentCharacterByList(scanned_text_list))
			{
				std::cout << u8"[Scanner] 成功找到角色！" << std::endl;
			}
			else
			{
				std::cout << u8"[Scanner] 無法找到角色！" << std::endl;
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
			umalog->print("[System::Exception] _LookingForCurrentCharacter: ", utility::systemStr2std(ex->Message));
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

bool Scanner::_IsEventTextEmpty(Screenshot& ss, std::string& eventText)
{
	DataManager* dataManager = DataManager::GetInstance();

	bool result = false;

	/*
	* 如果 eventText 是空字串就再用其他圖片比較
	* 如果還是空字串才算是真的空字串
	*/
	if (eventText.empty() && dataManager->IsCurrentCharacterInfoLocked() && ss.IsEventTitle())
	{
		std::string gray_event_text, thread_two_text;

		gray_event_text = this->_GetScannedText(ss.event_title_gray);
		if (eventText.empty() && !gray_event_text.empty())
		{
			eventText = gray_event_text;
		}

		thread_two_text = this->_GetScannedText(ss.event_title_gray_bin_high_thresh);
		if (eventText.empty() && !thread_two_text.empty())
		{
			eventText = thread_two_text;
		}

		if (gray_event_text.empty() && thread_two_text.empty())
		{
			std::cout << u8"[Scanner] 都是空字串" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(global::config->ScanInterval));
			result = true;
		}
	}

	return result;
}



void Scanner::_Scan()
{
	DataManager* dataManager = DataManager::GetInstance();
	WebManager* webManager = WebManager::GetInstance();
	UmaLog* umalog = UmaLog::GetInstance();

	this->_scanning = true;
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
		/*std::string characterNameText;*/
		std::string gray_bin_event_text;
		std::string henseiCharNameText;

		//eventText = this->_GetScannedText(ss.event_title_oimg);
		//std::cout << "event_title_oimg: " << eventText << std::endl;

		//eventText = this->_GetScannedText(ss.event_title_resize);
		//std::cout << "event_title_resize: " << eventText << std::endl;

		//eventText = this->_GetScannedText(ss.event_title_gray);
		//std::cout << "event_title_gray: " << eventText << std::endl;

		//eventText = this->_GetScannedText(ss.event_title_gray_bin_inv);
		//std::cout << "event_title_gray_bin_inv: " << eventText << std::endl;


		//eventText = this->_GetScannedText(ss.event_title_gray_bin);
		//henseiCharNameText = this->_GetScannedText(ss.hensei_character_name_gray, language, ImageType::IMG_HENSEI_CHARACTER_NAME);



		UmaEventData charUmaEventData;
		UmaEventData sapokaUmaEventData;
		ScenarioEventData scenarioEventData;

		if (ss.IsEventTitle())
		{
			gray_bin_event_text = this->_GetScannedText(ss.event_title_gray_bin);
		}


		//if (!dataManager->IsCurrentCharacterInfoLocked())
		//{
		//	henseiCharNameText = this->_GetScannedText(ss.hensei_character_name_gray, ImageType::IMG_HENSEI_CHARACTER_NAME);

		//	umalog->print(u8"[Scanner] hensei_character_name_gray: ", henseiCharNameText);
		//}


		// 檢查 eventText 是否為真的空字串
		if (this->_IsEventTextEmpty(ss, gray_bin_event_text))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(global::config->ScanInterval));
			continue;
		}


		umalog->print(u8"[Scanner] event_title_gray_bin: ", gray_bin_event_text);

		// 尋找 CurrentCharacter
		this->_LookingForCurrentCharacter(ss, henseiCharNameText);


#pragma region 尋找 character 或 sapoka 或 scenario 的事件
		if (_previousEventText != gray_bin_event_text && ss.IsEventTitle())
		{
			/*
			* 如果 _previousEventText 不一樣就重置 _updatedChoice
			*/
			_updatedChoice = false;

			/*
			* 有時候名字很像的事件名稱會先偵測到 scenarioEventData ，但是正確的事件在 sapokaUmaEventData
			* 為了避免先偵測到 scenarioEventData ，應該要先比較 similarity 再判斷要更新的事件是
			* scenarioEventData 還是 sapokaUmaEventData
			*/

			// 辨識其餘的 event_text
			std::string gray_event_text = this->_GetScannedText(ss.event_title_gray);
			std::string gray_bin_inv_event_text = this->_GetScannedText(ss.event_title_gray_bin_inv);

			umalog->print(u8"[Scanner] gray_event_text: ", gray_event_text);
			umalog->print(u8"[Scanner] gray_bin_inv_event_text: ", gray_bin_inv_event_text);

			// 把所有辨識到的 event_text 都放入 list 中
			std::deque<std::string> scanned_text_list;
			scanned_text_list.push_back(gray_bin_event_text);
			scanned_text_list.push_back(gray_event_text);
			scanned_text_list.push_back(gray_bin_inv_event_text);

			// ---------------------------------------------------------------------------------------------------- //

			// ========== 尋找 charUmaEventData ========== //
			if (dataManager->IsCurrentCharacterInfoLocked())
			{
				charUmaEventData = dataManager->GetCurrentCharacterUmaEventDataByList(scanned_text_list);

				if (charUmaEventData.IsDataComplete()) { _previousEventText = charUmaEventData.matched_scanned_text; }
			}

			// ========== 尋找 sapokaUmaEventData ========== //
			sapokaUmaEventData = dataManager->GetSapokaUmaEventDataByList(scanned_text_list);
			if (sapokaUmaEventData.IsDataComplete()) { _previousEventText = sapokaUmaEventData.matched_scanned_text; }

			// ========== 尋找 scenarioEventData ========== //
			scenarioEventData = dataManager->GetScenarioEventDataByList(scanned_text_list);
			if (scenarioEventData.IsDataComplete()) { _previousEventText = scenarioEventData.matched_scanned_text; }

			// ---------------------------------------------------------------------------------------------------- //

			umalog->print(u8"[Scanner] charUmaEventData.similarity: ", charUmaEventData.similarity);
			umalog->print(u8"[Scanner] sapokaUmaEventData.similarity: ", sapokaUmaEventData.similarity);
			umalog->print(u8"[Scanner] scenarioEventData.similarity: ", scenarioEventData.similarity);

			if (charUmaEventData.similarity > sapokaUmaEventData.similarity)
			{
				if (charUmaEventData.IsDataComplete())
				{
					// 檢查是否與上次的 UmaEventData 一致
					if (this->_IsSameAsPreviousUpdatedEventData(charUmaEventData))
					{
						umalog->print(u8"[Scanner] 獲取到的 charUmaEventData 和 _previousUpdatedUmaEventData 的 event_title 一致");

						this->_PrintScanned(timer->Stop());

						std::this_thread::sleep_for(std::chrono::milliseconds(global::config->ScanInterval));
						continue;
					}

					try
					{
						this->_UpdateCharChoice(webManager, charUmaEventData);

						umalog->print(u8"[Scanner] 成功更新 CharChoice");

						_previousEventText = gray_bin_event_text;
						_updatedChoice = true;
						_previousUpdatedUmaEventData = charUmaEventData;
					}
					catch (const std::exception& e)
					{
						umalog->print("[std::exception] _UpdateCharChoice:", e.what());
						umalog->print(u8"已終止 Scanner 運作");
						return;
					}
					catch (System::Exception^ ex)
					{
						umalog->print("[System::Exception] _UpdateCharChoice: ", utility::systemStr2std(ex->Message));
						umalog->print(u8"已終止 Scanner 運作");
						return;
					}
				}
			}
			else if (sapokaUmaEventData.similarity > scenarioEventData.similarity)
			{
				if (sapokaUmaEventData.IsDataComplete())
				{
					// 檢查是否與上次的 UmaEventData 一致
					if (this->_IsSameAsPreviousUpdatedEventData(sapokaUmaEventData))
					{
						umalog->print(u8"[Scanner] 獲取到的 sapokaUmaEventData 和 _previousUpdatedUmaEventData 的 event_title 一致");

						this->_PrintScanned(timer->Stop());

						std::this_thread::sleep_for(std::chrono::milliseconds(global::config->ScanInterval));
						continue;
					}

					try
					{
						this->_UpdateSapokaChoice(webManager, sapokaUmaEventData);
						_updatedChoice = true;
						_previousUpdatedUmaEventData = sapokaUmaEventData;
						umalog->print(u8"[Scanner] 成功更新 SapokaChoice");
						umalog->print(u8"[Scanner] _updatedChoice = ", _updatedChoice == true ? "true" : "false");
					}
					catch (const std::exception& e)
					{
						umalog->print("[std::exception] _UpdateSapokaChoice:", e.what());
						umalog->print(u8"已終止 Scanner 運作");
						return;
					}
					catch (System::Exception^ ex)
					{
						umalog->print("[System::Exception] _UpdateSapokaChoice: ", utility::systemStr2std(ex->Message));
						umalog->print(u8"已終止 Scanner 運作");
						return;
					}
				}
			}
			else if (sapokaUmaEventData.similarity < scenarioEventData.similarity)
			{
				if (scenarioEventData.IsDataComplete())
				{
					// 檢查是否與上次的 ScenarioEventData 一致
					if (this->_IsSameAsPreviousUpdatedEventData(scenarioEventData))
					{
						umalog->print(u8"[Scanner] 獲取到的 scenarioEventData 和 _previousUpdatedScenarioEventData 的 event_title 一致");

						this->_PrintScanned(timer->Stop());

						std::this_thread::sleep_for(std::chrono::milliseconds(global::config->ScanInterval));
						continue;
					}

					try
					{
						this->_UpdateScenarioChoice(webManager, scenarioEventData);
						_updatedChoice = true;
						_previousUpdatedScenarioEventData = scenarioEventData;
						umalog->print(u8"[Scanner] 成功更新 ScenarioChoice");
						umalog->print(u8"[Scanner] _updatedChoice = ", _updatedChoice == true ? "true" : "false");
					}
					catch (const std::exception& e)
					{
						umalog->print("[std::exception] _UpdateScenarioChoice:", e.what());
						umalog->print(u8"已終止 Scanner 運作");
						return;
					}
					catch (System::Exception^ ex)
					{
						umalog->print("[System::Exception] _UpdateScenarioChoice: ", utility::systemStr2std(ex->Message));
						umalog->print(u8"已終止 Scanner 運作");
						return;
					}
				}
			}
		}
		else if (_previousEventText == gray_bin_event_text && !_updatedChoice && ss.IsEventTitle())
		{
			charUmaEventData = dataManager->GetCurrentCharacterUmaEventData(gray_bin_event_text);
			sapokaUmaEventData = dataManager->GetSapokaUmaEventData(gray_bin_event_text);
			scenarioEventData = dataManager->GetScenarioEventData(gray_bin_event_text);

			std::map<UmaDataType,float> similarityDict =
			{
				{ UmaDataType::CHARACTER, charUmaEventData.similarity },
				{ UmaDataType::SAPOKA, sapokaUmaEventData.similarity },
				{ UmaDataType::SCENARIO, scenarioEventData.similarity },
			};

			auto maxElement = std::max_element(similarityDict.begin(), similarityDict.end(),
				[](const auto& lhs, const auto& rhs)
				{
					return lhs.second < rhs.second;
				});

			switch (maxElement->first)
			{
			case UmaDataType::CHARACTER:
				if (charUmaEventData.IsDataComplete())
				{
					this->_UpdateCharChoice(webManager, charUmaEventData);
					umalog->print(u8"[Scanner] else if 成功更新 CharChoice");
					_updatedChoice = true;
				}
				break;

			case UmaDataType::SAPOKA:
				if (sapokaUmaEventData.IsDataComplete())
				{
					this->_UpdateSapokaChoice(webManager, sapokaUmaEventData);
					umalog->print(u8"[Scanner] else if 成功更新 SapokaChoice");
					_updatedChoice = true;
				}
				break;

			case UmaDataType::SCENARIO:
				if (scenarioEventData.IsDataComplete())
				{
					this->_UpdateScenarioChoice(webManager, scenarioEventData);
					umalog->print(u8"[Scanner] else if 成功更新 ScenarioChoice");
					_updatedChoice = true;
				}
				break;
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
		umalog->print(u8"[Scanner] _previousEventText: ", _previousEventText);

		this->_PrintScanned(timer->Stop());

		std::this_thread::sleep_for(std::chrono::milliseconds(global::config->ScanInterval));
	}
	this->_scanning = false;
}

#pragma endregion 私人函數




void Scanner::Start()
{
	if (global::umaswitch::Scanning)
	{
		std::cout << u8"[Scanner] 必須先停止掃描 Scanner::GetInstance()->Stop()" << std::endl;
		return;
	}

	global::umaswitch::Scanning = true;

	std::thread scanThread(&Scanner::_Scan, this);

	scanThread.detach();
}

void Scanner::Stop()
{
	std::thread stopThread([=]()
		{
			bool stopped = false;

			do
			{
				if (_scanning)
				{
					global::umaswitch::Scanning = false;
					stopped = true;
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(300));
			} while (!stopped);
		});

	stopThread.detach();
}