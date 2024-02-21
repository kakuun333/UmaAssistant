#pragma once

// Window API
#include <vcclr.h>

// WinForm
#include "../UmaForm.h"
#include "../SettingsForm.h"
#include "../PreviewForm.h"

namespace global
{
	namespace form
	{
		extern gcroot<UmaAssistant::UmaForm^> umaForm;
		extern gcroot<UmaAssistant::SettingsForm^> settingsForm;
		extern gcroot<UmaAssistant::PreviewForm^> previewForm;
	};
};