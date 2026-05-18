#pragma once

#include "SkyrimSoulsRE.h"

namespace SkyrimSoulsRE
{
	class BestiaryMenuEx : public RE::IMenu
	{
	public:
		static constexpr std::string_view MENU_NAME = "BestiaryMenu";

		static RE::IMenu* Creator();
	};
}
