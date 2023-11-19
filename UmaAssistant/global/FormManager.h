#pragma once

#include <vcclr.h>

#include "../form/UmaForm.h"
#include "../form/SettingsForm.h"
#include "../form/PreviewForm.h"


namespace global
{
	namespace form
	{
		extern gcroot<UmaAssistant::UmaForm^> umaForm;
		extern gcroot<UmaAssistant::SettingsForm^> settingsForm;
		extern gcroot<UmaAssistant::PreviewForm^> previewForm;
	};
};

