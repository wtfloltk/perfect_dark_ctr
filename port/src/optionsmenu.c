#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <PR/ultratypes.h>
#include "platform.h"
#include "data.h"
#include "types.h"
#include "game/mainmenu.h"
#include "game/menu.h"
#include "video.h"
#include "input.h"
#include "config.h"

static s32 g_BindsPlayer = 0;
static s32 g_BindIndex = 0;
static u32 g_BindContKey = 0;
static char g_BindsPlayerText[] = "Player 1 Bindings";

static MenuItemHandlerResult menuhandlerMouseEnabled(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return inputMouseIsEnabled();
	case MENUOP_SET:
		inputMouseEnable(data->checkbox.value);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerMouseAimLock(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_PlayerMouseAimMode;
	case MENUOP_SET:
		g_PlayerMouseAimMode = data->checkbox.value;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerMouseDefaultLocked(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return inputGetMouseDefaultLocked();
	case MENUOP_SET:
		inputSetMouseDefaultLocked(data->checkbox.value);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerMouseSpeedX(s32 operation, struct menuitem *item, union handlerdata *data)
{
	f32 x, y;

	switch (operation) {
	case MENUOP_GETSLIDER:
		inputMouseGetSpeed(&x, &y);
		if (x < 0.f) {
			data->slider.value = 0;
		} else if (x > 10.f) {
			data->slider.value = 100;
		} else {
			data->slider.value = x * 10.f + 0.5f;
		}
		break;
	case MENUOP_SET:
		inputMouseGetSpeed(&x, &y);
		inputMouseSetSpeed((f32)data->slider.value / 10.f, y);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerMouseSpeedY(s32 operation, struct menuitem *item, union handlerdata *data)
{
	f32 x, y;

	switch (operation) {
	case MENUOP_GETSLIDER:
		inputMouseGetSpeed(&x, &y);
		if (y < 0.f) {
			data->slider.value = 0;
		} else if (y > 10.f) {
			data->slider.value = 100;
		} else {
			data->slider.value = y * 10.f + 0.5f;
		}
		break;
	case MENUOP_SET:
		inputMouseGetSpeed(&x, &y);
		inputMouseSetSpeed(x, (f32)data->slider.value / 10.f);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerMouseAimSpeedX(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		if (g_PlayerMouseAimSpeedX < 0.f) {
			data->slider.value = 0;
		} else if (g_PlayerMouseAimSpeedX > 10.f) {
			data->slider.value = 100;
		} else {
			data->slider.value = g_PlayerMouseAimSpeedX * 10.f + 0.5f;
		}
		break;
	case MENUOP_SET:
		g_PlayerMouseAimSpeedX = (f32)data->slider.value / 10.f;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerMouseAimSpeedY(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		if (g_PlayerMouseAimSpeedY < 0.f) {
			data->slider.value = 0;
		} else if (g_PlayerMouseAimSpeedY > 10.f) {
			data->slider.value = 100;
		} else {
			data->slider.value = g_PlayerMouseAimSpeedY * 10.f + 0.5f;
		}
		break;
	case MENUOP_SET:
		g_PlayerMouseAimSpeedY = (f32)data->slider.value / 10.f;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerRadialMenuSpeed(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		if (g_PlayerRadialMenuSpeed < 0.f) {
			data->slider.value = 0;
		} else if (g_PlayerRadialMenuSpeed> 10.f) {
			data->slider.value = 100;
		} else {
			data->slider.value = g_PlayerRadialMenuSpeed * 10.f + 0.5f;
		}
		break;
	case MENUOP_SET:
		g_PlayerRadialMenuSpeed = (f32)data->slider.value / 10.f;
		break;
	}

	return 0;
}


struct menuitem g_ExtendedMouseMenuItems[] = {
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Mouse Enabled",
		0,
		menuhandlerMouseEnabled,
	},
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Mouse Aim Lock",
		0,
		menuhandlerMouseAimLock,
	},
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Grab Mouse Input by Default",
		0,
		menuhandlerMouseDefaultLocked,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Mouse Speed X",
		100,
		menuhandlerMouseSpeedX,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Mouse Speed Y",
		100,
		menuhandlerMouseSpeedY,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Crosshair Speed X",
		100,
		menuhandlerMouseAimSpeedX,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Crosshair Speed Y",
		100,
		menuhandlerMouseAimSpeedY,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Radial Menu Speed",
		100,
		menuhandlerRadialMenuSpeed,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CLOSESDIALOG,
		L_OPTIONS_213, // "Back"
		0,
		NULL,
	},
	{ MENUITEMTYPE_END },
};

struct menudialogdef g_ExtendedMouseMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Extended Mouse Options",
	g_ExtendedMouseMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

static MenuItemHandlerResult menuhandlerStickSpeed(s32 operation, struct menuitem *item, union handlerdata *data);
static MenuItemHandlerResult menuhandlerStickDeadzone(s32 operation, struct menuitem *item, union handlerdata *data);

struct menuitem g_ExtendedStickMenuItems[] = {
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"LStick Scale X",
		20,
		menuhandlerStickSpeed,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"LStick Scale Y",
		20,
		menuhandlerStickSpeed,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"RStick Scale X",
		20,
		menuhandlerStickSpeed,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"RStick Scale Y",
		20,
		menuhandlerStickSpeed,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"LStick Deadzone X",
		32,
		menuhandlerStickDeadzone,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"LStick Deadzone Y",
		32,
		menuhandlerStickDeadzone,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"RStick Deadzone X",
		32,
		menuhandlerStickDeadzone,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"RStick Deadzone Y",
		32,
		menuhandlerStickDeadzone,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CLOSESDIALOG,
		L_OPTIONS_213, // "Back"
		0,
		NULL,
	},
	{ MENUITEMTYPE_END },
};

static MenuItemHandlerResult menuhandlerStickSpeed(s32 operation, struct menuitem *item, union handlerdata *data)
{
	const s32 idx = item - g_ExtendedStickMenuItems;
	const s32 stick = idx / 2;
	const s32 axis = idx % 2;

	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = inputControllerGetAxisScale(stick, axis) * 10.f + 0.5f;
		break;
	case MENUOP_SET:
		inputControllerSetAxisScale(stick, axis, (f32)data->slider.value / 10.f);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerStickDeadzone(s32 operation, struct menuitem *item, union handlerdata *data)
{
	const s32 idx = item - (g_ExtendedStickMenuItems + 5);
	const s32 stick = idx / 2;
	const s32 axis = idx % 2;

	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = inputControllerGetAxisDeadzone(stick, axis) * 32.f + 0.5f;
		break;
	case MENUOP_SET:
		inputControllerSetAxisDeadzone(stick, axis, (f32)data->slider.value / 32.f);
		break;
	}

	return 0;
}

struct menudialogdef g_ExtendedStickMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Analog Stick Settings",
	g_ExtendedStickMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

static MenuItemHandlerResult menuhandlerVibration(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = inputRumbleGetStrength() * 10.f + 0.5f;
		break;
	case MENUOP_SET:
		inputRumbleSetStrength((f32)data->slider.value / 10.f);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerAnalogMovement(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return inputControllerGetDualAnalog();
	case MENUOP_SET:
		inputControllerSetDualAnalog(data->checkbox.value);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerSwapSticks(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return inputControllerGetSticksSwapped();
	case MENUOP_SET:
		inputControllerSetSticksSwapped(data->checkbox.value);
		break;
	}

	return 0;
}

struct menuitem g_ExtendedControllerMenuItems[] = {
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Analog Movement",
		0,
		menuhandlerAnalogMovement,
	},
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Swap Sticks",
		0,
		menuhandlerSwapSticks,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_OPENSDIALOG | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Stick Settings...\n",
		0,
		(void *)&g_ExtendedStickMenuDialog,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Vibration",
		10,
		menuhandlerVibration,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CLOSESDIALOG,
		L_OPTIONS_213, // "Back"
		0,
		NULL,
	},
	{ MENUITEMTYPE_END },
};

struct menudialogdef g_ExtendedControllerMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Extended Controller Options",
	g_ExtendedControllerMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

static MenuItemHandlerResult menuhandlerFullScreen(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return videoGetFullscreen();
	case MENUOP_SET:
		videoSetFullscreen(data->checkbox.value);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerTexFilter(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return (videoGetTextureFilter() != 0);
	case MENUOP_SET:
		videoSetTextureFilter(data->checkbox.value);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerTexFilter2D(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return videoGetTextureFilter2D();
	case MENUOP_SET:
		videoSetTextureFilter2D(data->checkbox.value);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCenterHUD(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_HudAlignModeL == G_ASPECT_CENTER_EXT;
	case MENUOP_SET:
		if (data->checkbox.value) {
			g_HudAlignModeL = G_ASPECT_CENTER_EXT;
			g_HudAlignModeR = G_ASPECT_CENTER_EXT;
		} else {
			g_HudAlignModeL = G_ASPECT_LEFT_EXT;
			g_HudAlignModeR = G_ASPECT_RIGHT_EXT;
		}
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerFieldOfView(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = g_PlayerDefaultFovY + 0.5f;
		break;
	case MENUOP_SET:
		if (data->slider.value >= 15) {
			g_PlayerDefaultFovY = data->slider.value;
			if (g_PlayerFovAffectsZoom) {
				g_PlayerFovZoomMultiplier = g_PlayerDefaultFovY / 60.0f;
			}
		}
		break;
	}

	return 0;
}

struct menuitem g_ExtendedDisplayMenuItems[] = {
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Full Screen",
		0,
		menuhandlerFullScreen,
	},
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Texture Filtering",
		0,
		menuhandlerTexFilter,
	},
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"GUI Texture Filtering",
		0,
		menuhandlerTexFilter2D,
	},
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Center HUD",
		0,
		menuhandlerCenterHUD,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Vert FOV",
		170,
		menuhandlerFieldOfView,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CLOSESDIALOG,
		L_OPTIONS_213, // "Back"
		0,
		NULL,
	},
	{ MENUITEMTYPE_END },
};

struct menudialogdef g_ExtendedDisplayMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Extended Display Options",
	g_ExtendedDisplayMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

static MenuItemHandlerResult menuhandlerClassicCrouch(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_PlayerClassicCrouch;
	case MENUOP_SET:
		g_PlayerClassicCrouch = data->checkbox.value;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCrosshairSway(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = g_PlayerCrosshairSway * 10.f + 0.5f;
		break;
	case MENUOP_SET:
		g_PlayerCrosshairSway = (f32)data->slider.value / 10.f;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerScreenShake(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = g_ViShakeIntensityMult * 10.f + 0.5f;
		break;
	case MENUOP_SET:
		g_ViShakeIntensityMult = (f32)data->slider.value / 10.f;
		break;
	}

	return 0;
}

struct menuitem g_ExtendedGameMenuItems[] = {
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Allow Classic Crouch",
		0,
		menuhandlerClassicCrouch,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Crosshair Sway",
		20,
		menuhandlerCrosshairSway,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Explosion Shake",
		20,
		menuhandlerScreenShake,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CLOSESDIALOG,
		L_OPTIONS_213, // "Back"
		0,
		NULL,
	},
	{ MENUITEMTYPE_END },
};

struct menudialogdef g_ExtendedGameMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Extended Game Options",
	g_ExtendedGameMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

static MenuItemHandlerResult menuhandlerDoBind(s32 operation, struct menuitem *item, union handlerdata *data);

struct menuitem g_ExtendedBindKeyMenuItems[] = {
	{
		MENUITEMTYPE_LABEL,
		0,
		MENUITEMFLAG_SELECTABLE_CENTRE | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"\n",
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CENTRE | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Press new key or button...\n",
		0,
		menuhandlerDoBind,
	},
	{ MENUITEMTYPE_END },
};

struct menudialogdef g_ExtendedBindKeyMenuDialog = {
	MENUDIALOGTYPE_WHITE,
	(uintptr_t)"Bind",
	g_ExtendedBindKeyMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT | MENUDIALOGFLAG_IGNOREBACK | MENUDIALOGFLAG_STARTSELECTS,
	NULL,
};

struct menubind {
	u32 ck;
	const char *name;
};

static const struct menubind menuBinds[] = {
	{ CK_ZTRIG,  "Fire [ZT]\n" },
	{ CK_LTRIG,  "Fire Mode [LT]\n" },
	{ CK_RTRIG,  "Aim Mode [RT]\n" },
	{ CK_A,      "Use / Accept [A]\n" },
	{ CK_B,      "Use / Cancel [B]\n" },
	{ CK_X,      "Reload [X]\n" },
	{ CK_Y,      "Next Weapon [Y]\n" },
	{ CK_DPAD_L, "Prev Weapon [DL]\n" },
	{ CK_DPAD_L, "Radial Menu [DD]\n" },
	{ CK_START,  "Pause Menu [ST]\n" },
	{ CK_8000,   "Cycle Crouch [+]\n" },
	{ CK_4000,   "Half Crouch [+]\n" },
	{ CK_2000,   "Full Crouch [+]\n" },
};

static const char *menutextBind(struct menuitem *item);
static MenuItemHandlerResult menuhandlerBind(s32 operation, struct menuitem *item, union handlerdata *data);
static MenuItemHandlerResult menuhandlerResetBinds(s32 operation, struct menuitem *item, union handlerdata *data);

#define DEFINE_MENU_BIND() \
	{ \
		MENUITEMTYPE_DROPDOWN, \
		0, \
		0, \
		(uintptr_t)menutextBind, \
		0, \
		menuhandlerBind, \
	}

struct menuitem g_ExtendedBindsMenuItems[] = {
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	DEFINE_MENU_BIND(),
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Reset to Defaults\n",
		0,
		menuhandlerResetBinds,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CLOSESDIALOG,
		L_OPTIONS_213, // "Back"
		0,
		NULL,
	},
	{ MENUITEMTYPE_END },
};

static MenuItemHandlerResult menuhandlerDoBind(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (!menuIsDialogOpen(&g_ExtendedBindKeyMenuDialog)) {
		return 0;
	}

	if (inputKeyPressed(VK_ESCAPE)) {
		menuPopDialog();
		return 0;
	}

	const s32 key = inputGetLastKey();
	if (key && key != VK_ESCAPE) {
		inputKeyBind(g_BindsPlayer, g_BindContKey, g_BindIndex, key);
		menuPopDialog();
	}

	return 0;
}

static const char *menutextBind(struct menuitem *item)
{
	return menuBinds[item - g_ExtendedBindsMenuItems].name;
}

static MenuItemHandlerResult menuhandlerBind(s32 operation, struct menuitem *item, union handlerdata *data)
{
	const s32 idx = item - g_ExtendedBindsMenuItems;
	const u32 *binds;

	static char keyname[128];

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = INPUT_MAX_BINDS;
		break;
	case MENUOP_GETOPTIONTEXT:
		binds = inputKeyGetBinds(g_BindsPlayer, menuBinds[idx].ck);
		if (binds && binds[data->dropdown.value]) {
			strncpy(keyname, inputGetKeyName(binds[data->dropdown.value]), sizeof(keyname) - 1);
			for (char *p = keyname; *p; ++p) {
				if (*p == '_') *p = ' ';
			}
			return (intptr_t)keyname;
		}
		return (intptr_t)"NONE";
	case MENUOP_SET:
		g_ExtendedBindKeyMenuItems[0].param2 = (uintptr_t)menuBinds[idx].name;
		g_BindIndex = data->dropdown.value;
		g_BindContKey = menuBinds[idx].ck;
		inputClearLastKey();
		menuPushDialog(&g_ExtendedBindKeyMenuDialog);
		break;
	case MENUOP_GETSELECTEDINDEX:
		data->dropdown.value = 0;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerResetBinds(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		inputSetDefaultKeyBinds();
	}

	return 0;
}

struct menudialogdef g_ExtendedBindsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)g_BindsPlayerText,
	g_ExtendedBindsMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT | MENUDIALOGFLAG_STARTSELECTS | MENUDIALOGFLAG_IGNOREBACK,
	NULL,
};

static MenuItemHandlerResult menuhandlerOpenBinds(s32 operation, struct menuitem *item, union handlerdata *data);

struct menuitem g_ExtendedSelectBindsMenuItems[] = {
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Player 1\n",
		0,
		menuhandlerOpenBinds,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Player 2\n",
		0,
		menuhandlerOpenBinds,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Player 3\n",
		0,
		menuhandlerOpenBinds,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Player 4\n",
		0,
		menuhandlerOpenBinds,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CLOSESDIALOG,
		L_OPTIONS_213, // "Back"
		0,
		NULL,
	},
	{ MENUITEMTYPE_END },
};

static MenuItemHandlerResult menuhandlerOpenBinds(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_BindsPlayer = item - g_ExtendedSelectBindsMenuItems;
		g_BindsPlayerText[7] = g_BindsPlayer + '1';
		menuPushDialog(&g_ExtendedBindsMenuDialog);
	}

	return 0;
}

struct menudialogdef g_ExtendedSelectBindsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Key Bindings",
	g_ExtendedSelectBindsMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

struct menuitem g_ExtendedMenuItems[] = {
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_OPENSDIALOG | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Display\n",
		0,
		(void *)&g_ExtendedDisplayMenuDialog,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_OPENSDIALOG | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Mouse\n",
		0,
		(void *)&g_ExtendedMouseMenuDialog,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_OPENSDIALOG | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Controller\n",
		0,
		(void *)&g_ExtendedControllerMenuDialog,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_OPENSDIALOG | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Game\n",
		0,
		(void *)&g_ExtendedGameMenuDialog,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_OPENSDIALOG | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Key Bindings\n",
		0,
		(void *)&g_ExtendedSelectBindsMenuDialog,
	},
	{
		MENUITEMTYPE_SEPARATOR,
		0,
		0,
		0,
		0,
		NULL,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CLOSESDIALOG,
		L_OPTIONS_213, // "Back"
		0,
		NULL,
	},
	{ MENUITEMTYPE_END },
};

struct menudialogdef g_ExtendedMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Extended Options",
	g_ExtendedMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};
