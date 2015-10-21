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
	if (file)
		return (file);
	return strdup("-");
}

static GList *
xde_create(MenuContext *ctx, Style style, const char *name)
{
	return xde_create_simple(ctx, style, name);
}

static GList *
xde_wmmenu(MenuContext *ctx)
{
	GList *text = NULL;
	GList *xsessions, *xsession;
	char *icon;
	char *s;

	xde_increase_indent(ctx);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%smenu \"%s\" %s {\n", ctx->indent, "Window Managers", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%srestart \"%s\" %s\n", ctx->indent, "Restart", icon);
	text = g_list_append(text, s);
	free(icon);
	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;

		if (strncasecmp(xsess->key, "icewm", 5) == 0)
			continue;
		icon = xde_get_entry_icon(ctx, xsess->entry, "preferences-system-windows",
					  "metacity",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		icon = xde_wrap_icon(icon);
		s = g_strdup_printf("%srestart \"Start %s\" %s xdg-launch --pointer -X %s\n",
				    ctx->indent, xsess->name, icon, xsess->key);
		text = g_list_append(text, s);
		free(icon);
	}
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	xde_free_xsessions(xsessions);
	xde_decrease_indent(ctx);
	return (text);
}

static GList *
xde_appmenu(MenuContext *ctx, GList *entries, const char *name)
{
	GList *text = NULL;
	char *esc;
	char *icon;

	esc = xde_character_escape(name, '"');
	icon = xde_wrap_icon(xde_get_icon2(ctx, "start-here", "folder"));

	text = g_list_append(text, g_strdup_printf("menu \"%s\" %s {\n", name, icon));
	text = g_list_concat(text, entries);
	text = g_list_append(text, g_strdup_printf("}\n"));

	free(icon);
	free(esc);
	return (text);
}

/* IceWM does not actually support specifying the entire root menu. */

static GList *
xde_rootmenu(MenuContext *ctx, GList *entries)
{
	GList *text = NULL;
	char *icon;
	char *s;

	text = g_list_concat(text, entries);
	xde_increase_indent(ctx);
	text = g_list_concat(text, ctx->wmmenu(ctx));
	if (options.filename) {
		xde_increase_indent(ctx);
		icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
		s = g_strdup_printf
		    ("%sprog \"%s\" %s xde-menugen -format icewm -desktop ICEWM -launch -o %s\n",
		     ctx->indent, "Refresh Menu", icon, options.filename);
		text = g_list_append(text, s);
		free(icon);
		xde_decrease_indent(ctx);
	}
	xde_decrease_indent(ctx);
	return (text);
}

static GList *
xde_build(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
{
	return xde_build_simple(ctx, type, item);
}

static GList *
xde_menu(MenuContext *ctx, GMenuTreeDirectory *menu)
{
	return xde_menu_simple(ctx, menu);
}

static GList *
xde_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	/* IceWM does not support separators */
	return NULL;
}

static GList *
xde_header(MenuContext *ctx, GMenuTreeHeader *hdr)
{
	/* IceWM does not support inline headers */
	return NULL;
}

static GList *
xde_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GList *text = NULL;
	const char *name, *path;
	char *esc, *s;
	char *icon = NULL;

	name = gmenu_tree_directory_get_name(dir);

	esc = xde_character_escape(name, '"');

	DPRINTF("Processing menu '%s'\n", name);
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file;

		file = g_key_file_new();
		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon =
		    xde_get_entry_icon(ctx, file, "folder", "unknown",
				       GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
				       GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = xde_wrap_icon(icon);
	s = g_strdup_printf("%smenu \"%s\" %s {\n", ctx->indent, esc, icon);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->ops.menu(ctx, dir));
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	DPRINTF("Done processing menu '%s'\n", name);

	free(icon);
	free(esc);
	return (text);
}

static GList *
xde_entry(MenuContext *ctx, GMenuTreeEntry *ent)
{
	GDesktopAppInfo *info;
	GList *text = NULL;
	const char *name;
	char *esc, *cmd, *s, *p;
	char *icon = NULL;
	char *appid;

	info = gmenu_tree_entry_get_app_info(ent);
	name = g_app_info_get_name(G_APP_INFO(info));

	esc = xde_character_escape(name, '"');

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
	s = g_strdup_printf("%sprog \"%s\" %s %s\n", ctx->indent, esc, icon, cmd);
	text = g_list_append(text, s);
	free(icon);
	free(appid);
	free(esc);
	free(cmd);
	return (text);
}

static GList *
xde_alias(MenuContext *ctx, GMenuTreeAlias *als)
{
	return xde_alias_simple(ctx, als);
}

static GList *
xde_themes(MenuContext *ctx)
{
	/* IceWM does not support specification of themes menu */
	return NULL;
}

static GList *
xde_styles(MenuContext *ctx)
{
	/* IceWM does not support specification of styles menu */
	return NULL;
}

MenuContext xde_menu_ops = {
	.name = "icewm",
	.desktop = "ICEWM",
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
	.output = NULL,
	.create = &xde_create,
	.wmmenu = &xde_wmmenu,
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
		},
	.themes = &xde_themes,
	.styles = &xde_styles,
};
