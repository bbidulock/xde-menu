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

/** @name VTWM
  */
/** @{ */

static GList *
xde_create(MenuContext *ctx, Style style, const char *name)
{
	GMenuTreeDirectory *dir;
	GList *text = NULL;
	GList *entries = NULL;
	char *qname = NULL;
	char *s;

	ctx->wmm.output = NULL;

	s = g_strdup_printf("%s\n", "changequote(`[[[',`]]]')dnl");
	ctx->wmm.output = g_list_append(ctx->wmm.output, s);

	if (!(dir = gmenu_tree_get_root_directory(ctx->tree))) {
		EPRINTF("could not get root directory\n");
		return (text);
	}
	xde_reset_indent(ctx, 0);
	xde_increase_indent(ctx);
	entries = ctx->wmm.ops.menu(ctx, dir);
	xde_decrease_indent(ctx);

	if (!name)
		name = gmenu_tree_directory_get_name(dir);

	if (style == StyleFullmenu) {
		text = ctx->wmm.wmmenu(ctx);
		ctx->wmm.output = g_list_concat(ctx->wmm.output, text);
		text = ctx->wmm.wmspec(ctx);
		ctx->wmm.output = g_list_concat(ctx->wmm.output, text);
	}
	if (style == StyleAppmenu || style == StyleSubmenu) {
		text = ctx->wmm.appmenu(ctx, entries, name);
	}
	if (style == StyleEntries) {
		return (entries);
	}
	if (style == StyleSubmenu) {
		qname = g_strdup_printf("\"%s\"", name);
		s = g_strdup_printf("    %-32s  f.menu \"%s\"\n", qname, name);
		g_free(qname);
		/* FIXME: free other entries */
		entries = g_list_append(NULL, s);
	}
	if (style != StyleAppmenu) {
		text = ctx->wmm.rootmenu(ctx, entries);
		ctx->wmm.output = g_list_concat(ctx->wmm.output, text);
	}

	s = g_strdup_printf("\n%s\n", "changequote(`,)dnl");
	text = g_list_append(ctx->wmm.output, s);
	ctx->wmm.output = NULL;
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
	GMenuTreeDirectory *dir;
	GList *text = NULL;
	char *s, *esc, *qname;

	if (!(dir = gmenu_tree_get_root_directory(ctx->tree))) {
		EPRINTF("could not get root directory\n");
		return (text);
	}
	if (!name)
		name = gmenu_tree_directory_get_name(dir);
	esc = xde_character_escape(name, '"');
	s = g_strdup_printf("\nMenu \"%s\" twm_MenuColor\n", esc);
	text = g_list_append(text, s);
	s = strdup("{\n");
	text = g_list_append(text, s);
	qname = g_strdup_printf("\"%s\"", esc);
	s = g_strdup_printf("    %-32s  %s\n", qname, "f.title");
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	s = strdup("}\n");
	text = g_list_append(text, s);
	g_free(qname);
	free(esc);
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
	char *s, *menu;

	s = g_strdup_printf("\nMenu \"%s\" twm_MenuColor\n", "defops");
	text = g_list_append(text, s);
	s = strdup("{\n");
	text = g_list_append(text, s);
	menu = g_strdup_printf("\"%s\"", ctx->desktop);
	s = g_strdup_printf("    %-32s  %s\n", menu, "f.title");
	text = g_list_append(text, s);
	free(menu);
	text = g_list_concat(text, ctx->wmm.ops.pin(ctx));
	text = g_list_concat(text, entries);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	menu = g_strdup_printf("\"%s Menu\"", ctx->desktop);
	s = g_strdup_printf("    %-32s  %s\n", menu, "f.menu \"twmmenu\"");
	text = g_list_append(text, s);
	free(menu);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	s = g_strdup_printf("    %-32s  %s\n", "\"Refresh\"", "f.refresh");
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  %s\n", "\"Reconfigure\"", "f.function \"reconfig\"");
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  %s\n", "\"Restart\"", "f.restart");
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  %s\n", "\"Exit\"", "f.quit");
	text = g_list_append(text, s);
	s = strdup("}\n");
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
xde_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GList *text = NULL;
	char *s;

	if (strcmp(ctx->name, "twm")) {
		s = g_strdup_printf("    %-32s  %s\n", "\"\"", "f.separator");
		text = g_list_append(text, s);
	} else {
		s = g_strdup_printf("    %-32s  %s\n", "\"--------------------------------\"", "f.nop");
		text = g_list_append(text, s);
	}
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
	char *s, *qname, *esc;
	const char *name;

	if (!(dir = gmenu_tree_header_get_directory(hdr)))
		return (text);
	name = gmenu_tree_directory_get_name(dir);
	esc = xde_character_escape(name, '"');
	qname = g_strdup_printf("\"%s\"", esc);
	s = g_strdup_printf("    %-32s  %s\n", qname, "f.title");
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.directory(ctx, dir));

	g_free(qname);
	g_free(esc);
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
	const char *name;
	char *esc1, *qname, *s;

	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, '"');
	qname = g_strdup_printf("\"%s\"", esc1);

	s = g_strdup_printf("\nMenu \"%s\" twm_MenuColor\n{\n", esc1);
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  %s\n", qname, "f.title");
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.menu(ctx, dir));
	s = g_strdup_printf("}\n");
	text = g_list_append(text, s);
	ctx->wmm.output = g_list_concat(ctx->wmm.output, text);
	text = NULL;

	s = g_strdup_printf("    %-32s  f.menu \"%s\"\n", qname, esc1);
	text = g_list_append(text, s);

	g_free(qname);
	free(esc1);

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
	char *esc1, *qname, *esc2, *cmd, *p;
	char *s, *icon = NULL;
	char *appid;

	info = gmenu_tree_entry_get_app_info(ent);
	name = g_app_info_get_name(G_APP_INFO(info));
	esc1 = xde_character_escape(name, '"');
	qname = g_strdup_printf("\"%s\"", esc1);

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
	esc2 = xde_character_escape(cmd, '"');

	s = g_strdup_printf("    %-32s  f.exec \"exec %s &\"\n", qname, esc2);
	text = g_list_append(text, s);

	free(icon);
	free(appid);
	g_free(qname);
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
	char *s;

	if (!strcmp(ctx->name, "ctwm") || !strcmp(ctx->name, "etwm")) {
		s = g_strdup_printf("    %-32s  %s\n", "\"--------> pin <--------\"", "f.pin");
		text = g_list_append(text, s);
	}
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
	int gotone = FALSE;
	char *s;

	s = g_strdup_printf("\n%s\n", "Menu \"managers\" twm_MenuColor");
	text = g_list_append(text, s);
	s = strdup("{\n");
	text = g_list_append(text, s);

	xde_increase_indent(ctx);

	s = g_strdup_printf("    %-32s  %s\n", "\"Window Managers\"", "f.title");
	text = g_list_append(text, s);

	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		char *esc1, *esc2, *qname, *exec;

		if (strncasecmp(xsess->key, ctx->name, strlen(ctx->name)) == 0)
			continue;

		esc1 = xde_character_escape(xsess->name, '"');
		qname = g_strdup_printf("\"%s\"", esc1);

		if (options.launch) {
			exec = g_strdup_printf("xdg-launch --pointer -X %s", xsess->key);
		} else {
			exec = g_key_file_get_string(xsess->entry,
						     G_KEY_FILE_DESKTOP_GROUP,
						     G_KEY_FILE_DESKTOP_KEY_EXEC, NULL);
			exec = exec ? strdup(exec) : strdup("/usr/bin/true");
		}
		esc2 = xde_character_escape(exec, '"');
		if (!strcmp(ctx->name, "mwm") || !strcmp(ctx->name, "dtwm"))
			s = g_strdup_printf("    %-32s  %s \"%s\"\n", qname, "f.restart -", esc2);
		else if (!strcmp(ctx->name, "twm")||!strcmp(ctx->name, "vtwm"))
			s = g_strdup_printf("    %-32s  %s \"%s\"\n", qname, "f.startwm", esc2);
		else
			s = g_strdup_printf("    %-32s  %s \"exec %s &\"\n", qname, "f.exec", esc2);
		text = g_list_append(text, s);

		gotone = TRUE;
		free(esc1);
		free(esc2);
		free(qname);
		free(exec);
	}
	if (gotone)
		text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	s = g_strdup_printf("    %-32s  %s\n", "\"Restart\"", "f.restart");
	text = g_list_append(text, s);
	if (!strcmp(ctx->name, "mwm") || !strcmp(ctx->name, "dtwm"))
		s = g_strdup_printf("    %-32s  %s\n", "\"Quit\"", "f.quit_mwm");
	else
		s = g_strdup_printf("    %-32s  %s\n", "\"Quit\"", "f.quit");
	text = g_list_append(text, s);
	s = strdup("}\n");
	text = g_list_append(text, s);

	return (text);
}

static GtkMenuItem *
xde_gtk_wmmenu(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	item = xde_gtk_common_wmmenu(ctx);
	return (item);
}

/*
 * Don't need to do anything here as the native styles menu is built using a
 * the script 'getsytyles' and is set using the script 'setstyle'.  Only the
 * GTK+ version needs to be performed here.
 */
static GList *
xde_styles(MenuContext *ctx)
{
	GList *text = NULL;

	/* FIXME: this should just place the "Styles" entry in the menu refering to the
	   "twmstyles" menu which was built by the getstyles script before m4
	   configuration. */
	return (text);
}

static GtkMenuItem *
xde_gtk_styles(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	if (strcmp(ctx->name, "dtwm"))
		item = xde_gtk_styles_simple(ctx);
	return (item);
}

static GList *
xde_themes(MenuContext *ctx)
{
	GList *text = NULL;

	/* FIXME: because we have built up the internal twmstyles menu actions for
	   setting style, it is actually possible to create a "twmthemes" menu here that
	   will only contain the styles with an equivalent theme and invoke the
	   corresponding actions defined for the "twmstyles" menu. */
	return (text);
}

static GtkMenuItem *
xde_gtk_themes(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	if (!strcmp(ctx->name, "mwm") || !strcmp(ctx->name, "dtwm"))
		item = xde_gtk_common_themes(ctx);
	else
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
	char *s, *menu;

	s = g_strdup_printf("\n%s\n", "Menu \"twmmenu\" twm_MenuColor");
	text = g_list_append(text, s);
	s = g_strdup_printf("{\n");
	text = g_list_append(text, s);
	menu = g_strdup_printf("\"%s Menu\"", ctx->desktop);
	s = g_strdup_printf("    %-32s  %s\n", menu, "f.title");
	text = g_list_append(text, s);
	free(menu);
	if (!strcmp(ctx->name, "ctwm") || !strcmp(ctx->name, "etwm")) {
		s = g_strdup_printf("    %-32s  %s\n", "\"Icons List\"", "f.menu \"TwmIcons\"");
		text = g_list_append(text, s);
	}
	s = g_strdup_printf("    %-32s  %s\n", "\"Window List\"", "f.menu \"TwmWindows\"");
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  %s\n", "\"Window Operations\"", "f.menu \"windowops\"");
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  %s\n", "\"Styles\"", "f.menu \"twmstyles\"");
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  %s\n", "\"Window Managers\"", "f.menu \"managers\"");
	text = g_list_append(text, s);
	if (!strcmp(ctx->name, "mwm") || !strcmp(ctx->name, "dtwm")) {
		s = g_strdup_printf("    %-32s  %s\n", "\"Pack Icons\"", "f.pack_icons");
		text = g_list_append(text, s);
	}
	if (strcmp(ctx->name, "mwm") && strcmp(ctx->name, "dtwm")) {
		s = g_strdup_printf("    %-32s  %s\n", "\"Hide Icon Manager\"", "f.hideiconmgr");
		text = g_list_append(text, s);
		s = g_strdup_printf("    %-32s  %s\n", "\"Show Icon Manager\"", "f.showiconmgr");
		text = g_list_append(text, s);
	}
	if (!strcmp(ctx->name, "ctwm") || !strcmp(ctx->name, "etwm")) {
		s = g_strdup_printf("    %-32s  %s\n", "\"Hide Workspace Manager\"", "f.hideworkspacemgr");
		text = g_list_append(text, s);
		s = g_strdup_printf("    %-32s  %s\n", "\"Show Workspace Manager\"", "f.showworkspacemgr");
		text = g_list_append(text, s);
	}
	if (!strcmp(ctx->name, "vtwm")) {
		s = g_strdup_printf("    %-32s  %s\n", "\"Hide Desktop Display\"", "f.hidedesktopdisplay");
		text = g_list_append(text, s);
		s = g_strdup_printf("    %-32s  %s\n", "\"Show Desktop Display\"", "f.showdesktopdisplay");
		text = g_list_append(text, s);
	}
	s = g_strdup_printf("    %-32s  %s\n", "\"Refresh\"", "f.refresh");
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  %s\n", "\"Restart\"", "f.restart");
	text = g_list_append(text, s);
	s = g_strdup_printf("    %-32s  f.exec \"exec xde-menugen -format %s -desktop %s -o %s\"\n", "\"Refresh Menu\"", ctx->name, ctx->desktop, options.filename);
	text = g_list_append(text, s);
	s = g_strdup_printf("}\n");
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
	.name = "vtwm",
	.format = "vtwm",
	.desktop = "VTWM",
	.version = VERSION,
	.styles = {
		.sysdir = "/usr/share/vtwm",
		.usrdir = "/.vtwm",
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
