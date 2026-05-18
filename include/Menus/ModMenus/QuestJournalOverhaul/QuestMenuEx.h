#pragma once

#include "SkyrimSoulsRE.h"

namespace SkyrimSoulsRE
{
	struct QuestMenuState
	{
		char lastTimeDateString[200] = { 0 };
		float level = 0.0f;
		float xp = 0.0f;
		float levelUpThreshold = 0.0f;
	};

	class QuestMenuEx : public RE::IMenu
	{
	public:
		static constexpr std::string_view MENU_NAME = "QuestMenu";

		// override (RE::IMenu)
		RE::UI_MESSAGE_RESULTS ProcessMessage_Hook(RE::UIMessage& a_message);  // 04

		static QuestMenuState GetUpdatedState();
		void Update();

		static RE::IMenu* Creator();

		using ProcessMessage_t = decltype(&RE::IMenu::ProcessMessage);
		static inline REL::Relocation<ProcessMessage_t> _ProcessMessage;

		static inline QuestMenuState lastState = {};
		static inline bool isHookInstalled = false;
	};
}
