#include "../stdafx.h"

#include <opencv2/opencv.hpp>


constexpr inline int FIX_GAME_WIDTH = 13;
constexpr inline int FIX_GAME_POS_Y = 30;

Screenshot::Screenshot()
{
	// 獲取桌面視窗句柄
	HWND desktopHWND = GetDesktopWindow();
	HDC hdcWindow = GetDC(desktopHWND);
	HDC hdcMemDC = CreateCompatibleDC(hdcWindow);

	// 獲取遊戲視窗句柄
	HWND gameHWND = FindWindow(nullptr, L"umamusume");
	if (gameHWND == NULL)
	{
		std::cout << u8"找不到遊戲視窗" << std::endl;
		return;
	}
	RECT rcClient; GetClientRect(gameHWND, &rcClient);
	RECT rcWindow; GetWindowRect(gameHWND, &rcWindow);
	int gameWidth = rcClient.right - rcClient.left - FIX_GAME_WIDTH;
	int gameHeight = rcClient.bottom - rcClient.top;
	int gamePosX = rcWindow.left + FIX_GAME_WIDTH;
	int gamePosY = rcWindow.top + FIX_GAME_POS_Y;

#ifdef UMA_DEBUG
	Debug::WriteLine("[Client] left: {0}, right: {1}, top: {2}, bottom: {3}", rcClient.left, rcClient.right, rcClient.top, rcClient.bottom);
	Debug::WriteLine("[Window] left: {0}, right: {1}, top: {2}, bottom: {3}", rcWindow.left, rcWindow.right, rcWindow.top, rcWindow.bottom);
#endif

#pragma region Window Screenshot
	HBITMAP hBitmap = CreateCompatibleBitmap(hdcWindow, gameWidth, gameHeight);

	SelectObject(hdcMemDC, hBitmap);

	BitBlt(hdcMemDC, 0, 0,
		gameWidth,
		gameHeight,
		hdcWindow,
		gamePosX,
		gamePosY/* + (gameWidth * 0.2)*/,
		SRCCOPY);

	this->bmp_window = Bitmap::FromHbitmap(static_cast<IntPtr>(hBitmap));
	this->bmp_window->Save(global::path::screenshot, System::Drawing::Imaging::ImageFormat::Png);
#pragma endregion



#pragma region Event
	cv::Mat oimg = cv::imread((cv::String)global::path::c_screenshot);

	//cv::Mat bin, gray;

	// 灰度化
	cv::cvtColor(oimg, oimg, cv::COLOR_BGR2GRAY);

	// 二值化
	cv::threshold(oimg, oimg, 254/*230*/, 255, cv::THRESH_BINARY);

	// 模糊化
	//cv::GaussianBlur(oimg, oimg, cv::Size(1.5, 1.5), 0);



#pragma region 裁切圖片
	int img_width = oimg.cols;
	int img_height = oimg.rows;
	int crop_x		= img_width  - (img_width  * 0.85); // 起始 X 座標
	int crop_y		= img_height - (img_height * 0.81); // 起始 Y 座標
	int crop_width  = img_width  - (img_width  * 0.30); // 裁切寬度
	int crop_height = img_height - (img_height * 0.97); // 裁切高度

	// 使用 cv::Rect 定義裁切區域
	cv::Rect rect(crop_x, crop_y, crop_width, crop_height);

	// 進行圖片裁切
	cv::Mat croppedImage = oimg(rect);
#pragma endregion 裁切圖片

	//// 找輪廓
	//std::vector<std::vector<cv::Point>> contours;
	//cv::findContours(gray, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	//// 劃出輪廓
	//cv::Mat result = oimg.clone();
	//cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0), 2);

	cv::imwrite((cv::String)global::path::c_screenshot_event, croppedImage);
#pragma endregion Event


#pragma region 釋放記憶體
	ReleaseDC(desktopHWND, hdcWindow);
	DeleteDC(hdcMemDC);
	DeleteObject(hBitmap);
#pragma endregion 釋放記憶體
}





/*
棄用的擷取畫面的方法


private: Bitmap^ CaptureWindow()
{
	HWND desktopHWND = GetDesktopWindow();
	HWND gameHWND = FindWindow(nullptr, L"umamusume");

	// 取得視窗大小
	RECT rc;
	GetClientRect(gameHWND, &rc);

	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	Debug::WriteLine(width);
	Debug::WriteLine(height);

	// 建立 Bitmap 和 Graphics
	Bitmap^ bmp = gcnew Bitmap(width, height);
	Graphics^ gfx = Graphics::FromImage(bmp);


	// 擷取視窗畫面
	IntPtr hdc = gfx->GetHdc();
	//PrintWindow(desktopHWND, static_cast<HDC>(hdc.ToPointer()), PW_CLIENTONLY);
	PaintDesktop(static_cast<HDC>(hdc.ToPointer()));

	gfx->ReleaseHdc(hdc);
	// 釋放 Graphics
	delete gfx;

	return bmp;
}
*/