﻿#include "form.h"


namespace global
{
	namespace form
	{
		gcroot<UmaAssistant::UmaForm^> umaForm = nullptr;
		gcroot<UmaAssistant::SettingsForm^> settingsForm = nullptr;
		gcroot<UmaAssistant::PreviewForm^> previewForm = nullptr;
		gcroot<UmaAssistant::RaceScheduleForm^> raceScheduleForm = nullptr;
		gcroot<UmaAssistant::NotificationForm^> notificationForm = nullptr;
	};
};