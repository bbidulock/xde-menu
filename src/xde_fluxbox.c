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

/** @name FLUXBOX
  */
/** @{ */

static char *
xde_wrap_icon(MenuContext *ctx, char *file)
{
	char *icon;

	if (strcmp(ctx->name, "blackbox") && strcmp(ctx->name, "waimea")) {
		if (file) {
			icon = calloc(strlen(file) + 4, sizeof(*icon));
			strcpy(icon, " <");
			strcat(icon, file);
			strcat(icon, ">");
		} else
			icon = strdup("");
	} else
		icon = strdup("");
	free(file);
	return (icon);
}

static GList *
xde_create(MenuContext *ctx, Style style, const char *name)
{
	GList *text = NULL;

	text = xde_create_simple(ctx, style, name);
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
	char *esc1, *esc2;
	char *icon;

	esc1 = xde_character_escape(name, ')');
	esc2 = xde_character_escape(name, '}');
	icon = ctx->wmm.wrap(ctx, xde_get_icon2(ctx, "start-here", "folder"));

	text = g_list_append(text, g_strdup_printf("[submenu] (%s) {%s Menu}%s\n", esc1, esc2, icon));
	text = g_list_concat(text, entries);
	text = g_list_append(text, g_strdup_printf("[end]\n"));

	free(icon);
	free(esc1);
	free(esc2);
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

	s = g_strdup_printf("%s[begin] (%s)\n", ctx->indent, ctx->wmname);
	text = g_list_append(text, s);
	if (!strcmp(ctx->name, "fluxbox")) {
		s = g_strdup_printf("%s%s\n", ctx->indent, "[encoding] {UTF-8}");
		text = g_list_append(text, s);
	}
	text = g_list_concat(text, entries);
	xde_increase_indent(ctx);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));

	text = g_list_concat(text, ctx->wmm.wmspec(ctx));

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gnome-lockscreen"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Lock screen) {xlock}", icon);
	text = g_list_append(text, s);
	free(icon);
	if (!strcmp(ctx->name, "fluxbox")) {
		icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-execute"));
		s = g_strdup_printf("%s%s%s\n", ctx->indent, "[commanddialog] (Fluxbox Command)", icon);
		text = g_list_append(text, s);
		free(icon);
	}
	if (strcmp(ctx->name, "waimea")) {
		icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-redo-ltr"));
		s = g_strdup_printf("%s%s%s\n", ctx->indent, "[reconfig] (Reload config)", icon);
		text = g_list_append(text, s);
		free(icon);
	}
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[restart] (Restart) {}", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "help-about"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (About) {(fluxbox -v; fluxbox -info | sed 1d) | gxmessage -file - -center}", icon);
	text = g_list_append(text, s);
	free(icon);
	if (options.filename) {
		icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-refresh"));
		s = g_strdup_printf("%s%s%s%s%s%s%s%s%s\n", ctx->indent, "[exec] (Refresh Menu) {xde-menugen -format", ctx->format, " -desktop ", ctx->desktop, " -launch -o ", options.filename, "}", icon);
		text = g_list_append(text, s);
		free(icon);
	}
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exit] (Exit)", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_decrease_indent(ctx);
	if (!strcmp(ctx->name, "fluxbox")) {
		s = g_strdup_printf("%s%s\n", ctx->indent, "[endencoding]");
		text = g_list_append(text, s);
	}
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
	if (!strcmp(ctx->name, "waimea")) {
		s = g_strdup_printf("%s%s\n", ctx->indent, "[include] (~/.waimea/winmenu)");
		text = g_list_append(text, s);
	}
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
xde_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GList *text = NULL;
	char *s;

	if (!strcmp(ctx->name, "blackbox"))
		s = g_strdup_printf("%s%s\n", ctx->indent, "[nop] (————————————) {}");
	else if (!strcmp(ctx->name, "fluxbox"))
		s = g_strdup_printf("%s%s\n", ctx->indent, "[separator]");
	else if (!strcmp(ctx->name, "openbox"))
		s = g_strdup_printf("%s%s\n", ctx->indent, "[separator]");
	else if (!strcmp(ctx->name, "waimea"))
		s = g_strdup_printf("%s%s\n", ctx->indent, "[nop] (--------------------------------) {}");
	else if (!strcmp(ctx->name, "perlpanel"))
		s = g_strdup_printf("%s%s\n", ctx->indent, "[separator]");
	else
		s = g_strdup_printf("%s%s\n", ctx->indent, "[nop] (--------------------------------) {}");
	text = g_list_append(text, s);
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
	char *esc1, *esc2, *s;
	GIcon *gicon = NULL;
	char *icon = NULL;

	if (!(dir = gmenu_tree_header_get_directory(hdr)))
		return (text);
	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, ')');
	esc2 = xde_character_escape(name, '}');
	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, gicon, "folder", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG|
				GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = ctx->wmm.wrap(ctx, icon);
	s = g_strdup_printf("%s[nop] (%s) {%s}%s\n", ctx->indent, esc1, esc2, icon);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.directory(ctx, dir));
	free(icon);
	free(esc2);
	free(esc1);
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
	char *esc1, *esc2;
	GIcon *gicon = NULL;
	char *icon = NULL;

	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, ')');
	esc2 = xde_character_escape(name, '}');
	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, gicon, "folder", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = ctx->wmm.wrap(ctx, icon);
	text = g_list_append(text, g_strdup_printf("%s%s (%s) {%s Menu}%s\n", ctx->indent, "[submenu]", esc1, esc2, icon));
	text = g_list_concat(text, ctx->wmm.ops.menu(ctx, dir));
	text = g_list_append(text, g_strdup_printf("%s[end]\n", ctx->indent));
	free(icon);
	free(esc1);
	free(esc2);
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
	char *s, *icon = NULL;
	GIcon *gicon = NULL;
	char *appid;

	if (!(info = gmenu_tree_entry_get_app_info(ent)) || g_desktop_app_info_get_is_hidden(info)
	    || g_desktop_app_info_get_nodisplay(info) || !g_desktop_app_info_get_show_in(info, NULL)
	    || !g_app_info_should_show(G_APP_INFO(info)))
		return (text);
	name = g_app_info_get_name(G_APP_INFO(info));
	esc1 = xde_character_escape(name, ')');

	if ((appid = strdup(gmenu_tree_entry_get_desktop_file_id(ent)))
	    && (p = strstr(appid, ".desktop")))
		*p = '\0';

	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	icon = xde_get_app_icon(ctx, info, gicon, "exec", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
				GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);

	if (options.launch) {
		cmd = g_strdup_printf("xdg-launch --pointer %s", appid);
	} else {
		cmd = xde_get_command(info, appid, icon);
	}
	esc2 = xde_character_escape(cmd, '}');
	icon = ctx->wmm.wrap(ctx, icon);
	s = g_strdup_printf("%s[exec] (%s) {%s}%s\n", ctx->indent, esc1, esc2, icon);
	text = g_list_append(text, s);
	free(icon);
	free(appid);
	free(esc1);
	free(esc2);
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
	s = g_strdup_printf("%s[submenu] (Window Managers) {Window Managers}%s\n",
			    ctx->indent, icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%s[restart] (Restart)%s\n", ctx->indent, icon);
	text = g_list_append(text, s);
	free(icon);
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
				"metacity", GET_ENTRY_ICON_FLAG_XPM|GET_ENTRY_ICON_FLAG_PNG);
		if (options.launch)
			cmd = g_strdup_printf("xdg-launch --pointer -X %s", xsess->key);
		else
			cmd = xde_get_command(xsess->info, xsess->key, icon);
		esc1 = xde_character_escape(xsess->name, ')');
		esc2 = xde_character_escape(cmd, '}');
		icon = ctx->wmm.wrap(ctx, icon);
		s = g_strdup_printf("%s[restart] (Start %s) {%s}%s\n", ctx->indent, esc1, esc2, icon);
		text = g_list_append(text, s);
		free(icon);
		free(esc2);
		free(esc1);
		free(cmd);
	}
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s[end]\n", ctx->indent);
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
	static const char *sysfmt = "%s[exec] (%s) {xde-style -s -t -r -y '%s'}%s\n";
	static const char *usrfmt = "%s[exec] (%s) {xde-style -s -t -r -u '%s'}%s\n";
	static const char *mixfmt = "%s[exec] (%s) {xde-style -s -t -r '%s'}%s\n";
	char *sysdir, *usrdir;
	GList *text = NULL, *sysent, *usrent;
	char *s, *icon;

	sysdir = g_strdup_printf("%s%s", ctx->styles.sysdir, ctx->styles.subdir);
	usrdir = g_strdup_printf("%s%s%s", getenv("HOME"), ctx->styles.usrdir, ctx->styles.subdir);

	sysent = xde_common_get_styles(ctx, sysdir, ctx->styles.fname, ctx->styles.suffix);
	usrent = xde_common_get_styles(ctx, usrdir, ctx->styles.fname, ctx->styles.suffix);

	g_free(sysdir);
	g_free(usrdir);

	if (!sysent && !usrent)
		return (text);

	(void) mixfmt;

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "style"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Styles) {Choose a style...}", icon);
	text = g_list_append(text, s);
	if (sysent) {
		GList *style;

		xde_increase_indent(ctx);
		for (style = sysent; style; style = style->next) {
			char *name = style->data;

			style->data = g_strdup_printf(sysfmt, ctx->indent, name, name, icon);
			free(name);
		}
		xde_decrease_indent(ctx);
		text = g_list_concat(text, sysent);
	}
	if (sysent && usrent) {
		xde_increase_indent(ctx);
		text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
		xde_decrease_indent(ctx);
	}
	if (usrent) {
		GList *style;

		xde_increase_indent(ctx);
		for (style = usrent; style; style = style->next) {
			char *name = style->data;

			style->data = g_strdup_printf(usrfmt, ctx->indent, name, name, icon);
			free(name);
		}
		xde_decrease_indent(ctx);
		text = g_list_concat(text, usrent);
	}
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
	free(icon);
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
	static const char *sysfmt = "%s[exec] (%s) {xde-style -s -t -r -y '%s'}%s\n";
	static const char *usrfmt = "%s[exec] (%s) {xde-style -s -t -r -u '%s'}%s\n";
	static const char *mixfmt = "%s[exec] (%s) {xde-style -s -t -r '%s'}%s\n";
	char *sysdir, *usrdir;
	GList *text = NULL, *sysent, *usrent;
	char *s, *icon;

	sysdir = g_strdup_printf("%s%s", ctx->styles.sysdir, ctx->styles.subdir);
	usrdir = g_strdup_printf("%s%s%s", getenv("HOME"), ctx->styles.usrdir, ctx->styles.subdir);

	sysent = xde_common_get_styles(ctx, sysdir, ctx->styles.fname, ctx->styles.suffix);
	usrent = xde_common_get_styles(ctx, usrdir, ctx->styles.fname, ctx->styles.suffix);

	sysent = xde_common_find_themes(ctx, sysent);
	usrent = xde_common_find_themes(ctx, usrent);

	g_free(sysdir);
	g_free(usrdir);

	if (!sysent && !usrent)
		return (text);

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "style"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Themes) {Choose a theme...}", icon);
	text = g_list_append(text, s);

	(void) mixfmt;

	if (sysent) {
		GList *theme;

		xde_increase_indent(ctx);
		for (theme = sysent; theme; theme = theme->next) {
			char *name = theme->data;

			theme->data = g_strdup_printf(sysfmt, ctx->indent, name, name, icon);
			free(name);
		}
		xde_decrease_indent(ctx);
		text = g_list_concat(text, sysent);
	}
	if (sysent && usrent) {
		xde_increase_indent(ctx);
		text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
		xde_decrease_indent(ctx);
	}
	if (usrent) {
		GList *theme;

		xde_increase_indent(ctx);
		for (theme = usrent; theme; theme = theme->next) {
			char *name = theme->data;

			theme->data = g_strdup_printf(usrfmt, ctx->indent, name, name, icon);
			free(name);
		}
		xde_decrease_indent(ctx);
		text = g_list_concat(text, usrent);
	}

	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
	free(icon);
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
	char *icon, *s;
	GList *text = NULL;

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "preferences-desktop"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[config] (Configure)", icon);
	text = g_list_append(text, s);
	free(icon);
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
	char *icon, *s;

	if (strcmp(ctx->name, "waimea")) {
		icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "preferences-desktop-display"));
		s = g_strdup_printf("%s%s%s\n", ctx->indent, "[workspaces] (Workspace List)", icon);
		text = g_list_append(text, s);
		free(icon);
	}
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

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, ctx->name));
	s = g_strdup_printf("%s[submenu] (%s)%s\n", ctx->indent, ctx->wmname, icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	if (!strcmp(ctx->name, "waimea")) {
		s = g_strdup_printf("%s%s\n", ctx->indent, "[submenu] (Tools)");
		text = g_list_append(text, s);
		xde_increase_indent(ctx);
		s = g_strdup_printf("%s%s\n", ctx->indent,
				    "[exec] (Window name) {xprop WM_CLASS|cut -d \\\" -f 2|gxmessage -file - -center}");
		text = g_list_append(text, s);
		s = g_strdup_printf("%s%s\n", ctx->indent,
				    "[exec] (Screenshot - JPG) {import screenshot.jpg && display -resize 50% screenshot.jpg}");
		text = g_list_append(text, s);
		s = g_strdup_printf("%s%s\n", ctx->indent,
				    "[exec] (Screenshot - PNG) {import screenshot.png && display -resize 50% screenshot.png}");
		text = g_list_append(text, s);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[exec] (Run) {xde-run}");
		text = g_list_append(text, s);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[exec] (Run Command) {bbrun -a -w}");
		text = g_list_append(text, s);
		xde_decrease_indent(ctx);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
		text = g_list_append(text, s);
	}
	text = g_list_concat(text, ctx->wmm.config(ctx));
	text = g_list_concat(text, ctx->wmm.themes(ctx));
	text = g_list_concat(text, ctx->wmm.styles(ctx));
	if (strcmp(ctx->name, "blackbox") && strcmp(ctx->name, "waimea")) {
		s = g_strdup_printf("%s%s\n", ctx->indent, "[submenu] (Backgrounds) {Set the Background}");
		text = g_list_append(text, s);
		xde_increase_indent(ctx);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[exec] (Random Background) {fbsetbg -r /usr/share/fluxbox/backgrounds}");
		text = g_list_append(text, s);
		xde_decrease_indent(ctx);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
		text = g_list_append(text, s);
	}
	text = g_list_concat(text, ctx->wmm.wkspcs(ctx));
	if (!strcmp(ctx->name, "waimea")) {
		s = g_strdup_printf("%s%s\n", ctx->indent, "[sub] (Processes) <!procinfo.pl>");
		text = g_list_append(text, s);
	}
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "applications-utilities"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Tools)", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[exec] (Window name) {xprop WM_CLASS|cut -d \\\" -f 2|gxmessage -file - -center}");
	text = g_list_append(text, s);
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "applets-screenshooter"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Screenshot - JPG) {import screenshot.jpg && display -resize 50% screenshot.jpg}", icon);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Screenshot - PNG) {import screenshot.png && display -resize 50% screenshot.png}", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-execute"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Run) {fbrun -font 10x20 -fg grey -bg black -title run}", icon);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Run Command) {bbrun -a -w}", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
	if (!strcmp(ctx->name, "fluxbox")) {
		icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "preferences-system-windows"));
		s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Arrange Windows)", icon);
		text = g_list_append(text, s);
		free(icon);
		xde_increase_indent(ctx);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[arrangewindows] (Arrange Windows)");
		text = g_list_append(text, s);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[arrangewindowshorizontal] (Arrange Windows Horizontal)");
		text = g_list_append(text, s);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[arrangewindowsvertical] (Arrange Windows Vertical)");
		text = g_list_append(text, s);
		xde_decrease_indent(ctx);
		s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
		text = g_list_append(text, s);
	}
	text = g_list_concat(text, ctx->wmm.wmmenu(ctx));
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
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
	.name = "fluxbox",
	.format = "fluxbox",
	.wmname = "Fluxbox",
	.desktop = "FLUXBOX",
	.version = VERSION,
	.styles = {
		.sysdir = "/usr/share/fluxbox",
		.usrdir = "/.fluxbox",
		.subdir = "/styles",
		.fname = "/theme.cfg",
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
			.directory = &xde_directory,
			.header = &xde_header,
			.separator = &xde_separator,
			.entry = &xde_entry,
			.alias = &xde_alias,
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
