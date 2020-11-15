/*
 * This file is part of roccat-tools.
 *
 * roccat-tools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * roccat-tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with roccat-tools. If not, see <http://www.gnu.org/licenses/>.
 */

#include "roccat_talk.h"
#include "arvo.h"
#include "isku.h"
#include "iskufx.h"
#include "kiro.h"
#include "kone.h"
#include "koneplus.h"
#include "konepure.h"
#include "konepuremilitary.h"
#include "konepureoptical.h"
#include "konextd.h"
#include "konextdoptical.h"
#include "kova2016.h"
#include "kovaplus.h"
#include "lua.h"
#include "nyth.h"
#include "pyra.h"
#include "ryos.h"
#include "ryosmkfx.h"
#include "ryostkl.h"
#include "savu.h"
#include "skeltr.h"
#include "sova.h"
#include "suora.h"
#include "tyon.h"
#include "i18n-lib.h"

guint roccat_talk_device_get_type(guint talk_device) {
	switch(talk_device) {
	case ROCCAT_TALK_DEVICE_MOUSE:
	case USB_DEVICE_ID_ROCCAT_KIRO:
	case USB_DEVICE_ID_ROCCAT_KONE:
	case USB_DEVICE_ID_ROCCAT_KONEPLUS:
	case USB_DEVICE_ID_ROCCAT_KONEPURE:
	case USB_DEVICE_ID_ROCCAT_KONEPURE_OWLEYE:
	case USB_DEVICE_ID_ROCCAT_KONEPURE_MILITARY:
	case USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL:
	case USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL_BLACK:
	case USB_DEVICE_ID_ROCCAT_KONEXTD:
	case USB_DEVICE_ID_ROCCAT_KONEXTDOPTICAL:
	case USB_DEVICE_ID_ROCCAT_KOVA2016_BLACK:
	case USB_DEVICE_ID_ROCCAT_KOVA2016_GRAY:
	case USB_DEVICE_ID_ROCCAT_KOVA2016_WHITE:
	case USB_DEVICE_ID_ROCCAT_KOVAPLUS:
	case USB_DEVICE_ID_ROCCAT_LUA:
	case USB_DEVICE_ID_ROCCAT_NYTH_BLACK:
	case USB_DEVICE_ID_ROCCAT_NYTH_WHITE:
	case USB_DEVICE_ID_ROCCAT_PYRA_WIRED:
	case USB_DEVICE_ID_ROCCAT_PYRA_WIRELESS:
	case USB_DEVICE_ID_ROCCAT_SAVU:
	case USB_DEVICE_ID_ROCCAT_TYON_BLACK:
	case USB_DEVICE_ID_ROCCAT_TYON_WHITE:
		return ROCCAT_TALK_DEVICE_MOUSE;
		break;
	case ROCCAT_TALK_DEVICE_KEYBOARD:
	case USB_DEVICE_ID_ROCCAT_ARVO:
	case USB_DEVICE_ID_ROCCAT_ISKU:
	case USB_DEVICE_ID_ROCCAT_ISKUFX:
	case USB_DEVICE_ID_ROCCAT_RYOS_MK:
	case USB_DEVICE_ID_ROCCAT_RYOS_MK_FX:
	case USB_DEVICE_ID_ROCCAT_RYOS_MK_GLOW:
	case USB_DEVICE_ID_ROCCAT_RYOS_MK_PRO:
	case USB_DEVICE_ID_ROCCAT_RYOS_TKL:
	case USB_DEVICE_ID_ROCCAT_RYOS_TKL_PRO:
	case USB_DEVICE_ID_ROCCAT_SKELTR:
	case USB_DEVICE_ID_ROCCAT_SOVA:
	case USB_DEVICE_ID_ROCCAT_SOVA_MK:
	case USB_DEVICE_ID_ROCCAT_SUORA:
		return ROCCAT_TALK_DEVICE_KEYBOARD;
		break;
	default:
		return ROCCAT_TALK_DEVICE_NONE;
		break;
	}
}

gchar const *roccat_talk_device_get_text_static(guint talk_device) {
	switch(talk_device) {
	case ROCCAT_TALK_DEVICE_ALL:
		return _("All");
	case ROCCAT_TALK_DEVICE_KEYBOARD:
		return _("*Any keyboard");
	case USB_DEVICE_ID_ROCCAT_ARVO:
		return ARVO_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_ISKU:
		return ISKU_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_ISKUFX:
		return ISKUFX_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_RYOS_MK:
		return RYOS_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_RYOS_MK_FX:
		return RYOSMKFX_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_RYOS_MK_GLOW:
		return RYOS_DEVICE_NAME_GLOW;
	case USB_DEVICE_ID_ROCCAT_RYOS_MK_PRO:
		return RYOS_DEVICE_NAME_PRO;
	case USB_DEVICE_ID_ROCCAT_RYOS_TKL:
		return RYOSTKL_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_RYOS_TKL_PRO:
		return RYOSTKL_PRO_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_SKELTR:
		return SKELTR_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_SOVA:
		return SOVA_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_SOVA_MK:
		return SOVA_DEVICE_NAME_MK;
	case USB_DEVICE_ID_ROCCAT_SUORA:
		return SUORA_DEVICE_NAME;
	case ROCCAT_TALK_DEVICE_MOUSE:
		return _("*Any mouse");
	case USB_DEVICE_ID_ROCCAT_KIRO:
		return KIRO_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONE:
		return KONE_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONEPLUS:
		return KONEPLUS_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONEPURE:
		return KONEPURE_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONEPURE_OWLEYE:
		return KONEPURE_OWLEYE_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONEPURE_MILITARY:
		return KONEPUREMILITARY_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL:
		return KONEPUREOPTICAL_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL_BLACK:
		return KONEPUREOPTICALBLACK_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONEXTD:
		return KONEXTD_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KONEXTDOPTICAL:
		return KONEXTDOPTICAL_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_KOVA2016_BLACK:
		return KOVA2016_DEVICE_NAME_BLACK;
	case USB_DEVICE_ID_ROCCAT_KOVA2016_GRAY:
		return KOVA2016_DEVICE_NAME_GRAY;
	case USB_DEVICE_ID_ROCCAT_KOVA2016_WHITE:
		return KOVA2016_DEVICE_NAME_WHITE;
	case USB_DEVICE_ID_ROCCAT_KOVAPLUS:
		return KOVAPLUS_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_LUA:
		return LUA_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_NYTH_BLACK:
		return NYTH_DEVICE_NAME_BLACK;
	case USB_DEVICE_ID_ROCCAT_NYTH_WHITE:
		return NYTH_DEVICE_NAME_WHITE;
	case USB_DEVICE_ID_ROCCAT_PYRA_WIRED:
		return PYRA_DEVICE_NAME_WIRED;
	case USB_DEVICE_ID_ROCCAT_PYRA_WIRELESS:
		return PYRA_DEVICE_NAME_WIRELESS;
	case USB_DEVICE_ID_ROCCAT_SAVU:
		return SAVU_DEVICE_NAME;
	case USB_DEVICE_ID_ROCCAT_TYON_BLACK:
		return TYON_DEVICE_NAME_BLACK;
	case USB_DEVICE_ID_ROCCAT_TYON_WHITE:
		return TYON_DEVICE_NAME_WHITE;
	default:
		return _("Unknown");
	}
}
