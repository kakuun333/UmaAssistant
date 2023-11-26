#pragma once

#include "../enum/ImageType.h"
#include <opencv2/opencv.hpp>
#include <map>

using namespace System;
using namespace System::Drawing;


constexpr inline int FIX_GAME_WIDTH = 13;
constexpr inline int FIX_GAME_POS_Y = 30;
constexpr inline double EVENT_ICON_METRIC = 0.67;


//enum ImagePattern
//{
//	O_IMG,
//	EVENT_TITLE_OIMG,
//	EVENT_TITLE_GRAY,
//	EVENT_TITLE_GRAY_BIN,
//	EVENT_ICON,
//};

class Screenshot
{
private:
	cv::Mat hwnd2mat(HWND hwnd);
	

	void CropImage(cv::Mat& img, ImageType imgType);

	void ResizeImage(cv::Mat& img, float scale_factor);

	bool IsEventIcon(cv::Mat img);

	void GetEventTextImage();

	void GetEventIconImage();

public:
	Screenshot();

	static void ShowImage();

	//static std::map<std::string, cv::Mat> img_dict
	static cv::Mat oimg;
	static cv::Mat event_title_oimg;
	static cv::Mat event_title_resize;
	static cv::Mat event_title_gray;
	static cv::Mat event_title_gray_bin;
	static cv::Mat event_title_gray_bin_inv;

	static cv::Mat event_icon;
};