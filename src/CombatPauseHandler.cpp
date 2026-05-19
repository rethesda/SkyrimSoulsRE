#include "CombatPauseHandler.h"
#include "Settings.h"
#include "SkyrimSoulsRE.h"

namespace SkyrimSoulsRE
{
	void CombatPauseHandler::Update()
	{
		using MenuFlag = RE::IMenu::Flag;

		RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
		bool shouldPause = Settings::GetSingleton()->pauseDuringCombat && player && player->IsInCombat();

		RE::UI* ui = RE::UI::GetSingleton();
		for (auto& menu : ui->menuStack)
		{
			if (!menu->menuFlags.all(static_cast<MenuFlag>(MenuFlagEx::kUnpaused)))
			{
				continue;
			}

			bool isPaused = menu->menuFlags.all(MenuFlag::kPausesGame);

			if (shouldPause && !isPaused)
			{
				menu->menuFlags.set(MenuFlag::kPausesGame);
				ui->numPausesGame++;
			}
			else if (!shouldPause && isPaused)
			{
				menu->menuFlags.reset(MenuFlag::kPausesGame);
				ui->numPausesGame--;
			}
		}
	}

	CombatPauseHandler* CombatPauseHandler::GetSingleton()
	{
		static CombatPauseHandler singleton;
		return &singleton;
	}
}
