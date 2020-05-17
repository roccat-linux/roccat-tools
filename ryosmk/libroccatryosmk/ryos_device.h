#ifndef __ROCCAT_RYOS_DEVICE_H__
#define __ROCCAT_RYOS_DEVICE_H__

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

#include "roccat_device_scanner.h"

G_BEGIN_DECLS

#define RYOS_WRITE_CHECK_WAIT_LIGHT_CONTROL 10

/*
 * write selection: (before profile specific read)
 *   value = profile index 0-4
 *   request = RyosControlRequest or key index for macros
 */
typedef enum {
	RYOS_CONTROL_REQUEST_KEYS_PRIMARY = 0xa0,
	RYOS_CONTROL_REQUEST_KEYS_FUNCTION = 0xa1,
	RYOS_CONTROL_REQUEST_KEYS_MACRO = 0xa2,
	RYOS_CONTROL_REQUEST_KEYS_THUMBSTER = 0xa3,
	// TODO 0xa4
	RYOS_CONTROL_REQUEST_KEYS_EASYZONE = 0xa5,
	RYOS_CONTROL_REQUEST_KEY_MASK = 0xb0,
	RYOS_CONTROL_REQUEST_LIGHT = 0xb1,
	RYOS_CONTROL_REQUEST_KEYS_EXTRA = 0xb2,
	RYOS_CONTROL_REQUEST_STORED_LIGHTS_AUTOMATIC = 0xc0,
	RYOS_CONTROL_REQUEST_STORED_LIGHTS_MANUAL = 0xd0,
	RYOS_CONTROL_REQUEST_LIGHT_MACRO = 0xe0,
	RYOS_CONTROL_REQUEST_12 = 0xf0, // TODO called only for index 0
} RyosControlRequest;

typedef enum {
	RYOS_INTERFACE_KEYBOARD = 0,
	RYOS_INTERFACE_MOUSE = 1,
} RyosInterface;

RoccatDevice *ryos_device_first(void);
RoccatDeviceScanner *ryos_device_scanner_new(void);

gchar *ryos_device_read(RoccatDevice *roccat_device, guint report_id, gssize length, GError **error);
gboolean ryos_device_write(RoccatDevice *roccat_device, gchar const *buffer, gssize length, GError **error);
gboolean ryos_device_write_with_custom_wait(RoccatDevice *roccat_device, gchar const *buffer, gssize length, guint init_wait, GError **error);
gboolean ryos_select(RoccatDevice *ryos, guint profile_index, guint request, GError **error);

G_END_DECLS

#endif
