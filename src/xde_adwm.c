/*****************************************************************************

 Copyright (c) 2008-2015  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, version 3 of the license.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 details.

 You should have received a copy of the GNU General Public License along with
 this program.  If not, see <http://www.gnu.org/licenses/>, or write to the
 Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 *****************************************************************************/

#include "xde-menu.h"

/** @name ADWM
  */
/** @{ */

static GList *
xde_create(MenuContext *ctx, Style style, const char *name)
{
	GList *text = NULL;

	return (text);
}

static GtkMenu *
xde_gtk_create(MenuContext *ctx, Style style, const char *name)
{
	GtkMenu *menu = NULL;

	menu = xde_gtk_create_simple(ctx, style, name);
	return (menu);
}

static GList *
xde_appmenu(MenuContext *ctx, GList *entries, const char *name)
{
	GList *text = NULL;

	return (text);
}

static GtkMenu *
xde_gtk_appmenu(MenuContext *ctx, GtkMenu *entries, const char *name)
{
	GtkMenu *menu = NULL;

	menu = xde_gtk_common_appmenu(ctx, entries, name);
	return (menu);
}

static GList *
xde_rootmenu(MenuContext *ctx, GList *entries)
{
	GList *text = NULL;

	return (text);
}

static GtkMenu *
xde_gtk_rootmenu(MenuContext *ctx, GtkMenu *entries)
{
	GtkMenu *menu = NULL;

	menu = xde_gtk_common_rootmenu(ctx, entries);
	return (menu);
}

static GList *
xde_build(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_build(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
{
	GtkMenuItem *menu = NULL;

	menu = xde_gtk_build_simple(ctx, type, item);
	return (menu);
}

static GList *
xde_menu(MenuContext *ctx, GMenuTreeDirectory *menu)
{
	GList *text = NULL;

	return (text);
}

static GtkMenu *
xde_gtk_menu(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GtkMenu *menu = NULL;

	menu = xde_gtk_common_menu(ctx, dir);
	return (menu);
}

static GList *
xde_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_separator(ctx, sep);
	return (item);
}

static GList *
xde_header(MenuContext *ctx, GMenuTreeHeader *hdr)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_header(MenuContext *ctx, GMenuTreeHeader *hdr)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_header(ctx, hdr);
	return (item);
}

static GList *
xde_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_directory(ctx, dir);
	return (item);
}

static GList *
xde_entry(MenuContext *ctx, GMenuTreeEntry *ent)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_entry(MenuContext *ctx, GMenuTreeEntry *ent)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_entry(ctx, ent);
	return (item);
}

static GList *
xde_alias(MenuContext *ctx, GMenuTreeAlias *als)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_alias(MenuContext *ctx, GMenuTreeAlias *als)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_alias(ctx, als);
	return (item);
}

static GList *
xde_actions(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info)
{
	GList *text = NULL;

	return (text);
}

static GtkMenu *
xde_gtk_actions(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info)
{
	GtkMenu *menu = NULL;

	menu = xde_gtk_common_actions(ctx, ent, info);
	return (menu);
}

static GList *
xde_pin(MenuContext *ctx)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_pin(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_pin(ctx);
	return (item);
}

static GList *
xde_wmmenu(MenuContext *ctx)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_wmmenu(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_wmmenu(ctx);
	return (item);
}

static GList *
xde_styles(MenuContext *ctx)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_styles(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_styles_simple(ctx);
	return (item);
}

static GList *
xde_themes(MenuContext *ctx)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_themes(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_themes_simple(ctx);
	return (item);
}

static GList *
xde_config(MenuContext *ctx)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_config(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	/* FIXME */
	return (item);
}

static GList *
xde_wkspcs(MenuContext *ctx)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_wkspcs(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	/* FIXME */
	return (item);
}

static GList *
xde_wmspec(MenuContext *ctx)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_wmspec(MenuContext *ctx)
{
	GtkWidget *image, *menu;
	GtkMenuItem *item, *part;
	GdkPixbuf *pixbuf = NULL;
	const char *inames[4] = { ctx->name, "preferences-system-windows", "metacity", NULL };
	char *icon;

	menu = gtk_menu_new();
	item = (GtkMenuItem *)gtk_image_menu_item_new();
	gtk_menu_item_set_submenu(item, menu);
	gtk_menu_item_set_label(item, ctx->wmname);
	if ((icon = xde_get_icons(ctx, inames))
	    && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL))
	    && (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	gtk_widget_show_all(GTK_WIDGET(menu));
	gtk_widget_show_all(GTK_WIDGET(item));
	DPRINTF("calling \"config\"\n");
	if ((part = ctx->gtk.config(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF("calling \"themes\"\n");
	if ((part = ctx->gtk.themes(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF("calling \"styles\"\n");
	if ((part = ctx->gtk.styles(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF("calling \"wkspcs\"\n");
	if ((part = ctx->gtk.wkspcs(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF("calling \"wmmenu\"\n");
	if ((part = ctx->gtk.wmmenu(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF("done\n");
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	return (GTK_MENU_ITEM(item));
}

MenuContext xde_menu_ops = {
	.name = "adwm",
	.format = "adwm",
	.wmname = "ADWM",
	.desktop = "ADWM",
	.version = VERSION,
	.styles = {
		.sysdir = "/usr/share/adwm",
		.usrdir = "/.adwm",
		.subdir = "/styles",
		.fname = "/stylerc",
		.suffix = "",
	},
	.tree = NULL,
	.level = 0,
	.iconflags = 0
//              | GTK_ICON_LOOKUP_NO_SVG
//              | GTK_ICON_LOOKUP_FORCE_SVG
//              | GTK_ICON_LOOKUP_USE_BUILTIN
//              | GTK_ICON_LOOKUP_GENERIC_FALLBACK
//              | GTK_ICON_LOOKUP_FORCE_SIZE
	    ,
	.wmm = {
		.output = NULL,
		.create = &xde_create,
		.appmenu = &xde_appmenu,
		.rootmenu = &xde_rootmenu,
		.build = &xde_build,
		.ops = {
			.menu = &xde_menu,
			.directory = &xde_directory,
			.header = &xde_header,
			.separator = &xde_separator,
			.entry = &xde_entry,
			.alias = &xde_alias,
			.actions = &xde_actions,
			.pin = &xde_pin,
			},
		.wmmenu = &xde_wmmenu,
		.styles = &xde_styles,
		.themes = &xde_themes,
		.config = &xde_config,
		.wkspcs = &xde_wkspcs,
		.wmspec = &xde_wmspec,
		},
	.gtk = {
		.output = NULL,
		.create = &xde_gtk_create,
		.appmenu = &xde_gtk_appmenu,
		.rootmenu = &xde_gtk_rootmenu,
		.build = &xde_gtk_build,
		.ops = {
			.menu = &xde_gtk_menu,
			.directory = &xde_gtk_directory,
			.header = &xde_gtk_header,
			.separator = &xde_gtk_separator,
			.entry = &xde_gtk_entry,
			.alias = &xde_gtk_alias,
			.actions = &xde_gtk_actions,
			.pin = &xde_gtk_pin,
			},
		.wmmenu = &xde_gtk_wmmenu,
		.styles = &xde_gtk_styles,
		.themes = &xde_gtk_themes,
		.config = &xde_gtk_config,
		.wkspcs = &xde_gtk_wkspcs,
		.wmspec = &xde_gtk_wmspec,
		},
};

/** @} */

// vim: set sw=8 tw=100 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS foldmarker=@{,@} foldmethod=marker:
