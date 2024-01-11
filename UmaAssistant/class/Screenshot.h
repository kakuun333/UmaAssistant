#pragma once

// C++ std
#include <map>

// opencv
#include <opencv2/opencv.hpp>

// enum
#include "../enum/ImageType.h"

using namespace System;
using namespace System::Drawing;


constexpr inline int DMM_FIX_GAME_WIDTH = 13;
constexpr inline int DMM_FIX_GAME_POS_Y = 30;

constexpr inline int EMULATOR_FIX_GAME_WIDTH = 44;
constexpr inline int EMULATOR_FIX_GAME_HEIGHT = 37;
constexpr inline int EMULATOR_FIX_GAME_POS_X = 10;
constexpr inline int EMULATOR_FIX_GAME_POS_Y = 36;

constexpr inline double EVENT_ICON_METRIC = 0.535/*0.55*//*0.73*/;

constexpr inline double IS_EVENT_TITLE_METRIC = 0.3;

enum ImagePattern
{
	IMG_PATTERN_NONE,

	O_IMG,

	EVENT_ICON,

	EVENT_TITLE_OIMG,
	EVENT_TITLE_GRAY,
	EVENT_TITLE_GRAY_BIN,
	EVENT_TITLE_GRAY_BIN_INV,

	HENSEI_CHAR_GRAY,
	HENSEI_CHAR_GRAY_BIN,
	HENSEI_CHAR_GRAY_BIN_INV,
	HENSEI_CHAR_ANOTHER_NAME_GRAY,
};

class Screenshot
{
private:
	cv::Mat hwnd2mat(HWND hwnd);

	bool _isEventTitle = true;

	bool _hasEventIcon = false;
	double _eventIconWhitePixelRatio = -1;

	void CropImage(cv::Mat& img, ImageType imgType, ImagePattern imgPattern);

	void ResizeImage(cv::Mat& img, float scale_factor /*放大倍數*/, cv::InterpolationFlags interpolationFlag = cv::INTER_LINEAR/*INTER_LINEAR*/);

	const double GetWhitePixelRatio(cv::Mat img);

	const double GetBlackPixelRatio(cv::Mat img);

	// 檢查是否有 EventIcon，並設置 _hasEventIcon 和 _eventIconWhitePixelRatio
	void _CheckEventIcon(cv::Mat img);

	void GetEventTitleImage();

	void GetEventIconImage();

	void GetHenseiCharacterNameImage();

	void GetHenseiCharacterAnotherNameImage();

	void GetSyousaiCharacterName();

	bool IsWindowCovered(HWND hwnd);

	void SetEventTitleBound(cv::Mat& img);

public:
	Screenshot();

	static void ShowImage();

	inline bool IsDataComplete()
	{
		if (oimg.empty()) return false;

		return true;
	}

	inline bool IsEventTitle()
	{
		return _isEventTitle;
	}

	inline void SetHasEventIcon(bool value)
	{
		_hasEventIcon = value;
	}

	inline bool GetHasEventIcon()
	{
		return _hasEventIcon;
	}

	inline void SetEventIconWhitePixelRatio(double value)
	{
		_eventIconWhitePixelRatio = value;
	}

	inline double GetEventIconWhitePixelRatio()
	{
		return _eventIconWhitePixelRatio;
	}

	void ResetCharacterImage(cv::Mat& img, ImagePattern imgPattern, float scale_factor, int thresh_factor = NULL);

	//static std::map<std::string, cv::Mat> img_dict

	static cv::Mat oimg;

	// event_title
	static cv::Mat event_title_oimg;
	static cv::Mat event_title_resize;
	static cv::Mat event_title_gray;
	static cv::Mat event_title_gray_bin;
	static cv::Mat event_title_gray_bin_inv;
	static cv::Mat event_title_gray_bin_high_thresh;

	// event_icon
	static cv::Mat event_icon;

	// character_name
	static cv::Mat hensei_character_name_gray;
	static cv::Mat hensei_character_name_gray_bin;
	static cv::Mat hensei_character_name_gray_bin_inv;

	// another_name
	static cv::Mat hensei_character_another_name_gray;
	static cv::Mat hensei_character_another_name_gray_bin;
	static cv::Mat hensei_character_another_name_gray_bin_inv;

	// sentaku_character_name
	static cv::Mat sentaku_character_name;

	// syousai_character_name
	static cv::Mat syousai_character_name_gray_bin;
};