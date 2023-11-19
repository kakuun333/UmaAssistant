#pragma once

using namespace System;
using namespace System::Drawing;

class Screenshot
{
public:
	Screenshot();

	gcroot<Bitmap^> bmp_window;
	gcroot<Bitmap^> bmp_event;
};

