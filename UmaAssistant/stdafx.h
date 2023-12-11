#pragma once

//#define UMA_DEBUG


/*			C++ ¨ç¼Æ®w			*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <vector>
#include <cstring>
#include <thread>
#include <regex>
#include <future>
#include <functional>
#include <locale>
#include <codecvt>
#include <algorithm>


// Gdi+
#include <GdiPlus.h>
#pragma comment(lib, "gdiplus.lib")

/*			C++/CLI			*/
#include <vcclr.h>

// msclr
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
using namespace msclr::interop;

/*			3rdparty			*/
#include <curl/curl.h>

// nlohmann/json
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// tesseract
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

// opencv
#include <opencv2/opencv.hpp>

/*			class			*/	
#include "class/Screenshot.h"
#include "class/Scanner.h"
#include "class/DataManager.h"
#include "class/WebManager.h"
#include "class/FileManager.h"
#include "class/GameWindowFinder.h"
#include "class/LocalServer.h"
#include "class/ConsoleManager.h"
#include "class/PyManager.h"
#include "class/Config.h"
#include "class/AutoMouseClicker.h"
#include "class/UmaTimer.h"

// ¨ü±±
#include "class/ref/FormDesigner.h"
#include "class/ref/FormController.h"

// lua
#include "class/LuaManager.h"

// data
#include "class/data/UmaEventData.h"
#include "class/data/ScenarioEventData.h"
#include "class/data/UmaEventRoute.h"

/*			utility			*/
#include "utility/CharacterConvert.h"
#include "utility/CharacterCombine.h"
#include "utility/CharacterFilter.h"
#include "utility/CharacterCompare.h"
#include "utility/Pathfinder.h"
#include "utility/FormControl.h"

/*			enum			*/
#include "enum/UmaEventDataType.h"
#include "enum/GameWindowType.h"
#include "enum/ImageType.h"
#include "enum/FileType.h"
#include "enum/FilePathType.h"
#include "enum/GameServerType.h"
#include "enum/GameWindowType.h"
#include "enum/JpServerLangType.h"


/*			global			*/
#include "global/Path.h"
#include "global/FormManager.h"
#include "global/UmaSwitch.h"
#include "global/Others.h"





/*			.NET			*/
using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
//using namespace System::ComponentModel;
using namespace System::Data;
using namespace System::Diagnostics;
using namespace System::Drawing;
using namespace System::Drawing::Text;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Net;
using namespace System::Text;
using namespace System::Text::RegularExpressions;
using namespace System::Threading;
using namespace System::Threading::Tasks;