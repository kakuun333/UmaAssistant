#include "form.h"


namespace global
{
	namespace form
	{
		gcroot<UmaAssistant::UmaForm^> umaForm = nullptr;
		gcroot<UmaAssistant::SettingsForm^> settingsForm = nullptr;
		gcroot<UmaAssistant::PreviewForm^> previewForm = nullptr;
	};
};