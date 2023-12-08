#include "../stdafx.h"

cv::Mat Screenshot::oimg;
cv::Mat Screenshot::event_title_oimg;
cv::Mat Screenshot::event_title_resize;
cv::Mat Screenshot::event_title_gray;
cv::Mat Screenshot::event_title_gray_bin;
cv::Mat Screenshot::event_title_gray_bin_inv;

cv::Mat Screenshot::event_icon;

cv::Mat Screenshot::sentaku_character_name;

cv::Mat Screenshot::hensei_character_name_gray;
cv::Mat Screenshot::hensei_character_name_gray_bin;
cv::Mat Screenshot::hensei_character_name_gray_bin_inv;


cv::Mat Screenshot::syousai_character_name_gray_bin;


cv::Mat Screenshot::hwnd2mat(HWND hwnd = GetDesktopWindow())
{
	//HWND gameHWND = FindWindow(nullptr, L"umamusume");
	//if (gameHWND == NULL) { std::cout << u8"找不到遊戲視窗" << std::endl; return cv::Mat(); }
	HWND gameHWND = GameWindowFinder::GetInstance()->GetCurrentGameWindow();
	if (gameHWND == NULL) return cv::Mat();

	
	HDC hwindowDC, hwindowCompatibleDC;

	int height, width, srcheight, srcwidth, xsrc, ysrc;
	HBITMAP hbwindow;
	cv::Mat cvmat;
	BITMAPINFOHEADER bi;

	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	// 獲取遊戲視窗的 ClientRect 和 WindowRect
	RECT rcClient; GetClientRect(gameHWND, &rcClient);
	RECT rcWindow; GetWindowRect(gameHWND, &rcWindow);

#ifdef UMA_DEBUG
	Debug::WriteLine("[Client] left: {0}, right: {1}, top: {2}, bottom: {3}", rcClient.left, rcClient.right, rcClient.top, rcClient.bottom);
	Debug::WriteLine("[Window] left: {0}, right: {1}, top: {2}, bottom: {3}", rcWindow.left, rcWindow.right, rcWindow.top, rcWindow.bottom);
#endif

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
				crop_x = img_width - (img_width * 0.787);
				crop_y = img_height - (img_height * 0.813);
				crop_width = img_width - (img_width * 0.45);
				crop_height = img_height - (img_height * 0.97);
			}
			else
			{
				crop_x = img_width - (img_width * 0.86);
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



void Screenshot::ResizeImage(cv::Mat& img, float scale_factor = 2.0 /*放大倍數*/, cv::InterpolationFlags interpolationFlag = cv::INTER_LINEAR/*INTER_LINEAR*/)
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
	クリオグリ whitePixelRatio: 0.799745
	*/

	return this->GetWhitePixelRatio(img) > EVENT_ICON_METRIC;
}

Screenshot::Screenshot()
{
	oimg = this->hwnd2mat();
	if (oimg.empty()) return;


	// event_icon
	this->GetEventIconImage(); // 優先獲取 EventIconImage

	// event_title
	this->GetEventTitleImage();
	

	// character_name
	this->GetHenseiCharacterNameImage();
	//this->GetSyousaiCharacterName();
}



void Screenshot::ShowImage()
{
	if (oimg.empty()) return;

	cv::destroyAllWindows();

	// original
	//cv::imshow("oimg", oimg);

	// event_title
	cv::imshow("event_title_oimg", event_title_oimg);
	cv::imshow("event_title_resize", event_title_resize);
	cv::imshow("event_title_gray", event_title_gray);
	cv::imshow("event_title_gray_bin", event_title_gray_bin);
	cv::imshow("event_title_gray_bin_inv", event_title_gray_bin_inv);

	// event_icon
	cv::imshow("event_icon", event_icon);

	// character_name
	cv::imshow("hensei_character_name_oimg", hensei_character_name_gray_bin);
	cv::imshow("hensei_character_name_gray", hensei_character_name_gray);
	cv::imshow("hensei_character_name_gray_inv", hensei_character_name_gray_bin_inv);

	//cv::imshow("syousai_character_name_gray_bin", syousai_character_name_gray_bin);
	


	cv::waitKey(10);
}

void Screenshot::GetEventTitleImage()
{
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
	int thresh = 200/*210*/;
	event_title_gray_bin = oimg.clone();
	this->CropImage(event_title_gray_bin, ImageType::IMG_EVENT_TITLE, ImagePattern::EVENT_TITLE_GRAY_BIN);
	this->ResizeImage(event_title_gray_bin, 2);
	cv::cvtColor(event_title_gray_bin, event_title_gray_bin, cv::COLOR_BGR2GRAY);
	cv::threshold(event_title_gray_bin, event_title_gray_bin, thresh/*230*/, 255, cv::THRESH_BINARY);
	//std::cout << "test: " << this->GetWhitePixelRatio(event_title_gray_bin) << std::endl; // WhitePixelRatio: 0.215815

	//std::cout << "[WhitePixelRatio] event_title_gray_bin: " << this->GetWhitePixelRatio(event_title_gray_bin) << std::endl;

	// event_title_gray_bin_inv 裁切->放大+去鋸齒->灰值化->二值化//
	event_title_gray_bin_inv = oimg.clone();
	this->CropImage(event_title_gray_bin_inv, ImageType::IMG_EVENT_TITLE);
	this->ResizeImage(event_title_gray_bin_inv, 2);
	cv::cvtColor(event_title_gray_bin_inv, event_title_gray_bin_inv, cv::COLOR_BGR2GRAY);
	cv::threshold(event_title_gray_bin_inv, event_title_gray_bin_inv, thresh/*230*/, 255, cv::THRESH_BINARY_INV);
	//std::cout << "[BlackPixelRatio] event_title_gray_bin_inv: " << this->GetBlackPixelRatio(event_title_gray_bin_inv) << std::endl;


	
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
	this->ResizeImage(hensei_character_name_gray, 1.2);
	cv::cvtColor(hensei_character_name_gray, hensei_character_name_gray, cv::COLOR_BGR2GRAY);

	// hensei_character_name_gray_bin //
	hensei_character_name_gray_bin = oimg.clone();
	this->CropImage(hensei_character_name_gray_bin, ImageType::IMG_HENSEI_CHARACTER_NAME);
	this->ResizeImage(hensei_character_name_gray_bin, 1.2);
	cv::cvtColor(hensei_character_name_gray_bin, hensei_character_name_gray_bin, cv::COLOR_BGR2GRAY);
	cv::threshold(hensei_character_name_gray_bin, hensei_character_name_gray_bin, 120/*230*/, 255, cv::THRESH_BINARY);

	// hensei_character_name_bin_inv //
	hensei_character_name_gray_bin_inv = oimg.clone();
	this->CropImage(hensei_character_name_gray_bin_inv, ImageType::IMG_HENSEI_CHARACTER_NAME);
	this->ResizeImage(hensei_character_name_gray_bin_inv, 1.2);
	cv::cvtColor(hensei_character_name_gray_bin_inv, hensei_character_name_gray_bin_inv, cv::COLOR_BGR2GRAY);
	cv::threshold(hensei_character_name_gray_bin_inv, hensei_character_name_gray_bin_inv, 150/*230*/, 255, cv::THRESH_BINARY);
	hensei_character_name_gray_bin_inv = cv::Scalar::all(255) - hensei_character_name_gray_bin_inv; // 反轉顏色
	
}


//void Screenshot::GetCharacterNameImage()
//{
//	cv::Mat oimg = cv::imread((cv::String)global::path::c_screenshot);
//
//	// 灰度化
//	cv::cvtColor(oimg, oimg, cv::COLOR_BGR2GRAY);
//
//	// 二值化
//	cv::threshold(oimg, oimg, 230/*230*/, 255, cv::THRESH_BINARY);
//
//
//#pragma region 裁切圖片
//	int img_width = oimg.cols;
//	int img_height = oimg.rows;
//	int crop_x = img_width - (img_width * 0.96); // 起始 X 座標
//	int crop_y = img_height - (img_height * 0.693); // 起始 Y 座標
//	int crop_width = img_width - (img_width * 0.6); // 裁切寬度
//	int crop_height = img_height - (img_height * 0.96); // 裁切高度
//
//	// 使用 cv::Rect 定義裁切區域
//	cv::Rect rect(crop_x, crop_y, crop_width, crop_height);
//
//	// 進行圖片裁切
//	cv::Mat croppedImage = oimg(rect);
//#pragma endregion 裁切圖片
//
//	cv::imwrite((cv::String)global::path::c_screenshot_character_name, croppedImage);
//}
//
//
