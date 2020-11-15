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

#include "roccat_talk_target_combo_box.h"
#include "roccat_talk.h"
#include "isku.h"
#include "iskufx.h"
#include "kiro.h"
#include "koneplus.h"
#include "konepure.h"
#include "konepuremilitary.h"
#include "konepureoptical.h"
#include "konextd.h"
#include "konextdoptical.h"
#include "kova2016.h"
#include "nyth.h"
#include "ryos.h"
#include "ryosmkfx.h"
#include "ryostkl.h"
#include "skeltr.h"
#include "sova.h"
#include "tyon.h"
#include "gtk_roccat_helper.h"

#define ROCCAT_TALK_TARGET_COMBO_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), ROCCAT_TALK_TARGET_COMBO_BOX_TYPE, RoccatTalkTargetComboBoxClass))
#define IS_ROCCAT_TALK_TARGET_COMBO_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), ROCCAT_TALK_TARGET_COMBO_BOX_TYPE))
#define ROCCAT_TALK_TARGET_COMBO_BOX_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), ROCCAT_TALK_TARGET_COMBO_BOX_TYPE, RoccatTalkTargetComboBoxPrivate))

typedef struct _RoccatTalkTargetComboBoxClass RoccatTalkTargetComboBoxClass;

struct _RoccatTalkTargetComboBoxClass {
	GtkComboBoxClass parent_class;
	GtkListStore *store;
};

struct _RoccatTalkTargetComboBoxPrivate {
	GtkTreeModel *model;
	guint source_talk_device_type;
};

enum {
	PROP_0,
	PROP_VALUE,
	PROP_SOURCE_TALK_DEVICE_TYPE,
};

enum {
	NAME_COLUMN,
	VALUE_COLUMN,
	N_COLUMNS,
};

G_DEFINE_TYPE(RoccatTalkTargetComboBox, roccat_talk_target_combo_box, GTK_TYPE_COMBO_BOX);

static void list_store_add_keyboards(GtkListStore *store) {
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(ROCCAT_TALK_DEVICE_KEYBOARD),
			VALUE_COLUMN, ROCCAT_TALK_DEVICE_KEYBOARD,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_ISKU),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_ISKU,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_ISKUFX),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_ISKUFX,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_RYOS_MK),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_RYOS_MK,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_RYOS_MK_FX),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_RYOS_MK_FX,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_RYOS_MK_GLOW),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_RYOS_MK_GLOW,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_RYOS_MK_PRO),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_RYOS_MK_PRO,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_RYOS_TKL),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_RYOS_TKL,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_RYOS_TKL_PRO),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_RYOS_TKL_PRO,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_SKELTR),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_SKELTR,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_SOVA),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_SOVA,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_SOVA_MK),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_SOVA_MK,
			-1);
}

static void list_store_add_mice(GtkListStore *store) {
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(ROCCAT_TALK_DEVICE_MOUSE),
			VALUE_COLUMN, ROCCAT_TALK_DEVICE_MOUSE,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KONEPLUS),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KONEPLUS,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KONEPURE),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KONEPURE,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KONEPURE_OWLEYE),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KONEPURE_OWLEYE,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL_BLACK),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL_BLACK,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KONEPURE_MILITARY),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KONEPURE_MILITARY,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KONEXTD),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KONEXTD,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KONEXTDOPTICAL),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KONEXTDOPTICAL,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KOVA2016_BLACK),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KOVA2016_BLACK,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KOVA2016_GRAY),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KOVA2016_GRAY,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_KOVA2016_WHITE),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_KOVA2016_WHITE,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_NYTH_BLACK),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_NYTH_BLACK,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_NYTH_WHITE),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_NYTH_WHITE,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_TYON_BLACK),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_TYON_BLACK,
			-1);
	gtk_roccat_list_store_append_with_values(store, NULL,
			NAME_COLUMN, roccat_talk_device_get_text_static(USB_DEVICE_ID_ROCCAT_TYON_WHITE),
			VALUE_COLUMN, USB_DEVICE_ID_ROCCAT_TYON_WHITE,
			-1);
}

static GtkListStore *list_store_new(void) {
	GtkListStore *list_store;

	list_store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_UINT);
	list_store_add_keyboards(list_store);
	list_store_add_mice(list_store);
	return list_store;
}

static gboolean visible_func(GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data) {
	RoccatTalkTargetComboBoxPrivate *priv = ROCCAT_TALK_TARGET_COMBO_BOX(user_data)->priv;
	guint target_talk_device;

	gtk_tree_model_get(model, iter, VALUE_COLUMN, &target_talk_device, -1);
	if(roccat_talk_device_get_type(target_talk_device) == roccat_talk_device_get_type(priv->source_talk_device_type))
		return FALSE;
	return TRUE;
}

guint roccat_talk_target_combo_box_get_value(RoccatTalkTargetComboBox *talk_target_combo_box) {
	RoccatTalkTargetComboBoxPrivate *priv = talk_target_combo_box->priv;
	GtkTreeIter iter;
	gboolean valid;
	guint value;

	valid = gtk_combo_box_get_active_iter(GTK_COMBO_BOX(talk_target_combo_box), &iter);
	if (!valid)
		return ROCCAT_TALK_DEVICE_ALL;

	gtk_tree_model_get(priv->model, &iter, VALUE_COLUMN, &value, -1);
	return value;
}

void roccat_talk_target_combo_box_set_value(RoccatTalkTargetComboBox *talk_target_combo_box, guint value) {
	RoccatTalkTargetComboBoxPrivate *priv = talk_target_combo_box->priv;
	GtkTreeIter iter;
	gboolean valid;

	valid = gtk_roccat_tree_model_iter_find_int(priv->model, VALUE_COLUMN, value, &iter, NULL);
	if (valid)
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(talk_target_combo_box), &iter);
}

guint roccat_talk_target_combo_box_get_source_talk_device_type(RoccatTalkTargetComboBox *talk_target_combo_box) {
	return talk_target_combo_box->priv->source_talk_device_type;
}

void roccat_talk_target_combo_box_set_source_talk_device_type(RoccatTalkTargetComboBox *talk_target_combo_box, guint value) {
	RoccatTalkTargetComboBoxPrivate *priv = talk_target_combo_box->priv;
	priv->source_talk_device_type = value;
	if (priv->model)
		gtk_tree_model_filter_refilter(GTK_TREE_MODEL_FILTER(priv->model));
}

GtkWidget *roccat_talk_target_combo_box_new(guint source_talk_device_type) {
	RoccatTalkTargetComboBox *talk_target_combo_box;

	talk_target_combo_box = g_object_new(ROCCAT_TALK_TARGET_COMBO_BOX_TYPE,
			"source_talk_device_type", source_talk_device_type,
			NULL);

	return GTK_WIDGET(talk_target_combo_box);
}

static void roccat_talk_target_combo_box_set_property(GObject *object, guint prop_id, GValue const *value, GParamSpec *pspec) {
	RoccatTalkTargetComboBox *talk_target_combo_box = ROCCAT_TALK_TARGET_COMBO_BOX(object);

	switch(prop_id) {
	case PROP_VALUE:
		roccat_talk_target_combo_box_set_value(talk_target_combo_box, g_value_get_uint(value));
		break;
	case PROP_SOURCE_TALK_DEVICE_TYPE:
		roccat_talk_target_combo_box_set_source_talk_device_type(talk_target_combo_box, g_value_get_uint(value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
}

static void roccat_talk_target_combo_box_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec) {
	RoccatTalkTargetComboBox *talk_target_combo_box = ROCCAT_TALK_TARGET_COMBO_BOX(object);

	switch(prop_id) {
	case PROP_VALUE:
		g_value_set_uint(value, roccat_talk_target_combo_box_get_value(talk_target_combo_box));
		break;
	case PROP_SOURCE_TALK_DEVICE_TYPE:
		g_value_set_uint(value, roccat_talk_target_combo_box_get_source_talk_device_type(talk_target_combo_box));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
}

static void roccat_talk_target_combo_box_init(RoccatTalkTargetComboBox *talk_target_combo_box) {
	RoccatTalkTargetComboBoxPrivate *priv = ROCCAT_TALK_TARGET_COMBO_BOX_GET_PRIVATE(talk_target_combo_box);
	RoccatTalkTargetComboBoxClass *klass = G_TYPE_INSTANCE_GET_CLASS(talk_target_combo_box, ROCCAT_TALK_TARGET_COMBO_BOX_TYPE, RoccatTalkTargetComboBoxClass);
	GtkCellRenderer *cell;

	talk_target_combo_box->priv = priv;

	cell = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(talk_target_combo_box), cell, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(talk_target_combo_box), cell, "text",
			NAME_COLUMN, NULL);

	priv->model = gtk_tree_model_filter_new(GTK_TREE_MODEL(klass->store), NULL);
	gtk_tree_model_filter_set_visible_func(GTK_TREE_MODEL_FILTER(priv->model), visible_func, talk_target_combo_box, NULL);

	gtk_combo_box_set_model(GTK_COMBO_BOX(talk_target_combo_box), priv->model);
}

static void roccat_talk_target_combo_box_class_init(RoccatTalkTargetComboBoxClass *klass) {
	GObjectClass *gobject_class;

	gobject_class = (GObjectClass*)klass;

	gobject_class->set_property = roccat_talk_target_combo_box_set_property;
	gobject_class->get_property = roccat_talk_target_combo_box_get_property;

	g_type_class_add_private(klass, sizeof(RoccatTalkTargetComboBoxPrivate));

	// TODO how to finalize GObjectClass?
	klass->store = list_store_new();

	g_object_class_install_property(gobject_class, PROP_VALUE,
			g_param_spec_uint("value",
					"value",
					"Reads or sets value",
					0, ROCCAT_TALK_DEVICE_ALL, 0,
					G_PARAM_READWRITE));

	g_object_class_install_property(gobject_class, PROP_SOURCE_TALK_DEVICE_TYPE,
			g_param_spec_uint("source_talk_device_type",
					"source_talk_device_type",
					"Reads or sets source talk device type",
					0, 0xffff, 0,
					G_PARAM_READWRITE | G_PARAM_CONSTRUCT));
}

