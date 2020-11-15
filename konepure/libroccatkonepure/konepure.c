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

#include "konepure.h"
#include "roccat.h"

static guint const device_ids[3] = {
	USB_DEVICE_ID_ROCCAT_KONEPURE,
	USB_DEVICE_ID_ROCCAT_KONEPURE_OWLEYE,
	0
};

RoccatDevice *konepure_device_first(void) {
	return roccat_device_first(device_ids);
}

RoccatDeviceScanner *konepure_device_scanner_new(void) {
	return roccat_device_scanner_new(device_ids);
}
