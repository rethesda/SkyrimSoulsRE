#pragma once
#include "REL/Relocation.h"

namespace Offsets {

	//TODO - remove this
	static constexpr REL::ID LockpickingMenu_Hook(51071); // + 0xE0

	namespace Calendar
	{
		static constexpr REL::ID GetTimeString(static_cast<std::uint64_t>(35413));
	}

	namespace ConsoleCommands
	{
		static constexpr REL::ID CenterOnCell_Hook(static_cast<std::uint64_t>(22398)); // + 0x5B
		static constexpr REL::ID CenterOnWorld_Hook(static_cast<std::uint64_t>(22401)); // + 0x108
		static constexpr REL::ID CenterOnExterior_Hook(static_cast<std::uint64_t>(22400)); // + 0x118
		static constexpr REL::ID ServeTime_Hook(static_cast<std::uint64_t>(22145)); // + 0xE
		static constexpr REL::ID SaveGame_Hook(static_cast<std::uint64_t>(22465)); // + 0xC4
	}

	namespace Menus
	{
		namespace BarterMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(267991));

			static constexpr REL::ID UpdateBottomBar(static_cast<std::uint64_t>(50013));

			static constexpr REL::ID TargetRefHandle(static_cast<std::uint64_t>(519283));
		}

		namespace BookMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(268064));

			static constexpr REL::ID TargetRef(static_cast<std::uint64_t>(519300));
		}

		namespace Console
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(268119));
		}

		namespace ContainerMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(268222));

			static constexpr REL::ID ContainerMode(static_cast<std::uint64_t>(519396));
			static constexpr REL::ID TargetRefHandle(static_cast<std::uint64_t>(519421));

			static constexpr REL::ID UpdateBottomBar(static_cast<std::uint64_t>(50214));
		}

		namespace DialogueMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(268589));

			static constexpr REL::ID UpdateAutoCloseTimer_Hook(static_cast<std::uint64_t>(36540)); // + 0x4F9

			static constexpr REL::ID TargetRefHandle(static_cast<std::uint64_t>(517110));
		}

		namespace FavoritesMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(268567));

			static constexpr REL::ID CanProcess(static_cast<std::uint64_t>(50644));

			static constexpr REL::ID SelectItem_HookFunc_1(static_cast<std::uint64_t>(50640));
			static constexpr REL::ID SelectItem_HookFunc_2(static_cast<std::uint64_t>(50643));

			static constexpr REL::ID ItemSelect(static_cast<std::uint64_t>(50654));
		}

		namespace GiftMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(268697));

			static constexpr REL::ID UpdateBottomBar(static_cast<std::uint64_t>(50682));

			static constexpr REL::ID TargetRefHandle(static_cast<std::uint64_t>(519570));
		}

		namespace HUDMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(268816));
		}

		namespace InventoryMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(269049));

			static constexpr REL::ID UpdateBottomBar(static_cast<std::uint64_t>(50986));
		}

		namespace JournalMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(271141));

			static constexpr REL::ID RemapHandler_Vtbl(static_cast<std::uint64_t>(271032));
		}

		namespace LevelUpMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(269130));
		}

		namespace LockpickingMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(269215));

			static constexpr REL::ID TargetRef(static_cast<std::uint64_t>(519716));
		}

		namespace MagicMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(269321));

			static constexpr REL::ID UpdateBottomBar(static_cast<std::uint64_t>(51162));
		}

		namespace MapMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(270809));

			static constexpr REL::ID LocalMapUpdaterFunc(static_cast<std::uint64_t>(52225));
		}

		namespace MessageBoxMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(269561));
		}

		namespace ModManagerMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(257372));
		}

		namespace StatsMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(269955));

			static constexpr REL::ID ProcessMessage(static_cast<std::uint64_t>(51638));
			static constexpr REL::ID CanProcess(static_cast<std::uint64_t>(51645));
		}

		namespace SleepWaitMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(269872));
		}

		namespace TrainingMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(270141));
		}

		namespace TutorialMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(270169));
		}

		namespace TweenMenu
		{
			static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(270195));

			static constexpr REL::ID Camera_Hook(51833); // + 0x5A5

		}
	}

	namespace Papyrus::IsInMenuMode
	{
		static constexpr REL::ID Hook(static_cast<std::uint64_t>(56476));
		static constexpr REL::ID Value1(static_cast<std::uint64_t>(516934));
		static constexpr REL::ID Value2(static_cast<std::uint64_t>(516935));
	}

	namespace Misc
	{
		static constexpr REL::ID CreateSaveScreenshot(static_cast<std::uint64_t>(35886));
		static constexpr REL::ID CursorPosition(static_cast<std::uint64_t>(525564));
		static constexpr REL::ID ScreenEdgeCameraMoveHook(static_cast<std::uint64_t>(41259)); // + 0x241
	}

	namespace UnpausedTaskQueue
	{
		static constexpr REL::ID Hook(static_cast<std::uint64_t>(35551)); // + 0x11F
		static constexpr REL::ID OriginalFunc(static_cast<std::uint64_t>(35565));
	}

	namespace GlobalTimescaleMultiplier
	{
		static constexpr REL::ID Value1(static_cast<std::uint64_t>(511882));
		static constexpr REL::ID Value2(static_cast<std::uint64_t>(511883));
	}

	namespace MenuControls
	{
		static constexpr REL::ID Vtbl(static_cast<std::uint64_t>(269528));
	}

	// TODO:
	//const REL::Relocation<uintptr_t*> ItemMenu_MaximizeStatus = 0x2F3094C; //1.5.97
}
