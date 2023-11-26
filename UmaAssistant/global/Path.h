#pragma once

#include <vcclr.h>

namespace global
{
	namespace path
	{
		/*		System::String^		*/
		extern gcroot<System::String^> currentDir;

		// WebBrowser
		extern gcroot<System::String^> choiceWebBrowser;
		extern gcroot<System::String^> characterNameWebBrowser;
		
		extern gcroot<System::String^> umaTemp; // ¼È¦sÀÉ¦ì¸m
		extern gcroot<System::String^> screenshot;
		extern gcroot<System::String^> screenshot_event;

		/*		const char*		*/
		extern const char* c_currentDir; // char ªº CurrentDirectory

		extern const char* c_UmaTemp;
		extern const char* c_screenshot;
		extern const char* c_screenshot_event;
		extern const char* c_screenshot_character_name;
		extern const char* c_screenshot_hensei_character_name;

		extern const char* c_tessdata;
		extern const char* c_tessdata_best;

		extern const char* c_UmaData;
		extern const char* c_event_data_jp_json;
		extern const char* c_similar_char_list_json;


	}
};

