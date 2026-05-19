#pragma once

namespace SkyrimSoulsRE
{
	class CombatPauseHandler
	{
	public:
		void Update();

		static CombatPauseHandler* GetSingleton();

	private:
		CombatPauseHandler() {};
		~CombatPauseHandler() {};
		CombatPauseHandler(const CombatPauseHandler&) = delete;
		CombatPauseHandler& operator=(const CombatPauseHandler&) = delete;
	};
}
