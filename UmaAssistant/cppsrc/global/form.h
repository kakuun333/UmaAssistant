#pragma once

// C++/CLI
#include <vcclr.h>

// WinForm
#include "../../UmaForm.h"
#include "../../SettingsForm.h"
#include "../../PreviewForm.h"
#include "../../RaceScheduleForm.h"
#include "../../NotificationForm.h"

namespace global
{
	namespace form
	{
		extern gcroot<UmaAssistant::UmaForm^> umaForm;
		extern gcroot<UmaAssistant::SettingsForm^> settingsForm;
		extern gcroot<UmaAssistant::PreviewForm^> previewForm;
		extern gcroot<UmaAssistant::RaceScheduleForm^> raceScheduleForm;
		extern gcroot<UmaAssistant::NotificationForm^> notificationForm;
	};
};