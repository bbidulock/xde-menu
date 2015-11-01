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

char *
xde_wrap_icon(char *file)
{
	char *icon;

	if (file) {
		icon = calloc(strlen(file) + 3, sizeof(*icon));
		strcpy(icon, "%");
		strcat(icon, file);
		strcat(icon, "%");
	} else
		icon = strdup("");
	free(file);
	return (icon);
}

static GList *
xde_create(MenuContext *ctx, Style style, const char *name)
{
	GMenuTreeDirectory *dir;
	GList *result = NULL;
	GList *entries = NULL;

	ctx->wmm.output = NULL;

	if (!(dir = gmenu_tree_get_root_directory(ctx->tree))) {
		EPRINTF("could not get root directory\n");
		return (result);
	}
	xde_reset_indent(ctx, 0);
	xde_increase_indent(ctx);
	entries = ctx->wmm.ops.menu(ctx, dir);
	xde_decrease_indent(ctx);

	if (!name)
		name = gmenu_tree_directory_get_name(dir);

	if (style == StyleFullmenu) {
		result = ctx->wmm.wmmenu(ctx);
		ctx->wmm.output = g_list_concat(ctx->wmm.output, result);
		result = ctx->wmm.wmspec(ctx);
		ctx->wmm.output = g_list_concat(ctx->wmm.output, result);
	}
	result = ctx->wmm.appmenu(ctx, entries, name);
	ctx->wmm.output = g_list_concat(ctx->wmm.output, result);

	if (style == StyleEntries) {
		ctx->wmm.output = g_list_concat(ctx->wmm.output, entries);
		return (ctx->wmm.output);
	}
	if (style == StyleSubmenu)
		entries = NULL;
	if (style != StyleAppmenu) {
		result = ctx->wmm.rootmenu(ctx, entries);
		ctx->wmm.output = g_list_concat(ctx->wmm.output, result);
	}
	result = ctx->wmm.output;
	ctx->wmm.output = NULL;
	return (result);
}

static GtkMenu *
xde_gtk_create(MenuContext *ctx, Style style, const char *name)
{
	return xde_gtk_create_simple(ctx, style, name);
}

static GList *
xde_appmenu(MenuContext *ctx, GList *entries, const char *name)
{
	GList *text = NULL;
	char *s, *esc;

	esc = xde_character_escape(name, '"');
	s = strdup("DestroyMenu xdg_menu\n");
	text = g_list_append(text, s);
	s = g_strdup_printf("AddToMenu xdg_menu \"%s\" Title\n", esc);
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	free(esc);
	return (text);
}

static GtkMenu *
xde_gtk_appmenu(MenuContext *ctx, GtkMenu *entries, const char *name)
{
	GtkWidget *image, *item, *menu;
	GdkPixbuf *pixbuf;
	char *icon;

	menu = gtk_menu_new();
	item = gtk_image_menu_item_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), GTK_WIDGET(entries));
	if (name)
		gtk_menu_item_set_label(GTK_MENU_ITEM(item), name);
	if ((icon = xde_get_icon2(ctx, "start-here", "folder")) &&
	    (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	free(icon);
	gtk_menu_append(menu, item);
	return (GTK_MENU(menu));
}

static GList *
xde_rootmenu(MenuContext *ctx, GList *entries)
{
	GList *text = NULL;
	char *icon, *s;

	s = strdup("DestroyMenu Utilities\n");
	text = g_list_append(text, s);
	s = strdup("AddToMenu Utilities \"Root Menu\" Title\n");
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	icon = xde_wrap_icon(xde_get_icon(ctx, "fvwm"));
	s = g_strdup_printf("+ \"FVWM%s\" Popup FVWMmenu\n", icon);
	text = g_list_append(text, s);
	free(icon);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("+ \"Restart%s\" Restart\n", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("+ \"Quit%s\" Quit\n", icon);
	text = g_list_append(text, s);
	free(icon);
	return (text);
}

static GtkMenu *
xde_gtk_rootmenu(MenuContext *ctx, GtkMenu *entries)
{
	GtkMenu *menu = NULL;

	return (menu);
}

static GList *
xde_build(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
{
	return xde_build_simple(ctx, type, item);
}

static GtkMenuItem *
xde_gtk_build(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
{
	return xde_gtk_build_simple(ctx, type, item);
}

static GList *
xde_menu(MenuContext *ctx, GMenuTreeDirectory *menu)
{
	return xde_menu_simple(ctx, menu);
}

static GtkMenu *
xde_gtk_menu(MenuContext *ctx, GMenuTreeDirectory *menu)
{
	return xde_gtk_menu_simple(ctx, menu);
}

static GList *
xde_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GList *text = NULL;
	char *s;

	s = strdup("+ \"\" Nop\n");
	text = g_list_append(text, s);
	return (text);
}

static GtkMenuItem *
xde_gtk_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GtkMenuItem *item = NULL;

	return (item);
}

static GList *
xde_header(MenuContext *ctx, GMenuTreeHeader *hdr)
{
	GMenuTreeDirectory *dir;
	GList *text = NULL;
	const char *name, *path;
	char *icon = NULL, *s, *esc1;

	if (!(dir = gmenu_tree_header_get_directory(hdr)))
		return (text);
	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, '"');
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, "folder", "unknown",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = xde_wrap_icon(icon);
	s = g_strdup_printf("+ \"%s%s\" Nop\n", esc1, icon);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.directory(ctx, dir));
	free(icon);
	free(esc1);
	return (text);
}

static GtkMenuItem *
xde_gtk_header(MenuContext *ctx, GMenuTreeHeader *hdr)
{
	GtkMenuItem *item = NULL;

	return (item);
}

static GList *
xde_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GList *text = NULL;
	const char *name, *path;
	char *esc1, *icon = NULL, *s, *id, *p, *q;

	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, '"');
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file;

		file = g_key_file_new();
		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, "folder", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
				GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = xde_wrap_icon(icon);

	id = g_strdup_printf("/XDG/%s", name);
	for (p = q = id; *p; p++)
		if (!isspace(*p))
			*q++ = *p;
	*q = '\0';
	s = g_strdup_printf("DestroyMenu %s\n", id);
	text = g_list_append(text, s);
	s = g_strdup_printf("AddToMenu %s \"%s\" Title\n", id, esc1);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.menu(ctx, dir));
	ctx->wmm.output = g_list_concat(ctx->wmm.output, text);
	text = NULL;
	s = g_strdup_printf("+ \"%s%s\" Popup %s\n", esc1, icon, id);
	text = g_list_append(text, s);
	return (text);
}

static GtkMenuItem *
xde_gtk_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GtkMenuItem *item = NULL;

	return (item);
}

static GList *
xde_entry(MenuContext *ctx, GMenuTreeEntry *ent)
{
	GDesktopAppInfo *info;
	GList *text = NULL;
	const char *name;
	char *esc1, *cmd, *p;
	char *icon = NULL, *s;
	char *appid;

	info = gmenu_tree_entry_get_app_info(ent);
	name = g_app_info_get_name(G_APP_INFO(info));
	esc1 = xde_character_escape(name, '"');
	if ((appid = strdup(gmenu_tree_entry_get_desktop_file_id(ent)))
	    && (p = strstr(appid, ".desktop")))
		*p = '\0';
	icon = xde_get_app_icon(ctx, info, "exec", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
				GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
	if (options.launch) {
		cmd = g_strdup_printf("xdg-launch --pointer %s", appid);
	} else {
		cmd = xde_get_command(info, appid, icon);
	}
	icon = xde_wrap_icon(icon);
	s = g_strdup_printf("+ \"%s%s\" Exec exec %s\n", esc1, icon, cmd);
	text = g_list_append(text, s);
	free(appid);
	free(icon);
	free(esc1);
	free(cmd);
	return (text);
}

static GtkMenuItem *
xde_gtk_entry(MenuContext *ctx, GMenuTreeEntry *ent)
{
	GtkMenuItem *item = NULL;

	return (item);
}

static GList *
xde_alias(MenuContext *ctx, GMenuTreeAlias *als)
{
	return xde_alias_simple(ctx, als);
}

static GtkMenuItem *
xde_gtk_alias(MenuContext *ctx, GMenuTreeAlias *als)
{
	GtkMenuItem *item = NULL;

	return (item);
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

	return (item);
}

static GList *
xde_wmmenu(MenuContext *ctx)
{
	GList *text = NULL;
	GList *xsessions, *xsession;
	int gotone = FALSE;
	char *icon;
	char *s;

	s = strdup("DestroyMenu WindowManagers\n");
	text = g_list_append(text, s);
	s = strdup("AddToMenu WindowManagers \"Window Managers\" Title\n");
	text = g_list_append(text, s);

	xde_increase_indent(ctx);

	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		char *esc1, *exec;

		if (strncasecmp(xsess->key, "fvwm", 4) == 0)
			continue;

		esc1 = xde_character_escape(xsess->name, '"');
		icon = xde_get_entry_icon(ctx, xsess->entry, "preferences-system-windows",
					  "metacity",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		icon = xde_wrap_icon(icon);

		if (options.launch) {
			exec = g_strdup_printf("xdg-launch -X %s", xsess->key);
		} else {
			exec = g_key_file_get_string(xsess->entry,
						     G_KEY_FILE_DESKTOP_GROUP,
						     G_KEY_FILE_DESKTOP_KEY_EXEC, NULL);
			exec = exec ? strdup(exec) : strdup("/usr/bin/true");
		}
		s = g_strdup_printf("+ \"%s%s\" Restart %s\n", esc1, icon, exec);
		text = g_list_append(text, s);
		gotone = TRUE;
		free(exec);
		free(icon);
		free(esc1);
	}
	if (gotone)
		text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("+ \"%s%s\" Restart\n", "Restart", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("+ \"%s%s\" Quit\n", "Quit", icon);
	text = g_list_append(text, s);
	free(icon);
	return (text);
}

static GtkMenuItem *
xde_gtk_wmmenu(MenuContext *ctx)
{
	GtkWidget *menu = NULL, *image, *item;
	GtkMenuItem *result = NULL;
	GList *xsessions, *xsession;
	GdkPixbuf *pixbuf;
	char *icon;

	menu = gtk_menu_new();
	result = GTK_MENU_ITEM(gtk_image_menu_item_new());
	gtk_menu_item_set_submenu(result, menu);
	gtk_menu_item_set_label(result, "Window Managers");
	if ((icon = xde_get_icon(ctx, "gtk-quit")) &&
	    (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(result), image);
	free(icon);
	item = gtk_menu_item_new();
	gtk_menu_append(menu, item);
	gtk_menu_item_set_label(GTK_MENU_ITEM(item), "Restart");
	if ((icon = xde_get_icon(ctx, "gtk-refresh")) &&
	    (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(result), image);
	free(icon);
	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		char *label;

		if (strncasecmp(xsess->key, "blackbox", strlen("blackbox")) == 0)
			continue;
		item = gtk_menu_item_new();
		gtk_menu_append(menu, item);
		label = g_strdup_printf("Start %s", xsess->name);
		gtk_menu_item_set_label(GTK_MENU_ITEM(item), label);
		if ((icon = xde_get_entry_icon(ctx, xsess->entry, "preferences-system-windows",
					       "metacity",
					       GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					       GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG))
		    && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL))
		    && (image = gtk_image_new_from_pixbuf(pixbuf)))
			gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
		free(icon);
		free(label);
	}
	return (result);
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

	return (item);
}

static GList *
xde_wmspec(MenuContext *ctx)
{
	GList *text = NULL;
	char *s;

	s = strdup("DestroyMenu FVWMmenu\n");
	text = g_list_append(text, s);
	s = strdup("AddToMenu FVWMmenu \"FVWM\" Title\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Modules%mini.modules.xpm%\" Popup Module-Popup\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Settings%mini.desktop.xpm%\" Popup Settings\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Documents%mini.books.xpm%\" Popup Documents\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Screen Saver%mini.display.xpm%\" Popup Screen\n");
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	if (options.filename) {
		s = g_strdup_printf
		    ("+ \"Refresh &Menu%%mini.turn.xpm%%\" Exec xdg-menugen -format fvwm -desktop FVWM -o %s\n",
		     options.filename);
		text = g_list_append(text, s);
	}
	s = strdup("+ \"&Restart%mini.turn.xpm%\" Popup Restart\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Quit FVWM%mini.stop.xpm%\" FvwmForm FvwmForm-QuitVerify\n\n");
	text = g_list_append(text, s);

	s = strdup("DestroyMenu StartMenu\n");
	text = g_list_append(text, s);
	s = strdup("AddToMenu StartMenu@side.fvwm2.xpm@^black^\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Applications%programs.xpm%\" Popup xdg_menu\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Shells%shells.xpm%\" Popup Shells\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Programs%programs.xpm%\" Popup Programs\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Documents%documents.xpm%\" Popup Documents\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Settings%settings.xpm%\" Popup Settings\n");
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	s = strdup("+ \"&Modules%modules.xpm%\" Popup Module-Popup\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Find%find1.xpm%\" FvwmScript FvwmScript-Find\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Help%help.xpm%\" Exec exec xman\n");
	text = g_list_append(text, s);
	s = strdup("+ \"&Run%run.xpm%\" Exec exec xde-run\n");
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	s = strdup("+ \"&Screen Saver%screen.xpm%\" Popup Screen\n");
	text = g_list_append(text, s);
	s = strdup("+ \"Shut &Down%shutdown.xpm%\" Module FvwmScript FvwmScript-Quit\n");
	text = g_list_append(text, s);
	return (text);
}

static GtkMenuItem *
xde_gtk_wmspec(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	return (item);
}

MenuContext xde_menu_ops = {
	.name = "fvwm",
	.format = "fvwm",
	.desktop = "FVWM",
	.version = VERSION,
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
			.pin = &xde_pin,
			},
		.wmmenu = &xde_wmmenu,
		.themes = &xde_themes,
		.styles = &xde_styles,
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
			.pin = &xde_gtk_pin,
			},
		.wmmenu = &xde_gtk_wmmenu,
		.themes = &xde_gtk_themes,
		.styles = &xde_gtk_styles,
		.config = &xde_gtk_config,
		.wkspcs = &xde_gtk_wkspcs,
		.wmspec = &xde_gtk_wmspec,
		},
};
