#include "Settings.h"
#include "Util.h"

#include "Menus/ModMenus/DragonbornsBestiary/BestiaryMenuEx.h"
#include "Menus/ModMenus/QuestJournalOverhaul/QuestMenuEx.h"

#include <SimpleIni.h>

namespace
{
	void IniSection(CSimpleIniA& a_ini, const char* a_section, const char* a_comment = nullptr)
	{
		a_ini.SetValue(a_section, nullptr, nullptr, a_comment);
		SKSE::log::info("[{}]", a_section);
	}

	bool IniGetBool(CSimpleIniA& a_ini, const char* a_section, const char* a_key, bool a_default, const char* a_comment = nullptr)
	{
		bool val = a_ini.GetBoolValue(a_section, a_key, a_default);
		a_ini.SetBoolValue(a_section, a_key, val, a_comment, true);
		SKSE::log::info("  {}: {}", a_key, val);
		return val;
	}

	float IniGetFloat(CSimpleIniA& a_ini, const char* a_section, const char* a_key, float a_default, const char* a_comment = nullptr)
	{
		float val = static_cast<float>(a_ini.GetDoubleValue(a_section, a_key, a_default));
		a_ini.SetDoubleValue(a_section, a_key, val, a_comment, true);
		SKSE::log::info("  {}: {}", a_key, val);
		return val;
	}

	std::uint32_t IniGetUInt(CSimpleIniA& a_ini, const char* a_section, const char* a_key, std::uint32_t a_default, const char* a_comment = nullptr)
	{
		std::uint32_t val = static_cast<std::uint32_t>(a_ini.GetLongValue(a_section, a_key, a_default));
		a_ini.SetLongValue(a_section, a_key, val, a_comment, false, true);
		SKSE::log::info("  {}: {}", a_key, val);
		return val;
	}
}

namespace SkyrimSoulsRE
{
	Settings* Settings::GetSingleton()
	{
		static Settings singleton;
		return &singleton;
	}

	void LoadSettings()
	{
		Settings* settings = Settings::GetSingleton();

		constexpr const char* iniPath = R"(.\Data\SKSE\Plugins\SkyrimSoulsRE.ini)";

		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile(iniPath);

		SKSE::log::info("Loading settings from: {}", std::filesystem::absolute(iniPath).string());

		IniSection(ini, "UNPAUSED_MENUS", "# DELETE THIS FILE AND RUN THE GAME IF YOU WANT TO REGENERATE THE DEFAULT SETTINGS\n\n#  Here you can set which menus you want to be paused or unpaused.");
		settings->unpausedMenus[RE::BarterMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bBarterMenu", true);
		settings->unpausedMenus[RE::BookMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bBookMenu", true);
		settings->unpausedMenus[RE::Console::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bConsole", true);
		settings->unpausedMenus[RE::ContainerMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bContainerMenu", true);
		settings->unpausedMenus[RE::FavoritesMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bFavoritesMenu", true);
		settings->unpausedMenus[RE::GiftMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bGiftMenu", true);
		settings->unpausedMenus[RE::InventoryMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bInventoryMenu", true);
		settings->unpausedMenus[RE::JournalMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bJournalMenu", true);
		settings->unpausedMenus[RE::LevelUpMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bLevelUpMenu", true);
		settings->unpausedMenus[RE::LockpickingMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bLockpickingMenu", true);
		settings->unpausedMenus[RE::MagicMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bMagicMenu", true);
		settings->unpausedMenus[RE::MapMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bMapMenu", true);
		settings->unpausedMenus[RE::MessageBoxMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bMessageBoxMenu", true);
		settings->unpausedMenus[RE::ModManagerMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bModManagerMenu", true);
		settings->unpausedMenus[RE::SleepWaitMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bSleepWaitMenu", true);
		settings->unpausedMenus[RE::StatsMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bStatsMenu", true);
		settings->unpausedMenus[RE::TrainingMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bTrainingMenu", true);
		settings->unpausedMenus[RE::TutorialMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bTutorialMenu", true);
		settings->unpausedMenus[RE::TweenMenu::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bTweenMenu", true);
		settings->unpausedMenus["CustomMenu"] = IniGetBool(ini, "UNPAUSED_MENUS", "bCustomMenu", true);
		settings->unpausedMenus[QuestMenuEx::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bQuestJournalOverhaul_QuestMenu", true);
		settings->unpausedMenus[BestiaryMenuEx::MENU_NAME.data()] = IniGetBool(ini, "UNPAUSED_MENUS", "bDragonbornsBestiary_BestiaryMenu", true);

		IniSection(ini, "AUTOCLOSE");
		settings->autoCloseMenus = IniGetBool(ini, "AUTOCLOSE", "bAutoCloseMenus", true, "#  Auto close menus if the distance to the object is larger than the specified value.");
		settings->autoCloseDistance = IniGetFloat(ini, "AUTOCLOSE", "fAutoCloseDistance", 400.f, "#  The maximum distance (in in-game units) before the menus will automatically close.\n#  Too small values can cause the menus to close unexpectedly.");
		settings->autoCloseTolerance = IniGetFloat(ini, "AUTOCLOSE", "fAutoCloseTolerance", 100.f, "#  The maximum distance (in in-game units) where the menus NEVER auto-close (in relation to the players initial position when the menu was opened).\n#  This is used as a failsafe when the initial distance is larger than the maximum allowed to prevent the menu from closing immediately (e.g. a container opened by a script).");

		IniSection(ini, "DATA_UPDATES");
		settings->bottomBarMeterUpdateSteps = IniGetUInt(ini, "DATA_UPDATES", "iBottomBarMeterUpdateSteps", 100, "#  Actor value meter update divisor for the bottom bar. The bar updates only when the value crosses 1/divisor of the maximum. 0 updates on any change.");
		settings->updateInventoryMenuBottomBar = IniGetBool(ini, "DATA_UPDATES", "bUpdateInventoryMenuBottomBar", true);
		settings->updateContainerMenuBottomBar = IniGetBool(ini, "DATA_UPDATES", "bUpdateContainerMenuBottomBar", true);
		settings->updateContainerMenuPickpocketChance = IniGetBool(ini, "DATA_UPDATES", "bUpdateContainerMenuPickpocketChance", true);
		settings->updateMagicMenuBottomBar = IniGetBool(ini, "DATA_UPDATES", "bUpdateMagicMenuBottomBar", true);
		settings->updateMagicMenuActiveEffectTimers = IniGetBool(ini, "DATA_UPDATES", "bUpdateMagicMenuActiveEffectTimers", true);
		settings->updateStatsMenuPlayerInfo = IniGetBool(ini, "DATA_UPDATES", "bUpdateStatsMenuPlayerInfo", true);
		settings->updateStatsMenuSkillList = IniGetBool(ini, "DATA_UPDATES", "bUpdateStatsMenuSkillList", true);
		settings->updateTweenMenuBottomBar = IniGetBool(ini, "DATA_UPDATES", "bUpdateTweenMenuBottomBar", true);
		settings->updateJournalMenuBottomBar = IniGetBool(ini, "DATA_UPDATES", "bUpdateJournalMenuBottomBar", true);
		settings->updateMapMenuBottomBar = IniGetBool(ini, "DATA_UPDATES", "bUpdateMapMenuBottomBar", true);
		settings->updateSleepWaitMenuClock = IniGetBool(ini, "DATA_UPDATES", "bUpdateSleepWaitMenuClock", true);
		settings->updateQuestJournalOverhaulQuestMenuPlayerInfo = IniGetBool(ini, "DATA_UPDATES", "bUpdateQuestJournalOverhaulQuestMenuPlayerInfo", true);

		IniSection(ini, "CONTROLS");
		settings->enableMovementInMenus = IniGetBool(ini, "CONTROLS", "bEnableMovementInMenus", true, "# If enabled, you will be able to move when a menu is open. Use the mouse (or the D-pad on controllers) to navigate the menus.\n#  (For controllers users) To change tabs in SkyUI favorites menu, use LB and RB buttons.");
		settings->enableToggleRun = IniGetBool(ini, "CONTROLS", "bEnableToggleRun", false, "# Allows \"Toggle walk/run\" control to be available when in menus (Caps Lock by default).");
		settings->enableGamepadCameraMove = IniGetBool(ini, "CONTROLS", "bEnableGamepadCameraMove", true, "# If enabled, you will be able to move the camera when using controllers. To rotate items in the inventory, maximize the preview first by pressing on the thumb stick.");
		settings->enableCursorCameraMove = IniGetBool(ini, "CONTROLS", "bEnableCursorCameraMove", true, "# If enabled, you will be able to move the camera with the mouse by moving it to the edge of the screen (similar to how it works in the dialogue menu).");
		settings->cursorCameraVerticalSpeed = IniGetFloat(ini, "CONTROLS", "fCursorCameraVerticalSpeed", 0.15f, "# The vertical and horizontal speed the camera moves when bEnableCursorCameraMove is enabled.");
		settings->cursorCameraHorizontalSpeed = IniGetFloat(ini, "CONTROLS", "fCursorCameraHorizontalSpeed", 0.25f);
		settings->favoritesTabLeft = IniGetUInt(ini, "CONTROLS", "iFavoritesTabLeft", Util::GamepadMaskToKeycode(RE::BSWin32GamepadDevice::Key::kLeftShoulder), "# Gamepad button id used to switch to the previous tab in the SkyUI favorites menu. Default is LB (274).");
		settings->favoritesTabRight = IniGetUInt(ini, "CONTROLS", "iFavoritesTabRight", Util::GamepadMaskToKeycode(RE::BSWin32GamepadDevice::Key::kRightShoulder), "# Gamepad button id used to switch to the next tab in the SkyUI favorites menu. Default is RB (275).");

		IniSection(ini, "SLOWMOTION");
		settings->slowMotionMultiplier = IniGetFloat(ini, "SLOWMOTION", "fSlowMotionMultiplier", 0.3f, "# This is the multiplier that will affect the game speed when a menu is open.\n# Default is 0.3, which is 30% of the full speed\n# Values lower than 0.25-0.3 can cause physics issues and are not recommended.\n# This feature also doesn't play nice with other sources of slowdowns, as it won't stack properly (like potion effects or the Slow Time shout).");
		settings->slowMotionCombatOnly = IniGetBool(ini, "SLOWMOTION", "bSlowMotionCombatOnly", false, "# If enabled, slow-motion will only be applied when the player is in combat.");
		settings->slowMotionMenus[RE::BarterMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_BarterMenu", false, "#  Enable or disable slow-motion when a menu is open. Configurable on a per-menu basis.");
		settings->slowMotionMenus[RE::BookMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_BookMenu", false);
		settings->slowMotionMenus[RE::ContainerMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_ContainerMenu", false);
		settings->slowMotionMenus[RE::FavoritesMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_FavoritesMenu", false);
		settings->slowMotionMenus[RE::GiftMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_GiftMenu", false);
		settings->slowMotionMenus[RE::InventoryMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_InventoryMenu", false);
		settings->slowMotionMenus[RE::JournalMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_JournalMenu", false);
		settings->slowMotionMenus[RE::LevelUpMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_LevelUpMenu", false);
		settings->slowMotionMenus[RE::LockpickingMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_LockpickingMenu", false);
		settings->slowMotionMenus[RE::MagicMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_MagicMenu", false);
		settings->slowMotionMenus[RE::MapMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_MapMenu", false);
		settings->slowMotionMenus[RE::MessageBoxMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_MessageBoxMenu", false);
		settings->slowMotionMenus[RE::ModManagerMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_ModManagerMenu", false);
		settings->slowMotionMenus[RE::SleepWaitMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_SleepWaitMenu", false);
		settings->slowMotionMenus[RE::StatsMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_StatsMenu", false);
		settings->slowMotionMenus[RE::TrainingMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_TrainingMenu", false);
		settings->slowMotionMenus[RE::TutorialMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_TutorialMenu", false);
		settings->slowMotionMenus[RE::TweenMenu::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_TweenMenu", false);
		settings->slowMotionMenus["CustomMenu"] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_CustomMenu", false);
		settings->slowMotionMenus[QuestMenuEx::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_QuestJournalOverhaul_QuestMenu", false);
		settings->slowMotionMenus[BestiaryMenuEx::MENU_NAME.data()] = IniGetBool(ini, "SLOWMOTION", "bEnableSlowMotion_DragonbornsBestiary_BestiaryMenu", false);

		IniSection(ini, "COMBAT_ALERT_OVERLAY", "# Shows a blinking red overlay when your character is in combat. Especially useful in full screen menus. You can enable or disable it individually for each menu.");
		settings->overlayMenus[RE::BarterMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_BarterMenu", true);
		settings->overlayMenus[RE::BookMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_BookMenu", true);
		settings->overlayMenus[RE::ContainerMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_ContainerMenu", true);
		settings->overlayMenus[RE::DialogueMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_DialogueMenu", true);
		settings->overlayMenus[RE::FavoritesMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_FavoritesMenu", true);
		settings->overlayMenus[RE::GiftMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_GiftMenu", true);
		settings->overlayMenus[RE::InventoryMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_InventoryMenu", true);
		settings->overlayMenus[RE::JournalMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_JournalMenu", true);
		settings->overlayMenus[RE::LevelUpMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_LevelUpMenu", true);
		settings->overlayMenus[RE::LockpickingMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_LockpickingMenu", true);
		settings->overlayMenus[RE::MagicMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_MagicMenu", true);
		settings->overlayMenus[RE::MapMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_MapMenu", true);
		settings->overlayMenus[RE::MessageBoxMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_MessageBoxMenu", true);
		settings->overlayMenus[RE::ModManagerMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_ModManagerMenu", true);
		settings->overlayMenus[RE::SleepWaitMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_SleepWaitMenu", true);
		settings->overlayMenus[RE::StatsMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_StatsMenu", true);
		settings->overlayMenus[RE::TrainingMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_TrainingMenu", true);
		settings->overlayMenus[RE::TutorialMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_TutorialMenu", true);
		settings->overlayMenus[RE::TweenMenu::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_TweenMenu", true);
		settings->overlayMenus["CustomMenu"] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_CustomMenu", true);
		settings->overlayMenus[QuestMenuEx::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_QuestJournalOverhaul_QuestMenu", true);
		settings->overlayMenus[BestiaryMenuEx::MENU_NAME.data()] = IniGetBool(ini, "COMBAT_ALERT_OVERLAY", "bShowCAO_DragonbornsBestiary_BestiaryMenu", true);

		IniSection(ini, "HUD");
		settings->disableHUDModifications = IniGetBool(ini, "HUD", "bDisableHUDModifications", false, "# If set to true, SkyrimSouls will not attempt to modify the location of the sneak meter. Use it if you have a compatibility issue with something");
		settings->sneakMeterPosX = IniGetFloat(ini, "HUD", "fSneakMeterPosX", 24.f, "# The position where the sneak meter will appear on the screen when a menu is open. It's necessary as some menu elements would hide it otherwise (eg. lockpicking).\n# The values are a bit arbitrary so just try different values until you find what suits you.");
		settings->sneakMeterPosY = IniGetFloat(ini, "HUD", "fSneakMeterPosY", 120.f);

		IniSection(ini, "BLUR");
		settings->disableBlur = IniGetBool(ini, "BLUR", "bDisableBlur", false, "# If this is enabled, background blur will be disabled in menus");

		IniSection(ini, "MESSAGES");
		settings->hideEngineFixesWarning = IniGetBool(ini, "MESSAGES", "bHideEngineFixesWarning", false, "# Disables the warning message on startup if Engine Fixes is not detected.");

		IniSection(ini, "MAP_MENU");
		settings->mapMenuAmbientSoundLoop = IniGetBool(ini, "MAP_MENU", "bMapMenuAmbientSoundLoop", false, "# If enabled, the map menu looping ambient sound will play as normal. By default it is disabled since the game world is unpaused and both would play simultaneously.");
		settings->mapMenuCustomSky = IniGetBool(ini, "MAP_MENU", "bMapMenuCustomSky", true, "# If enabled, the map menu will use a separate sky/weather state decoupled from the real world weather.\n# This prevents the map from affecting gameplay (e.g. weather changes, precipitation), but it can be invasive.\n# Highly recommended to keep it enabled, but can be disabled if it conflicts with something.");

		SKSE::log::info("Settings loaded.");

		ini.SaveFile(R"(.\Data\SKSE\Plugins\SkyrimSoulsRE.ini)");
	}
}
