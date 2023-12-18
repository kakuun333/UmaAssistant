#include "../stdafx.h"

#pragma region 靜態變數
// event_title
cv::Mat Screenshot::oimg;
cv::Mat Screenshot::event_title_oimg;
cv::Mat Screenshot::event_title_resize;
cv::Mat Screenshot::event_title_gray;
cv::Mat Screenshot::event_title_gray_bin;
cv::Mat Screenshot::event_title_gray_bin_inv;

// event_icon
cv::Mat Screenshot::event_icon;

// sentaku_character_name
cv::Mat Screenshot::sentaku_character_name;

// hensei_character_name
cv::Mat Screenshot::hensei_character_name_gray;
cv::Mat Screenshot::hensei_character_name_gray_bin;
cv::Mat Screenshot::hensei_character_name_gray_bin_inv;
cv::Mat Screenshot::hensei_character_another_name_gray;

// syousai_character_name
cv::Mat Screenshot::syousai_character_name_gray_bin;
#pragma endregion




bool Screenshot::IsWindowCovered(HWND gameHWND)
{
	RECT gameWindowRect;
	if (GetWindowRect(gameHWND, &gameWindowRect))
	{
		// 檢查視窗是否可見
		if (IsWindowVisible(gameHWND))
		{
			// 檢查視窗是否被其他視窗覆蓋
			HWND hwndBehind = GetWindow(gameHWND, GW_HWNDPREV);
			RECT behindRect;
			while (hwndBehind != NULL)
			{
				if (IsWindowVisible(hwndBehind))
				{
					// 更新 behindRect
					GetWindowRect(hwndBehind, &behindRect);

					// 如果 gameWindowRect 和 behindRect 交會
					if (IntersectRect(&behindRect, &gameWindowRect, &behindRect))
					{
						// 視窗被其他視窗覆蓋
						return true;
					}
				}
				// 更新 hwndBehind
				hwndBehind = GetWindow(hwndBehind, GW_HWNDPREV);
			}
		}
	}

	// 視窗未被覆蓋
	return false;
}

cv::Mat Screenshot::hwnd2mat(HWND hwnd = GetDesktopWindow())
{
	UmaLog* umalog = UmaLog::GetInstance();

	//HWND gameHWND = FindWindow(nullptr, L"umamusume");
	//if (gameHWND == NULL) { std::cout << u8"找不到遊戲視窗" << std::endl; return cv::Mat(); }
	HWND gameHWND = GameWindowFinder::GetInstance()->GetCurrentGameWindow();
	if (gameHWND == NULL) return cv::Mat();

	//if (this->IsWindowCovered(gameHWND))
	//{
	//	std::cout << u8"視窗被覆蓋" << std::endl;
	//	return cv::Mat();
	//}

	// 獲取遊戲視窗的 ClientRect 和 WindowRect
	RECT rcWindow; GetWindowRect(gameHWND, &rcWindow);
	RECT rcClient; GetClientRect(gameHWND, &rcClient);

	//printf("[Client] left: %d, right: %d, top: %d, bottom: %d\n", rcClient.left, rcClient.right, rcClient.top, rcClient.bottom);
	//printf("[Window] left: %d, right: %d, top: %d, bottom: %d\n", rcWindow.left, rcWindow.right, rcWindow.top, rcWindow.bottom);

	if (rcClient.left != 0 || rcClient.top != 0)
	{
		//printf(u8"遊戲視窗的 reClient 發生異常！有可能視窗正在被關閉。rcClient.left: %d, rcClient.top: %d", rcClient.left, rcClient.top);
		umalog->print(u8"遊戲視窗的 reClient 發生異常！有可能視窗正在被關閉。reClient.left: ", rcClient.left, "rcClient.top: ", rcClient.top);
		return cv::Mat();
	}

	if (rcClient.left <= 0 && rcClient.right <= 0 && rcClient.top <= 0 && rcClient.bottom <= 0)
	{
		umalog->print(u8"視窗被最小化");
		return cv::Mat();
	}

	if (rcClient.right - rcClient.left > rcClient.bottom - rcClient.top)
	{
		umalog->print(u8"視窗處於橫向狀態");
		return cv::Mat();
	}


	int height, width, srcheight, srcwidth, xsrc, ysrc;



	HDC hwindowDC, hwindowCompatibleDC;
	HBITMAP hbwindow;
	cv::Mat cvmat;
	BITMAPINFOHEADER bi;

	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);


	int gameWidth, gameHeight, gamePosX, gamePosY = 0;



	switch (global::config->GameWindow)
	{
	case static_cast<int>(GameWindowType::DMM):
		gameWidth = rcClient.right - rcClient.left - DMM_FIX_GAME_WIDTH;
		gameHeight = rcClient.bottom - rcClient.top;
		gamePosX = rcWindow.left + DMM_FIX_GAME_WIDTH;
		gamePosY = rcWindow.top + DMM_FIX_GAME_POS_Y;
		break;

	case static_cast<int>(GameWindowType::BLUE_STACKS):
		gameWidth = rcClient.right - rcClient.left - BLUE_STACKS_FIX_GAME_WIDTH;
		gameHeight = rcClient.bottom - rcClient.top - BLUE_STACKS_FIX_GAME_HEIGHT;
		gamePosX = rcWindow.left + BLUE_STACKS_FIX_GAME_POS_X;
		gamePosY = rcWindow.top + BLUE_STACKS_FIX_GAME_POS_Y;
		break;
	}



	// 依照遊戲視窗修改 bmp 的大小和位置
	srcwidth = gameWidth;
	srcheight = gameHeight;
	width = gameWidth;
	height = gameHeight;
	xsrc = gamePosX;
	ysrc = gamePosY;

	// 創建 bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth = width;
	bi.biHeight = -height;  // 這行決定了 bmp 是否顛倒
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	// 創建 cv::Mat
	cvmat.create(height, width, CV_8UC4);

	// 使用先前創建的 device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// 複製 window device context 到 bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, xsrc, ysrc, srcwidth, srcheight, SRCCOPY);
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, cvmat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow


	// 釋放記憶體
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);


	return cvmat;
}

void Screenshot::CropImage(cv::Mat& img, ImageType imgType, ImagePattern imgPattern = ImagePattern::IMG_PATTERN_NONE)
{
	// 獲取圖片大小
	float img_width = img.cols;
	float img_height = img.rows;


	int crop_x		 = 0; // 起始 X 座標
	int crop_y		 = 0; // 起始 Y 座標
	int crop_width	 = 0; // 裁切寬度
	int crop_height	 = 0; // 裁切高度


	switch (global::config->GameWindow)
	{
	case static_cast<int>(GameWindowType::DMM):
		switch (imgType)
		{
		case IMG_EVENT_TITLE:
			if (IsEventIcon(event_icon))
			{
				crop_x = img_width - (img_width * 0.78);
				crop_y = img_height - (img_height * 0.81);
				crop_width = img_width - (img_width * 0.45);
				crop_height = img_height - (img_height * 0.97);
			}
			else
			{
				crop_x = img_width - (img_width * 0.85);
				crop_y = img_height - (img_height * 0.81);
				crop_width = img_width - (img_width * 0.4);
				crop_height = img_height - (img_height * 0.97);
			}
			break;
		case IMG_EVENT_ICON:
			crop_x = img_width - (img_width * 0.841);
			crop_y = img_height - (img_height * 0.81);
			crop_width = img_width - (img_width * 0.946);
			crop_height = img_height - (img_height * 0.97);
			break;
		case IMG_SENTAKU_CHARACTER_NAME:
			crop_x = img_width - (img_width * 0.96);
			crop_y = img_height - (img_height * 0.693);
			crop_width = img_width - (img_width * 0.6);
			crop_height = img_height - (img_height * 0.96);
			break;
		case IMG_HENSEI_CHARACTER_NAME:
			crop_x = img_width - (img_width * 0.75);
			crop_y = img_height - (img_height * 0.845);
			crop_width = img_width - (img_width * 0.55);
			crop_height = img_height - (img_height * 0.948);
			break;
		case IMG_HENSEI_CHARACTER_ANOTHER_NAME:
			crop_x = img_width - (img_width * 0.76);
			crop_y = img_height - (img_height * 0.845);
			crop_width = img_width - (img_width * 0.6);
			crop_height = img_height - (img_height * 0.975);
			break;
		case IMG_SYOUSAI_CHARACTER_NAME:
			crop_x = img_width - (img_width * 0.75);
			crop_y = img_height - (img_height * 0.845);
			crop_width = img_width - (img_width * 0.55);
			crop_height = img_height - (img_height * 0.948);
			break;
		}
		break;

	case static_cast<int>(GameWindowType::BLUE_STACKS):
		switch (imgType)
		{
		case IMG_EVENT_TITLE:
			if (IsEventIcon(event_icon))
			{
				crop_x = img_width - (img_width * 0.785);
				crop_y = img_height - (img_height * 0.813);
				crop_width = img_width - (img_width * 0.45);
				crop_height = img_height - (img_height * 0.97);
			}
			else
			{
				crop_x = img_width - (img_width * 0.855);
				crop_y = img_height - (img_height * 0.813);
				crop_width = img_width - (img_width * 0.4);
				crop_height = img_height - (img_height * 0.97);
			}
			break;
		case IMG_EVENT_ICON:
			crop_x = img_width - (img_width * 0.85);
			crop_y = img_height - (img_height * 0.8139);
			crop_width = img_width - (img_width * 0.946);
			crop_height = img_height - (img_height * 0.97);
			break;
		case IMG_SENTAKU_CHARACTER_NAME:
			crop_x = img_width - (img_width * 0.96);
			crop_y = img_height - (img_height * 0.693);
			crop_width = img_width - (img_width * 0.6);
			crop_height = img_height - (img_height * 0.96);
			break;
		case IMG_HENSEI_CHARACTER_NAME:
			crop_x = img_width - (img_width * 0.76);
			crop_y = img_height - (img_height * 0.85);
			crop_width = img_width - (img_width * 0.6);
			crop_height = img_height - (img_height * 0.948);
			break;
		case IMG_HENSEI_CHARACTER_ANOTHER_NAME:
			crop_x = img_width - (img_width * 0.76);
			crop_y = img_height - (img_height * 0.85);
			crop_width = img_width - (img_width * 0.6);
			crop_height = img_height - (img_height * 0.975);
			break;
		case IMG_SYOUSAI_CHARACTER_NAME:
			crop_x = img_width - (img_width * 0.75);
			crop_y = img_height - (img_height * 0.845);
			crop_width = img_width - (img_width * 0.55);
			crop_height = img_height - (img_height * 0.948);
			break;
		}
		break;
	}




	// 使用 cv::Rect 定義裁切區域
	cv::Rect rect(crop_x, crop_y, crop_width, crop_height);

	// 進行圖片裁切
	cv::Mat croppedImg = img(rect);


	img = croppedImg;
}

void Screenshot::SetEventTitleBound(cv::Mat& img)
{
	/*
	假設一個字佔 0.015 whitePixelRatio

	[GetEventTitleBound] 0.0494271
	[Scanner] event_title_gray_bin: ー敬にて

	[GetEventTitleBound] textBound: 0.825316
	[GetEventTitleBound] whitePixelRatio: 0.123797
	[Scanner] event_title_gray_bin: タ暮れにひと勝負


	[GetEventTitleBound] whitePixelRatio: 0.161974
	*/
	const double WHITE_PIXEL_RATIO = this->GetWhitePixelRatio(img);

	// 一個字大概佔的 whitePixelRatio
	double single_char_white_pixel_ratio;


	// 一個字大概佔的圖片大小
	double single_char_img_width_ratio;

	// 獲取圖片大小
	float img_width = img.cols;
	float img_height = img.rows;

	int crop_x = 0; // 起始 X 座標
	int crop_y = 0; // 起始 Y 座標
	int crop_width = 0; // 裁切寬度

	int textCount;
	double textBound;
	cv::Rect rect;

	switch (global::config->GameWindow)
	{
	case static_cast<int>(GameWindowType::DMM):
		single_char_white_pixel_ratio = 0.015;
		single_char_img_width_ratio = 0.06;

		textCount = WHITE_PIXEL_RATIO / single_char_white_pixel_ratio;
		textBound = single_char_img_width_ratio * textCount;

		if (textBound > 1) return; // 無視 whitePixelRatio 太大的情況，以防 cv::Exception

		if (IsEventIcon(event_icon))
		{
			crop_width = img_width - (img_width * (textBound - single_char_img_width_ratio));
		}
		else
		{
			crop_width = img_width - (img_width * textBound);
		}

		// 使用 cv::Rect 定義裁切區域
		rect = cv::Rect(crop_x, crop_y, crop_width, img_height);

		// 進行圖片裁切
		img = img(rect);

		// 裁切其他圖片
		event_title_resize = event_title_resize(rect);
		event_title_gray = event_title_gray(rect);
		event_title_gray_bin_inv = event_title_gray_bin_inv(rect);
		break;
	case static_cast<int>(GameWindowType::BLUE_STACKS):
		single_char_white_pixel_ratio = 0.016;
		single_char_img_width_ratio = 0.06;

		textCount = WHITE_PIXEL_RATIO / single_char_white_pixel_ratio;
		textBound = single_char_img_width_ratio * textCount;

		if (textBound > 1) return; // 無視 whitePixelRatio 太大的情況，以防 cv::Exception

		if (IsEventIcon(event_icon))
		{
			crop_width = img_width - (img_width * (textBound - single_char_img_width_ratio));
		}
		else
		{
			crop_width = img_width - (img_width * textBound);
		}

		// 使用 cv::Rect 定義裁切區域
		rect = cv::Rect(crop_x, crop_y, crop_width, img_height);

		// 進行圖片裁切
		img = img(rect);

		// 裁切其他圖片
		event_title_resize = event_title_resize(rect);
		event_title_gray = event_title_gray(rect);
		event_title_gray_bin_inv = event_title_gray_bin_inv(rect);
		break;
	}






	std::cout << "[GetEventTitleBound] textCount: " << textCount << std::endl;
	std::cout << "[GetEventTitleBound] textBound: " << textBound << std::endl;
	std::cout << "[GetEventTitleBound] whitePixelRatio: " << WHITE_PIXEL_RATIO << std::endl;
}

void Screenshot::ResizeImage(cv::Mat& img, float scale_factor = 2.0 /*放大倍數*/, cv::InterpolationFlags interpolationFlag)
{
	// 計算放大後的寬和高
	int new_width = static_cast<int>(img.cols * scale_factor);
	int new_height = static_cast<int>(img.rows * scale_factor);
	// 進行縮放
	cv::resize(img, img, cv::Size(new_width, new_height), interpolationFlag);
}

const double Screenshot::GetWhitePixelRatio(cv::Mat img)
{


	const int whitePixelCount = cv::countNonZero(img);
	const int imgPixelCount = img.cols * img.rows;
	const double whitePixelRatio = static_cast<double>(whitePixelCount) / static_cast<double>(imgPixelCount);

	//std::cout << "whitePixelRatio: " << whitePixelRatio << std::endl;

	return whitePixelRatio;
}

const double Screenshot::GetBlackPixelRatio(cv::Mat img)
{
	/*
	縁がいすれ行きつくは
	[WhitePixelRatio] event_title_gray_bin: 0.134094
	[BlackPixelRatio] event_title_gray_bin_inv: 0.134094



	*/ 


	const double whitePixelRatio = this->GetWhitePixelRatio(img);
	const double blackPixelRatio = 1.0f - whitePixelRatio;

	return blackPixelRatio;
}

bool Screenshot::IsEventIcon(cv::Mat img)
{
	/*
	* クリオグリ whitePixelRatio: 0.799745
	* 真機伶黑色婚紗 thresh: 160, whitePixelRatio: 0.572825
	*/
	return this->GetWhitePixelRatio(img) > EVENT_ICON_METRIC;
}

Screenshot::Screenshot()
{
	oimg = this->hwnd2mat();
	if (oimg.empty()) return;

	UmaLog* umalog = UmaLog::GetInstance();

	// event_icon
	try
	{
		this->GetEventIconImage(); // 優先獲取 EventIconImage
	}
	catch (const std::exception& e)
	{
		umalog->print("[std::exception] GetEventIconImage:", e.what());
	}
	catch (System::Exception^ ex)
	{
		umalog->print("[System::Exception] GetEventIconImage: ", utility::systemStr2std(ex->Message));
	}
	

	// event_title
	try
	{
		this->GetEventTitleImage();
	}
	catch (const std::exception& e)
	{
		umalog->print("[std::exception] GetEventTitleImage:", e.what());
	}
	catch (System::Exception^ ex)
	{
		umalog->print("[System::Exception] GetEventTitleImage: ", utility::systemStr2std(ex->Message));
	}

	
	
	
	

	// character_name
	try
	{
		this->GetHenseiCharacterNameImage();
	}
	catch (const std::exception& e)
	{
		umalog->print("[std::exception] GetHenseiCharacterNameImage:", e.what());
	}
	catch (System::Exception^ ex)
	{
		umalog->print("[System::Exception] GetHenseiCharacterNameImage: ", utility::systemStr2std(ex->Message));
	}
	



	//this->GetSyousaiCharacterName();
}



void Screenshot::ShowImage()
{
	if (oimg.empty()) return;

	cv::destroyAllWindows();

	//// original ////
	//cv::imshow("oimg", oimg);

	//// event_title ////
	//cv::imshow("event_title_oimg", event_title_oimg);
	//cv::imshow("event_title_resize", event_title_resize);
	cv::imshow("event_title_gray", event_title_gray);
	cv::imshow("event_title_gray_bin", event_title_gray_bin);
	cv::imshow("event_title_gray_bin_inv", event_title_gray_bin_inv);

	//// event_icon ////
	cv::imshow("event_icon", event_icon);

	//// character_name ////
	//cv::imshow("hensei_character_name_oimg", hensei_character_name_gray_bin);
	cv::imshow("hensei_character_name_gray", hensei_character_name_gray);
	cv::imshow("hensei_character_name_gray_inv", hensei_character_name_gray_bin_inv);

	cv::imshow("hensei_character_another_name_gray", hensei_character_another_name_gray);

	//cv::imshow("syousai_character_name_gray_bin", syousai_character_name_gray_bin);
	


	cv::waitKey(10);
}

void Screenshot::GetEventTitleImage()
{
	UmaLog* umalog = UmaLog::GetInstance();

	// event_title_oimg //
	event_title_oimg = oimg.clone();
	this->CropImage(event_title_oimg, ImageType::IMG_EVENT_TITLE);
	//std::cout << "event_title_oimg whiteRatio: " << this->GetWhitePixelRatio(event_title_oimg) << std::endl;

	// event_title_resize //
	event_title_resize = oimg.clone();
	this->CropImage(event_title_resize, ImageType::IMG_EVENT_TITLE);	
	this->ResizeImage(event_title_resize, 2);
	//std::cout << "event_title_resize whiteRatio: " << this->GetWhitePixelRatio(event_title_resize) << std::endl;

	// event_title_gray //
	event_title_gray = oimg.clone();
	this->CropImage(event_title_gray, ImageType::IMG_EVENT_TITLE);
	this->ResizeImage(event_title_gray, 2);
	cv::cvtColor(event_title_gray, event_title_gray, cv::COLOR_BGR2GRAY);

	// event_title_gray_bin 裁切->放大+去鋸齒->灰值化->二值化//
	int thresh = 208/*210*/;
	event_title_gray_bin = oimg.clone();
	this->CropImage(event_title_gray_bin, ImageType::IMG_EVENT_TITLE, ImagePattern::EVENT_TITLE_GRAY_BIN);
	this->ResizeImage(event_title_gray_bin, 2);
	cv::cvtColor(event_title_gray_bin, event_title_gray_bin, cv::COLOR_BGR2GRAY);
	cv::threshold(event_title_gray_bin, event_title_gray_bin, thresh/*230*/, 255, cv::THRESH_BINARY);

	double event_title_gray_bin_WPR = GetWhitePixelRatio(event_title_gray_bin);
	std::cout << "[Screenshot] event_title_gray_bin_WPR: " << event_title_gray_bin_WPR << std::endl;
	if (event_title_gray_bin_WPR > IS_EVENT_TITLE_METRIC || event_title_gray_bin_WPR == 0)
	{
		/*
		* WPR: 0.12677
		* [Scanner] event_title_gray_bin:  ボナペティポカブフランス料理
		* 
		* WPR: 0.276314
		* [Screenshot] 可能不是事件
		* [Scanner] event_title_gray_bin:  交感走力の限界突破に関する買的研
		*/
		umalog->print(u8"[Screenshot] 可能不是事件");
		_isEventTitle = false;
	}

	

	// event_title_gray_bin_inv 裁切->放大+去鋸齒->灰值化->二值化-//
	event_title_gray_bin_inv = oimg.clone();
	this->CropImage(event_title_gray_bin_inv, ImageType::IMG_EVENT_TITLE);
	this->ResizeImage(event_title_gray_bin_inv, 1.5);
	cv::cvtColor(event_title_gray_bin_inv, event_title_gray_bin_inv, cv::COLOR_BGR2GRAY);
	cv::threshold(event_title_gray_bin_inv, event_title_gray_bin_inv, thresh/*230*/, 255, cv::THRESH_BINARY_INV);


	//this->SetEventTitleBound(event_title_gray_bin);
}

void Screenshot::GetEventIconImage()
{
	event_icon = oimg.clone();

	cv::cvtColor(event_icon, event_icon, cv::COLOR_BGR2GRAY);
	this->CropImage(event_icon, ImageType::IMG_EVENT_ICON);
	cv::threshold(event_icon, event_icon, 160/*230*/, 255, cv::THRESH_BINARY);
}


void Screenshot::GetSyousaiCharacterName()
{
	syousai_character_name_gray_bin = oimg.clone();
	this->CropImage(syousai_character_name_gray_bin, ImageType::IMG_SYOUSAI_CHARACTER_NAME);
	this->ResizeImage(syousai_character_name_gray_bin, 1.2);
	cv::cvtColor(syousai_character_name_gray_bin, syousai_character_name_gray_bin, cv::COLOR_BGR2GRAY);
	cv::threshold(syousai_character_name_gray_bin, syousai_character_name_gray_bin, 200, 255, cv::THRESH_BINARY_INV);
}

void Screenshot::GetHenseiCharacterNameImage()
{
	// hensei_character_name_bin //
	hensei_character_name_gray = oimg.clone();
	this->CropImage(hensei_character_name_gray, ImageType::IMG_HENSEI_CHARACTER_NAME);
	this->ResizeImage(hensei_character_name_gray, 1.0);
	cv::cvtColor(hensei_character_name_gray, hensei_character_name_gray, cv::COLOR_BGR2GRAY);

	// hensei_character_name_gray_bin //
	hensei_character_name_gray_bin = oimg.clone();
	this->CropImage(hensei_character_name_gray_bin, ImageType::IMG_HENSEI_CHARACTER_NAME);
	this->ResizeImage(hensei_character_name_gray_bin, 1.0);
	cv::cvtColor(hensei_character_name_gray_bin, hensei_character_name_gray_bin, cv::COLOR_BGR2GRAY);
	cv::threshold(hensei_character_name_gray_bin, hensei_character_name_gray_bin, 170/*120*/, 255, cv::THRESH_BINARY);

	// hensei_character_name_bin_inv //
	hensei_character_name_gray_bin_inv = oimg.clone();
	this->CropImage(hensei_character_name_gray_bin_inv, ImageType::IMG_HENSEI_CHARACTER_NAME);
	this->ResizeImage(hensei_character_name_gray_bin_inv, 1.0);
	cv::cvtColor(hensei_character_name_gray_bin_inv, hensei_character_name_gray_bin_inv, cv::COLOR_BGR2GRAY);
	cv::threshold(hensei_character_name_gray_bin_inv, hensei_character_name_gray_bin_inv, 175/*130*/, 255, cv::THRESH_BINARY);
	hensei_character_name_gray_bin_inv = cv::Scalar::all(255) - hensei_character_name_gray_bin_inv; // 反轉顏色
	
	hensei_character_another_name_gray = oimg.clone();
	this->CropImage(hensei_character_another_name_gray, ImageType::IMG_HENSEI_CHARACTER_ANOTHER_NAME);
	this->ResizeImage(hensei_character_another_name_gray, 1.0);
	cv::cvtColor(hensei_character_another_name_gray, hensei_character_another_name_gray, cv::COLOR_BGR2GRAY);
	cv::threshold(hensei_character_another_name_gray, hensei_character_another_name_gray, 175/*130*/, 255, cv::THRESH_BINARY);
}

void Screenshot::ResetCharacterImage(cv::Mat& img, ImagePattern imgPattern, float scale_factor, int thresh_factor)
{
	switch (imgPattern)
	{
	case ImagePattern::HENSEI_CHAR_GRAY:
		img = oimg.clone();
		this->CropImage(img, ImageType::IMG_HENSEI_CHARACTER_NAME);
		this->ResizeImage(img, scale_factor);
		cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
		break;

	case ImagePattern::HENSEI_CHAR_GRAY_BIN:
		img = oimg.clone();
		this->CropImage(img, ImageType::IMG_HENSEI_CHARACTER_NAME);
		this->ResizeImage(img, scale_factor);
		cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
		cv::threshold(img, img, /*thresh_factor*/170/*120*/, 255, cv::THRESH_BINARY);
		break;

	case ImagePattern::HENSEI_CHAR_GRAY_BIN_INV:
		img = oimg.clone();
		this->CropImage(img, ImageType::IMG_HENSEI_CHARACTER_NAME);
		this->ResizeImage(img, scale_factor);
		cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
		cv::threshold(img, img, /*thresh_factor*/175/*130*/, 255, cv::THRESH_BINARY);
		img = cv::Scalar::all(255) - img; // 反轉顏色
		break;

	case ImagePattern::HENSEI_CHAR_ANOTHER_NAME_GRAY:
		img = oimg.clone();
		this->CropImage(img, ImageType::IMG_HENSEI_CHARACTER_ANOTHER_NAME);
		this->ResizeImage(img, scale_factor);
		cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
		break;
	}



}