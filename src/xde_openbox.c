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

/** @name OPENBOX
  */
/** @{ */

static char *
xde_wrap_icon(MenuContext *ctx, char *file)
{
	char *icon = file ? g_markup_printf_escaped(" icon=\"%s\"", file) : strdup("");

	free(file);
	return (icon);
}

static GList *
xde_create(MenuContext *ctx, Style style, const char *name)
{
	GMenuTreeDirectory *dir;
	GList *text = NULL;
	GList *entries = NULL;
	char *s;

	ctx->wmm.output = NULL;

	s = g_strdup_printf("%s\n\n", "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	ctx->wmm.output = g_list_append(ctx->wmm.output, s);
	s = g_strdup_printf("%s\n\n", "<openbox_menu xmlns=\"http://openbox.org/3.4/menu\">");
	ctx->wmm.output = g_list_append(ctx->wmm.output, s);

	if (!(dir = gmenu_tree_get_root_directory(ctx->tree))) {
		EPRINTF("could not get root directory\n");
		return (text);
	}
	xde_reset_indent(ctx, 0);
	xde_increase_indent(ctx);
	entries = ctx->wmm.ops.menu(ctx, dir);
	xde_decrease_indent(ctx);

	switch(style) {
	case StyleFullmenu:
	default:
		text = ctx->wmm.rootmenu(ctx, entries);
		break;
	case StyleAppmenu:
		if (!name)
			name = gmenu_tree_directory_get_name(dir);
		text = ctx->wmm.appmenu(ctx, entries, name);
		break;
	case StyleEntries:
		break;
	}
	text = g_list_concat(ctx->wmm.output, text);
	ctx->wmm.output = NULL;

	s = g_strdup_printf("\n%s\n", "</openbox_menu>");
	text = g_list_append(text, s);
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
	char *icon;
	char *s;

	icon = ctx->wmm.wrap(ctx, xde_get_icon2(ctx, "start-here", "folder"));
	s = g_strdup_printf("%s<menu id=\"%s Menu\" label=\"%s\"%s>\n",
			    ctx->indent, name, name, icon);
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	s = g_strdup_printf("%s</menu>\n", ctx->indent);
	text = g_list_append(text, s);

	free(icon);
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
	char *icon;
	char *s;

	ctx->wmm.output = g_list_concat(ctx->wmm.output, ctx->wmm.wmspec(ctx));

	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\">\n",
			    ctx->indent, "root-menu", "Openbox 3");
	text = g_list_append(text, s);

	text = g_list_concat(text, entries);

	xde_increase_indent(ctx);

	s = g_strdup_printf("%s<separator />\n", ctx->indent);
	text = g_list_append(text, s);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "openbox"));
	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\"%s />\n", ctx->indent, "Openbox",
			    "Openbox", icon);
	text = g_list_append(text, s);
	free(icon);

	if (options.filename) {
		icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-refresh"));
		s = g_strdup_printf("%s<item label=\"%s\"%s>\n", ctx->indent, "Refresh Menu",
				    icon);
		text = g_list_append(text, s);
		free(icon);
		s = g_strdup_printf("%s  <action name=\"Execute\">\n", ctx->indent);
		text = g_list_append(text, s);

		s = g_strdup_printf("%s    <command>%s %s</command>\n", ctx->indent,
				    "xde-menugen -format openbox3 -desktop OPENBOX -launch -o",
				    options.filename);
		text = g_list_append(text, s);

		s = g_strdup_printf("%s  </action>\n", ctx->indent);
		text = g_list_append(text, s);

		s = g_strdup_printf("%s</item>\n", ctx->indent);
		text = g_list_append(text, s);
	}

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-redo-ltr"));
	s = g_strdup_printf("%s<item label=\"%s\"%s>\n", ctx->indent, "Reload", icon);
	text = g_list_append(text, s);
	free(icon);
	s = g_strdup_printf("%s  <action name=\"Reconfigure\" />\n", ctx->indent);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s</item>\n", ctx->indent);
	text = g_list_append(text, s);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%s<item label=\"%s\"%s>\n", ctx->indent, "Restart", icon);
	text = g_list_append(text, s);
	free(icon);
	s = g_strdup_printf("%s  <action name=\"Restart\" />\n", ctx->indent);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s</item>\n", ctx->indent);
	text = g_list_append(text, s);

	s = g_strdup_printf("%s<separator />\n", ctx->indent);
	text = g_list_append(text, s);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s<item label=\"%s\"%s>\n", ctx->indent, "Exit", icon);
	text = g_list_append(text, s);
	free(icon);
	s = g_strdup_printf("%s  <action name=\"Exit\" />\n", ctx->indent);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s</item>\n", ctx->indent);
	text = g_list_append(text, s);

	xde_decrease_indent(ctx);

	s = g_strdup_printf("%s</menu>\n", ctx->indent);
	text = g_list_append(text, s);

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

	text = xde_build_simple(ctx, type, item);
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

	text = xde_menu_simple(ctx, menu);
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
xde_actions(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info)
{
	GList *text = NULL;

	text = xde_actions_simple(ctx, ent, info);
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
xde_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GList *text = NULL;

	text = g_list_append(text, g_strdup_printf("%s<separator />\n", ctx->indent));
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
	GMenuTreeDirectory *dir;
	GList *text = NULL;
	const char *name, *path;
	GIcon *gicon = NULL;
	char *icon = NULL, *s;
	char *esc;

	if (!(dir = gmenu_tree_header_get_directory(hdr)))
		return (text);

	name = gmenu_tree_directory_get_name(dir);

	esc = g_markup_escape_text(name, -1);

	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, gicon, "folder", "unknown",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = ctx->wmm.wrap(ctx, icon);

	s = g_strdup_printf("%s<separator label=\"%s\"%s />\n", ctx->indent, esc, icon);
	text = g_list_append(text, s);
	free(icon);
	g_free(esc);

	text = g_list_concat(text, ctx->wmm.ops.directory(ctx, dir));
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
	const char *name, *path;
	char *icon = NULL, *s;
	GIcon *gicon = NULL;
	char *esc;
	int level;

	name = gmenu_tree_directory_get_name(dir);

	esc = g_markup_escape_text(name, -1);

	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, gicon, "folder", "unknown",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = ctx->wmm.wrap(ctx, icon);

	level = xde_reset_indent(ctx, 0);
	s = g_strdup_printf("%s<menu id=\"%s Menu\" label=\"%s\"%s>\n", ctx->indent, esc, esc,
			    icon);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.menu(ctx, dir));
	s = g_strdup_printf("%s</menu> <!-- %s Menu -->\n\n", ctx->indent, esc);
	text = g_list_append(text, s);
	level = xde_reset_indent(ctx, level);

	ctx->wmm.output = g_list_concat(ctx->wmm.output, text);
	s = g_strdup_printf("%s<menu id=\"%s Menu\" label=\"%s\"%s />\n", ctx->indent, esc, esc,
			    icon);
	text = g_list_append(NULL, s);

	free(icon);
	g_free(esc);
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
	GDesktopAppInfo *info;
	GList *text = NULL;
	const char *name;
	char *esc1, *esc2, *cmd, *p;
	char *icon = NULL, *wrap, *s;
	GIcon *gicon = NULL;
	gboolean notify;
	char *wmclass, *appid;

	if (!(info = gmenu_tree_entry_get_app_info(ent)) || g_desktop_app_info_get_is_hidden(info)
	    || g_desktop_app_info_get_nodisplay(info) || !g_desktop_app_info_get_show_in(info, NULL)
	    || !g_app_info_should_show(G_APP_INFO(info)))
		return (text);
	name = g_app_info_get_name(G_APP_INFO(info));

	esc1 = g_markup_escape_text(name, -1);

	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	icon = xde_get_app_icon(ctx, info, gicon, "exec", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
				GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
	wrap = ctx->wmm.wrap(ctx, strdup(icon));

	notify = g_desktop_app_info_get_boolean(info, G_KEY_FILE_DESKTOP_KEY_STARTUP_NOTIFY);
	wmclass = g_desktop_app_info_get_string(info, G_KEY_FILE_DESKTOP_KEY_STARTUP_WM_CLASS);

	if ((appid = strdup(gmenu_tree_entry_get_desktop_file_id(ent)))
	    && (p = strstr(appid, ".desktop")))
		*p = '\0';

	if (options.launch) {
		cmd = g_strdup_printf("xdg-launch --pointer %s", appid);
	} else {
		cmd = xde_get_command(info, appid, icon);
	}

	esc2 = g_markup_escape_text(cmd, -1);

	s = g_strdup_printf("%s<item label=\"%s\"%s>\n", ctx->indent, esc1, wrap);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s  <action name=\"Execute\">\n", ctx->indent);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s    <command>%s</command>\n", ctx->indent, esc2);
	text = g_list_append(text, s);

	if (!options.launch && (notify || wmclass)) {
		/* don't put launch specifics if we are launching with xdg-launch */
		s = g_strdup_printf("%s    <startupnotify>\n", ctx->indent);
		text = g_list_append(text, s);
		if (notify) {
			s = g_strdup_printf("%s      <enabled>yes</enabled>\n", ctx->indent);
			text = g_list_append(text, s);
		}
		if (wmclass) {
			s = g_strdup_printf("%s      <wmclass>%s</wmclass>\n", ctx->indent,
					    wmclass);
			text = g_list_append(text, s);
		}
		s = g_strdup_printf("%s      <name>%s</name>\n", ctx->indent, esc1);
		text = g_list_append(text, s);
		if (icon) {
			s = g_strdup_printf("%s      <icon>%s</icon>\n", ctx->indent, icon);
			text = g_list_append(text, s);
		}
		s = g_strdup_printf("%s    </startupnotify>\n", ctx->indent);
		text = g_list_append(text, s);
	}

	s = g_strdup_printf("%s  </action>\n", ctx->indent);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s</item>\n", ctx->indent);
	text = g_list_append(text, s);

	free(wrap);
	free(icon);
	g_free(wmclass);
	free(appid);
	g_free(esc1);
	g_free(esc2);
	free(cmd);
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

	text = xde_alias_simple(ctx, als);
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
xde_action(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info, const char *action)
{
	GList *text = NULL;

	return (text);
}

static GtkMenuItem *
xde_gtk_action(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info, const char *action)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_action(ctx, ent, info, action);
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

	item = xde_gtk_common_pin(ctx);
	return (item);
}

static GList *
xde_wmmenu(MenuContext *ctx)
{
	GList *text = NULL;
	GList *xsessions, *xsession;
	char *icon;
	char *s;

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\"%s>\n", ctx->indent,
				    "Window Managers Menu", "Window Managers", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		char *esc1, *esc2, *cmd;
		GIcon *gicon = NULL;

		if (strncasecmp(xsess->key, ctx->name, strlen(ctx->name)) == 0)
			continue;
		if (ctx->stack)
			gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
		icon = xde_get_entry_icon(ctx, xsess->entry, gicon, "preferences-system-windows",
					  "metacity",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG);
		if (options.launch)
			cmd = g_strdup_printf("xdg-launch --pointer -X %s", xsess->key);
		else
			cmd = xde_get_command(xsess->info, xsess->key, icon);
		icon = ctx->wmm.wrap(ctx, icon);
		esc1 = g_markup_printf_escaped("%s", xsess->name);
		esc2 = g_markup_printf_escaped("%s", cmd);
		s = g_strdup_printf("%s<item label=\"%s\"%s>\n", ctx->indent, esc1, icon);
		text = g_list_append(text, s);
		s = g_strdup_printf("%s  <action name=\"Restart\">\n", ctx->indent);
		text = g_list_append(text, s);
		s = g_strdup_printf("%s    <command>%s</command>\n", ctx->indent, esc2);
		text = g_list_append(text, s);
		s = g_strdup_printf("%s  </action>\n", ctx->indent);
		text = g_list_append(text, s);
		s = g_strdup_printf("%s</item>\n", ctx->indent);
		text = g_list_append(text, s);
		g_free(esc2);
		g_free(esc1);
		g_free(icon);
		g_free(cmd);
	}
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s</menu>\n\n", ctx->indent);
	text = g_list_append(text, s);
	xde_free_xsessions(xsessions);
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
	char *icon;
	char *s;

	ctx->wmm.output = g_list_concat(ctx->wmm.output, ctx->wmm.wmmenu(ctx));

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "openbox"));
	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\"%s>\n",
			    ctx->indent, "Openbox", "Openbox", icon);
	text = g_list_append(text, s);
	free(icon);

	xde_increase_indent(ctx);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "preferences-desktop-display"));
	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\"%s />\n",
			    ctx->indent, "client-list-menu", "Desktops", icon);
	text = g_list_append(text, s);
	free(icon);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "preferences-system-windows"));
	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\"%s />\n",
			    ctx->indent, "client-list-combined-menu", "Windows", icon);
	text = g_list_append(text, s);
	free(icon);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\"%s />\n",
			    ctx->indent, "Window Managers Menu", "Window Managers", icon);
	text = g_list_append(text, s);
	free(icon);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "style"));
	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\"%s execute=\"%s\" />\n",
			    ctx->indent, "Themes Menu", "Themes", icon, "xde-style -m -t");
	text = g_list_append(text, s);
	free(icon);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "style"));
	s = g_strdup_printf("%s<menu id=\"%s\" label=\"%s\"%s execute=\"%s\" />\n",
			    ctx->indent, "Styles Menu", "Styles", icon, "xde-style -m");
	text = g_list_append(text, s);
	free(icon);

	xde_decrease_indent(ctx);

	s = g_strdup_printf("%s</menu>\n\n", ctx->indent);
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
	.name = "openbox",
	.format = "openbox",
	.wmname = "Openbox",
	.desktop = "OPENBOX",
	.version = VERSION,
	.styles = {
		.sysdir = "/usr/share/themes",
		.usrdir = "/.config/openbox/styles",
		.subdir = "",
		.fname = "/openbox-3/themerc",
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
		.wrap = &xde_wrap_icon,
		.create = &xde_create,
		.appmenu = &xde_appmenu,
		.rootmenu = &xde_rootmenu,
		.build = &xde_build,
		.ops = {
			.menu = &xde_menu,
			.actions = &xde_actions,
			.directory = &xde_directory,
			.header = &xde_header,
			.separator = &xde_separator,
			.entry = &xde_entry,
			.alias = &xde_alias,
			.action = &xde_action,
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
			.actions = &xde_gtk_actions,
			.directory = &xde_gtk_directory,
			.header = &xde_gtk_header,
			.separator = &xde_gtk_separator,
			.entry = &xde_gtk_entry,
			.alias = &xde_gtk_alias,
			.action = &xde_gtk_action,
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
