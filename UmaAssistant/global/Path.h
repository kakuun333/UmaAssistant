#pragma once

#include <vcclr.h>
#include <string>

namespace global
{
	namespace path
	{
		/*		System::String^		*/
		extern gcroot<System::String^> currentDir;

		// UmaWeb
		extern gcroot<System::String^> umaWeb;
		extern gcroot<System::String^> choice_html;
		extern gcroot<System::String^> choice_style_css;
		extern gcroot<System::String^> choice_displayer_js;
		extern gcroot<System::String^> skill_displayer_js;

		extern gcroot<System::String^> character_name_html;
		extern gcroot<System::String^> character_name_style_css;
		extern gcroot<System::String^> character_name_displayer_js;
		

		// UmaTemp
		extern gcroot<System::String^> umaTemp; // ¼È¦sÀÉ¦ì¸m
		extern gcroot<System::String^> screenshot;
		extern gcroot<System::String^> screenshot_event;


		/*		std::string		*//*		std::string		*//*		std::string		*/
		extern std::string std_currentDir;

		// UmaPy
		extern std::string std_umaPy;
		extern std::string std_event_data_jp2tw_dumper_py;

		// UmaMisc
		extern std::string std_umaMisc;
		extern std::string std_config;
		extern std::string std_MochiyPopOne;

		// UmaTemp
		extern std::string std_UmaTemp;
		extern std::string std_screenshot;
		extern std::string std_screenshot_event;
		extern std::string std_screenshot_character_name;
		extern std::string std_screenshot_hensei_character_name;

		// tessdata
		extern std::string std_tessdata;
		extern std::string std_tessdata_best;

		// UmaData
		extern std::string std_UmaData;

		extern std::string std_event_data_jp_json;
		extern std::string std_skill_data_jp_json;

		extern std::string std_event_data_tw_json;
		extern std::string std_skill_data_tw_json;

		extern std::string std_similar_char_list_json;

		// UmaLua
		extern std::string std_update_event_data_lua;
		extern std::string std_update_skill_data_lua;



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
		extern const char* c_skill_data_jp_json;
		extern const char* c_similar_char_list_json;


	}
};

