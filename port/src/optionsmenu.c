#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <PR/ultratypes.h>
#include "platform.h"
#include "data.h"
#include "types.h"
#include "game/mainmenu.h"
#include "game/menu.h"
#include "game/gamefile.h"
#include "video.h"
#include "input.h"
#include "config.h"

static s32 g_ExtMenuPlayer = 0;
static struct menudialogdef *g_ExtNextDialog = NULL;

static s32 g_BindIndex = 0;
static u32 g_BindContKey = 0;

static MenuItemHandlerResult menuhandlerSelectPlayer(s32 operation, struct menuitem *item, union handlerdata *data);

struct menuitem g_ExtendedSelectPlayerMenuItems[] = {
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Player 1\n",
		0,
		menuhandlerSelectPlayer,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Player 2\n",
		0,
		menuhandlerSelectPlayer,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Player 3\n",
		0,
		menuhandlerSelectPlayer,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Player 4\n",
		0,
		menuhandlerSelectPlayer,
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

struct menudialogdef g_ExtendedSelectPlayerMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Select Player",
	g_ExtendedSelectPlayerMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

static MenuItemHandlerResult menuhandlerSelectPlayer(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_ExtMenuPlayer = item - g_ExtendedSelectPlayerMenuItems;
		((char *)g_ExtNextDialog->title)[7] = g_ExtMenuPlayer + '1';
		menuPushDialog(g_ExtNextDialog);
	}

	return 0;
}

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
		return g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimmode;
	case MENUOP_SET:
		g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimmode = data->checkbox.value;
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
		if (g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimspeedx < 0.f) {
			data->slider.value = 0;
		} else if (g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimspeedx > 10.f) {
			data->slider.value = 100;
		} else {
			data->slider.value = g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimspeedx * 10.f + 0.5f;
		}
		break;
	case MENUOP_SET:
		g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimspeedx = (f32)data->slider.value / 10.f;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerMouseAimSpeedY(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		if (g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimspeedy < 0.f) {
			data->slider.value = 0;
		} else if (g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimspeedy > 10.f) {
			data->slider.value = 100;
		} else {
			data->slider.value = g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimspeedy * 10.f + 0.5f;
		}
		break;
	case MENUOP_SET:
		g_PlayerExtCfg[g_ExtMenuPlayer].mouseaimspeedy = (f32)data->slider.value / 10.f;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerRadialMenuSpeed(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		if (g_PlayerExtCfg[0].radialmenuspeed < 0.f) {
			data->slider.value = 0;
		} else if (g_PlayerExtCfg[0].radialmenuspeed > 10.f) {
			data->slider.value = 100;
		} else {
			data->slider.value = g_PlayerExtCfg[0].radialmenuspeed * 10.f + 0.5f;
		}
		break;
	case MENUOP_SET:
		g_PlayerExtCfg[0].radialmenuspeed = (f32)data->slider.value / 10.f;
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
		data->slider.value = inputControllerGetAxisScale(g_ExtMenuPlayer, stick, axis) * 10.f + 0.5f;
		break;
	case MENUOP_SET:
		inputControllerSetAxisScale(g_ExtMenuPlayer, stick, axis, (f32)data->slider.value / 10.f);
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
		data->slider.value = inputControllerGetAxisDeadzone(g_ExtMenuPlayer, stick, axis) * 32.f + 0.5f;
		break;
	case MENUOP_SET:
		inputControllerSetAxisDeadzone(g_ExtMenuPlayer, stick, axis, (f32)data->slider.value / 32.f);
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
		data->slider.value = inputRumbleGetStrength(g_ExtMenuPlayer) * 10.f + 0.5f;
		break;
	case MENUOP_SET:
		inputRumbleSetStrength(g_ExtMenuPlayer, (f32)data->slider.value / 10.f);
		break;
	case MENUOP_CHECKHIDDEN:
	case MENUOP_CHECKDISABLED:
		if (!inputRumbleSupported(g_ExtMenuPlayer)) {
			return true;
		}
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerAnalogMovement(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return inputControllerGetDualAnalog(g_ExtMenuPlayer);
	case MENUOP_SET:
		inputControllerSetDualAnalog(g_ExtMenuPlayer, data->checkbox.value);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerSwapSticks(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return inputControllerGetSticksSwapped(g_ExtMenuPlayer);
	case MENUOP_SET:
		inputControllerSetSticksSwapped(g_ExtMenuPlayer, data->checkbox.value);
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerController(s32 operation, struct menuitem *item, union handlerdata *data)
{
	static char ctrlname[35];
	s32 ctrls[INPUT_MAX_CONNECTED_CONTROLLERS];
	const s32 numCtrls = inputGetConnectedControllers(ctrls);
	const s32 curCtrl = inputGetAssignedControllerId(g_ExtMenuPlayer);

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = numCtrls + 1; // first option is "None"
		break;
	case MENUOP_GETOPTIONTEXT:
		if (data->dropdown.value) {
			const s32 jid = ctrls[data->dropdown.value - 1];
			const char *name = inputGetConnectedControllerName(jid);
			strncpy(ctrlname, name, sizeof(ctrlname) - 1);
			return (intptr_t)ctrlname;
		} else {
			return (intptr_t)"None";
		}
	case MENUOP_SET:
		if (data->dropdown.value == 0) {
			// unassign controller
			inputAssignController(g_ExtMenuPlayer, -1);
		} else if (data->dropdown.value <= numCtrls) {
			inputAssignController(g_ExtMenuPlayer, ctrls[data->dropdown.value - 1]);
		}
		break;
	case MENUOP_GETSELECTEDINDEX:
		for (s32 i = 0; i < numCtrls; ++i) {
			if (curCtrl == ctrls[i]) {
				data->dropdown.value = i + 1;
				return 0;
			}
		}
		data->dropdown.value = 0;
		break;
	}

	return 0;
}

struct menuitem g_ExtendedControllerMenuItems[] = {
	{
		MENUITEMTYPE_DROPDOWN,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Controller",
		0,
		menuhandlerController,
	},
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

static char g_ExtendedControllerMenuTitle[] = "Player 1 Controller Options";
struct menudialogdef g_ExtendedControllerMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)g_ExtendedControllerMenuTitle,
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

static MenuItemHandlerResult menuhandlerMaximizeWindow(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return videoGetMaximizeWindow();
	case MENUOP_SET:
		videoSetMaximizeWindow(data->checkbox.value);
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

static MenuItemHandlerResult menuhandlerGeMuzzleFlashes(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_BgunGeMuzzleFlashes;
	case MENUOP_SET:
		g_BgunGeMuzzleFlashes = data->checkbox.value;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCenterHUD(s32 operation, struct menuitem *item, union handlerdata *data)
{
	static const char *opts[] = {
		"None",
		"4:3",
		"Wide"
	};

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = ARRAYCOUNT(opts);
		break;
	case MENUOP_GETOPTIONTEXT:
		return (intptr_t)opts[data->dropdown.value];
	case MENUOP_SET:
		g_HudCenter = data->checkbox.value;
		if (g_HudCenter == HUDCENTER_NORMAL) {
			g_HudAlignModeL = G_ASPECT_CENTER_EXT;
			g_HudAlignModeR = G_ASPECT_CENTER_EXT;
		} else if (g_HudCenter == HUDCENTER_WIDE) {
			g_HudAlignModeL = G_ASPECT_LEFT_EXT | G_ASPECT_WIDE_EXT;
			g_HudAlignModeR = G_ASPECT_RIGHT_EXT | G_ASPECT_WIDE_EXT;
		}	else {
			g_HudAlignModeL = G_ASPECT_LEFT_EXT;
			g_HudAlignModeR = G_ASPECT_RIGHT_EXT;
		}
		break;
	case MENUOP_GETSELECTEDINDEX:
		data->dropdown.value = g_HudCenter;
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

struct menuitem g_ExtendedVideoMenuItems[] = {
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
		(uintptr_t)"Maximize Window",
		0,
		menuhandlerMaximizeWindow,
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
		(uintptr_t)"GE64-style Muzzle Flashes",
		0,
		menuhandlerGeMuzzleFlashes,
	},
	{
		MENUITEMTYPE_DROPDOWN,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"HUD Centering",
		0,
		menuhandlerCenterHUD,
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

struct menudialogdef g_ExtendedVideoMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Extended Video Options",
	g_ExtendedVideoMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

static MenuItemHandlerResult menuhandlerDisableMpDeathMusic(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GET:
		return g_MusicDisableMpDeath;
	case MENUOP_SET:
		g_MusicDisableMpDeath = data->checkbox.value;
		break;
	}

	return 0;
}

struct menuitem g_ExtendedAudioMenuItems[] = {
	{
		MENUITEMTYPE_CHECKBOX,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Disable MP Death Music",
		0,
		menuhandlerDisableMpDeathMusic,
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

struct menudialogdef g_ExtendedAudioMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Extended Audio Options",
	g_ExtendedAudioMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

static MenuItemHandlerResult menuhandlerCrouchMode(s32 operation, struct menuitem *item, union handlerdata *data)
{
	static const char *opts[] = {
		"Hold",
		"Analog",
		"Toggle",
		"Toggle + Analog"
	};

	switch (operation) {
	case MENUOP_GETOPTIONCOUNT:
		data->dropdown.value = ARRAYCOUNT(opts);
		break;
	case MENUOP_GETOPTIONTEXT:
		return (intptr_t)opts[data->dropdown.value];
	case MENUOP_SET:
		g_PlayerExtCfg[g_ExtMenuPlayer].crouchmode = data->dropdown.value;
		break;
	case MENUOP_GETSELECTEDINDEX:
		data->dropdown.value = g_PlayerExtCfg[g_ExtMenuPlayer].crouchmode;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerFieldOfView(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = g_PlayerExtCfg[g_ExtMenuPlayer].fovy + 0.5f;
		break;
	case MENUOP_SET:
		if (data->slider.value >= 15) {
			g_PlayerExtCfg[g_ExtMenuPlayer].fovy = data->slider.value;
			if (g_PlayerExtCfg[g_ExtMenuPlayer].fovzoom) {
				g_PlayerExtCfg[g_ExtMenuPlayer].fovzoommult = g_PlayerExtCfg[g_ExtMenuPlayer].fovy / 60.f;
			}
		}
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCrosshairSway(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = g_PlayerExtCfg[g_ExtMenuPlayer].crosshairsway * 10.f + 0.5f;
		break;
	case MENUOP_SET:
		g_PlayerExtCfg[g_ExtMenuPlayer].crosshairsway = (f32)data->slider.value / 10.f;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCrosshairR(s32 operation, struct menuitem* item, union handlerdata* data)
{
	u32 newColor;

	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = (g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour >> 24) & 0xFF;
		break;

	case MENUOP_SET:
		newColor = (g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour & 0xFFFFFF) | data->slider.value << 24;
		g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour = newColor;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCrosshairG(s32 operation, struct menuitem* item, union handlerdata* data)
{
	u32 newColor;

	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = (g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour >> 16) & 0xFF;
		break;

	case MENUOP_SET:
		newColor = (g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour & 0xFF00FFFF) | data->slider.value << 16;
		g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour = newColor;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCrosshairB(s32 operation, struct menuitem* item, union handlerdata* data)
{
	u32 newColor;

	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = (g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour >> 8) & 0xFF;
		break;

	case MENUOP_SET:
		newColor = (g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour & 0xFFFF00FF) | data->slider.value << 8;
		g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour = newColor;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCrosshairA(s32 operation, struct menuitem* item, union handlerdata* data)
{
	u32 newColor;

	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour & 0xFF;
		break;

	case MENUOP_SET:
		newColor = (g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour & 0xFFFFFF00) | data->slider.value;
		g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour = newColor;
		break;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCrosshairColorPreview(s32 operation, struct menuitem* item, union handlerdata* data)
{
	if (operation == MENUOP_GETCOLOUR) {
		data->label.colour1 = g_PlayerExtCfg[g_ExtMenuPlayer].crosshaircolour;
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerCrosshairSize(s32 operation, struct menuitem *item, union handlerdata *data)
{
	switch (operation) {
	case MENUOP_GETSLIDER:
		data->slider.value = g_PlayerExtCfg[g_ExtMenuPlayer].crosshairsize;
		break;
	case MENUOP_SET:
		g_PlayerExtCfg[g_ExtMenuPlayer].crosshairsize = data->slider.value;
		break;
	}

	return 0;
}

struct menuitem g_ExtendedGameCrosshairColourMenuItems[] = {
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Red",
		255,
		menuhandlerCrosshairR,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Green",
		255,
		menuhandlerCrosshairG,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Blue",
		255,
		menuhandlerCrosshairB,
	},
	{
		MENUITEMTYPE_SLIDER,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SLIDER_WIDE,
		(uintptr_t)"Alpha",
		255,
		menuhandlerCrosshairA,
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
		MENUITEMTYPE_COLORBOX,
		0,
		0,
		0,
		0,
		menuhandlerCrosshairColorPreview,
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

struct menudialogdef g_ExtendedGameCrosshairColourMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)"Crosshair Colour",
	g_ExtendedGameCrosshairColourMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT,
	NULL,
};

struct menuitem g_ExtendedGameMenuItems[] = {
	{
		MENUITEMTYPE_DROPDOWN,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Crouch Mode",
		0,
		menuhandlerCrouchMode,
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
		(uintptr_t)"Crosshair Size",
		4,
		menuhandlerCrosshairSize,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT | MENUITEMFLAG_SELECTABLE_OPENSDIALOG,
		(uintptr_t)"Crosshair Colour\n",
		0,
		(void*)&g_ExtendedGameCrosshairColourMenuDialog,
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

static char g_ExtendedGameMenuTitle[] = "Player 1 Game Options";
struct menudialogdef g_ExtendedGameMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)g_ExtendedGameMenuTitle,
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
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_CENTRE | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"ESC to cancel, DEL to remove binding\n",
		0,
		menuhandlerDoBind,
	},
	{ MENUITEMTYPE_END },
};

struct menudialogdef g_ExtendedBindKeyMenuDialog = {
	MENUDIALOGTYPE_SUCCESS,
	(uintptr_t)"Bind",
	g_ExtendedBindKeyMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT | MENUDIALOGFLAG_IGNOREBACK | MENUDIALOGFLAG_STARTSELECTS,
	NULL,
};

struct menubind {
	u32 ck;
	const char *name;
	const char *n64name;
};

static const struct menubind menuBinds[] = {
	{ CK_ZTRIG,  "Fire [ZT]\n",         "N64 Z Trigger\n" },
	{ CK_LTRIG,  "Fire Mode [LT]\n",    "N64 L Trigger\n"},
	{ CK_RTRIG,  "Aim Mode [RT]\n",     "N64 R Trigger\n" },
	{ CK_A,      "Use / Accept [A]\n",  "N64 A Button\n" },
	{ CK_B,      "Use / Cancel [B]\n",  "N64 B Button\n" },
	{ CK_START,  "Pause Menu [ST]\n",   "N64 Start\n" },
	{ CK_DPAD_U, "D-Pad Up [DU]\n",     "N64 D-Pad Up\n" },
	{ CK_DPAD_R, "D-Pad Right [DR]\n",  "N64 D-Pad Right\n" },
	{ CK_DPAD_L, "Prev Weapon [DL]\n",  "N64 D-Pad Left\n" },
	{ CK_DPAD_D, "Radial Menu [DD]\n",  "N64 D-Pad Down\n" },
	{ CK_C_U,    "Forward [CU]\n",      "N64 C-Up\n" },
	{ CK_C_D,    "Backward [CD]\n",     "N64 C-Down\n" },
	{ CK_C_R,    "Strafe Right [CR]\n", "N64 C-Right\n" },
	{ CK_C_L,    "Strafe Left [CL]\n",  "N64 C-Left\n" },
	{ CK_X,      "Reload [X]\n",        "N64 Ext X\n" },
	{ CK_Y,      "Next Weapon [Y]\n",   "N64 Ext Y\n" },
	{ CK_8000,   "Cycle Crouch [+]\n",  "N64 Ext 8000\n" },
	{ CK_4000,   "Half Crouch [+]\n",   "N64 Ext 4000\n" },
	{ CK_2000,   "Full Crouch [+]\n",   "N64 Ext 2000\n" },
};

static const char *menutextBind(struct menuitem *item);
static MenuItemHandlerResult menuhandlerBind(s32 operation, struct menuitem *item, union handlerdata *data);
static MenuItemHandlerResult menuhandlerResetBindsPC(s32 operation, struct menuitem *item, union handlerdata *data);
static MenuItemHandlerResult menuhandlerResetBindsN64(s32 operation, struct menuitem *item, union handlerdata *data);

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
		(uintptr_t)"Reset to PC Defaults\n",
		0,
		menuhandlerResetBindsPC,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Reset to N64 Defaults\n",
		0,
		menuhandlerResetBindsN64,
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
		inputKeyBind(g_ExtMenuPlayer, g_BindContKey, g_BindIndex, (key == VK_DELETE ? 0 : key));
		menuPopDialog();
	}

	return 0;
}

static const char *menutextBind(struct menuitem *item)
{
	return g_PlayerExtCfg[g_ExtMenuPlayer].extcontrols ?
		menuBinds[item - g_ExtendedBindsMenuItems].name :
		menuBinds[item - g_ExtendedBindsMenuItems].n64name;
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
		binds = inputKeyGetBinds(g_ExtMenuPlayer, menuBinds[idx].ck);
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

static MenuItemHandlerResult menuhandlerResetBindsPC(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		inputSetDefaultKeyBinds(g_ExtMenuPlayer, false);
	}

	return 0;
}

static MenuItemHandlerResult menuhandlerResetBindsN64(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		inputSetDefaultKeyBinds(g_ExtMenuPlayer, true);
	}

	return 0;
}

static char g_ExtendedBindsMenuTitle[] = "Player 1 Bindings";
struct menudialogdef g_ExtendedBindsMenuDialog = {
	MENUDIALOGTYPE_DEFAULT,
	(uintptr_t)g_ExtendedBindsMenuTitle,
	g_ExtendedBindsMenuItems,
	NULL,
	MENUDIALOGFLAG_LITERAL_TEXT | MENUDIALOGFLAG_STARTSELECTS | MENUDIALOGFLAG_IGNOREBACK,
	NULL,
};

static MenuItemHandlerResult menuhandlerOpenControllerMenu(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_ExtNextDialog = &g_ExtendedControllerMenuDialog;
		menuPushDialog(&g_ExtendedSelectPlayerMenuDialog);
	}
	return 0;
}

static MenuItemHandlerResult menuhandlerOpenGameMenu(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_ExtNextDialog = &g_ExtendedGameMenuDialog;
		menuPushDialog(&g_ExtendedSelectPlayerMenuDialog);
	}
	return 0;
}

static MenuItemHandlerResult menuhandlerOpenBindsMenu(s32 operation, struct menuitem *item, union handlerdata *data)
{
	if (operation == MENUOP_SET) {
		g_ExtNextDialog = &g_ExtendedBindsMenuDialog;
		menuPushDialog(&g_ExtendedSelectPlayerMenuDialog);
	}
	return 0;
}

struct menuitem g_ExtendedMenuItems[] = {
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_OPENSDIALOG | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Video\n",
		0,
		(void *)&g_ExtendedVideoMenuDialog,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_SELECTABLE_OPENSDIALOG | MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Audio\n",
		0,
		(void *)&g_ExtendedAudioMenuDialog,
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
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Controller\n",
		0,
		menuhandlerOpenControllerMenu,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Game\n",
		0,
		menuhandlerOpenGameMenu,
	},
	{
		MENUITEMTYPE_SELECTABLE,
		0,
		MENUITEMFLAG_LITERAL_TEXT,
		(uintptr_t)"Key Bindings\n",
		0,
		menuhandlerOpenBindsMenu,
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
