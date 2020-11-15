#ifndef __ROCCAT_KONEPURE_H__
#define __ROCCAT_KONEPURE_H__

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

#include "roccat_light.h"
#include "konextd.h"

G_BEGIN_DECLS

#define USB_DEVICE_ID_ROCCAT_KONEPURE 0x2dbe
#define USB_DEVICE_ID_ROCCAT_KONEPURE_OWLEYE 0x2dcd

typedef struct _KonepureProfileSettings KonepureProfileSettings;
typedef struct _KonepureProfileButtons KonepureProfileButtons;

enum {
	KONEPURE_PROFILE_BUTTON_NUM = 18,
	KONEPURE_RMP_LIGHT_INFO_COLORS_NUM = 16,
};

struct _KonepureProfileSettings {
	guint8 report_id; /* KONEPLUS_REPORT_ID_PROFILE_SETTINGS */
	guint8 size; /* 0x1f */
	guint8 profile_number; /* range 0-4 */
	guint8 xy_sync;
	guint8 sensitivity_x; /* range 0x1-0xb */
	guint8 sensitivity_y; /* range 0x1-0xb */
	guint8 cpi_levels_enabled; /* bits 1-5 */

	 /* range 1-60 means 100-6000 cpi */
	guint8 cpi_levels_x[KONEPLUS_PROFILE_SETTING_CPI_LEVELS_NUM];
	guint8 cpi_startup_level; /* range 0-4 */

	/*
	 * These values can be set differently to cpi_levels_x and are reported
	 * by cpi change events, but are not used.
	 */
	guint8 cpi_levels_y[KONEPLUS_PROFILE_SETTING_CPI_LEVELS_NUM];
	guint8 unknown1;
	guint8 polling_rate;
	guint8 light_enabled; /* bit 0, only recognized when effect type = breathing */
	guint8 light_chose_type; /* KonextdRmpLightChoseType */
	guint8 color_flow_effect;
	guint8 light_effect_type;
	guint8 light_effect_speed; /* range 1-3 */
	RoccatLight light;
	guint16 checksum;
} __attribute__ ((packed));

typedef enum {
	KONEPURE_PROFILE_SETTINGS_LIGHT_EFFECT_TYPE_OFF = 0,
	KONEPURE_PROFILE_SETTINGS_LIGHT_EFFECT_TYPE_FULLY_LIGHTED = 1,
	KONEPURE_PROFILE_SETTINGS_LIGHT_EFFECT_TYPE_BREATHING = 2,
} KonepureProfileSettingsLightEffectType;

void konepure_profile_settings_finalize(KonepureProfileSettings *profile_settings, guint index);
gboolean konepure_profile_settings_write(RoccatDevice *konepure, guint profile_number, KonepureProfileSettings *profile_settings, GError **error);
KonepureProfileSettings *konepure_profile_settings_read(RoccatDevice *konepure, guint profile_number, GError **error);
KonepureProfileSettings *konepure_rmp_to_profile_settings(KoneplusRmp *rmp);
void konepure_rmp_update_with_profile_settings(KoneplusRmp *rmp, KonepureProfileSettings const *profile_settings);
gboolean konepure_profile_settings_equal(KonepureProfileSettings const *left, KonepureProfileSettings const *right);

struct _KonepureProfileButtons {
	guint8 report_id; /* KONEPLUS_REPORT_ID_PROFILE_BUTTONS */
	guint8 size; /* always 0x3b */
	guint8 profile_number; /* range 0-4 */
	RoccatButton buttons[KONEPURE_PROFILE_BUTTON_NUM];
	guint16 checksum;
} __attribute__ ((packed));

gboolean konepure_profile_buttons_write(RoccatDevice *konepure, guint profile_index, KonepureProfileButtons *profile_buttons, GError **error);
KonepureProfileButtons *konepure_profile_buttons_read(RoccatDevice *konepure, guint profile_index, GError **error);
KonepureProfileButtons *konepure_rmp_to_profile_buttons(KoneplusRmp *rmp);
void konepure_rmp_update_with_profile_buttons(KoneplusRmp *rmp, KonepureProfileButtons const *profile_buttons);
gboolean konepure_profile_buttons_equal(KonepureProfileButtons const *left, KonepureProfileButtons const *right);

gint konepure_profile_button_index_to_rmp_index(guint profile_button_index);

/* Button positions in rmp are identical with koneplus */
typedef enum {
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_LEFT = 0,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_RIGHT = 1,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_MIDDLE = 2,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_FORWARD = 3,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_BACKWARD = 4,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_WHEEL_UP = 5,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_WHEEL_DOWN = 6,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_PLUS = 7,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_MINUS = 8,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_LEFT = 9,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_RIGHT = 10,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_MIDDLE = 11,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_FORWARD = 12,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_BACKWARD = 13,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_WHEEL_UP = 14,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_WHEEL_DOWN = 15,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_PLUS = 16,
	KONEPURE_PROFILE_BUTTONS_BUTTON_INDEX_SHIFT_MINUS = 17,
} KonepureProfileButtonsButtonIndex;

typedef enum {
	KONEPURE_REPORT_ID_SROM_WRITE = 0x0d,
} KonepureReportId;

RoccatDevice *konepure_device_first(void);
RoccatDeviceScanner *konepure_device_scanner_new(void);

gboolean konepure_select(RoccatDevice *konepure, guint profile_index, guint request, GError **error);

RoccatKeyFile *konepure_configuration_load(void);
gboolean konepure_configuration_save(RoccatKeyFile *config, GError **error);

KoneplusRmp *konepure_default_rmp(void);
GKeyFile *konepure_rmp_defaults(void);
KoneplusRmp *konepure_rmp_load(RoccatDevice *konepure, guint profile_index, GError **error);
gboolean konepure_rmp_save(RoccatDevice *konepure, KoneplusRmp *rmp, guint profile_index, GError **error);
KoneplusRmp *konepure_rmp_load_save_after_reset(RoccatDevice *konepure, guint profile_index, GError **error);

KoneplusRmp *konepure_rmp_load_actual(guint profile_index);
gboolean konepure_rmp_save_actual(KoneplusRmp *rmp, guint profile_index, GError **error);
void konepure_rmp_update_from_device(KoneplusRmp *rmp, RoccatDevice *konepure, guint profile_index);

KoneplusRmpLightInfo const *konepure_rmp_light_info_get_standard(guint index);

DBusGProxy *konepure_dbus_proxy_new(void);
gboolean konepure_dbus_emit_profile_data_changed_outside(DBusGProxy *proxy, guint profile_number);
gboolean konepure_dbus_emit_profile_data_changed_outside_instant(guint profile_number);
gboolean konepure_dbus_emit_profile_changed_outside(DBusGProxy *proxy, guint profile_number);
gboolean konepure_dbus_emit_profile_changed_outside_instant(guint profile_number);
gboolean konepure_dbus_emit_configuration_changed_outside(DBusGProxy *proxy);

#define KONEPURE_DBUS_SERVER_PATH "/org/roccat/Konepure"
#define KONEPURE_DBUS_SERVER_INTERFACE "org.roccat.Konepure"

#define KONEPURE_DEVICE_NAME "Kone Pure"
#define KONEPURE_OWLEYE_DEVICE_NAME "Kone Pure OwlEye"

G_END_DECLS

#endif

