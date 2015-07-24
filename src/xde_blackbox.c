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

const char *
xde_increase_indent(MenuContext *ctx)
{
	int i, chars;

	ctx->level++;
	chars = ctx->level << 1;
	ctx->indent = realloc(ctx->indent, chars + 1);
	for (i = 0; i < chars; i++)
		ctx->indent[i] = ' ';
	ctx->indent[chars] = '\0';
	return ctx->indent;
}

const char *
xde_decrease_indent(MenuContext *ctx)
{
	int chars;

	ctx->level--;
	if (ctx->level < 0)
		ctx->level = 0;
	chars = ctx->level <<1;
	ctx->indent = realloc(ctx->indent, chars + 1);
	ctx->indent[chars] = '\0';
	return ctx->indent;
}

static char *
xde_blackbox_escape(const char *string, char special)
{
	const char *p;
	char *escaped, *q;
	int len;

	len = strlen(string) + 1;
	escaped = calloc(len << 1, sizeof(*escaped));
	for (p = string, q = escaped; p && *p; p++, q++) {
		if ((*q = *p) == special) {
			*q++ = '\\';
			*q = special;
		}
	}
	*q = '\0';
	return (escaped);
}

static GList *
xde_create(MenuContext *ctx, Style style, const char *name)
{
	GMenuTreeDirectory *directory;
	GList *result = NULL;

	if (!(directory = gmenu_tree_get_root_directory(ctx->tree))) {
		EPRINTF("could not get root directory\n");
		return (result);
	}
	ctx->level = 0;
	xde_increase_indent(ctx);
	result = ctx->ops.menu(ctx, directory);
	xde_decrease_indent(ctx);
	switch (style) {
	case StyleFullmenu:
	default:
		result = ctx->rootmenu(ctx, result);
		break;
	case StyleAppmenu:
		if (!name)
			name = gmenu_tree_directory_get_name(directory);
		result = ctx->appmenu(ctx, result, name);
		break;
	case StyleEntries:
		/* do nothing */
		break;
	}
	return (result);
}

static GList *
xde_wmmenu(MenuContext *ctx)
{
	GList *text = NULL;

	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[submenu] (WindowManagers)"));
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "  [restart] (Restart)"));
	/* FIXME need to get xsessions and fill in all the entries */
	/* following is what each entry should look like */
	/* text = g_list_append(text, g_strdup_printf("%s  [restart] (Start %s) {%s}\n", ctx->indent, "Blackbox", "xdg-launch -X blackbox")); */
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[end]"));
	return (text);
}

static GList *
xde_appmenu(MenuContext *ctx, GList *entries, const char *name)
{
	GList *text = NULL;
	char *esc1, *esc2;

	esc1 = xde_blackbox_escape(name, ')');
	esc2 = xde_blackbox_escape(name, '}');

	text = g_list_append(text, g_strdup_printf("[submenu] (%s) {%s Menu}\n", esc1, esc2));
	text = g_list_concat(text, entries);
	text = g_list_append(text, g_strdup_printf("[end]\n"));

	free(esc1);
	free(esc2);
	return (text);
}

static GList *
xde_rootmenu(MenuContext *ctx, GList *entries)
{
	GList *text = NULL;

	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[begin] (Blackbox)"));
	text = g_list_concat(text, entries);
	xde_increase_indent(ctx);
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[nop] (————————————) {}"));
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[workspaces] (Workspace List)"));
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[config] (Configuration)"));
	text = g_list_concat(text, ctx->themes(ctx));
	text = g_list_concat(text, ctx->styles(ctx));
	text = g_list_concat(text, ctx->wmmenu(ctx));
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[reconfig] (Reconfigure)"));
	if (options.filename)
		text = g_list_append(text, g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Refresh Menu) {xde-menugen -format blackbox -desktop BLACKBOX -launch -o ", options.filename));
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[nop] (————————————) {}"));
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[exit] (Exit)"));
	xde_decrease_indent(ctx);
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[end]"));
	return (text);
}

static GList *
xde_build(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
{
	GList *text = NULL;

	switch (type) {
	case GMENU_TREE_ITEM_INVALID:
		break;
	case GMENU_TREE_ITEM_DIRECTORY:
		if (ctx->ops.directory)
			text = ctx->ops.directory(ctx, item);
		break;
	case GMENU_TREE_ITEM_ENTRY:
		if (ctx->ops.entry)
			text = ctx->ops.entry(ctx, item);
		break;
	case GMENU_TREE_ITEM_SEPARATOR:
		if (ctx->ops.separator)
			text = ctx->ops.separator(ctx, item);
		break;
	case GMENU_TREE_ITEM_HEADER:
		if (ctx->ops.header)
			text = ctx->ops.header(ctx, item);
		break;
	case GMENU_TREE_ITEM_ALIAS:
		if (ctx->ops.alias)
			text = ctx->ops.alias(ctx, item);
		break;
	}
	return (text);
}

static GList *
xde_menu(MenuContext *ctx, GMenuTreeDirectory *menu)
{
	GMenuTreeItemType type;
	GMenuTreeIter *iter;
	GList *text = NULL;

	iter = gmenu_tree_directory_iter(menu);

	xde_increase_indent(ctx);
	while((type = gmenu_tree_iter_next(iter)) != GMENU_TREE_ITEM_INVALID) {
		switch (type) {
		case GMENU_TREE_ITEM_INVALID:
		default:
			break;
		case GMENU_TREE_ITEM_DIRECTORY:
			text = g_list_concat(text, ctx->build(ctx, type, gmenu_tree_iter_get_directory(iter)));
			continue;
		case GMENU_TREE_ITEM_ENTRY:
			text = g_list_concat(text, ctx->build(ctx, type, gmenu_tree_iter_get_entry(iter)));
			continue;
		case GMENU_TREE_ITEM_SEPARATOR:
			text = g_list_concat(text, ctx->build(ctx, type, gmenu_tree_iter_get_separator(iter)));
			continue;
		case GMENU_TREE_ITEM_HEADER:
			text = g_list_concat(text, ctx->build(ctx, type, gmenu_tree_iter_get_header(iter)));
			continue;
		case GMENU_TREE_ITEM_ALIAS:
			text = g_list_concat(text, ctx->build(ctx, type, gmenu_tree_iter_get_alias(iter)));
			continue;
		}
		break;
	}
	xde_decrease_indent(ctx);
	return (text);
}

static GList *
xde_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GList *text = NULL;
	const char *name;
	char *esc1, *esc2;

	name = gmenu_tree_directory_get_name(dir);

	esc1 = xde_blackbox_escape(name, ')');
	esc2 = xde_blackbox_escape(name, '}');

	DPRINTF("Processing menu '%s'\n", name);
	text = g_list_append(text, g_strdup_printf("%s[submenu] (%s) {%s Menu}\n", ctx->indent, esc1, esc2));
	text = g_list_concat(text, ctx->ops.menu(ctx, dir));
	text = g_list_append(text, g_strdup_printf("%s[end]\n", ctx->indent));
	DPRINTF("Done processing menu '%s'\n", name);

	free(esc1);
	free(esc2);
	return (text);
}

static GList *
xde_header(MenuContext *ctx, GMenuTreeHeader *hdr)
{
	GMenuTreeDirectory *dir;
	GList *text = NULL;

	if (!(dir = gmenu_tree_header_get_directory(hdr)))
		return (text);
	text = g_list_append(text, g_strdup_printf("%s[nop] (%s)\n", ctx->indent, gmenu_tree_directory_get_name(dir)));
	text = g_list_concat(text, ctx->ops.directory(ctx, dir));
	return (text);
}

static GList *
xde_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GList *text = NULL;

	text = g_list_append(text, g_strdup_printf("%s[nop] (————————————) {}\n", ctx->indent));
	return (text);
}

static GList *
xde_entry(MenuContext *ctx, GMenuTreeEntry *ent)
{
	GDesktopAppInfo *info;
	GList *text = NULL;
	const char *name, *exec;
	char *esc1, *esc2, *cmd;

	info = gmenu_tree_entry_get_app_info(ent);
	name = g_app_info_get_name(G_APP_INFO(info));

	esc1 = xde_blackbox_escape(name, ')');

	if (options.launch) {
		char *p, *str = strdup(gmenu_tree_entry_get_desktop_file_id(ent));
		if ((p = strstr(str, ".desktop")))
			*p = '\0';
		cmd = g_strdup_printf("xdg-launch --pointer %s", str);
		free(str);
	} else {
		exec = g_app_info_get_commandline(G_APP_INFO(info));
		cmd = g_strdup(exec);
	}

	esc2 = xde_blackbox_escape(cmd, '}');
	text = g_list_append(text, g_strdup_printf("%s[exec] (%s) {%s}\n", ctx->indent, esc1, esc2));

	free(esc1);
	free(esc2);
	free(cmd);
	return (text);
}

static GList *
xde_alias(MenuContext *ctx, GMenuTreeAlias *als)
{
	GMenuTreeItemType type;
	GList *text = NULL;

	switch ((type = gmenu_tree_alias_get_aliased_item_type(als))) {
	case GMENU_TREE_ITEM_INVALID:
		break;
	case GMENU_TREE_ITEM_DIRECTORY:
		text = ctx->build(ctx, type, gmenu_tree_alias_get_aliased_directory(als));
		break;
	case GMENU_TREE_ITEM_ENTRY:
		text = ctx->build(ctx, type, gmenu_tree_alias_get_aliased_entry(als));
		break;
	case GMENU_TREE_ITEM_SEPARATOR:
		break;
	case GMENU_TREE_ITEM_HEADER:
		break;
	case GMENU_TREE_ITEM_ALIAS:
		break;
	}
	return (text);
}

static GList *
xde_themes(MenuContext *ctx)
{
	return NULL;
}

static GList *
xde_styles(MenuContext *ctx)
{
	return NULL;
}

MenuContext xde_menu_ops = {
	.name = "blackbox",
	.version = VERSION,
	.tree = NULL,
	.level = 0,
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
