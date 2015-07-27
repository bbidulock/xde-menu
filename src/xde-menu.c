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

#define XA_SELECTION_NAME	"_XDE_MENU_S%d"

int saveArgc;
char **saveArgv;

Atom _XA_XDE_ICON_THEME_NAME;	/* XXX */
Atom _XA_XDE_THEME_NAME;
Atom _XA_XDE_WM_CLASS;
Atom _XA_XDE_WM_CMDLINE;
Atom _XA_XDE_WM_COMMAND;
Atom _XA_XDE_WM_ETCDIR;
Atom _XA_XDE_WM_HOST;
Atom _XA_XDE_WM_HOSTNAME;
Atom _XA_XDE_WM_ICCCM_SUPPORT;
Atom _XA_XDE_WM_ICON;
Atom _XA_XDE_WM_ICONTHEME;	/* XXX */
Atom _XA_XDE_WM_INFO;
Atom _XA_XDE_WM_MENU;
Atom _XA_XDE_WM_NAME;
Atom _XA_XDE_WM_NETWM_SUPPORT;
Atom _XA_XDE_WM_PID;
Atom _XA_XDE_WM_PRVDIR;
Atom _XA_XDE_WM_RCFILE;
Atom _XA_XDE_WM_REDIR_SUPPORT;
Atom _XA_XDE_WM_STYLE;
Atom _XA_XDE_WM_STYLENAME;
Atom _XA_XDE_WM_SYSDIR;
Atom _XA_XDE_WM_THEME;
Atom _XA_XDE_WM_THEMEFILE;
Atom _XA_XDE_WM_USRDIR;
Atom _XA_XDE_WM_VERSION;

Atom _XA_GTK_READ_RCFILES;
Atom _XA_MANAGER;

Options options = {
	.debug = 0,
	.output = 1,
	.command = CommandDefault,
	.launch = True,
};

Options defaults = {
	.debug = 1,
	.output = 1,
	.command = CommandDefault,
	.format = NULL,
	.style = StyleFullmenu,
	.desktop = "XDE",
	.charset = "UTF-8",
	.language = NULL,
	.locale = "en_US.UTF-8",
	.rootmenu = NULL,
	.dieonerr = False,
	.fileout = False,
	.filename = NULL,
	.noicons = False,
	.theme = NULL,
	.launch = True,
	.clientId = NULL,
	.saveFile = NULL,
	.runhist = "~/.config/xde/run-history",
	.recapps = "~/.config/xde/recent-applications",
	.recently = "~/.local/share/recently-used",
	.recent = NULL,
	.keep = "10",
	.menu = "applications",
};

XdeScreen *screens;

char *xdg_data_home = NULL;
char *xdg_data_dirs = NULL;
char *xdg_data_path = NULL;
char *xdg_data_last = NULL;

static inline char *
xdg_find_str(char *s, char *b)
{
	for (s--; s > b && *s != '\0'; s--) ;
	if (s > b)
		s++;
	return (s);
}

char *xdg_config_home = NULL;
char *xdg_config_dirs = NULL;
char *xdg_config_path = NULL;
char *xdg_config_last = NULL;

GMenuTree *tree = NULL;

static void
display_level(FILE *file, int level)
{
	int i;

	for (i = 0; i < level; i++)
		fputs("  ", file);
}

static void display_directory(FILE *file, GMenuTreeDirectory *directory, int level);
static void display_entry(FILE *file, GMenuTreeEntry *entry, int level);
static void display_separator(FILE *file, GMenuTreeSeparator *separator, int level);
static void display_header(FILE *file, GMenuTreeHeader *header, int level);
static void display_alias(FILE *file, GMenuTreeAlias *alias, int level);

static void
display_invalid(FILE *file, int level)
{
	display_level(file, level);
	fprintf(file, "%s\n", "Invalid Entry");
}

static char **
xde_get_xsession_dirs(int *np)
{
	char *home, *xhome, *xdata, *dirs, *pos, *end, **xdg_dirs;
	int len, n;

	home = getenv("HOME") ? : ".";
	xhome = getenv("XDG_DATA_HOME");
	xdata = getenv("XDG_DATA_DIRS") ? : "/usr/local/share:/usr/share";

	len = (xhome ? strlen(xhome) : strlen(home) + strlen("/.local/share")) + strlen(xdata) + 2;
	dirs = calloc(len, sizeof(*dirs));
	if (xhome)
		strcpy(dirs, xhome);
	else {
		strcpy(dirs, home);
		strcat(dirs, "/.local/share");
	}
	strcat(dirs, ":");
	strcat(dirs, xdata);
	end = dirs + strlen(dirs);
	for (n = 0, pos = dirs; pos < end; n++,
	     *strchrnul(pos, ':') = '\0', pos += strlen(pos) + 1) ;
	xdg_dirs = calloc(n + 1, sizeof(*xdg_dirs));
	for (n = 0, pos = dirs; pos < end; n++, pos += strlen(pos) + 1) {
		len = strlen(pos) + strlen("/xsessions") + 1;
		xdg_dirs[n] = calloc(len, sizeof(*xdg_dirs[n]));
		strcpy(xdg_dirs[n], pos);
		strcat(xdg_dirs[n], "/xsessions");
	}
	free(dirs);
	if (np)
		*np = n;
	return (xdg_dirs);
}

static GKeyFile *
xde_get_xsession_entry(const char *key, const char *file)
{
	GKeyFile *entry;

	if (!(entry = g_key_file_new())) {
		EPRINTF("%s: could not allocate key file\n", file);
		return (NULL);
	}
	if (!g_key_file_load_from_file(entry, file, G_KEY_FILE_NONE, NULL)) {
		EPRINTF("%s: could not load keyfile\n", file);
		g_key_file_unref(entry);
		return (NULL);
	}
	if (!g_key_file_has_group(entry, G_KEY_FILE_DESKTOP_GROUP)) {
		EPRINTF("%s: has no [%s] section\n", file, G_KEY_FILE_DESKTOP_GROUP);
		g_key_file_free(entry);
		return (NULL);
	}
	if (!g_key_file_has_key(entry, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_TYPE, NULL)) {
		EPRINTF("%s: has no %s= entry\n", file, G_KEY_FILE_DESKTOP_KEY_TYPE);
		g_key_file_free(entry);
		return (NULL);
	}
	DPRINTF("got xsession file: %s (%s)\n", key, file);
	return (entry);
}

static gboolean
xde_bad_xsession(const char *appid, GKeyFile *entry)
{
	gchar *name, *exec, *tryexec, *binary;

	if (!(name = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
					   G_KEY_FILE_DESKTOP_KEY_NAME, NULL))) {
		DPRINTF("%s: no Name\n", appid);
		return TRUE;
	}
	g_free(name);
	if (!(exec = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
					   G_KEY_FILE_DESKTOP_KEY_EXEC, NULL))) {
		DPRINTF("%s: no Exec\n", appid);
		return TRUE;
	}
	if (g_key_file_get_boolean(entry, G_KEY_FILE_DESKTOP_GROUP,
				   G_KEY_FILE_DESKTOP_KEY_HIDDEN, NULL)) {
		DPRINTF("%s: is Hidden\n", appid);
		return TRUE;
	}
#if 0
	/* NoDisplay is often used to hide XSession desktop entries from the
	   application menu and does not indicate that it should not be
	   displayed as an XSession entry. */

	if (g_key_file_get_boolean(entry, G_KEY_FILE_DESKTOP_GROUP,
				   G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY, NULL)) {
		DPRINTF("%s: is NoDisplay\n", appid);
		return TRUE;
	}
#endif
	if ((tryexec = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
					     G_KEY_FILE_DESKTOP_KEY_TRY_EXEC, NULL))) {
		binary = g_strdup(tryexec);
		g_free(tryexec);
	} else {
		char *p;

		/* parse the first word of the exec statement and see whether
		   it is executable or can be found in PATH */
		binary = g_strdup(exec);
		if ((p = strpbrk(binary, " \t")))
			*p = '\0';

	}
	g_free(exec);
	if (binary[0] == '/') {
		if (access(binary, X_OK)) {
			DPRINTF("%s: %s: %s\n", appid, binary, strerror(errno));
			g_free(binary);
			return TRUE;
		}
	} else {
		char *dir, *end;
		char *path = strdup(getenv("PATH") ? : "");
		int blen = strlen(binary) + 2;
		gboolean execok = FALSE;

		for (dir = path, end = dir + strlen(dir); dir < end;
		     *strchrnul(dir, ':') = '\0', dir += strlen(dir) + 1) ;
		for (dir = path; dir < end; dir += strlen(dir) + 1) {
			int len = strlen(dir) + blen;
			char *file = calloc(len, sizeof(*file));

			strcpy(file, dir);
			strcat(file, "/");
			strcat(file, binary);
			if (!access(file, X_OK)) {
				execok = TRUE;
				free(file);
				break;
			}
			// to much noise
			// DPRINTF("%s: %s: %s\n", appid, file,
			// strerror(errno));
		}
		free(path);
		if (!execok) {
			DPRINTF("%s: %s: not executable\n", appid, binary);
			g_free(binary);
			return TRUE;
		}
	}
	return FALSE;
}

static void
xde_xsession_key_free(gpointer data)
{
	free(data);
}

void
xde_xsession_value_free(gpointer filename)
{
	free(filename);
}

static GHashTable *
xde_find_xsessions(void)
{
	char **xdg_dirs, **dirs;
	int i, n = 0;
	static const char *suffix = ".desktop";
	static const int suflen = 8;
	static GHashTable *xsessions = NULL;

	if (xsessions)
		return (xsessions);

	if (!(xdg_dirs = xde_get_xsession_dirs(&n)) || !n)
		return (xsessions);

	xsessions = g_hash_table_new_full(g_str_hash, g_str_equal,
					  xde_xsession_key_free, xde_xsession_value_free);

	/* go through them backward */
	for (i = n - 1, dirs = &xdg_dirs[i]; i >= 0; i--, dirs--) {
		char *file, *p;
		DIR *dir;
		struct dirent *d;
		int len;
		char *key;

		if (!(dir = opendir(*dirs))) {
			DPRINTF("%s: %s\n", *dirs, strerror(errno));
			continue;
		}
		while ((d = readdir(dir))) {
			if (d->d_name[0] == '.')
				continue;
			if (!(p = strstr(d->d_name, suffix)) || p[suflen]) {
				DPRINTF("%s: no %s suffix\n", d->d_name, suffix);
				continue;
			}
			len = strlen(*dirs) + strlen(d->d_name) + 2;
			file = calloc(len, sizeof(*file));
			strcpy(file, *dirs);
			strcat(file, "/");
			strcat(file, d->d_name);
			key = strdup(d->d_name);
			*strstr(key, suffix) = '\0';
			g_hash_table_replace(xsessions, key, file);
		}
		closedir(dir);
	}
	for (i = 0; i < n; i++)
		free(xdg_dirs[i]);
	free(xdg_dirs);
	return (xsessions);
}

static gint
xde_xsession_compare(gconstpointer a, gconstpointer b)
{
	const XdeXsession *A = a;
	const XdeXsession *B = b;

	return strcasecmp(A->name, B->name);
}

GList *
xde_get_xsessions(void)
{
	GList *result = NULL;
	GHashTable *xsessions;

	if (!(xsessions = xde_find_xsessions())) {
		EPRINTF("cannot build XSessions\n");
		return (result);
	}
	if (!g_hash_table_size(xsessions)) {
		EPRINTF("cannot find any XSessions\n");
		return (result);
	}

	GHashTableIter xiter;
	const char *key;
	const char *file;

	g_hash_table_iter_init(&xiter, xsessions);
	while (g_hash_table_iter_next(&xiter, (gpointer *)&key, (gpointer *)&file)) {
		GKeyFile *entry;
		XdeXsession *xsession;

		if (!(entry = xde_get_xsession_entry(key, file)))
			continue;
		if (xde_bad_xsession(key, entry)) {
			g_key_file_free(entry);
			continue;
		}
		xsession = calloc(1, sizeof(*xsession));
		xsession->key = g_strdup(key);
		xsession->name = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
				G_KEY_FILE_DESKTOP_KEY_NAME, NULL);
		xsession->entry = g_key_file_ref(entry);
		result = g_list_prepend(result, xsession);
	}
	g_hash_table_destroy(xsessions);
	return g_list_sort(result, &xde_xsession_compare);
}

static void
xde_xsession_free(gpointer data)
{
	XdeXsession *xsess = data;

	g_free(xsess->key);
	g_free(xsess->name);
	g_key_file_free(xsess->entry);
	free(xsess);
}

void
xde_free_xsessions(GList *list)
{
	g_list_free_full(list, &xde_xsession_free);
}

char *
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

char *
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

char *
xde_character_escape(const char *string, char special)
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

gint
xde_string_compare(gconstpointer a, gconstpointer b)
{
	return strcasecmp(a, b);
}


#ifdef HAVE_GNOME_MENUS_3

static void
display_entry(FILE *file, GMenuTreeEntry *entry, int level)
{
	GDesktopAppInfo *info;
	GIcon *icon;
	const gchar *const *act;

	info = gmenu_tree_entry_get_app_info(entry);

	display_level(file, level);
	fprintf(file, "%s\n", "Menu Entry");

	level++;

	display_level(file, level);
	fprintf(file, "Name=%s\n", g_app_info_get_name(G_APP_INFO(info)));
	display_level(file, level);
	fprintf(file, "GenericName=%s\n", g_desktop_app_info_get_generic_name(info));
	display_level(file, level);
	fprintf(file, "DisplayName=%s\n", g_app_info_get_display_name(G_APP_INFO(info)));
	display_level(file, level);
	fprintf(file, "Comment=%s\n", g_app_info_get_description(G_APP_INFO(info)));
	if ((icon = g_app_info_get_icon(G_APP_INFO(info)))) {
		display_level(file, level);
		fprintf(file, "Icon=%s\n", g_icon_to_string(icon));
	}
	display_level(file, level);
	fprintf(file, "TryExec=%s\n", g_app_info_get_executable(G_APP_INFO(info)));
	display_level(file, level);
	fprintf(file, "Exec=%s\n", g_app_info_get_commandline(G_APP_INFO(info)));
	display_level(file, level);
	fprintf(file, "Terminal=%s\n",
		g_desktop_app_info_get_string(info, "Terminal") ? "true" : "false");

	display_level(file, level);
	fprintf(file, "Path=%s\n", gmenu_tree_entry_get_desktop_file_path(entry));
	display_level(file, level);
	fprintf(file, "Id=%s\n", gmenu_tree_entry_get_desktop_file_id(entry));
	display_level(file, level);
	fprintf(file, "Excluded=%s\n", gmenu_tree_entry_get_is_excluded(entry) ? "true" : "false");
	display_level(file, level);
	fprintf(file, "NoDisplay=%s\n",
		gmenu_tree_entry_get_is_nodisplay_recurse(entry) ? "true" : "false");
	display_level(file, level);
	fprintf(file, "Unallocated=%s\n",
		gmenu_tree_entry_get_is_unallocated(entry) ? "true" : "false");

	if ((act = g_desktop_app_info_list_actions(info)) && *act) {
		display_level(file, level);
		fprintf(file, "%s\n", "Menu Entry Actions");

		level++;

		while (*act) {
			display_level(file, level);
			fprintf(file, "DesktopAction=%s\n", *act);
			display_level(file, level);
			fprintf(file, "Name=%s\n", g_desktop_app_info_get_action_name(info, *act));
			act++;
		}
	}
}

static void
display_separator(FILE *file, GMenuTreeSeparator *separator, int level)
{
	display_level(file, level);
	fprintf(file, "%s\n", "Menu Separator");
}

static void
display_header(FILE *file, GMenuTreeHeader *header, int level)
{
	display_level(file, level);
	fprintf(file, "%s\n", "Menu Header");
}

static void
display_alias(FILE *file, GMenuTreeAlias *alias, int level)
{
	display_level(file, level);
	fprintf(file, "%s\n", "Menu Alias");
}

static void
display_directory(FILE* file, GMenuTreeDirectory *directory, int level)
{
	GMenuTreeIter *iter;
	GMenuTreeItemType type;
	GIcon *icon;

	display_level(file, level);
	fprintf(file, "%s\n", "Menu Directory");
	display_level(file, level + 1);
	fprintf(file, "Name=%s\n", gmenu_tree_directory_get_name(directory));
	display_level(file, level + 1);
	fprintf(file, "GenericName=%s\n", gmenu_tree_directory_get_generic_name(directory));
	display_level(file, level + 1);
	fprintf(file, "Comment=%s\n", gmenu_tree_directory_get_comment(directory));
	if ((icon = gmenu_tree_directory_get_icon(directory))) {
		display_level(file, level + 1);
		fprintf(file, "Icon=%s\n", g_icon_to_string(icon));
	}
	display_level(file, level + 1);
	fprintf(file, "Path=%s\n", gmenu_tree_directory_get_desktop_file_path(directory));
	display_level(file, level + 1);
	fprintf(file, "Id=%s\n", gmenu_tree_directory_get_menu_id(directory));
	display_level(file, level + 1);
	fprintf(file, "NoDisplay=%s\n",
		gmenu_tree_directory_get_is_nodisplay(directory) ? "true" : "false");

	iter = gmenu_tree_directory_iter(directory);
	while ((type = gmenu_tree_iter_next(iter)) != GMENU_TREE_ITEM_INVALID) {
		switch (type) {
		case GMENU_TREE_ITEM_INVALID:
			display_invalid(file, level);
			break;
		case GMENU_TREE_ITEM_DIRECTORY:
			display_directory(file, gmenu_tree_iter_get_directory(iter), level + 1);
			break;
		case GMENU_TREE_ITEM_ENTRY:
			display_entry(file, gmenu_tree_iter_get_entry(iter), level);
			break;
		case GMENU_TREE_ITEM_SEPARATOR:
			display_separator(file, gmenu_tree_iter_get_separator(iter), level);
			break;
		case GMENU_TREE_ITEM_HEADER:
			display_header(file, gmenu_tree_iter_get_header(iter), level);
			break;
		case GMENU_TREE_ITEM_ALIAS:
			display_alias(file, gmenu_tree_iter_get_alias(iter), level);
			break;
		}
	}
}

static void
print_line(gpointer string, gpointer file)
{
	fputs(string, file);
}

GList *
xde_create_simple(MenuContext *ctx, Style style, const char *name)
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

GList *
xde_build_simple(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
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

GList *
xde_menu_simple(MenuContext *ctx, GMenuTreeDirectory *menu)
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

GList *
xde_alias_simple(MenuContext *ctx, GMenuTreeAlias *als)
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

static void
make_menu(int argc, char *argv[])
{
	GList *menu;
	MenuContext *ctx;

	if (options.desktop)
		setenv("XDG_CURRENT_DESKTOP", options.desktop, TRUE);

	if (!(tree = gmenu_tree_new_for_path(options.rootmenu, 0
//					     | GMENU_TREE_FLAGS_INCLUDE_EXCLUDED
//					     | GMENU_TREE_FLAGS_INCLUDE_NODISPLAY
//					     | GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED
//					     | GMENU_TREE_FLAGS_SHOW_EMPTY
//					     | GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS
					     | GMENU_TREE_FLAGS_SORT_DISPLAY_NAME
					     ))) {
		EPRINTF("could not look up menu %s\n", options.rootmenu);
		exit(EXIT_FAILURE);
	}
	if (!gmenu_tree_load_sync(tree, NULL)) {
		EPRINTF("could not load menu %s\n", options.rootmenu);
		exit(EXIT_FAILURE);
	}
#if 0
	{
		GMenuTreeDirectory *directory;

		fprintf(stdout, "Path=%s\n", gmenu_tree_get_canonical_menu_path(tree));
		if ((directory = gmenu_tree_get_root_directory(tree))) {
			display_directory(stdout, directory, 0);
		}
	}
#else
	(void) display_directory;
#endif
	if (!(ctx = screens[0].context)) {
		EPRINTF("no menu context for screen 0\n");
		exit(EXIT_FAILURE);
	}
	ctx->tree = tree;
	ctx->level = 0;
	ctx->indent = calloc(64, sizeof(*ctx->indent));
	DPRINTF("calling create!\n");
	menu = ctx->create(ctx, options.style, NULL);
	DPRINTF("done create!\n");
	g_list_foreach(menu, print_line, stdout);
}

#else				/* HAVE_GNOME_MENUS_3 */

static void
display_entry(FILE *file, GMenuTreeEntry *entry, int level)
{
	display_level(file, level);
	fprintf(file, "%s\n", "Menu Entry");
	display_level(file, level + 1);
	fprintf(file, "Name=%s\n", gmenu_tree_entry_get_name(entry));
	display_level(file, level + 1);
	fprintf(file, "GenericName=%s\n", gmenu_tree_entry_get_generic_name(entry));
	display_level(file, level + 1);
	fprintf(file, "DisplayName=%s\n", gmenu_tree_entry_get_display_name(entry));
	display_level(file, level + 1);
	fprintf(file, "Comment=%s\n", gmenu_tree_entry_get_comment(entry));
	display_level(file, level + 1);
	fprintf(file, "Icon=%s\n", gmenu_tree_entry_get_icon(entry));
	display_level(file, level + 1);
	fprintf(file, "Exec=%s\n", gmenu_tree_entry_get_exec(entry));
	display_level(file, level + 1);
	fprintf(file, "Terminal=%s\n", gmenu_tree_entry_get_launch_in_terminal(entry) ? "true" : "false");
	display_level(file, level + 1);
	fprintf(file, "Path=%s\n", gmenu_tree_entry_get_desktop_file_path(entry));
	display_level(file, level + 1);
	fprintf(file, "Id=%s\n", gmenu_tree_entry_get_desktop_file_id(entry));
	display_level(file, level + 1);
	fprintf(file, "Excluded=%s\n", gmenu_tree_entry_get_is_excluded(entry) ? "true" : "false");
	display_level(file, level + 1);
	fprintf(file, "NoDisplay=%s\n", gmenu_tree_entry_get_is_nodisplay(entry) ? "true" : "false");
}

static void
display_separator(FILE *file, GMenuTreeSeparator *separator, int level)
{
	display_level(file, level);
	fprintf(file, "%s\n", "Menu Separator");
}

static void
display_header(FILE *file, GMenuTreeHeader *header, int level)
{
	display_level(file, level);
	fprintf(file, "%s\n", "Menu Header");
}

static void
display_alias(FILE *file, GMenuTreeAlias *alias, int level)
{
	display_level(file, level);
	fprintf(file, "%s\n", "Menu Alias");
}

struct display_context {
	int level;
	FILE *file;
};

static void
display_item(gpointer data, gpointer user_data)
{
	struct display_context *ctx = user_data;
	GMenuTreeItem *item = data;

	switch (gmenu_tree_item_get_type(item)) {
	case GMENU_TREE_ITEM_INVALID:
		display_invalid(ctx->file, ctx->level);
		break;
	case GMENU_TREE_ITEM_DIRECTORY:
		display_directory(ctx->file, GMENU_TREE_DIRECTORY(item), ctx->level + 1);
		break;
	case GMENU_TREE_ITEM_ENTRY:
		display_entry(ctx->file, GMENU_TREE_ENTRY(item), ctx->level);
		break;
	case GMENU_TREE_ITEM_SEPARATOR:
		display_separator(ctx->file, GMENU_TREE_SEPARATOR(item), ctx->level);
		break;
	case GMENU_TREE_ITEM_HEADER:
		display_header(ctx->file, GMENU_TREE_HEADER(item), ctx->level);
		break;
	case GMENU_TREE_ITEM_ALIAS:
		display_alias(ctx->file, GMENU_TREE_ALIAS(item), ctx->level);
		break;
	}
}

static void
display_directory(FILE *file, GMenuTreeDirectory *directory, int level)
{
	GSList *contents;
	struct display_context ctx = {
		.level = level,
		.file = file,
	};

	display_level(file, level);
	fprintf(file, "%s\n", "Menu Directory");
	display_level(file, level + 1);
	fprintf(file, "Name=%s\n", gmenu_tree_directory_get_name(directory));
	display_level(file, level + 1);
	fprintf(file, "Comment=%s\n", gmenu_tree_directory_get_comment(directory));
	display_level(file, level + 1);
	fprintf(file, "Icon=%s\n", gmenu_tree_directory_get_icon(directory));
	display_level(file, level + 1);
	fprintf(file, "Path=%s\n", gmenu_tree_directory_get_desktop_file_path(directory));
	display_level(file, level + 1);
	fprintf(file, "Id=%s\n", gmenu_tree_directory_get_menu_id(directory));
	display_level(file, level + 1);
	fprintf(file, "NoDisplay=%s\n", gmenu_tree_directory_get_is_nodisplay(directory) ? "true" : "false");
	contents = gmenu_tree_directory_get_contents(directory);
	g_slist_foreach(contents, display_item, &ctx);
}

static void
make_menu(int argc, char *argv[])
{
	GMenuTreeDirectory *directory;

	if (!(tree = gmenu_tree_lookup(options.rootmenu, 0))) {
		EPRINTF("could not look up menu %s\n", options.rootmenu);
		exit(EXIT_FAILURE);
	}
	if ((directory = gmenu_tree_get_root_directory(tree))) {
		display_directory(stdout, directory, 0);
	}
	gmenu_tree_unref(tree);
	tree = NULL;
}

#endif				/* HAVE_GNOME_MENUS_3 */

static Window
get_selection(Bool replace, Window selwin)
{
	char selection[64] = { 0, };
	GdkDisplay *disp;
	Display *dpy;
	int s, nscr;
	Atom atom;
	Window owner, gotone = None;

	disp = gdk_display_get_default();
	nscr = gdk_display_get_n_screens(disp);

	dpy = GDK_DISPLAY_XDISPLAY(disp);

	for (s = 0; s < nscr; s++) {
		snprintf(selection, sizeof(selection), XA_SELECTION_NAME, s);
		atom = XInternAtom(dpy, selection, False);
		if (!(owner = XGetSelectionOwner(dpy, atom)))
			DPRINTF("No owner for %s\n", selection);
		if ((owner && replace) || (!owner && selwin)) {
			DPRINTF("Setting owner of %s to 0x%08lx from 0x%08lx\n", selection, selwin,
				owner);
			XSetSelectionOwner(dpy, atom, selwin, CurrentTime);
			XSync(dpy, False);
		}
		if (!gotone && owner)
			gotone = owner;
	}
	if (replace) {
		if (gotone) {
			if (selwin)
				DPRINTF("%s: replacing running instance\n", NAME);
			else
				DPRINTF("%s: quitting running instance\n", NAME);
		} else {
			if (selwin)
				DPRINTF("%s: no running instance to replace\n", NAME);
			else
				DPRINTF("%s: no running instance to quit\n", NAME);
		}
		if (selwin) {
			XEvent ev;

			for (s = 0; s < nscr; s++) {
				snprintf(selection, sizeof(selection), XA_SELECTION_NAME, s);

				ev.xclient.type = ClientMessage;
				ev.xclient.serial = 0;
				ev.xclient.send_event = False;
				ev.xclient.display = dpy;
				ev.xclient.window = RootWindow(dpy, s);
				ev.xclient.message_type = _XA_MANAGER;
				ev.xclient.format = 32;
				ev.xclient.data.l[0] = CurrentTime;
				ev.xclient.data.l[1] = XInternAtom(dpy, selection, False);
				ev.xclient.data.l[2] = selwin;
				ev.xclient.data.l[3] = 0;
				ev.xclient.data.l[4] = 0;

				XSendEvent(dpy, RootWindow(dpy, s), False, StructureNotifyMask,
					   &ev);
				XFlush(dpy);
			}
		}
	} else if (gotone)
		DPRINTF("%s: not replacing running instance\n", NAME);
	return (gotone);
}

static MenuContext *
wm_menu_context(const char *name)
{
	char dlfile[128], *p;
	void *handle;
	MenuContext *ops = NULL;

	if (!name)
		return NULL;
	snprintf(dlfile, sizeof(dlfile), "xde-menu-%s.so", name);
	for (p = dlfile; *p; p++)
		*p = tolower(*p);
	DPRINTF("attempting to dlopen %s\n", dlfile);
	if ((handle = dlopen(dlfile, RTLD_NOW | RTLD_LOCAL))) {
		DPRINTF("dlopen of %s succeeded\n", dlfile);
		if ((ops = dlsym(handle, "xde_menu_ops")))
			ops->handle = handle;
		else
			EPRINTF("could not find symbol xde_menu_ops");
	} else
		EPRINTF("dlopen of %s failed: %s\n", dlfile, dlerror());
	return ops;
}

static void
window_manager_changed(WnckScreen *wnck, gpointer user)
{
	XdeScreen *xscr = user;
	const char *name;

	if (!xscr) {
		EPRINTF("xscr is NULL\n");
		exit(EXIT_FAILURE);
	}
	wnck_screen_force_update(wnck);
	free(xscr->wmname);
	xscr->wmname = NULL;
	xscr->goodwm = False;
	if ((name = wnck_screen_get_window_manager_name(wnck))) {
		xscr->wmname = strdup(name);
		*strchrnul(xscr->wmname, ' ') = '\0';
		/* Some versions of wmx have an error in that they only set the
		   _NET_WM_NAME to the first letter of wmx. */
		if (!strcmp(xscr->wmname, "w")) {
			free(xscr->wmname);
			xscr->wmname = strdup("wmx");
		}
		/* Ahhhh, the strange naming of μwm...  Unfortunately there are several
		   ways to make a μ in utf-8!!! */
		if (!strcmp(xscr->wmname, "\xce\xbcwm") || !strcmp(xscr->wmname, "\xc2\xb5wm")) {
			free(xscr->wmname);
			xscr->wmname = strdup("uwm");
		}
		xscr->context = wm_menu_context(xscr->wmname);
		xscr->goodwm = xscr->context ? True : False;
	}
	DPRINTF("window manager is '%s'\n", xscr->wmname);
	DPRINTF("window manager is %s\n", xscr->goodwm ? "usable" : "unusable");
}

static void
init_wnck(XdeScreen *xscr)
{
	WnckScreen *wnck = xscr->wnck = wnck_screen_get(xscr->index);

	g_signal_connect(G_OBJECT(wnck), "window_manager_changed",
			 G_CALLBACK(window_manager_changed), xscr);

	window_manager_changed(wnck, xscr);
}

static GdkFilterReturn selwin_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data);
static GdkFilterReturn root_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data);
static void update_theme(XdeScreen *xscr, Atom prop);
static void update_icon_theme(XdeScreen *xscr, Atom prop);

static void
do_generate(int argc, char *argv[])
{
	GdkDisplay *disp;
	Display *dpy;
	GdkScreen *scrn;
	GdkWindow *root, *sel;
	char selection[64] = { 0, };
	Window selwin, owner;
	XdeScreen *xscr;
	int s, nscr;

	DPRINTF("getting default GDK display\n");
	disp = gdk_display_get_default();
	DPRINTF("getting default display\n");
	dpy = GDK_DISPLAY_XDISPLAY(disp);
	DPRINTF("getting default GDK screen\n");
	scrn = gdk_display_get_default_screen(disp);
	DPRINTF("getting default GDK root window\n");
	root = gdk_screen_get_root_window(scrn);

	DPRINTF("creating select window\n");
	selwin = XCreateSimpleWindow(dpy, GDK_WINDOW_XID(root), 0, 0, 1, 1, 0, 0, 0);

	DPRINTF("checking for selection\n");
	if ((owner = get_selection(False, selwin))) {
		XDestroyWindow(dpy, selwin);
		EPRINTF("%s: an instance 0x%08lx is running\n", argv[0], owner);
		exit(EXIT_FAILURE);
	}
	DPRINTF("selecting inputs on 0x%08lx\n", selwin);
	XSelectInput(dpy, selwin,
		     StructureNotifyMask | SubstructureNotifyMask | PropertyChangeMask);

	DPRINTF("getting number of screens\n");
	nscr = gdk_display_get_n_screens(disp);
	DPRINTF("allocating %d screen structures\n", nscr);
	screens = calloc(nscr, sizeof(*screens));

	DPRINTF("getting GDK window for 0x%08lx\n", selwin);
	sel = gdk_x11_window_foreign_new_for_display(disp, selwin);
	DPRINTF("adding a filter for the select window\n");
	gdk_window_add_filter(sel, selwin_handler, screens);

	DPRINTF("initializing %d screens\n", nscr);
	for (s = 0, xscr = screens; s < nscr; s++, xscr++) {
		snprintf(selection, sizeof(selection), XA_SELECTION_NAME, s);
		xscr->index = s;
		xscr->atom = XInternAtom(dpy, selection, False);
		xscr->disp = disp;
		xscr->scrn = gdk_display_get_screen(disp, s);
		xscr->root = gdk_screen_get_root_window(xscr->scrn);
		xscr->selwin = selwin;
		gdk_window_add_filter(xscr->root, root_handler, xscr);
		init_wnck(xscr);
		update_theme(xscr, None);
		update_icon_theme(xscr, None);
	}
	make_menu(argc, argv);
}

static void
do_run(int argc, char *argv[], Bool replace)
{
	GdkDisplay *disp = gdk_display_get_default();
	Display *dpy = GDK_DISPLAY_XDISPLAY(disp);
	GdkScreen *scrn = gdk_display_get_default_screen(disp);
	GdkWindow *root = gdk_screen_get_root_window(scrn), *sel;
	char selection[64] = { 0, };
	Window selwin, owner;
	XdeScreen *xscr;
	int s, nscr;

	selwin = XCreateSimpleWindow(dpy, GDK_WINDOW_XID(root), 0, 0, 1, 1, 0, 0, 0);

	if ((owner = get_selection(replace, selwin))) {
		if (!replace) {
			XDestroyWindow(dpy, selwin);
			EPRINTF("%s: instance already running\n", NAME);
			exit(EXIT_FAILURE);
		}
	}
	XSelectInput(dpy, selwin,
		     StructureNotifyMask | SubstructureNotifyMask | PropertyChangeMask);

	nscr = gdk_display_get_n_screens(disp);
	screens = calloc(nscr, sizeof(*screens));

	sel = gdk_x11_window_foreign_new_for_display(disp, selwin);
	gdk_window_add_filter(sel, selwin_handler, screens);

	DPRINTF("initializing %d screens\n", nscr);
	for (s = 0, xscr = screens; s < nscr; s++, xscr++) {
		snprintf(selection, sizeof(selection), XA_SELECTION_NAME, s);
		xscr->index = s;
		xscr->atom = XInternAtom(dpy, selection, False);
		xscr->disp = disp;
		xscr->scrn = gdk_display_get_screen(disp, s);
		xscr->root = gdk_screen_get_root_window(xscr->scrn);
		xscr->selwin = selwin;
		gdk_window_add_filter(xscr->root, root_handler, xscr);
		init_wnck(xscr);
		update_theme(xscr, None);
		update_icon_theme(xscr, None);
	}
	make_menu(argc, argv);
	gtk_main();
}

static void
do_quit(int argc, char *argv[])
{
	get_selection(True, None);
}

static void
update_theme(XdeScreen *xscr, Atom prop)
{
	Display *dpy = GDK_DISPLAY_XDISPLAY(xscr->disp);
	Window root = RootWindow(dpy, xscr->index);
	XTextProperty xtp = { NULL, };
	Bool changed = False;
	GtkSettings *set;

	gtk_rc_reparse_all();
	if (!prop || prop == _XA_GTK_READ_RCFILES)
		prop = _XA_XDE_THEME_NAME;
	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		char **list = NULL;
		int strings = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, &list, &strings) == Success) {
			if (strings >= 1) {
				static const char *prefix = "gtk-theme-name=\"";
				static const char *suffix = "\"";
				char *rc_string;
				int len;

				len = strlen(prefix) + strlen(list[0]) + strlen(suffix);
				rc_string = calloc(len + 1, sizeof(*rc_string));
				strncpy(rc_string, prefix, len);
				strncat(rc_string, list[0], len);
				strncat(rc_string, suffix, len);
				gtk_rc_parse_string(rc_string);
				free(rc_string);
				if (!xscr->theme || strcmp(xscr->theme, list[0])) {
					free(xscr->theme);
					xscr->theme = strdup(list[0]);
					changed = True;
				}
			}
			if (list)
				XFreeStringList(list);
		} else
			EPRINTF("could not get text list for property\n");
		if (xtp.value)
			XFree(xtp.value);
	} else
		DPRINTF("could not get %s for root 0x%lx\n", XGetAtomName(dpy, prop), root);
	if ((set = gtk_settings_get_for_screen(xscr->scrn))) {
		GValue theme_v = G_VALUE_INIT;
		const char *theme;

		g_value_init(&theme_v, G_TYPE_STRING);
		g_object_get_property(G_OBJECT(set), "gtk-theme-name", &theme_v);
		theme = g_value_get_string(&theme_v);
		if (theme && (!xscr->theme || strcmp(xscr->theme, theme))) {
			free(xscr->theme);
			xscr->theme = strdup(theme);
			changed = True;
		}
		g_value_unset(&theme_v);
	}
	if (changed) {
		DPRINTF("New theme is %s\n", xscr->theme);
		/* FIXME: do somthing more about it. */
	}
}

static void
update_icon_theme(XdeScreen *xscr, Atom prop)
{
	Display *dpy = GDK_DISPLAY_XDISPLAY(xscr->disp);
	Window root = RootWindow(dpy, xscr->index);
	XTextProperty xtp = { NULL, };
	Bool changed = False;
	GtkSettings *set;

	gtk_rc_reparse_all();
	if (!prop || prop == _XA_GTK_READ_RCFILES)
		prop = _XA_XDE_ICON_THEME_NAME;
	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		char **list = NULL;
		int strings = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, &list, &strings) == Success) {
			if (strings >= 1) {
				static const char *prefix = "gtk-icon-theme-name=\"";
				static const char *suffix = "\"";
				char *rc_string;
				int len;

				len = strlen(prefix) + strlen(list[0]) + strlen(suffix);
				rc_string = calloc(len + 1, sizeof(*rc_string));
				strncpy(rc_string, prefix, len);
				strncat(rc_string, list[0], len);
				strncat(rc_string, suffix, len);
				gtk_rc_parse_string(rc_string);
				free(rc_string);
				if (!xscr->itheme || strcmp(xscr->itheme, list[0])) {
					free(xscr->itheme);
					xscr->itheme = strdup(list[0]);
					changed = True;
				}
			}
			if (list)
				XFreeStringList(list);
		} else
			EPRINTF("could not get text list for property\n");
		if (xtp.value)
			XFree(xtp.value);
	} else
		DPRINTF("could not get %s for root 0x%lx\n", XGetAtomName(dpy, prop), root);
	if ((set = gtk_settings_get_for_screen(xscr->scrn))) {
		GValue theme_v = G_VALUE_INIT;
		const char *itheme;

		g_value_init(&theme_v, G_TYPE_STRING);
		g_object_get_property(G_OBJECT(set), "gtk-icon-theme-name", &theme_v);
		itheme = g_value_get_string(&theme_v);
		if (itheme && (!xscr->itheme || strcmp(xscr->itheme, itheme))) {
			free(xscr->itheme);
			xscr->itheme = strdup(itheme);
			changed = True;
		}
		g_value_unset(&theme_v);
	}
	if (changed) {
		DPRINTF("New icon theme is %s\n", xscr->itheme);
		/* FIXME: do something more about it. */
	}
}

static GdkFilterReturn
event_handler_PropertyNotify(Display *dpy, XEvent *xev, XdeScreen *xscr)
{
	Atom atom;

	if (options.debug > 2) {
		fprintf(stderr, "==> PropertyNotify:\n");
		fprintf(stderr, "    --> window = 0x%08lx\n", xev->xproperty.window);
		fprintf(stderr, "    --> atom = %s\n", XGetAtomName(dpy, xev->xproperty.atom));
		fprintf(stderr, "    --> time = %ld\n", xev->xproperty.time);
		fprintf(stderr, "    --> state = %s\n",
			(xev->xproperty.state == PropertyNewValue) ? "NewValue" : "Delete");
		fprintf(stderr, "<== PropertyNotify:\n");
	}
	atom = xev->xproperty.atom;

	if (xev->xproperty.state == PropertyNewValue) {
		if (atom == _XA_XDE_THEME_NAME || atom == _XA_XDE_WM_THEME) {
			update_theme(xscr, xev->xproperty.atom);
			return GDK_FILTER_REMOVE;
		} else if (atom == _XA_XDE_ICON_THEME_NAME || atom == _XA_XDE_WM_ICONTHEME) {
			update_icon_theme(xscr, xev->xproperty.atom);
			return GDK_FILTER_REMOVE;
		}
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
event_handler_ClientMessage(Display *dpy, XEvent *xev)
{
	XdeScreen *xscr = NULL;
	int s, nscr = ScreenCount(dpy);

	for (s = 0; s < nscr; s++)
		if (xev->xclient.window == RootWindow(dpy, s))
			xscr = screens + s;
	if (options.debug) {
		fprintf(stderr, "==> ClientMessage: %p\n", xscr);
		fprintf(stderr, "    --> window = 0x%08lx\n", xev->xclient.window);
		fprintf(stderr, "    --> message_type = %s\n",
			XGetAtomName(dpy, xev->xclient.message_type));
		fprintf(stderr, "    --> format = %d\n", xev->xclient.format);
		switch (xev->xclient.format) {
			int i;

		case 8:
			fprintf(stderr, "    --> data =");
			for (i = 0; i < 20; i++)
				fprintf(stderr, " %02x", (int) xev->xclient.data.b[i]);
			fprintf(stderr, "\n");
			break;
		case 16:
			fprintf(stderr, "    --> data =");
			for (i = 0; i < 10; i++)
				fprintf(stderr, " %04x", (int) xev->xclient.data.s[i]);
			fprintf(stderr, "\n");
			break;
		case 32:
			fprintf(stderr, "    --> data =");
			for (i = 0; i < 20; i++)
				fprintf(stderr, " %08lx", xev->xclient.data.l[i]);
			fprintf(stderr, "\n");
			break;
		}
		fprintf(stderr, "<== ClientMessage: %p\n", xscr);
	}
	if (xscr && xev->xclient.message_type == _XA_GTK_READ_RCFILES) {
		update_theme(xscr, xev->xclient.message_type);
		update_icon_theme(xscr, xev->xclient.message_type);
		return GDK_FILTER_REMOVE;
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
event_handler_SelectionClear(Display *dpy, XEvent *xev, XdeScreen *xscr)
{
	DPRINT();
	if (options.debug > 1) {
		fprintf(stderr, "==> SelectionClear: %p\n", xscr);
		fprintf(stderr, "    --> send_event = %s\n",
			xev->xselectionclear.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%08lx\n", xev->xselectionclear.window);
		fprintf(stderr, "    --> selection = %s\n",
			XGetAtomName(dpy, xev->xselectionclear.selection));
		fprintf(stderr, "    --> time = %lu\n", xev->xselectionclear.time);
		fprintf(stderr, "<== SelectionClear: %p\n", xscr);
	}
	if (xscr && xev->xselectionclear.window == xscr->selwin) {
		XDestroyWindow(dpy, xscr->selwin);
		EPRINTF("selection cleared, exiting\n");
		exit(EXIT_SUCCESS);
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
root_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;
	XdeScreen *xscr = (typeof(xscr)) data;
	Display *dpy = GDK_DISPLAY_XDISPLAY(xscr->disp);

	DPRINT();
	if (!xscr) {
		EPRINTF("xscr is NULL\n");
		exit(EXIT_FAILURE);
	}
	switch (xev->type) {
	case PropertyNotify:
		return event_handler_PropertyNotify(dpy, xev, xscr);
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
selwin_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;
	XdeScreen *xscr = (typeof(xscr)) data;
	Display *dpy = GDK_DISPLAY_XDISPLAY(xscr->disp);

	DPRINT();
	if (!xscr) {
		EPRINTF("xscr is NULL\n");
		exit(EXIT_FAILURE);
	}
	switch (xev->type) {
	case SelectionClear:
		return event_handler_SelectionClear(dpy, xev, xscr);
	}
	EPRINTF("wrong message type for handler %d\n", xev->type);
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
client_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;
	Display *dpy = (typeof(dpy)) data;

	DPRINT();
	switch (xev->type) {
	case ClientMessage:
		return event_handler_ClientMessage(dpy, xev);
	}
	EPRINTF("wrong message type for handler %d\n", xev->type);
	return GDK_FILTER_CONTINUE;
}

static void
clientSetProperties(SmcConn smcConn, SmPointer data)
{
	char userID[20];
	int i, j, argc = saveArgc;
	char **argv = saveArgv;
	char *cwd = NULL;
	char hint;
	struct passwd *pw;
	SmPropValue *penv = NULL, *prst = NULL, *pcln = NULL;
	SmPropValue propval[11];
	SmProp prop[11];

	SmProp *props[11] = {
		&prop[0], &prop[1], &prop[2], &prop[3], &prop[4],
		&prop[5], &prop[6], &prop[7], &prop[8], &prop[9],
		&prop[10]
	};

	j = 0;

	/* CloneCommand: This is like the RestartCommand except it restarts a copy of the 
	   application.  The only difference is that the application doesn't supply its
	   client id at register time.  On POSIX systems the type should be a
	   LISTofARRAY8. */
	prop[j].name = SmCloneCommand;
	prop[j].type = SmLISTofARRAY8;
	prop[j].vals = pcln = calloc(argc, sizeof(*pcln));
	prop[j].num_vals = 0;
	props[j] = &prop[j];
	for (i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-clientId") || !strcmp(argv[i], "-restore"))
			i++;
		else {
			prop[j].vals[prop[j].num_vals].value = (SmPointer) argv[i];
			prop[j].vals[prop[j].num_vals++].length = strlen(argv[i]);
		}
	}
	j++;

#if 0
	/* CurrentDirectory: On POSIX-based systems, specifies the value of the current
	   directory that needs to be set up prior to starting the program and should be
	   of type ARRAY8. */
	prop[j].name = SmCurrentDirectory;
	prop[j].type = SmARRAY8;
	prop[j].vals = &propval[j];
	prop[j].num_vals = 1;
	props[j] = &prop[j];
	propval[j].value = NULL;
	propval[j].length = 0;
	cwd = calloc(PATH_MAX + 1, sizeof(propval[j].value[0]));
	if (getcwd(cwd, PATH_MAX)) {
		propval[j].value = cwd;
		propval[j].length = strlen(propval[j].value);
		j++;
	} else {
		free(cwd);
		cwd = NULL;
	}
#endif

#if 0
	/* DiscardCommand: The discard command contains a command that when delivered to
	   the host that the client is running on (determined from the connection), will
	   cause it to discard any information about the current state.  If this command
	   is not specified, the SM will assume that all of the client's state is encoded
	   in the RestartCommand [and properties].  On POSIX systems the type should be
	   LISTofARRAY8. */
	prop[j].name = SmDiscardCommand;
	prop[j].type = SmLISTofARRAY8;
	prop[j].vals = &propval[j];
	prop[j].num_vals = 1;
	props[j] = &prop[j];
	propval[j].value = "/bin/true";
	propval[j].length = strlen("/bin/true");
	j++;
#endif

#if 0
	char **env;

	/* Environment: On POSIX based systems, this will be of type LISTofARRAY8 where
	   the ARRAY8s alternate between environment variable name and environment
	   variable value. */
	/* XXX: we might want to filter a few out */
	for (i = 0, env = environ; *env; i += 2, env++) ;
	prop[j].name = SmEnvironment;
	prop[j].type = SmLISTofARRAY8;
	prop[j].vals = penv = calloc(i, sizeof(*penv));
	prop[j].num_vals = i;
	props[j] = &prop[j];
	for (i = 0, env = environ; *env; i += 2, env++) {
		char *equal;
		int len;

		equal = strchrnul(*env, '=');
		len = (int) (*env - equal);
		if (*equal)
			equal++;
		prop[j].vals[i].value = *env;
		prop[j].vals[i].length = len;
		prop[j].vals[i + 1].value = equal;
		prop[j].vals[i + 1].length = strlen(equal);
	}
	j++;
#endif

#if 0
	char procID[20];

	/* ProcessID: This specifies an OS-specific identifier for the process. On POSIX
	   systems this should be of type ARRAY8 and contain the return of getpid()
	   turned into a Latin-1 (decimal) string. */
	prop[j].name = SmProcessID;
	prop[j].type = SmARRAY8;
	prop[j].vals = &propval[j];
	prop[j].num_vals = 1;
	props[j] = &prop[j];
	snprintf(procID, sizeof(procID), "%ld", (long) getpid());
	propval[j].value = procID;
	propval[j].length = strlen(procID);
	j++;
#endif

	/* Program: The name of the program that is running.  On POSIX systems, this
	   should eb the first parameter passed to execve(3) and should be of type
	   ARRAY8. */
	prop[j].name = SmProgram;
	prop[j].type = SmARRAY8;
	prop[j].vals = &propval[j];
	prop[j].num_vals = 1;
	props[j] = &prop[j];
	propval[j].value = argv[0];
	propval[j].length = strlen(argv[0]);
	j++;

	/* RestartCommand: The restart command contains a command that when delivered to
	   the host that the client is running on (determined from the connection), will
	   cause the client to restart in its current state.  On POSIX-based systems this 
	   if of type LISTofARRAY8 and each of the elements in the array represents an
	   element in the argv[] array.  This restart command should ensure that the
	   client restarts with the specified client-ID.  */
	prop[j].name = SmRestartCommand;
	prop[j].type = SmLISTofARRAY8;
	prop[j].vals = prst = calloc(argc + 4, sizeof(*prst));
	prop[j].num_vals = 0;
	props[j] = &prop[j];
	for (i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-clientId") || !strcmp(argv[i], "-restore"))
			i++;
		else {
			prop[j].vals[prop[j].num_vals].value = (SmPointer) argv[i];
			prop[j].vals[prop[j].num_vals++].length = strlen(argv[i]);
		}
	}
	prop[j].vals[prop[j].num_vals].value = (SmPointer) "-clientId";
	prop[j].vals[prop[j].num_vals++].length = 9;
	prop[j].vals[prop[j].num_vals].value = (SmPointer) options.clientId;
	prop[j].vals[prop[j].num_vals++].length = strlen(options.clientId);

	prop[j].vals[prop[j].num_vals].value = (SmPointer) "-restore";
	prop[j].vals[prop[j].num_vals++].length = 9;
	prop[j].vals[prop[j].num_vals].value = (SmPointer) options.saveFile;
	prop[j].vals[prop[j].num_vals++].length = strlen(options.saveFile);
	j++;

	/* ResignCommand: A client that sets the RestartStyleHint to RestartAnyway uses
	   this property to specify a command that undoes the effect of the client and
	   removes any saved state. */
	prop[j].name = SmResignCommand;
	prop[j].type = SmLISTofARRAY8;
	prop[j].vals = calloc(2, sizeof(*prop[j].vals));
	prop[j].num_vals = 2;
	props[j] = &prop[j];
	prop[j].vals[0].value = "/usr/bin/xde-pager";
	prop[j].vals[0].length = strlen("/usr/bin/xde-pager");
	prop[j].vals[1].value = "-quit";
	prop[j].vals[1].length = strlen("-quit");
	j++;

	/* RestartStyleHint: If the RestartStyleHint property is present, it will contain 
	   the style of restarting the client prefers.  If this flag is not specified,
	   RestartIfRunning is assumed.  The possible values are as follows:
	   RestartIfRunning(0), RestartAnyway(1), RestartImmediately(2), RestartNever(3). 
	   The RestartIfRunning(0) style is used in the usual case.  The client should be 
	   restarted in the next session if it is connected to the session manager at the
	   end of the current session. The RestartAnyway(1) style is used to tell the SM
	   that the application should be restarted in the next session even if it exits
	   before the current session is terminated. It should be noted that this is only
	   a hint and the SM will follow the policies specified by its users in
	   determining what applications to restart.  A client that uses RestartAnyway(1)
	   should also set the ResignCommand and ShutdownCommand properties to the
	   commands that undo the state of the client after it exits.  The
	   RestartImmediately(2) style is like RestartAnyway(1) but in addition, the
	   client is meant to run continuously.  If the client exits, the SM should try to 
	   restart it in the current session.  The RestartNever(3) style specifies that
	   the client does not wish to be restarted in the next session. */
	prop[j].name = SmRestartStyleHint;
	prop[j].type = SmARRAY8;
	prop[j].vals = &propval[0];
	prop[j].num_vals = 1;
	props[j] = &prop[j];
	hint = SmRestartImmediately;	/* <--- */
	propval[j].value = &hint;
	propval[j].length = 1;
	j++;

	/* ShutdownCommand: This command is executed at shutdown time to clean up after a 
	   client that is no longer running but retained its state by setting
	   RestartStyleHint to RestartAnyway(1).  The command must not remove any saved
	   state as the client is still part of the session. */
	prop[j].name = SmShutdownCommand;
	prop[j].type = SmLISTofARRAY8;
	prop[j].vals = calloc(2, sizeof(*prop[j].vals));
	prop[j].num_vals = 2;
	props[j] = &prop[j];
	prop[j].vals[0].value = "/usr/bin/xde-pager";
	prop[j].vals[0].length = strlen("/usr/bin/xde-pager");
	prop[j].vals[1].value = "-quit";
	prop[j].vals[1].length = strlen("-quit");
	j++;

	/* UserID: Specifies the user's ID.  On POSIX-based systems this will contain the 
	   user's name (the pw_name field of struct passwd).  */
	errno = 0;
	prop[j].name = SmUserID;
	prop[j].type = SmARRAY8;
	prop[j].vals = &propval[j];
	prop[j].num_vals = 1;
	props[j] = &prop[j];
	if ((pw = getpwuid(getuid())))
		strncpy(userID, pw->pw_name, sizeof(userID) - 1);
	else {
		EPRINTF("%s: %s\n", "getpwuid()", strerror(errno));
		snprintf(userID, sizeof(userID), "%ld", (long) getuid());
	}
	propval[j].value = userID;
	propval[j].length = strlen(userID);
	j++;

	SmcSetProperties(smcConn, j, props);

	free(cwd);
	free(pcln);
	free(prst);
	free(penv);
}

static Bool saving_yourself;
static Bool shutting_down;

static void
clientSaveYourselfPhase2CB(SmcConn smcConn, SmPointer data)
{
	clientSetProperties(smcConn, data);
	SmcSaveYourselfDone(smcConn, True);
}

/** @brief save yourself
  *
  * The session manager sends a "Save Yourself" message to a client either to
  * check-point it or just before termination so that it can save its state.
  * The client responds with zero or more calls to SmcSetProperties to update
  * the properties indicating how to restart the client.  When all the
  * properties have been set, the client calls SmcSaveYourselfDone.
  *
  * If interact_type is SmcInteractStyleNone, the client must not interact with
  * the user while saving state.  If interact_style is SmInteractStyleErrors,
  * the client may interact with the user only if an error condition arises.  If
  * interact_style is  SmInteractStyleAny then the client may interact with the
  * user for any purpose.  Because only one client can interact with the user at
  * a time, the client must call SmcInteractRequest and wait for an "Interact"
  * message from the session maanger.  When the client is done interacting with
  * the user, it calls SmcInteractDone.  The client may only call
  * SmcInteractRequest() after it receives a "Save Yourself" message and before
  * it calls SmcSaveYourSelfDone().
  */
static void
clientSaveYourselfCB(SmcConn smcConn, SmPointer data, int saveType, Bool shutdown,
		     int interactStyle, Bool fast)
{
	if (!(shutting_down = shutdown)) {
		if (!SmcRequestSaveYourselfPhase2(smcConn, clientSaveYourselfPhase2CB, data))
			SmcSaveYourselfDone(smcConn, False);
		return;
	}
	clientSetProperties(smcConn, data);
	SmcSaveYourselfDone(smcConn, True);
}

/** @brief die
  *
  * The session manager sends a "Die" message to a client when it wants it to
  * die.  The client should respond by calling SmcCloseConnection.  A session
  * manager that behaves properly will send a "Save Yourself" message before the
  * "Die" message.
  */
static void
clientDieCB(SmcConn smcConn, SmPointer data)
{
	SmcCloseConnection(smcConn, 0, NULL);
	shutting_down = False;
	gtk_main_quit();
}

static void
clientSaveCompleteCB(SmcConn smcConn, SmPointer data)
{
	if (saving_yourself) {
		saving_yourself = False;
		gtk_main_quit();
	}

}

/** @brief shutdown cancelled
  *
  * The session manager sends a "Shutdown Cancelled" message when the user
  * cancelled the shutdown during an interaction (see Section 5.5, "Interacting
  * With the User").  The client can now continue as if the shutdown had never
  * happended.  If the client has not called SmcSaveYourselfDone() yet, it can
  * either abort the save and then send SmcSaveYourselfDone() with the success
  * argument set to False or it can continue with the save and then call
  * SmcSaveYourselfDone() with the success argument set to reflect the outcome
  * of the save.
  */
static void
clientShutdownCancelledCB(SmcConn smcConn, SmPointer data)
{
	shutting_down = False;
	gtk_main_quit();
}

/* *INDENT-OFF* */
static unsigned long clientCBMask =
	SmcSaveYourselfProcMask |
	SmcDieProcMask |
	SmcSaveCompleteProcMask |
	SmcShutdownCancelledProcMask;

static SmcCallbacks clientCBs = {
	.save_yourself = {
		.callback = &clientSaveYourselfCB,
		.client_data = NULL,
	},
	.die = {
		.callback = &clientDieCB,
		.client_data = NULL,
	},
	.save_complete = {
		.callback = &clientSaveCompleteCB,
		.client_data = NULL,
	},
	.shutdown_cancelled = {
		.callback = &clientShutdownCancelledCB,
		.client_data = NULL,
	},
};
/* *INDENT-ON* */

static gboolean
on_ifd_watch(GIOChannel *chan, GIOCondition cond, pointer data)
{
	SmcConn smcConn = data;
	IceConn iceConn = SmcGetIceConnection(smcConn);

	if (cond & (G_IO_NVAL | G_IO_HUP | G_IO_ERR)) {
		EPRINTF("poll failed: %s %s %s\n",
			(cond & G_IO_NVAL) ? "NVAL" : "",
			(cond & G_IO_HUP) ? "HUP" : "", (cond & G_IO_ERR) ? "ERR" : "");
		return G_SOURCE_REMOVE;	/* remove event source */
	} else if (cond & (G_IO_IN | G_IO_PRI)) {
		IceProcessMessages(iceConn, NULL, NULL);
	}
	return G_SOURCE_CONTINUE;	/* keep event source */
}

static void
init_smclient(void)
{
	char err[256] = { 0, };
	GIOChannel *chan;
	int ifd, mask = G_IO_IN | G_IO_ERR | G_IO_HUP | G_IO_PRI;
	char *env;
	SmcConn smcConn;
	IceConn iceConn;

	if (!(env = getenv("SESSION_MANAGER"))) {
		if (options.clientId)
			EPRINTF("clientId provided but no SESSION_MANAGER\n");
		return;
	}
	smcConn = SmcOpenConnection(env, NULL, SmProtoMajor, SmProtoMinor,
				    clientCBMask, &clientCBs, options.clientId,
				    &options.clientId, sizeof(err), err);
	if (!smcConn) {
		EPRINTF("SmcOpenConnection: %s\n", err);
		return;
	}
	iceConn = SmcGetIceConnection(smcConn);
	ifd = IceConnectionNumber(iceConn);
	chan = g_io_channel_unix_new(ifd);
	g_io_add_watch(chan, mask, on_ifd_watch, smcConn);
}

static void
startup(int argc, char *argv[])
{
	static const char *suffix = "/.gtkrc-2.0.xde";
	const char *home;
	GdkAtom atom;
	GdkEventMask mask;
	GdkDisplay *disp;
	GdkScreen *scrn;
	GdkWindow *root;
	Display *dpy;
	char *file;
	int len;

	home = getenv("HOME") ? : ".";
	len = strlen(home) + strlen(suffix);
	file = calloc(len + 1, sizeof(*file));
	strncpy(file, home, len);
	strncat(file, suffix, len);
	gtk_rc_add_default_file(file);
	free(file);

	init_smclient();

	gtk_init(&argc, &argv);

	disp = gdk_display_get_default();
	dpy = GDK_DISPLAY_XDISPLAY(disp);

	atom = gdk_atom_intern_static_string("_XDE_ICON_THEME_NAME");
	_XA_XDE_ICON_THEME_NAME = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_THEME_NAME");
	_XA_XDE_THEME_NAME = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_CLASS");
	_XA_XDE_WM_CLASS = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_CMDLINE");
	_XA_XDE_WM_CMDLINE = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_COMMAND");
	_XA_XDE_WM_COMMAND = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_ETCDIR");
	_XA_XDE_WM_ETCDIR = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_HOST");
	_XA_XDE_WM_HOST = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_HOSTNAME");
	_XA_XDE_WM_HOSTNAME = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_ICCCM_SUPPORT");
	_XA_XDE_WM_ICCCM_SUPPORT = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_ICON");
	_XA_XDE_WM_ICON = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_ICONTHEME");
	_XA_XDE_WM_ICONTHEME = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_INFO");
	_XA_XDE_WM_INFO = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_MENU");
	_XA_XDE_WM_MENU = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_NAME");
	_XA_XDE_WM_NAME = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_NETWM_SUPPORT");
	_XA_XDE_WM_NETWM_SUPPORT = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_PID");
	_XA_XDE_WM_PID = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_PRVDIR");
	_XA_XDE_WM_PRVDIR = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_RCFILE");
	_XA_XDE_WM_RCFILE = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_REDIR_SUPPORT");
	_XA_XDE_WM_REDIR_SUPPORT = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_STYLE");
	_XA_XDE_WM_STYLE = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_STYLENAME");
	_XA_XDE_WM_STYLENAME = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_SYSDIR");
	_XA_XDE_WM_SYSDIR = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_THEME");
	_XA_XDE_WM_THEME = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_THEMEFILE");
	_XA_XDE_WM_THEMEFILE = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_USRDIR");
	_XA_XDE_WM_USRDIR = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XDE_WM_VERSION");
	_XA_XDE_WM_VERSION = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_GTK_READ_RCFILES");
	_XA_GTK_READ_RCFILES = gdk_x11_atom_to_xatom_for_display(disp, atom);
	gdk_display_add_client_message_filter(disp, atom, client_handler, dpy);

	atom = gdk_atom_intern_static_string("MANAGER");
	_XA_MANAGER = gdk_x11_atom_to_xatom_for_display(disp, atom);

	scrn = gdk_display_get_default_screen(disp);
	root = gdk_screen_get_root_window(scrn);
	mask = gdk_window_get_events(root);
	mask |= GDK_PROPERTY_CHANGE_MASK | GDK_STRUCTURE_MASK | GDK_SUBSTRUCTURE_MASK;
	gdk_window_set_events(root, mask);

	wnck_set_client_type(WNCK_CLIENT_TYPE_PAGER);
}

static void
copying(int argc, char *argv[])
{
	if (!options.output && !options.debug)
		return;
	(void) fprintf(stdout, "\
--------------------------------------------------------------------------------\n\
%1$s\n\
--------------------------------------------------------------------------------\n\
Copyright (c) 2008-2015  Monavacon Limited <http://www.monavacon.com/>\n\
Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>\n\
Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>\n\
\n\
All Rights Reserved.\n\
--------------------------------------------------------------------------------\n\
This program is free software: you can  redistribute it  and/or modify  it under\n\
the terms of the  GNU Affero  General  Public  License  as published by the Free\n\
Software Foundation, version 3 of the license.\n\
\n\
This program is distributed in the hope that it will  be useful, but WITHOUT ANY\n\
WARRANTY; without even  the implied warranty of MERCHANTABILITY or FITNESS FOR A\n\
PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.\n\
\n\
You should have received a copy of the  GNU Affero General Public License  along\n\
with this program.   If not, see <http://www.gnu.org/licenses/>, or write to the\n\
Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.\n\
--------------------------------------------------------------------------------\n\
U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on behalf\n\
of the U.S. Government (\"Government\"), the following provisions apply to you. If\n\
the Software is supplied by the Department of Defense (\"DoD\"), it is classified\n\
as \"Commercial  Computer  Software\"  under  paragraph  252.227-7014  of the  DoD\n\
Supplement  to the  Federal Acquisition Regulations  (\"DFARS\") (or any successor\n\
regulations) and the  Government  is acquiring  only the  license rights granted\n\
herein (the license rights customarily provided to non-Government users). If the\n\
Software is supplied to any unit or agency of the Government  other than DoD, it\n\
is  classified as  \"Restricted Computer Software\" and the Government's rights in\n\
the Software  are defined  in  paragraph 52.227-19  of the  Federal  Acquisition\n\
Regulations (\"FAR\")  (or any successor regulations) or, in the cases of NASA, in\n\
paragraph  18.52.227-86 of  the  NASA  Supplement  to the FAR (or any  successor\n\
regulations).\n\
--------------------------------------------------------------------------------\n\
", NAME " " VERSION);
}

static void
version(int argc, char *argv[])
{
	if (!options.output && !options.debug)
		return;
	(void) fprintf(stdout, "\
%1$s (OpenSS7 %2$s) %3$s\n\
Written by Brian Bidulock.\n\
\n\
Copyright (c) 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015  Monavacon Limited.\n\
Copyright (c) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008  OpenSS7 Corporation.\n\
Copyright (c) 1997, 1998, 1999, 2000, 2001  Brian F. G. Bidulock.\n\
This is free software; see the source for copying conditions.  There is NO\n\
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\
\n\
Distributed by OpenSS7 under GNU Affero General Public License Version 3,\n\
with conditions, incorporated herein by reference.\n\
\n\
See `%1$s --copying' for copying permissions.\n\
", NAME, PACKAGE, VERSION);
}

static void
usage(int argc, char *argv[])
{
	if (!options.output && !options.debug)
		return;
	(void) fprintf(stderr, "\
Usage:\n\
    %1$s [options]\n\
    %1$s {-m|--monitor} [options]\n\
    %1$s {-R|--replace} [options]\n\
    %1$s {-q|--quit} [options]\n\
    %1$s {-h|--help} [options]\n\
    %1$s {-V|--version}\n\
    %1$s {-C|--copying}\n\
", argv[0]);
}

const char *
show_bool(Bool boolval)
{
	if (boolval)
		return ("true");
	return ("false");
}

const char *
show_style(Style style)
{
	switch (style) {
	case StyleFullmenu:
		return ("fullmenu");
	case StyleAppmenu:
		return ("appmenu");
	case StyleEntries:
		return ("entries");
	}
	return ("(unknown)");
}

static void
help(int argc, char *argv[])
{
	if (!options.output && !options.debug)
		return;
	/* *INDENT-OFF* */
	(void) fprintf(stdout, "\
Usage:\n\
    %1$s [options]\n\
    %1$s {-m|--monitor} [options]\n\
    %1$s {-R|--replace} [options]\n\
    %1$s {-q|--quit} [options]\n\
    %1$s {-h|--help} [options]\n\
    %1$s {-V|--version}\n\
    %1$s {-C|--copying}\n\
Command options:\n\
    -m, --monitor\n\
        generate a menu and monitor for changes\n\
    -R, --replace\n\
        replace a running instance\n\
    -q, --quit\n\
        ask a running instance to quit\n\
    -h, --help, -?, --?\n\
        print this usage information and exit\n\
    -V, --version\n\
        print version and exit\n\
    -C, --copying\n\
        print copying permission and exit\n\
Options:\n\
    -f, --format FORMAT\n\
        specify the menu format [default: %2$s]\n\
    -F, --fullmenu, -N, --nofullmenu\n\
        full menu or applications menu [default: %3$s]\n\
    -d, --desktop DESKTOP\n\
        desktop environment [default: %4$s]\n\
    -c, --charset CHARSET\n\
        character set for menu [default: %5$s]\n\
    -l, --language LANGUAGE\n\
        language for menu [default: %6$s]\n\
    -r, --root-menu MENU\n\
        root menu file [default: %7$s]\n\
    -e, --die-on-error\n\
        abort on error [default: %8$s]\n\
    -o, --output [OUTPUT]\n\
        output file [default: %9$s]\n\
    -n, --noicons\n\
        do not place icons in menu [default: %10$s]\n\
    -t, --theme THEME\n\
        icon theme name to use [default: %11$s]\n\
    -L, --launch, --nolaunch\n\
        use xde-launch to launch programs [default: %12$s]\n\
    -s, --style STYLE\n\
        fullmenu, appmenu or entries [default: %13$s]\n\
    -M, --menu MENU\n\
        filename stem of root menu filename [default: %16$s]\n\
    -D, --debug [LEVEL]\n\
        increment or set debug LEVEL [default: %14$d]\n\
    -v, --verbose [LEVEL]\n\
        increment or set output verbosity LEVEL [default: %15$d]\n\
        this option may be repeated.\n\
", argv[0] 
	, defaults.format
	, show_style(defaults.style)
	, defaults.desktop
	, defaults.charset
	, defaults.language
	, defaults.rootmenu
	, show_bool(defaults.dieonerr)
	, defaults.filename
	, show_bool(defaults.noicons)
	, defaults.theme
	, show_bool(defaults.launch)
	, show_style(defaults.style)
	, defaults.debug
	, defaults.output
	, defaults.menu
);
	/* *INDENT-ON* */
}

static void
set_default_paths()
{
	char *env, *p, *e;
	int len;

	if ((env = getenv("XDG_DATA_HOME")))
		xdg_data_home = strdup(env);
	else {
		static const char *suffix = "/.local/share";

		env = getenv("HOME") ? : "~";
		len = strlen(env) + strlen(suffix) + 1;
		xdg_data_home = calloc(len, sizeof(*xdg_data_home));
		strcpy(xdg_data_home, env);
		strcat(xdg_data_home, suffix);
	}
	env = getenv("XDG_DATA_DIRS") ? : "/usr/local/share:/usr/share";
	xdg_data_dirs = strdup(env);
	len = strlen(xdg_data_home) + 1 + strlen(xdg_data_dirs) + 1;
	xdg_data_path = calloc(len, sizeof(*xdg_data_path));
	strcpy(xdg_data_path, xdg_data_home);
	strcat(xdg_data_path, ":");
	strcat(xdg_data_path, xdg_data_dirs);
	xdg_data_last = xdg_data_path + strlen(xdg_data_path);
	DPRINTF("Full data path is: '%s'\n", xdg_data_path);
	p = xdg_data_path;
	e = xdg_data_last;
	while ((p = strchrnul(p, ':')) < e)
		*p++ = '\0';
	DPRINTF("Directories in forward order:\n");
	for (p = xdg_data_path; p < xdg_data_last; p += strlen(p) + 1) {
		DPRINTF("\t%s\n", p);
	}
	DPRINTF("Directories in reverse order:\n");
	for (p = xdg_find_str(xdg_data_last, xdg_data_path);
	     p >= xdg_data_path; p = xdg_find_str(p - 1, xdg_data_path)) {
		DPRINTF("\t%s\n", p);
	}

	if ((env = getenv("XDG_CONFIG_HOME")))
		xdg_config_home = strdup(env);
	else {
		static const char *suffix = "/.config";

		env = getenv("HOME") ? : "~";
		len = strlen(env) + strlen(suffix) + 1;
		xdg_config_home = calloc(len, sizeof(*xdg_config_home));
		strcpy(xdg_config_home, env);
		strcat(xdg_config_home, suffix);
	}
	env = getenv("XDG_CONFIG_DIRS") ? : "/etc/xdg";
	xdg_config_dirs = strdup(env);
	len = strlen(xdg_config_home) + 1 + strlen(xdg_config_dirs) + 1;
	xdg_config_path = calloc(len, sizeof(*xdg_config_path));
	strcpy(xdg_config_path, xdg_config_home);
	strcat(xdg_config_path, ":");
	strcat(xdg_config_path, xdg_config_dirs);
	xdg_config_last = xdg_config_path + strlen(xdg_config_path);
	DPRINTF("Full config path is; '%s'\n", xdg_config_path);
	p = xdg_config_path;
	e = xdg_config_last;
	while ((p = strchrnul(p, ':')) < e)
		*p++ = '\0';
	DPRINTF("Directories in forward order:\n");
	for (p = xdg_config_path; p < xdg_config_last; p += strlen(p) + 1) {
		DPRINTF("\t%s\n", p);
	}
	DPRINTF("Directories in reverse order:\n");
	for (p = xdg_find_str(xdg_config_last, xdg_config_path);
	     p >= xdg_config_path; p = xdg_find_str(p - 1, xdg_config_path)) {
		DPRINTF("\t%s\n", p);
	}
}

static void
set_default_files()
{
	static const char *rsuffix = "/xde/run-history";
	static const char *asuffix = "/xde/recent-applications";
	static const char *xsuffix = "/recently-used";
	static const char *hsuffix = "/.recently-used";
	int len;
	char *env;

	if ((env = getenv("XDG_CONFIG_HOME"))) {
		len = strlen(env) + strlen(rsuffix) + 1;
		free(options.runhist);
		defaults.runhist = options.runhist = calloc(len, sizeof(*options.runhist));
		strcpy(options.runhist, env);
		strcat(options.runhist, rsuffix);

		len = strlen(env) + strlen(asuffix) + 1;
		free(options.recapps);
		defaults.recapps = options.recapps = calloc(len, sizeof(*options.recapps));
		strcpy(options.recapps, env);
		strcat(options.recapps, asuffix);

		len = strlen(env) + strlen(xsuffix) + 1;
		free(options.recently);
		defaults.recently = options.recently = calloc(len, sizeof(*options.recently));
		strcpy(options.recently, env);
		strcat(options.recently, xsuffix);
	} else {
		static const char *cfgdir = "/.config";
		static const char *datdir = "/.local/share";

		env = getenv("HOME") ? : ".";

		len = strlen(env) + strlen(cfgdir) + strlen(rsuffix) + 1;
		free(options.runhist);
		defaults.runhist = options.runhist = calloc(len, sizeof(*options.runhist));
		strcpy(options.runhist, env);
		strcat(options.runhist, cfgdir);
		strcat(options.runhist, rsuffix);

		len = strlen(env) + strlen(cfgdir) + strlen(asuffix) + 1;
		free(options.recapps);
		defaults.recapps = options.recapps = calloc(len, sizeof(*options.recapps));
		strcpy(options.recapps, env);
		strcat(options.recapps, cfgdir);
		strcat(options.recapps, asuffix);

		len = strlen(env) + strlen(datdir) + strlen(xsuffix) + 1;
		free(options.recently);
		defaults.recently = options.recently = calloc(len, sizeof(*options.recently));
		strcpy(options.recently, env);
		strcat(options.recently, datdir);
		strcat(options.recently, xsuffix);
	}
	if (access(options.recently, R_OK | W_OK)) {
		env = getenv("HOME") ? : ".";

		len = strlen(env) + strlen(hsuffix) + 1;
		free(options.recently);
		defaults.recently = options.recently = calloc(len, sizeof(*options.recently));
		strcpy(options.recently, env);
		strcat(options.recently, hsuffix);
	}
	return;
}

static void
set_defaults(void)
{
	char *env;

	if ((env = getenv("XDG_CURRENT_DESKTOP"))) {
		free(options.desktop);
		defaults.desktop = options.desktop = strdup(env);
	}

	set_default_paths();
	set_default_files();
}

static void
get_default_locale()
{
	char *val;
	int len, set;

	set = (options.charset || options.language);

	if (!options.charset && (val = nl_langinfo(CODESET)))
		defaults.charset = options.charset = strdup(val);
	if (!options.language && options.locale) {
		defaults.language = options.language = strdup(options.locale);
		*strchrnul(options.language, '.') = '\0';
	}
	if (set && options.language && options.charset) {
		len = strlen(options.language) + 1 + strlen(options.charset);
		val = calloc(len, sizeof(*val));
		strcpy(val, options.language);
		strcat(val, ".");
		strcat(val, options.charset);
		DPRINTF("setting locale to: '%s'\n", val);
		if (!setlocale(LC_ALL, val))
			EPRINTF("cannot set locale to '%s'\n", val);
		free(val);
	}
	DPRINTF("locale is '%s'\n", options.locale);
	DPRINTF("charset is '%s'\n", options.charset);
	DPRINTF("language is '%s'\n", options.language);
}

static void
get_default_format()
{
	GdkDisplay *disp = gdk_display_get_default();
	Display *dpy = GDK_DISPLAY_XDISPLAY(disp);
	GdkScreen *scrn = gdk_display_get_default_screen(disp);
	GdkWindow *wind = gdk_screen_get_root_window(scrn);
	Window root = GDK_WINDOW_XID(wind);
	XTextProperty xtp = { NULL, };
	Atom prop = _XA_XDE_WM_NAME;

	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		char **list = NULL;
		int strings = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, &list, &strings) == Success) {
			if (strings >= 1) {
				if (!options.format || strcmp(options.format, list[0])) {
					free(options.format);
					defaults.format = options.format = strdup(list[0]);
				}
			}
			if (list)
				XFreeStringList(list);
		} else
			EPRINTF("could not get text list for %s property\n",
				XGetAtomName(dpy, prop));
	} else
		DPRINTF("could not get %s for root 0x%lx\n", XGetAtomName(dpy, prop), root);
}

static void
get_default_output()
{
	GdkDisplay *disp = gdk_display_get_default();
	Display *dpy = GDK_DISPLAY_XDISPLAY(disp);
	GdkScreen *scrn = gdk_display_get_default_screen(disp);
	GdkWindow *wind = gdk_screen_get_root_window(scrn);
	Window root = GDK_WINDOW_XID(wind);
	XTextProperty xtp = { NULL, };
	Atom prop = _XA_XDE_WM_MENU;

	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		char **list = NULL;
		int strings = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, &list, &strings) == Success) {
			if (strings >= 1) {
				if (!options.filename || strcmp(options.filename, list[0])) {
					free(options.filename);
					defaults.filename = options.filename = strdup(list[0]);
				}
			}
			if (list)
				XFreeStringList(list);
		} else
			EPRINTF("could not get text list for %s property\n",
				XGetAtomName(dpy, prop));
	} else {
		DPRINTF("could not get %s for root 0x%lx\n", XGetAtomName(dpy, prop), root);
		DPRINTF("chances are window manager does not have a root menu\n");
	}
}

static void
get_default_theme()
{
#if 1
	GdkDisplay *disp = gdk_display_get_default();
	Display *dpy = GDK_DISPLAY_XDISPLAY(disp);
	GdkScreen *scrn = gdk_display_get_default_screen(disp);
	GdkWindow *wind = gdk_screen_get_root_window(scrn);
	Window root = GDK_WINDOW_XID(wind);
	XTextProperty xtp = { NULL, };
	Atom prop = _XA_XDE_ICON_THEME_NAME;
	GtkSettings *set;

	gtk_rc_reparse_all();

	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		char **list = NULL;
		int strings = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, &list, &strings) == Success) {
			if (strings >= 1) {
				static const char *prefix = "gtk-icon-theme-name=\"";
				static const char *suffix = "\"";
				char *rc_string;
				int len;

				len = strlen(prefix) + strlen(list[0]) + strlen(suffix);
				rc_string = calloc(len + 1, sizeof(*rc_string));
				strncpy(rc_string, prefix, len);
				strncat(rc_string, list[0], len);
				strncat(rc_string, suffix, len);
				gtk_rc_parse_string(rc_string);
				free(rc_string);
				if (!options.theme || strcmp(options.theme, list[0])) {
					free(options.theme);
					defaults.theme = options.theme = strdup(list[0]);
				}
			}
			if (list)
				XFreeStringList(list);
		} else
			EPRINTF("could not get text list for %s property\n",
				XGetAtomName(dpy, prop));
		if (xtp.value)
			XFree(xtp.value);
	} else
		DPRINTF("could not get %s for root 0x%lx\n", XGetAtomName(dpy, prop), root);
	if ((set = gtk_settings_get_for_screen(scrn))) {
		GValue theme_v = G_VALUE_INIT;
		const char *itheme;

		g_value_init(&theme_v, G_TYPE_STRING);
		g_object_get_property(G_OBJECT(set), "gtk-icon-theme-name", &theme_v);
		itheme = g_value_get_string(&theme_v);
		if (itheme && (!options.theme || strcmp(options.theme, itheme))) {
			free(options.theme);
			defaults.theme = options.theme = strdup(itheme);
		}
		g_value_unset(&theme_v);
	}
#else

	static const char *suffix1 = "/etc/gtk-2.0/gtkrc";
	static const char *suffix2 = "/.gtkrc-2.0";
	static const char *suffix3 = "/.gtkrc-2.0.xde";
	static const char *prefix = "gtk-icon-theme-name=\"";
	char *env;
	int len;

	if (options.theme)
		return;
	if ((env = getenv("XDG_ICON_THEME"))) {
		free(options.theme);
		defaults.theme = options.theme = strdup(env);
		return;
	} else {
		char *path, *d, *e, *buf;

		/* need to go looking for the theme name */

		if ((env = getenv("GTK_RC_FILES"))) {
			path = strdup(env);
		} else {
			env = getenv("HOME") ? : "~";
			len = 1 + strlen(suffix1) + 1 + strlen(env) + strlen(suffix2) +
			    1 + strlen(env) + strlen(suffix3);
			path = calloc(len, sizeof(*path));
			strcpy(path, suffix1);
			strcat(path, ":");
			strcat(path, env);
			strcat(path, suffix2);
			strcat(path, ":");
			strcat(path, env);
			strcat(path, suffix3);
		}
		buf = calloc(BUFSIZ, sizeof(*buf));
		d = path;
		e = d + strlen(d);
		while ((d = strchrnul(d, ':')) < e)
			*d++ = '\0';
		for (d = path; d < e; d += strlen(d) + 1) {
			FILE *f;

			if (!(f = fopen(d, "r")))
				continue;
			while (fgets(buf, BUFSIZ, f)) {
				if (!strncmp(buf, prefix, strlen(prefix))) {
					char *p;

					p = buf + strlen(prefix);
					*strchrnul(p, '"') = '\0';
					free(options.theme);
					defaults.theme = options.theme = strdup(p);
				}
				/* FIXME: this does not traverse "include" statements */
			}
			fclose(f);
		}
		free(buf);
	}
	if (!options.theme)
		defaults.theme = options.theme = strdup("hicolor");
#endif
}

static void
get_default_root()
{
	char *env, *dirs, *pfx, *p, *q, *d, *e;

	if (!options.menu) {
		free(options.menu);
		defaults.menu = options.menu = strdup("applications");
	}

	if (options.rootmenu)
		return;

	dirs = calloc(PATH_MAX, sizeof(*dirs));

	if ((env = getenv("XDG_CONFIG_HOME"))) {
		strcpy(dirs, env);
	} else if ((env = getenv("HOME"))) {
		strcpy(dirs, env);
		strcat(dirs, "/.config");
	} else {
		strcpy(dirs, "~/.config");
	}
	if ((env = getenv("XDG_CONFIG_DIRS"))) {
		strcat(dirs, ":");
		strcat(dirs, env);
	} else {
		strcat(dirs, ":");
		strcat(dirs, "/etc/xdg");
	}
	DPRINTF("$XDG_CONFIG_HOME:$XDG_CONFIG_DIRS is '%s'\n", dirs);
	e = dirs + strlen(dirs);
	d = dirs;
	while ((d = strchrnul(d, ':')) < e)
		*d++ = '\0';

	pfx = calloc(PATH_MAX, sizeof(*dirs));

	if ((env = getenv("XDG_VENDOR_ID"))) {
		if (pfx[0])
			strcat(pfx, ":");
		strcat(pfx, env);
		strcat(pfx, "-");
	}
	if ((env = getenv("XDG_MENU_PREFIX"))) {
		strcat(pfx, env);
	}
	if (pfx[0])
		strcat(pfx, ":");
	strcat(pfx, "xde-");
	if (pfx[0])
		strcat(pfx, ":");
	strcat(pfx, "arch-");
	DPRINTF("$XDG_MENU_PREFIX:$XDG_VENDOR_ID- is '%s'\n", pfx);
	q = pfx + strlen(pfx);
	p = pfx;
	while ((p = strchrnul(p, ':')) < q)
		*p++ = '\0';

	for (p = pfx; p < q; p += strlen(p) + 1) {
		for (d = dirs; d < e; d += strlen(d) + 1) {
			int len;
			char *path;

			len = strlen(d) + strlen("/menus/") + strlen(p) + strlen(options.menu)
			    + strlen(".menu") + 1;
			path = calloc(len, sizeof(*path));
			strcpy(path, d);
			strcat(path, "/menus/");
			strcat(path, p);
			strcat(path, options.menu);
			strcat(path, ".menu");
			DPRINTF("Testing path: '%s'\n", path);
			if (access(path, R_OK) == 0) {
				free(options.rootmenu);
				defaults.rootmenu = options.rootmenu = path;
				break;
			}
			free(path);
		}
		if (options.rootmenu)
			break;
	}
	DPRINTF("Default root menu is: '%s'\n", options.rootmenu);
	free(dirs);
	free(pfx);
}

static void
get_defaults(void)
{
	get_default_locale();
	get_default_root();
}

int
main(int argc, char *argv[])
{
	Command command = CommandDefault;
	char *loc;

	if ((loc = setlocale(LC_ALL, ""))) {
		free(options.locale);
		defaults.locale = options.locale = strdup(loc);
	}
	set_defaults();

	saveArgc = argc;
	saveArgv = argv;

	while (1) {
		int c, val;

#ifdef _GNU_SOURCE
		int option_index = 0;
		/* *INDENT-OFF* */
		static struct option long_options[] = {
			{"format",	required_argument,	NULL,	'f'},
			{"fullmenu",	no_argument,		NULL,	'F'},
			{"nofullmenu",	no_argument,		NULL,	'N'},
			{"desktop",	required_argument,	NULL,	'd'},
			{"charset",	required_argument,	NULL,	'c'},
			{"language",	required_argument,	NULL,	'l'},
			{"root-menu",	required_argument,	NULL,	'r'},
			{"die-on-error",no_argument,		NULL,	'e'},
			{"output",	optional_argument,	NULL,	'o'},
			{"noicons",	no_argument,		NULL,	'n'},
			{"theme",	required_argument,	NULL,	't'},
			{"monitor",	no_argument,		NULL,	'm'},
			{"launch",	no_argument,		NULL,	'L'},
			{"nolaunch",	no_argument,		NULL,	'0'},
			{"style",	required_argument,	NULL,	's'},
			{"menu",	required_argument,	NULL,	'M'},

			{"quit",	no_argument,		NULL,	'q'},
			{"replace",	no_argument,		NULL,	'R'},

			{"debug",	optional_argument,	NULL,	'D'},
			{"verbose",	optional_argument,	NULL,	'v'},
			{"help",	no_argument,		NULL,	'h'},
			{"version",	no_argument,		NULL,	'V'},
			{"copying",	no_argument,		NULL,	'C'},
			{"?",		no_argument,		NULL,	'H'},
			{ 0, }
		};
		/* *INDENT-ON* */

		c = getopt_long_only(argc, argv, "f:FNd:c:l:r:eo::nt:mL0s:M:qRD::v::hVCH?",
				     long_options, &option_index);
#else
		c = getopt(argc, argv, "f:FNd:c:l:r:eo:nt:mL0s:M:qRD:vhVC?");
#endif
		if (c == -1) {
			if (options.debug)
				fprintf(stderr, "%s: done options processing\n", argv[0]);
			break;
		}
		switch (c) {
		case 0:
			goto bad_usage;

		case 'f':	/* --format, -f FORMAT */
			free(options.format);
			defaults.format = options.format = strdup(optarg);
			break;
		case 'F':	/* -F, --fullmenu */
			defaults.style = options.style = StyleFullmenu;
			break;
		case 'N':	/* -N, --nofullmenu */
			defaults.style = options.style = StyleAppmenu;
			break;
		case 'd':	/* -d, --desktop DESKTOP */
			free(options.desktop);
			defaults.desktop = options.desktop = strdup(optarg);
			break;
		case 'c':	/* -c, --charset CHARSET */
			free(options.charset);
			defaults.charset = options.charset = strdup(optarg);
			break;
		case 'l':	/* -l, --language LANGUAGE */
			free(options.language);
			defaults.language = options.language = strdup(optarg);
			break;
		case 'r':	/* -r, --root-menu MENU */
			free(options.rootmenu);
			defaults.rootmenu = options.rootmenu = strdup(optarg);
			break;
		case 'e':	/* -e, --die-on-error */
			defaults.dieonerr = options.dieonerr = True;
			break;
		case 'o':	/* -o, --output [OUTPUT] */
			defaults.fileout = options.fileout = True;
			if (optarg != NULL) {
				free(options.filename);
				defaults.filename = options.filename = strdup(optarg);
			}
			break;
		case 'n':	/* -n, --noicons */
			defaults.noicons = options.noicons = True;
			break;
		case 't':	/* -t, --theme THEME */
			free(options.theme);
			defaults.theme = options.theme = strdup(optarg);
			break;
		case 'm':	/* -m, --monitor */
			if (options.command != CommandDefault)
				goto bad_option;
			if (command == CommandDefault)
				command = CommandRun;
			defaults.command = options.command = CommandRun;
			break;
		case 'L':	/* -L, --launch */
			defaults.launch = options.launch = True;
			break;
		case '0':	/* -0, --nolaunch */
			defaults.launch = options.launch = False;
			break;
		case 's':	/* -s, --style STYLE */
			if (!strncmp("fullmenu", optarg, strlen(optarg))) {
				defaults.style = options.style = StyleFullmenu;
				break;
			}
			if (!strncmp("appmenu", optarg, strlen(optarg))) {
				defaults.style = options.style = StyleAppmenu;
				break;
			}
			if (!strncmp("entries", optarg, strlen(optarg))) {
				defaults.style = options.style = StyleEntries;
				break;
			}
			goto bad_option;
		case 'M':	/* -M, --menu MENUS */
			free(options.menu);
			defaults.menu = options.menu = strdup(optarg);
			break;

		case 'q':	/* -q, --quit */
			if (options.command != CommandDefault)
				goto bad_option;
			if (command == CommandDefault)
				command = CommandQuit;
			defaults.command = options.command = CommandQuit;
			break;
		case 'R':	/* -R, --replace */
			if (options.command != CommandDefault)
				goto bad_option;
			if (command == CommandDefault)
				command = CommandReplace;
			defaults.command = options.command = CommandReplace;
			break;

		case 'D':	/* -D, --debug [LEVEL] */
			if (options.debug)
				fprintf(stderr, "%s: increasing debug verbosity\n", argv[0]);
			if (optarg == NULL)
				defaults.debug = options.debug = options.debug + 1;
			else {
				if ((val = strtol(optarg, NULL, 0)) < 0)
					goto bad_option;
				defaults.debug = options.debug = val;
			}
			break;
		case 'v':	/* -v, --verbose [LEVEL] */
			if (options.debug)
				fprintf(stderr, "%s: increasing output verbosity\n", argv[0]);
			if (optarg == NULL)
				defaults.output = options.output = options.output + 1;
			else {
				if ((val = strtol(optarg, NULL, 0)) < 0)
					goto bad_option;
				defaults.output = options.output = val;
			}
			break;
		case 'h':	/* -h, --help */
		case 'H':	/* -H, --? */
			command = CommandHelp;
			break;
		case 'V':
			if (options.command != CommandDefault)
				goto bad_option;
			if (command == CommandDefault)
				command = CommandVersion;
			defaults.command = options.command = CommandVersion;
			break;
		case 'C':	/* -C, --copying */
			if (options.command != CommandDefault)
				goto bad_option;
			if (command == CommandDefault)
				command = CommandCopying;
			defaults.command = options.command = CommandCopying;
			break;
		case '?':
		default:
		      bad_option:
			optind--;
			goto bad_nonopt;
		      bad_nonopt:
			if (options.output || options.debug) {
				if (optind < argc) {
					fprintf(stderr, "%s: syntax error near '", argv[0]);
					while (optind < argc) {
						fprintf(stderr, "%s", argv[optind++]);
						fprintf(stderr, "%s", (optind < argc) ? " " : "");
					}
					fprintf(stderr, "'\n");
				} else {
					fprintf(stderr, "%s: missing option or argument", argv[0]);
					fprintf(stderr, "\n");
				}
				fflush(stderr);
			      bad_usage:
				usage(argc, argv);
			}
			exit(EXIT_SYNTAXERR);
		}
	}
	DPRINTF("%s: option index = %d\n", argv[0], optind);
	DPRINTF("%s: option count = %d\n", argv[0], argc);
	if (optind < argc) {
		fprintf(stderr, "%s: excess non-option arguments near '", argv[0]);
		while (optind < argc) {
			fprintf(stderr, "%s", argv[optind++]);
			fprintf(stderr, "%s", (optind < argc) ? " " : "");
		}
		fprintf(stderr, "'\n");
		usage(argc, argv);
		exit(EXIT_SYNTAXERR);
	}
	get_defaults();

	startup(argc, argv);

	if (!options.format)
		get_default_format();
	if (!options.filename)
		get_default_output();
	if (!options.theme)
		get_default_theme();

	switch (command) {
	default:
	case CommandDefault:
		DPRINTF("%s: running without monitoring\n", argv[0]);
		do_generate(argc, argv);
		break;
	case CommandRun:
		DPRINTF("%s: running a new instance\n", argv[0]);
		do_run(argc, argv, False);
		break;
	case CommandQuit:
		DPRINTF("%s: asking existing instance to quit\n", argv[0]);
		do_quit(argc, argv);
		break;
	case CommandReplace:
		DPRINTF("%s: replacing existing instance\n", argv[0]);
		do_run(argc, argv, True);
		break;
	case CommandHelp:
		DPRINTF("%s: printing help message\n", argv[0]);
		help(argc, argv);
		break;
	case CommandVersion:
		DPRINTF("%s: printing version message\n", argv[0]);
		version(argc, argv);
		break;
	case CommandCopying:
		DPRINTF("%s: printing copying message\n", argv[0]);
		copying(argc, argv);
		break;
	}
	exit(EXIT_SUCCESS);
}

// vim: tw=100 com=sr0\:/**,mb\:*,ex\:*/,sr0\:/*,mb\:*,ex\:*/,b\:TRANS formatoptions+=tcqlor
