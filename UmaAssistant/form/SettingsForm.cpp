#include "../stdafx.h"

namespace UmaAssistant
{
	System::Void SettingsForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LuaManager* luaManager = LuaManager::GetInstance();

		if (!luaManager->IsBusy())
			luaManager->DumpEventData();
	}

	System::Void SettingsForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		LuaManager* luaManager = LuaManager::GetInstance();

		if (!luaManager->IsBusy())
			luaManager->DumpSkillData();
	}
}