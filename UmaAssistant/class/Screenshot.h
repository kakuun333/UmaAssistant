#pragma once

using namespace System;
using namespace System::Drawing;

class Screenshot
{
private:
	void GetEventTextImage();

	void GetCharacterNameImage();

public:
	Screenshot();


	gcroot<Bitmap^> bmp_window;
	gcroot<Bitmap^> bmp_event;
};

