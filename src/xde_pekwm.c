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
		icon = calloc(strlen(file) + 12, sizeof(*icon));
		strcpy(icon, "Icon = \"");
		strcat(icon, file);
		strcat(icon, "\"; ");
	} else
		icon = strdup("");
	free(file);
	return (icon);
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
	char *icon, *s;

	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%sSubmenu = \"Window Managers\" { %s\n", ctx->indent, icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		char *esc1;

		esc1 = xde_character_escape(xsess->name, '"');
		if (strncasecmp(xsess->key, "pekwm", 5) == 0)
			continue;
		icon = xde_get_entry_icon(ctx, xsess->entry, "preferences-system-windows",
					  "metacity",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		icon = xde_wrap_icon(icon);
		s = g_strdup_printf
		    ("%s  Entry = \"Start %s\" { %sActions = \"RestartOther xdg-launch --pointer -X %s\" }\n",
		     ctx->indent, esc1, icon, xsess->key);
		text = g_list_append(text, s);
		free(esc1);
		free(icon);
	}
	text = g_list_concat(text, ctx->ops.separator(ctx, NULL));
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-redo-ltr"));
	s = g_strdup_printf("%s  Entry = \"Reload\" { %sActions = \"Reload\" }\n", ctx->indent,
			    icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%s  Entry = \"Restart\" { %sActions = \"Restart\" }\n", ctx->indent,
			    icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s  Entry = \"Exit\" { %sActions = \"Exit\" }\n", ctx->indent, icon);
	text = g_list_append(text, s);
	free(icon);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	return (text);
}

static GList *
xde_appmenu(MenuContext *ctx, GList *entries, const char *name)
{
	GList *text = NULL;
	char *esc1, *icon, *s;

	esc1 = xde_character_escape(name, '"');
	icon = xde_wrap_icon(xde_get_icon2(ctx, "start-here", "folder"));
	s = g_strdup_printf("%sSubmenu = \"%s\" { %s\n", ctx->indent, esc1, icon);
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	free(icon);
	free(esc1);
	return (text);
}

static GList *
xde_rootmenu(MenuContext *ctx, GList *entries)
{
	GList *text = NULL;
	char *icon, *s;

	s = strdup("# Menu config for pekwm\n\n");
	text = g_list_append(text, s);
	s = strdup("# Variables\n");
	text = g_list_append(text, s);
	s = strdup("INCLUDE = \"vars\"\n\n");
	text = g_list_append(text, s);
	s = strdup("RootMenu = \"Pekwm\" {\n");
	xde_increase_indent(ctx);
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	text = g_list_concat(text, ctx->ops.separator(ctx, NULL));
	icon = xde_wrap_icon(xde_get_icon(ctx, "pekwm"));
	s = g_strdup_printf("%sSubmenu = \"%s\" { %s\n", ctx->indent, "Pekwm", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-execute"));
	s = g_strdup_printf("%sEntry = \"%s\" { %sActions = \"%s\" }\n",
			    ctx->indent, "Run Command...", icon, "ShowCmdDialog");
	text = g_list_append(text, s);
	free(icon);
	icon = xde_wrap_icon(xde_get_icon(ctx, "preferences-desktop-display"));
	s = g_strdup_printf("%sSubmenu = \"%s\" { %s\n", ctx->indent, "Workspace List", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "",
			    "Dynamic $_PEKWM_SCRIPT_PATH/pekwm_ws_menu.sh goto dynamic");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	icon = xde_wrap_icon(xde_get_icon(ctx, "preferences-system-windows"));
	s = g_strdup_printf("%sEntry = \"%s\" { %sActions = \"%s\" }\n",
			    ctx->indent, "Window List", icon, "ShowMenu GotoClient True");
	text = g_list_append(text, s);
	free(icon);
	text = g_list_concat(text, ctx->themes(ctx));
	text = g_list_concat(text, ctx->styles(ctx));
	s = g_strdup_printf("%sSubmenu = \"%s\" {\n", ctx->indent, "Layout");
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Smart", "SetLayouter Smart");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Mouse Not Under", "SetLayouter MouseNotUnder");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Mouse Centered", "SetLayouter MouseCentered");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Mouse Top Left", "SetLayouter MouseTopLeft");
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->ops.separator(ctx, NULL));
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Layout Horizontal", "SetLayouter TILE_Horizontal");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Layout Vertical", "SetLayouter TILE_Vertical");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Layout Dwindle", "SetLayouter TILE_Dwindle");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Layout Stacked", "SetLayouter TILE_Stacked");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Layout Center One", "SetLayouter TILE_CenterOne");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Layout Boxed", "SetLayouter TILE_Boxed");
	text = g_list_append(text, s);
	s = g_strdup_printf("%sEntry = \"%s\" { Actions = \"%s\" }\n",
			    ctx->indent, "Layout Fib", "SetLayouter TILE_Fib");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->wmmenu(ctx));
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	if (options.filename) {
		icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
		s = g_strdup_printf("%sEntry = \"%s\" { %sActions = \"%s%s\" }\n",
				    ctx->indent, "Refresh Menu", icon,
				    "Exec xdg-menugen -format pekwm -desktop PEKWM -launch -o ",
				    options.filename);
		text = g_list_append(text, s);
		free(icon);
	}
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-redo-ltr"));
	s = g_strdup_printf("%sEntry = \"%s\" { %sActions = \"%s\" }\n",
			    ctx->indent, "Reload", icon, "Reload");
	text = g_list_append(text, s);
	free(icon);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%sEntry = \"%s\" { %sActions = \"%s\" }\n",
			    ctx->indent, "Restart", icon, "Restart");
	text = g_list_append(text, s);
	free(icon);
	text = g_list_concat(text, ctx->ops.separator(ctx, NULL));
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%sEntry = \"%s\" { %sActions = \"%s\" }\n",
			    ctx->indent, "Exit", icon, "Exit");
	text = g_list_append(text, s);
	free(icon);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n\n", ctx->indent);
	text = g_list_append(text, s);
	s = strdup("INCLUDE = \"window\"\n\n");
	text = g_list_append(text, s);
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
	GList *text = NULL;
	char *s;

	s = g_strdup_printf("%sSeparator {}\n", ctx->indent);
	text = g_list_append(text, s);
	return (text);
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
	text = g_list_concat(text, ctx->ops.separator(ctx, NULL));
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
	if (icon)
		s = g_strdup_printf("%sEntry = \"%s\" { Icon = \"%s\" }\n", ctx->indent, esc1,
				    icon);
	else
		s = g_strdup_printf("%sEntry = \"%s\" { }\n", ctx->indent, esc1);
	text = g_list_append(text, s);
	text = g_list_concat(text, ctx->ops.separator(ctx, NULL));
	text = g_list_concat(text, ctx->ops.directory(ctx, dir));

	free(icon);
	free(esc1);
	return (text);
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
		GKeyFile *file;

		file = g_key_file_new();
		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, "folder", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG|
				GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	s = g_strdup_printf("%sSubmenu = \"%s\" { \n", ctx->indent, esc1);
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	if (icon) {
		s = g_strdup_printf("%sIcon = \"%s\"\n", ctx->indent, icon);
		text = g_list_append(text, s);
	}
	text = g_list_concat(text, ctx->ops.menu(ctx, dir));
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	free(icon);
	free(esc1);
	return (text);
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
	icon = xde_wrap_icon(icon);
	s = g_strdup_printf("%sEntry = \"%s\" { %sActions = \"Exec %s\" }\n",
			    ctx->indent, esc1, icon, esc2);
	text = g_list_append(text, s);
	free(icon);
	free(appid);
	free(esc1);
	free(esc2);
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
	GList *text = NULL;
	char *icon = NULL, *s;

	icon = xde_wrap_icon(xde_get_icon(ctx, "style"));
	s = g_strdup_printf("%sSubmenu = \"%s\" { %s\n", ctx->indent, "Themes", icon);
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%sEntry { Actions = \"%s\" }\n",
			    ctx->indent, "Dynamic xde-style -m -t");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	free(icon);
	return (text);
}

static GList *
xde_styles(MenuContext *ctx)
{
	GList *text = NULL;
	char *icon = NULL, *s;

	icon = xde_wrap_icon(xde_get_icon(ctx, "style"));
	s = g_strdup_printf("%sSubmenu = \"%s\" { %s\n", ctx->indent, "Styles", icon);
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%sEntry { Actions = \"%s\" }\n", ctx->indent, "Dynamic xde-style -m");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s}\n", ctx->indent);
	text = g_list_append(text, s);
	free(icon);
	return (text);
}

static GtkMenu *
xde_submenu(void)
{
	return NULL;
}

MenuContext xde_menu_ops = {
	.name = "pekwm",
	.desktop = "PEKWM",
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
	.submenu = &xde_submenu,
};
