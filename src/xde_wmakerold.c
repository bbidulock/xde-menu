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

static GList *
xde_create(MenuContext *ctx, Style style, const char *name)
{
	return xde_create_simple(ctx, style, name);
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
	char *s;

	s = strdup("\"● Root Menu\" MENU\n");
	text = g_list_append(text, s);
	s = strdup("\"Run...\" SHEXEC \"%A(Run,Type Command:)\"\n");
	text = g_list_append(text, s);
	s = strdup("\"Gvim\" SHORTCUT \"Control+Mod1+v\" SHEXEC \"gvim -geometry 120x142\"\n");
	text = g_list_append(text, s);
	s = strdup("\"Gvim (wilbur)\" SHORTCUT \"Control+Shift+Mod1+v\" SHEXEC \"ssh -f wilbur gvim -geometry 120x100\"\n");
	text = g_list_append(text, s);
	s = strdup("\"Rxvt\" SHORTCUT \"Control+Mod1+r\" SHEXEC \"rxvt -ls -fn 6x10 -fb 6x10 -geometry 120x116 -sl 10000 +sb\"\n");
	text = g_list_append(text, s);
	s = strdup("\"Terminal\" SHORTCUT \"Control+Mod1+t\" SHEXEC \"xterm-wrapper\"\n");
	text = g_list_append(text, s);
	s = strdup("\"XTerm\" SHORTCUT \"Control+Mod1+x\" SHEXEC \"xterm -ls -fn 6x10 -fb 6x10 -geometry 120x116 -sl 15000\"\n");
	text = g_list_append(text, s);
	s = strdup("\"XTerm Tiny\" SHORTCUT \"Control+Mod1+s\" SHEXEC \"xterm -ls -fn -schumacher-clean-medium-r-normal--8-80-75-75-c-50-iso646.1991-irv -fb -schumacher-clean-medium-r-bold--8-80-75-75-c-50-iso646.1991-irv -geometry 146x145 -sl 15000\"\n");
	text = g_list_append(text, s);
	s = strdup("\"XTerm Small\" SHORTCUT \"Control+Mod1+y\" SHEXEC \"xterm -ls -fn -schumacher-clean-medium-r-normal--8-80-75-75-c-60-iso646.1991-irv -fb -schumacher-clean-bold-r-normal--8-80-75-75-c-60-iso646.1991-irv -geometry 120x145 -sl 15000\"\n");
	text = g_list_append(text, s);
	s = strdup("\"XTerm Large\" SHORTCUT \"Control+Mod1+l\" SHEXEC \"xterm -ls -fn 6x13 -fb 6x13bold -geometry 120x89 -sl 15000\"\n");
	text = g_list_append(text, s);
	s = strdup("\"XTerm Big\" SHORTCUT \"Control+Mod1+b\" SHEXEC \"xterm -ls -fn 7x13 -fb 7x13bold -geometry 104x89 -sl 15000\"\n");
	text = g_list_append(text, s);
	s = strdup("\"XTerm Huge\" SHORTCUT \"Control+Mod1+h\" SHEXEC \"xterm -ls -fn 9x15 -fb 9x15bold -geometry 81x77 -sl 15000\"\n");
	text = g_list_append(text, s);

	text = g_list_concat(text, entries);

	s = strdup("\"● Screen\" MENU\n");
	text = g_list_append(text, s);
	s = strdup("  \"● Locking\" MENU\n");
	text = g_list_append(text, s);
	s = strdup("    \"Lock Screen (XScreenSaver)\" SHEXEC /usr/bin/xscreensaver-command -lock\n");
	text = g_list_append(text, s);
	s = strdup("    \"Lock Screen (slock)\" SHEXEC /usr/bin/slock\n");
	text = g_list_append(text, s);
	s = strdup("  \"● Locking\" END\n");
	text = g_list_append(text, s);
	s = strdup("  \"● Saving\" MENU\n");
	text = g_list_append(text, s);
	s = strdup("    \"Activate ScreenSaver (Next)\" SHEXEC /usr/bin/xscreensaver-command -next\n");
	text = g_list_append(text, s);
	s = strdup("    \"Activate ScreenSaver (Prev)\" SHEXEC /usr/bin/xscreensaver-command -prev\n");
	text = g_list_append(text, s);
	s = strdup("    \"Activate ScreenSaver (Rand)\" SHEXEC /usr/bin/xscreensaver-command -activate\n");
	text = g_list_append(text, s);
	s = strdup("    \"Demo Screen Hacks\" SHEXEC /usr/bin/xscreensaver-command -demo\n");
	text = g_list_append(text, s);
	s = strdup("    \"Disable XScreenSaver\" SHEXEC /usr/bin/xscreensaver-command -exit\n");
	text = g_list_append(text, s);
	s = strdup("    \"Enable XScreenSaver\" SHEXEC /usr/bin/xscreensaver\n");
	text = g_list_append(text, s);
	s = strdup("    \"Reinitialize XScreenSaver\" SHEXEC /usr/bin/xscreensaver-command -restart\n");
	text = g_list_append(text, s);
	s = strdup("    \"ScreenSaver Preferences\" SHEXEC /usr/bin/xscreensaver-command -prefs\n");
	text = g_list_append(text, s);
	s = strdup("  \"● Saving\" END\n");
	text = g_list_append(text, s);
	s = strdup("\"● Screen\" END\n");
	text = g_list_append(text, s);
	s = strdup("\"● Window Maker\" MENU\n");
	text = g_list_append(text, s);
	s = strdup("  \"Info Panel ...\" INFO_PANEL\n");
	text = g_list_append(text, s);
	s = strdup("  \"Legal Panel ...\" LEGAL_PANEL\n");
	text = g_list_append(text, s);
	s = strdup("  \"Preferences\" EXEC WPrefs\n");
	text = g_list_append(text, s);

	if (options.filename) {
		s = g_strdup_printf("  \"Refresh Menu\" SHEXEC xdg-menugen -format wmakerold -desktop WMAKER -launch -o %s\n", options.filename);
		text = g_list_append(text, s);
	}

	s = strdup("  \"Refresh screen\" REFRESH\n");
	text = g_list_append(text, s);
	s = strdup("  \"Restart\" RESTART\n");
	text = g_list_append(text, s);
	s = strdup("\"● Window Maker\" END\n");
	text = g_list_append(text, s);

	text = g_list_concat(text, ctx->wmm.wmmenu(ctx));

	s = strdup("\"● WorkSpace\" MENU\n");
	text = g_list_append(text, s);
	s = strdup("  \"Appearance\" OPEN_MENU appearance.menu\n");
	text = g_list_append(text, s);
	s = strdup("  \"Arrange Icons\" ARRANGE_ICONS\n");
	text = g_list_append(text, s);
	s = strdup("  \"Clear Session\" CLEAR_SESSION\n");
	text = g_list_append(text, s);
	s = strdup("  \"Hide Others\" HIDE_OTHERS\n");
	text = g_list_append(text, s);
	s = strdup("  \"Save Session\" SAVE_SESSION\n");
	text = g_list_append(text, s);
	s = strdup("  \"Show All\" SHOW_ALL\n");
	text = g_list_append(text, s);
	s = strdup("  \"Workspaces\" WORKSPACE_MENU\n");
	text = g_list_append(text, s);
	s = strdup("\"● WorkSpace\" END\n");
	text = g_list_append(text, s);
	s = strdup("\"Exit\" EXIT\n");
	text = g_list_append(text, s);
	s = strdup("\"Exit Session\" SHUTDOWN\n");
	text = g_list_append(text, s);

	s = strdup("\"● Root Menu\" END\n");
	text = g_list_append(text, s);

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

	return (text);
}

static GtkMenuItem *
xde_gtk_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GtkMenuItem *item = NULL;

	item = GTK_MENU_ITEM(gtk_separator_menu_item_new());
	return (item);
}

static GList *
xde_header(MenuContext *ctx, GMenuTreeHeader *hdr)
{
	GMenuTreeDirectory *dir;
	GList *text = NULL;

	if (!(dir = gmenu_tree_header_get_directory(hdr)))
		return (text);
	text = g_list_concat(text, ctx->wmm.ops.directory(ctx, dir));
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
	const char *name;
	char *esc1, *s;

	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, '"');
	s = g_strdup_printf("%s\"● %s\" MENU\n", ctx->indent, esc1);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.menu(ctx, dir));
	s = g_strdup_printf("%s\"● %s\" END\n", ctx->indent, esc1);
	text = g_list_append(text, s);
	free(esc1);
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
	char *s, *icon = NULL;
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
	s = g_strdup_printf("%s\"%s\" SHEXEC %s\n", ctx->indent, esc1, cmd);
	text = g_list_append(text, s);
	free(icon);
	free(appid);
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

	item = GTK_MENU_ITEM(gtk_tearoff_menu_item_new());
	return (item);
}

static GList *
xde_wmmenu(MenuContext *ctx)
{
	GList *text = NULL;
	GList *xsessions, *xsession;
	char *s;

	s = strdup("\"● Window Managers\" MENU\n");
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		char *esc1;

		if (strncasecmp(xsess->key, "fluxbox", strlen("fluxbox")) == 0)
			continue;
		esc1 = xde_character_escape(xsess->name, '"');
		s = g_strdup_printf("%s\"%s\" RESTART xdg-launch --pointer -X %s\n",
				ctx->indent, esc1, xsess->key);
		text = g_list_append(text, s);
		free(esc1);
	}
	xde_free_xsessions(xsessions);
	xde_decrease_indent(ctx);
	s = strdup("\"● Window Managers\" END\n");
	text = g_list_append(text, s);
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

	return (text);
}

static GtkMenuItem *
xde_gtk_wmspec(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	return (item);
}

MenuContext xde_menu_ops = {
	.name = "wmaker",
	.format = "wmakerold",
	.desktop = "WMAKER",
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
