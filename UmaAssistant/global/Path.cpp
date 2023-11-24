#include "../stdafx.h"

namespace global
{
	namespace path
	{
		/*		System::String^		*/
		gcroot<System::String^> currentDir			= gcnew System::String(Directory::GetCurrentDirectory());
		gcroot<System::String^> umaTemp				= currentDir + "\\UmaTemp";
		gcroot<System::String^> screenshot			= umaTemp + "\\screenshot.png";
		gcroot<System::String^> screenshot_event	= umaTemp + "\\screenshot_event.png";


		/*		const char*		*/
		const char* c_currentDir					= utility::GetCurrentDir();  // char ªº CurrentDirectory
		
		// UmaTemp
		const char* c_UmaTemp						= utility::CombineChar(c_currentDir, "\\UmaTemp");
		const char* c_screenshot					= utility::CombineChar(c_UmaTemp, "\\screenshot.png");
		const char* c_screenshot_event				= utility::CombineChar(c_UmaTemp, "\\screenshot_event.png");

		// tessdata
		const char* c_tessdata						= utility::CombineChar(c_currentDir, "\\tessdata");
		const char* c_tessdata_best					= utility::CombineChar(c_currentDir, "\\tessdata\\best");

		// UmaData
		const char* c_UmaData						= utility::CombineChar(c_currentDir, "\\UmaData");
		const char* c_event_data_jp_json			= utility::CombineChar(c_UmaData, "\\event_data_jp.json");
		const char* c_similar_char_list_json		= utility::CombineChar(global::path::c_UmaData, "\\similar_char_list.json");
	}
};
