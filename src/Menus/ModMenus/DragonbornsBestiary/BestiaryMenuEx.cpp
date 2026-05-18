#include "Menus/ModMenus/DragonbornsBestiary/BestiaryMenuEx.h"

namespace SkyrimSoulsRE
{
	RE::IMenu* BestiaryMenuEx::Creator()
	{
		return CreateMenu(MENU_NAME);
	}
}
