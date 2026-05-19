#include "Menus/BarterMenuEx.h"
#include "HookUtils.h"
#include "Util.h"

namespace SkyrimSoulsRE
{
	RE::UI_MESSAGE_RESULTS BarterMenuEx::ProcessMessage_Hook(RE::UIMessage& a_message)
	{
		AutoCloseManager* autoCloseManager = AutoCloseManager::GetSingleton();

		switch (a_message.type.get())
		{
		case RE::UI_MESSAGE_TYPE::kShow:
			if (RE::RefHandle handle = GetTargetRefHandle())
			{
				autoCloseManager->InitAutoClose(RE::BarterMenu::MENU_NAME, handle, true);
			}
			break;

		case RE::UI_MESSAGE_TYPE::kUpdate:
			autoCloseManager->CheckAutoClose(RE::BarterMenu::MENU_NAME);
			break;

		case RE::UI_MESSAGE_TYPE::kHide:
			Util::ReleaseSkyUISearchWidgetTextInput(this->root);
			break;
		}

		return _ProcessMessage(this, a_message);
	}

	RE::IMenu* BarterMenuEx::Creator()
	{
		RE::BarterMenu* menu = static_cast<RE::BarterMenu*>(CreateMenu(RE::BarterMenu::MENU_NAME));
		return menu;
	}

	void BarterMenuEx::InstallHook()
	{
		REL::Relocation<std::uintptr_t> vTable(RE::VTABLE_BarterMenu[0]);
		_ProcessMessage = HookUtils::WriteVFunc(vTable, 0x4, &BarterMenuEx::ProcessMessage_Hook);
	}
}
