#include "../stdafx.h"

namespace global
{
	namespace path
	{
		/*		System::String^		*//*		System::String^		*//*		System::String^		*/
		gcroot<System::String^> currentDir				 = gcnew System::String(Directory::GetCurrentDirectory());

		// UmaWeb
		gcroot<System::String^> umaWeb = currentDir + "\\UmaWeb";
		gcroot<System::String^> choice_html		 = /*"file://" +*/ umaWeb + "\\choice.html";
		gcroot<System::String^> choice_style_css = umaWeb + "\\choice_style.css";
		gcroot<System::String^> choice_displayer_js = umaWeb + "\\choice_displayer.js";
		gcroot<System::String^> skill_displayer_js = umaWeb + "\\skill_displayer.js";

		gcroot<System::String^> character_name_html  = /*"file://" +*/ umaWeb + "\\character_name.html";
		gcroot<System::String^> character_name_style_css = umaWeb + "\\character_name_style.css";
		gcroot<System::String^> character_name_displayer_js = umaWeb + "\\character_name_displayer.js";

		// UmaTemp
		gcroot<System::String^> umaTemp					 = currentDir + "\\UmaTemp";
		gcroot<System::String^> screenshot				 = umaTemp + "\\screenshot.png";
		gcroot<System::String^> screenshot_event		 = umaTemp + "\\screenshot_event.png";

		/*		std::string		*//*		std::string		*//*		std::string		*/
		// UmaTemp
		std::string std_currentDir						 = utility::GetCurrentDir();  // char ªº CurrentDirectory
		std::string std_UmaTemp							 = std_currentDir + "\\UmaTemp";
		std::string std_screenshot						 = std_UmaTemp + "\\screenshot.png";
		std::string std_screenshot_event				 = std_UmaTemp + "\\screenshot_event.png";
		std::string std_screenshot_character_name		 = std_UmaTemp + "\\screenshot_character_name.png";
		std::string std_screenshot_hensei_character_name = std_UmaTemp + "\\screenshot_hensei_character_name.png";

		// tessdata
		std::string std_tessdata						 = std_currentDir + "\\tessdata";
		std::string std_tessdata_best					 = std_currentDir + "\\tessdata\\best";

		// UmaData
		std::string std_UmaData							 = std_currentDir + "\\UmaData";
		std::string std_event_data_jp_json				 = std_UmaData + "\\event_data_jp.json";
		std::string std_skill_data_jp_json				 = std_UmaData + "\\skill_data_jp.json";
		std::string std_similar_char_list_json			 = std_UmaData + "\\similar_char_list.json";

		// UmaLua
		std::string std_UmaLua							 = std_currentDir + "\\UmaLua";
		std::string std_update_event_data_lua			 = std_UmaLua + "\\update_event_data.lua";
		std::string std_update_skill_data_lua			 = std_UmaLua + "\\update_skill_data.lua";


		/*		const char*		*//*		const char*		*//*		const char*		*/
		const char* c_currentDir						= utility::GetCurrentDir();  // char ªº CurrentDirectory
		
		// UmaTemp
		const char* c_UmaTemp							= utility::CombineChar(c_currentDir, "\\UmaTemp");
		const char* c_screenshot						= utility::CombineChar(c_UmaTemp, "\\screenshot.png");
		const char* c_screenshot_event					= utility::CombineChar(c_UmaTemp, "\\screenshot_event.png");
		const char* c_screenshot_character_name			= utility::CombineChar(c_UmaTemp, "\\screenshot_character_name.png");
		const char* c_screenshot_hensei_character_name	= utility::CombineChar(c_UmaTemp, "\\screenshot_hensei_character_name.png");

		// tessdata
		const char* c_tessdata							= utility::CombineChar(c_currentDir, "\\tessdata");
		const char* c_tessdata_best						= utility::CombineChar(c_currentDir, "\\tessdata\\best");

		// UmaData
		const char* c_UmaData							= utility::CombineChar(c_currentDir, "\\UmaData");
		const char* c_event_data_jp_json				= utility::CombineChar(c_UmaData, "\\event_data_jp.json");
		const char* c_skill_data_jp_json				= utility::CombineChar(c_UmaData, "\\skill_data_jp.json");
		const char* c_similar_char_list_json			= utility::CombineChar(c_UmaData, "\\similar_char_list.json");
	}
};
