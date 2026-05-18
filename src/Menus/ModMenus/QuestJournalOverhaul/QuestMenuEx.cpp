#include "Menus/ModMenus/QuestJournalOverhaul/QuestMenuEx.h"

namespace SkyrimSoulsRE
{
	RE::UI_MESSAGE_RESULTS QuestMenuEx::ProcessMessage_Hook(RE::UIMessage& a_message)
	{
		RE::UI_MESSAGE_RESULTS result = _ProcessMessage(this, a_message);

		switch (a_message.type.get())
		{
		case RE::UI_MESSAGE_TYPE::kShow:
			lastState = GetUpdatedState();
			break;

		case RE::UI_MESSAGE_TYPE::kUpdate:
			RE::UIMessageQueue::GetSingleton()->AddMessage(RE::HUDMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kUpdate, nullptr);
			Update();
			break;
		}

		return result;
	}

	QuestMenuState QuestMenuEx::GetUpdatedState()
	{
		QuestMenuState state{};
		RE::Calendar::GetSingleton()->GetTimeDateString(state.lastTimeDateString, sizeof(state.lastTimeDateString), true);

		RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
		state.level = static_cast<float>(player->GetLevel());
		state.xp = player->skills->data->xp;
		state.levelUpThreshold = player->skills->data->levelThreshold;

		return state;
	}

	void QuestMenuEx::Update()
	{
		Settings* settings = Settings::GetSingleton();
		if (!settings->updateQuestJournalOverhaulQuestMenuPlayerInfo)
		{
			return;
		}

		QuestMenuState newState = GetUpdatedState();

		bool timeDateChanged = std::strncmp(lastState.lastTimeDateString, newState.lastTimeDateString, sizeof(QuestMenuState::lastTimeDateString)) != 0;
		bool xpChanged = newState.level != lastState.level || newState.xp != lastState.xp || newState.levelUpThreshold != lastState.levelUpThreshold;

		if (timeDateChanged || xpChanged)
		{
			float xpPercent = (newState.xp / newState.levelUpThreshold) * 100.0f;

			RE::GFxValue args[3];
			args[0].SetNumber(newState.level);
			args[1].SetNumber(xpPercent);
			args[2].SetString(newState.lastTimeDateString);
			this->uiMovie->Invoke("_root.QuestJournal_mc.SetHeaderInfo", nullptr, args, 3);
		}

		lastState = newState;
	}

	RE::IMenu* QuestMenuEx::Creator()
	{
		RE::IMenu* menu = CreateMenu(MENU_NAME);

		if (!isHookInstalled)
		{
			isHookInstalled = true;
			REL::Relocation<std::uintptr_t> vTable(*reinterpret_cast<std::uintptr_t*>(menu));
			_ProcessMessage = vTable.write_vfunc(0x4, &QuestMenuEx::ProcessMessage_Hook);
		}

		return menu;
	}
}
