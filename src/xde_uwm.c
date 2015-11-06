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

/** @name UWM
  */
/** @{ */

static char *
xde_wrap_icon(MenuContext *ctx, char *file)
{
	char *icon;

	if (file) {
		icon = calloc(strlen(file) + 11, sizeof(*icon));
		strcpy(icon, "icon = \"");
		strcat(icon, file);
		strcat(icon, "\" ");
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
	char *esc1, *icon, *s;

	esc1 = xde_character_escape(name, '"');
	icon = ctx->wmm.wrap(ctx, xde_get_icon2(ctx, "start-here", "folder"));
	s = g_strdup_printf("%s[ %stext = \"%s\" menu = [\n", ctx->indent, icon, esc1);
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%slabel = \"%s\"\n", ctx->indent, esc1);
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	s = g_strdup_printf("%s] ; menu %s\n", ctx->indent, esc1);
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s]\n", ctx->indent);
	text = g_list_append(text, s);
	free(icon);
	free(esc1);
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
	char *icon, *s;

	s = strdup("root-menu = [\n");
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = strdup("  opacity = 1.0\n");
	text = g_list_append(text, s);
	s = strdup("  [0] = [\n");
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = strdup("    label = \"μWM \" ~ UWM-VERSION\n");
	text = g_list_append(text, s);
	s = strdup("    height = 18\n");
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	s = strdup("    [ icon = \"uwm16x16.xpm\" text = \"μWM Menu\" menu = [\n");
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = strdup("      label = \"μWM Menu\"\n");
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.wmmenu(ctx));
	s = strdup("      ] ; μWM Menu\n");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = strdup("    ]\n");
	text = g_list_append(text, s);
	if (options.filename) {
		icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-redo-ltr"));
		s = g_strdup_printf("xdg-menugen -format uwm -desktop UWM -launch -o %s",
				    options.filename);
		s = g_strdup_printf("%s[ %stext = \"%s\", execute = \"%s\" ]\n", ctx->indent, icon,
				    "Refresh Menu", s);
		text = g_list_append(text, s);
		free(icon);
	}
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%s[ %stext = \"%s\" restart = true ]\n", ctx->indent, icon, "Restart");
	text = g_list_append(text, s);
	free(icon);
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s[ %stext = \"%s\" exit = true ]\n",
			ctx->indent, icon, "Exit");
	text = g_list_append(text, s);
	free(icon);
	s = strdup("\n");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = strdup("  ] ; 0\n");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = strdup("] ; root-menu\n");
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

	s = g_strdup_printf("%s[ separator = true ]\n", ctx->indent);
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
	char *esc1, *icon = NULL, *s;

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
	if (icon) {
		s = g_strdup_printf("%sicon = \"%s\"\n", ctx->indent, icon);
		text = g_list_append(text, s);
	}
	s = g_strdup_printf("%slabel = \"%s\"\n", ctx->indent, esc1);
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

	item = xde_gtk_common_header(ctx, hdr);
	return (item);
}

static GList *
xde_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GList *text = NULL;
	const char *name, *path;
	char *esc1, *icon = NULL, *s;

	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, '"');
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, "folder", "unknown",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = ctx->wmm.wrap(ctx, icon);
	s = g_strdup_printf("%s[ %stext = \"%s\" menu = [\n", ctx->indent, icon, esc1);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmm.ops.menu(ctx, dir));
	s = g_strdup_printf("%s  ] ; menu %s\n", ctx->indent, esc1);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s]\n", ctx->indent);
	text = g_list_append(text, s);
	free(icon);
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
	char *esc1, *esc2, *cmd, *p;
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
	esc2 = xde_character_escape(cmd, '"');
	icon = ctx->wmm.wrap(ctx, icon);
	s = g_strdup_printf("%s[ %stext = \"%s\" execute = \"%s\" ]\n",
			    ctx->indent, icon, esc1, esc2);
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
	char *icon, *s;

	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s[ %stext = \"%s\" menu = [\n", ctx->indent, icon, "Window Managers");
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%slabel = \"%s\"\n", ctx->indent, "Window Managers");
	text = g_list_append(text, s);
	icon = ctx->wmm.wrap(ctx, xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%s[ %stext = \"%s\" restart = true ]\n", ctx->indent, icon, "Restart");
	text = g_list_append(text, s);
	free(icon);
	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		char *esc1;

		if (strncasecmp(xsess->key, "uwm", strlen("uwm")) == 0 ||
		    strncasecmp(xsess->key, "μWM", strlen("μWM")) == 0)
			continue;
		icon =
		    xde_get_entry_icon(ctx, xsess->entry, "preferences-system-windows", "metacity",
				       GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
				       GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		icon = ctx->wmm.wrap(ctx, icon);
		esc1 = xde_character_escape(xsess->name, '"');
		s = g_strdup_printf("xdg-launch -X %s", xsess->key);
		s = g_strdup_printf("%s[ %stext = \"%s\" exit = \"%s\" ]\n",
				    ctx->indent, icon, esc1, s);
		text = g_list_append(text, s);
		free(esc1);
		free(icon);
	}
	s = g_strdup_printf("%s] ; menu Window Managers\n", ctx->indent);
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s]\n", ctx->indent);
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

static GList *
xde_styles(MenuContext *ctx)
{
	GList *text = NULL;

	/* FIXME */
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

	/* FIXME */
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

	return (text);
}

static GtkMenuItem *
xde_gtk_wmspec(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	return (item);
}

MenuContext xde_menu_ops = {
	.name = "uwm",
	.format = "uwm",
	.desktop = "UWM",
	.version = VERSION,
	.styles = {
		.sysdir = "/usr/share/uwm",
		.usrdir = "/.uwm",
		.subdir = "/styles",
		.fname = "/theme",
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
