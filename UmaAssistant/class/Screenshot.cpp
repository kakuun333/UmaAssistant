#include "../stdafx.h"

//std::map<std::string, cv::Mat> img_dict =
//{
//	{ "oimg", cv::Mat() },
//	{ "event_title_oimg", cv::Mat() },
//	{ "event_title_gray", cv::Mat() },
//	{ "event_title_gray_bin", cv::Mat() },
//	{ "event_icon", cv::Mat() },
//};

cv::Mat Screenshot::oimg;
cv::Mat Screenshot::event_title_oimg;
cv::Mat Screenshot::event_title_resize;
cv::Mat Screenshot::event_title_gray;
cv::Mat Screenshot::event_title_gray_bin;
cv::Mat Screenshot::event_title_gray_bin_inv;

cv::Mat Screenshot::event_icon;

cv::Mat Screenshot::hwnd2mat(HWND hwnd = GetDesktopWindow())
{
	HWND gameHWND = FindWindow(nullptr, L"umamusume");
	if (gameHWND == NULL) { std::cout << u8"找不到遊戲視窗" << std::endl; return cv::Mat(); }

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

	int gameWidth = rcClient.right - rcClient.left - FIX_GAME_WIDTH;
	int gameHeight = rcClient.bottom - rcClient.top;
	int gamePosX = rcWindow.left + FIX_GAME_WIDTH;
	int gamePosY = rcWindow.top + FIX_GAME_POS_Y;


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
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
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

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, xsrc, ysrc, srcwidth, srcheight, SRCCOPY);
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, cvmat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

	// avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);


	return cvmat;
}


void Screenshot::CropImage(cv::Mat& img, ImageType imgType)
{
	// 獲取圖片大小
	int img_width = img.cols;
	int img_height = img.rows;


	int crop_x		 = 0; // 起始 X 座標
	int crop_y		 = 0; // 起始 Y 座標
	int crop_width	 = 0; // 裁切寬度
	int crop_height	 = 0; // 裁切高度


	switch (imgType)
	{
	case IMG_EVENT_TITLE:
		if (IsEventIcon(event_icon))
		{
			crop_x		 = img_width  - (img_width  * 0.78);
			crop_y		 = img_height - (img_height * 0.81);
			crop_width	 = img_width  - (img_width  * 0.45);
			crop_height  = img_height - (img_height * 0.97);
		}
		else
		{
			crop_x		 = img_width  - (img_width  * 0.85);
			crop_y		 = img_height - (img_height * 0.81);
			crop_width	 = img_width  - (img_width  * 0.30);
			crop_height	 = img_height - (img_height * 0.97);
		}
		break;
	case IMG_EVENT_ICON:
		crop_x		 = img_width  - (img_width  * 0.85);
		crop_y		 = img_height - (img_height * 0.81);
		crop_width	 = img_width  - (img_width  * 0.935);
		crop_height	 = img_height - (img_height * 0.97);
		break;
	case IMG_SENTAKU_CHARACTER_NAME:
		crop_x		 = img_width  - (img_width  * 0.96);
		crop_y		 = img_height - (img_height * 0.693);
		crop_width	 = img_width  - (img_width  * 0.6);
		crop_height  = img_height - (img_height * 0.96);
		break;
	case IMG_HENSEI_CHARACTER_NAME:
		crop_x		 = img_width  - (img_width  * 0.75);
		crop_y		 = img_height - (img_height * 0.845);
		crop_width	 = img_width  - (img_width  * 0.55);
		crop_height	 = img_height - (img_height * 0.938);
		break;
	}

	// 使用 cv::Rect 定義裁切區域
	cv::Rect rect(crop_x, crop_y, crop_width, crop_height);

	// 進行圖片裁切
	cv::Mat croppedImage = img(rect);

	img = croppedImage;
}



void Screenshot::ResizeImage(cv::Mat& img, float scale_factor = 2.0 /*放大倍數*/)
{
	// 計算放大後的寬和高
	int new_width = static_cast<int>(img.cols * scale_factor);
	int new_height = static_cast<int>(img.rows * scale_factor);

	// 進行縮放
	cv::resize(img, img, cv::Size(new_width, new_height));
}

bool Screenshot::IsEventIcon(cv::Mat img)
{
	const int whitePixelCount = cv::countNonZero(event_icon);
	const int imgPixelCount = img.cols * img.rows;
	const double whitePixelRatio = static_cast<double>(whitePixelCount) / imgPixelCount; 

	/*
	クリオグリ whitePixelRatio: 0.87605
	*/


	//std::cout << "whitePixelRatio: " << whitePixelRatio << std::endl;

	return whitePixelRatio > EVENT_ICON_METRIC;
}

Screenshot::Screenshot()
{
	oimg = this->hwnd2mat();

	this->GetEventIconImage(); // 優先獲取 EventIconImage

	

	this->GetEventTextImage();

}



void Screenshot::ShowImage()
{
	if (oimg.empty()) return;

	cv::destroyAllWindows();

	// original
	cv::imshow("oimg", oimg);

	// event_title
	cv::imshow("event_title_oimg", event_title_oimg);
	cv::imshow("event_title_resize", event_title_resize);
	cv::imshow("event_title_gray", event_title_gray);
	cv::imshow("event_title_gray_bin", event_title_gray_bin);
	cv::imshow("event_title_gray_bin_inv", event_title_gray_bin_inv);

	// event_icon
	cv::imshow("event_icon", event_icon);

	cv::waitKey(10);
}

void Screenshot::GetEventTextImage()
{
	// event_title_oimg //
	event_title_oimg = oimg.clone();
	this->CropImage(event_title_oimg, ImageType::IMG_EVENT_TITLE);

	// event_title_resize //
	event_title_resize = oimg.clone();
	this->CropImage(event_title_resize, ImageType::IMG_EVENT_TITLE);
	this->ResizeImage(event_title_resize, 2);

	// event_title_gray //
	event_title_gray = oimg.clone();
	// 灰度化
	cv::cvtColor(event_title_gray, event_title_gray, cv::COLOR_BGR2GRAY);
	this->CropImage(event_title_gray, ImageType::IMG_EVENT_TITLE);
	this->ResizeImage(event_title_gray, 2);

	int thresh = 210;
	// event_title_gray_bin //
	event_title_gray_bin = oimg.clone();
	// 二值化
	cv::cvtColor(event_title_gray_bin, event_title_gray_bin, cv::COLOR_BGR2GRAY);
	cv::threshold(event_title_gray_bin, event_title_gray_bin, thresh/*230*/, 255, cv::THRESH_BINARY);
	this->CropImage(event_title_gray_bin, ImageType::IMG_EVENT_TITLE);
	this->ResizeImage(event_title_gray_bin, 2);

	// event_title_gray_bin_inv //
	event_title_gray_bin_inv = oimg.clone();
	// 二值化
	cv::cvtColor(event_title_gray_bin_inv, event_title_gray_bin_inv, cv::COLOR_BGR2GRAY);
	cv::threshold(event_title_gray_bin_inv, event_title_gray_bin_inv, thresh/*230*/, 255, cv::THRESH_BINARY_INV);
	this->CropImage(event_title_gray_bin_inv, ImageType::IMG_EVENT_TITLE);
	this->ResizeImage(event_title_gray_bin_inv, 2);
}

void Screenshot::GetEventIconImage()
{
	event_icon = oimg.clone();

	cv::threshold(event_icon, event_icon, 160/*230*/, 255, cv::THRESH_BINARY);

	cv::cvtColor(event_icon, event_icon, cv::COLOR_BGR2GRAY);

	this->CropImage(event_icon, ImageType::IMG_EVENT_ICON);
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
//void Screenshot::GetHenSeiCharacterNameImage()
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
//	int crop_x = img_width - (img_width * 0.75); // 起始 X 座標
//	int crop_y = img_height - (img_height * 0.845); // 起始 Y 座標
//	int crop_width = img_width - (img_width * 0.55); // 裁切寬度
//	int crop_height = img_height - (img_height * 0.938); // 裁切高度
//
//	// 使用 cv::Rect 定義裁切區域
//	cv::Rect rect(crop_x, crop_y, crop_width, crop_height);
//
//	// 進行圖片裁切
//	cv::Mat croppedImage = oimg(rect);
//#pragma endregion 裁切圖片
//
//	cv::imwrite((cv::String)global::path::c_screenshot_hensei_character_name, croppedImage);
//}
