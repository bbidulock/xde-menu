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
xde_get_icons(MenuContext *ctx, const char *inames[])
{
	GtkIconTheme *theme;
	GtkIconInfo *info;
	const gchar *name;
	char *file = NULL;

	if ((theme = gtk_icon_theme_get_default())) {
		if ((info = gtk_icon_theme_choose_icon(theme, inames, 16, ctx->iconflags))) {
			if ((name = gtk_icon_info_get_filename(info))) {
				file = calloc(strlen(name) + 4, sizeof(*file));
				strcpy(file, " <");
				strcat(file, name);
				strcat(file, ">");
			}
			gtk_icon_info_free(info);
		}
	}
	if (!file)
		file = strdup("");
	return (file);
}

char *
xde_get_icon(MenuContext *ctx, const char *iname)
{
	GtkIconTheme *theme;
	GtkIconInfo *info;
	const gchar *name;
	char *file = NULL;

	if ((theme = gtk_icon_theme_get_default())) {
		if ((info = gtk_icon_theme_lookup_icon(theme, iname, 16, ctx->iconflags))) {
			if ((name = gtk_icon_info_get_filename(info))) {
				file = calloc(strlen(name) + 4, sizeof(*file));
				strcpy(file, " <");
				strcat(file, name);
				strcat(file, ">");
			}
			gtk_icon_info_free(info);
		}
	}
	if (!file)
		file = strdup("");
	return (file);
}

char *
xde_get_icon2(MenuContext *ctx, const char *iname1, const char *iname2)
{
	GtkIconTheme *theme;
	GtkIconInfo *info;
	const gchar *name;
	char *file = NULL;
	const char *inames[3];

	if ((inames[0] = iname1)) {
		inames[1] = iname2;
		inames[2] = NULL;
	} else {
		inames[0] = iname2;
		inames[1] = NULL;
		inames[2] = NULL;
	}
	if ((theme = gtk_icon_theme_get_default())) {
		if ((info = gtk_icon_theme_choose_icon(theme, inames, 16, ctx->iconflags))) {
			if ((name = gtk_icon_info_get_filename(info))) {
				file = calloc(strlen(name) + 4, sizeof(*file));
				strcpy(file, " <");
				strcat(file, name);
				strcat(file, ">");
			}
			gtk_icon_info_free(info);
		}
	}
	if (!file)
		file = strdup("");
	return (file);
}

#define GET_ENTRY_ICON_FLAG_XPM	(1<<0)
#define GET_ENTRY_ICON_FLAG_PNG (1<<1)
#define GET_ENTRY_ICON_FLAG_SVG (1<<2)
#define GET_ENTRY_ICON_FLAG_JPG (1<<3)
#define GET_ENTRY_ICON_FLAG_GIF (1<<4)
#define GET_ENTRY_ICON_FLAG_TIF (1<<5)

gboolean
xde_test_icon_ext(MenuContext *ctx, const char *path, int flags)
{
	char *p;

	if ((p = strrchr(path, '.'))) {
		if ((flags & GET_ENTRY_ICON_FLAG_XPM) && strcmp(p, ".xpm") == 0)
			return TRUE;
		else if ((flags & GET_ENTRY_ICON_FLAG_PNG) && strcmp(p, ".png") == 0)
			return TRUE;
		else if ((flags & GET_ENTRY_ICON_FLAG_SVG) && strcmp(p, ".svg") == 0)
			return TRUE;
		else if ((flags & GET_ENTRY_ICON_FLAG_JPG)
			 && (strcmp(p, ".jpg") == 0 || strcmp(p, ".jpeg") == 0))
			return TRUE;
		else if ((flags & GET_ENTRY_ICON_FLAG_GIF) && strcmp(p, ".gif") == 0)
			return TRUE;
		else if ((flags & GET_ENTRY_ICON_FLAG_TIF)
			 && (strcmp(p, ".tif") == 0 || strcmp(p, ".tiff") == 0))
			return TRUE;
	}
	return FALSE;
}

/**
 * Basically get the icon for a given entry, whether application or directory, with specified
 * defaults or fallbacks.  If the desktop entry specification contains an absolute file name, then
 * check if it exists and use it; otherwise, if the file is a relative path, then the path is
 * relative to the menu file (but we don't do that).  Otherwise, remove any extension, and remove
 * any leading path elements and look for the icon by name.  The flags above are used.
 */
char *
xde_get_entry_icon(MenuContext *ctx, GKeyFile *entry, const char *dflt1,
		   const char *dflt2, int flags)
{
	GtkIconTheme *theme;
	GtkIconInfo *info;
	const gchar *name;
	char *file = NULL;
	const char *inames[4];
	char *icon;
	int i = 0;

	if ((icon = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
					  G_KEY_FILE_DESKTOP_KEY_ICON, NULL))) {
		char *base, *p;

		if (icon[0] == '/' && !access(icon, R_OK) && xde_test_icon_ext(ctx, icon, flags))
			return (icon);
		if ((p = strrchr(icon, '/')))
			base = p + 1;
		else
			base = icon;
		if ((p = strrchr(base, '.')))
			*p = '\0';
		inames[i++] = base;
	}
	if (dflt1)
		inames[i++] = dflt1;
	if (dflt2)
		inames[i++] = dflt2;
	inames[i++] = NULL;
	if ((theme = gtk_icon_theme_get_default())) {
		if ((info = gtk_icon_theme_choose_icon(theme, inames, 16, ctx->iconflags))) {
			if ((name = gtk_icon_info_get_filename(info))) {
				file = calloc(strlen(name) + 4, sizeof(*file));
				strcpy(file, " <");
				strcat(file, name);
				strcat(file, ">");
			}
			gtk_icon_info_free(info);
		}
	}
	g_free(icon);
	if (!file)
		file = strdup("");
	return (file);
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

	icon = xde_get_icon(ctx, "gtk-quit");
	s = g_strdup_printf("%s[submenu] (Window Managers) {Window Managers}%s\n",
			    ctx->indent, icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	icon = xde_get_icon(ctx, "gtk-refresh");
	s = g_strdup_printf("%s[restart] (Restart)%s\n", ctx->indent, icon);
	text = g_list_append(text, s);
	free(icon);
	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;

		if (strncasecmp(xsess->key, "fluxbox", 7) == 0)
			continue;
		icon = xde_get_entry_icon(ctx, xsess->entry, "preferences-system-windows",
				"metacity", GET_ENTRY_ICON_FLAG_XPM|GET_ENTRY_ICON_FLAG_PNG);
		s = g_strdup_printf("%s[restart] (Start %s) {xdg-launch --pointer -X %s}%s\n",
				    ctx->indent, xsess->name, xsess->key, icon);
		text = g_list_append(text, s);
		free(icon);
	}
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s[end] # (Window Managers)\n", ctx->indent);
	text = g_list_append(text, s);
	xde_free_xsessions(xsessions);
	return (text);
}

static GList *
xde_appmenu(MenuContext *ctx, GList *entries, const char *name)
{
	GList *text = NULL;
	char *esc1, *esc2;
	char *icon;

	esc1 = xde_character_escape(name, ')');
	esc2 = xde_character_escape(name, '}');
	icon = xde_get_icon2(ctx, "start-here", "folder");

	text = g_list_append(text, g_strdup_printf("[submenu] (%s) {%s}%s\n", esc1, esc2, icon));
	text = g_list_concat(text, entries);
	text = g_list_append(text, g_strdup_printf("[end]\n"));

	free(icon);
	free(esc1);
	free(esc2);
	return (text);
}

static GList *
xde_rootmenu(MenuContext *ctx, GList *entries)
{
	GList *text = NULL;
	char *icon;
	char *s;

	s = g_strdup_printf("%s%s\n", ctx->indent, "[begin] (Fluxbox)");
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[encoding] {UTF-8}");
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[separator]");
	text = g_list_append(text, s);
	icon = xde_get_icon(ctx, "fluxbox");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Fluxbox menu)", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	icon = xde_get_icon(ctx, "preferences-desktop");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[config] (Configure)", icon);
	text = g_list_append(text, s);
	free(icon);
	text = g_list_concat(text, ctx->themes(ctx));
	text = g_list_concat(text, ctx->styles(ctx));
	s = g_strdup_printf("%s%s\n", ctx->indent, "[submenu] (Backgrounds) {Set the Background}");
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[submenu] (Backgrounds) {Set the Background}");
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[exec] (Random Background) {fbsetbg -r /usr/share/fluxbox/backgrounds}");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
	icon = xde_get_icon(ctx, "preferences-desktop-display");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[workspaces] (Workspace List)", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_get_icon(ctx, "applications-utilities");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Tools)", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[exec] (Window name) {xprop WM_CLASS|cut -d \\\" -f 2|gxmessage -file - -center");
	text = g_list_append(text, s);
	icon = xde_get_icon(ctx, "applets-screenshooter");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Screenshot - JPG) {import screenshot.jpg && display -resize 50% screenshot.jpg}", icon);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Screenshot - PNG) {import screenshot.png && display -resize 50% screenshot.png}", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_get_icon(ctx, "gtk-execute");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Run) {fbrun -font 10x20 -fg grey -bg black -title run", icon);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Run Command) {bbrun -a -w}", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
	icon = xde_get_icon(ctx, "preferences-system-windows");
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
	text = g_list_concat(text, ctx->wmmenu(ctx));
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end] # (Fluxbox menu)");
	text = g_list_append(text, s);
	icon = xde_get_icon(ctx, "gnome-lock-screen");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Lock screen)", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_get_icon(ctx, "gtk-execute");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[commanddialog] (Fluxbox Command)", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_get_icon(ctx, "gtk-redo-ltr");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[reconfig] (Reload config)", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_get_icon(ctx, "gtk-referesh");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[restart] (Restart) {}", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_get_icon(ctx, "help-about");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (About) {(fluxbox -v; fluxbox -info | sed 1d) | gxmessage -file - -center}", icon);
	text = g_list_append(text, s);
	free(icon);
	if (options.output) {
		icon = xde_get_icon(ctx, "gtk-refresh");
		s = g_strdup_printf("%s%s%s%s%s\n", ctx->indent, "[exec] (Refresh Menu) {xde-menugen -format fluxbox -desktop FLUXBOX -o ",
				options.filename, "}", icon);
		text = g_list_append(text, s);
		free(icon);
	}
	s = g_strdup_printf("%s%s\n", ctx->indent, "[separator]");
	text = g_list_append(text, s);
	icon = xde_get_icon(ctx, "gtk-quit");
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exit] (Exit)", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[endencoding]");
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end] # (Fluxbox)");
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
xde_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GList *text = NULL;
	const char *name;
	char *esc1, *esc2;

	name = gmenu_tree_directory_get_name(dir);

	esc1 = xde_character_escape(name, ')');
	esc2 = xde_character_escape(name, '}');

	DPRINTF("Processing menu '%s'\n", name);
	/* FIXME: add an icon */
	text = g_list_append(text, g_strdup_printf("%s%s (%s) {%s Menu}\n", ctx->indent, "[submenu]", esc1, esc2));
	text = g_list_concat(text, ctx->ops.menu(ctx, dir));
	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[end]"));
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

	text = g_list_append(text, g_strdup_printf("%s%s\n", ctx->indent, "[separator]"));
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

	esc1 = xde_character_escape(name, ')');

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

	esc2 = xde_character_escape(cmd, '}');

	/* FIXME: add an icon */
	text = g_list_append(text, g_strdup_printf("%s[exec] (%s) {%s}\n", ctx->indent, esc1, esc2));

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
xde_theme_entries(MenuContext *ctx, const char *dname, Which which)
{
	GList *text = NULL;
	DIR *dir;
	static const char *sysfmt = "%s[exec] (%s) {xde-style -s -t -r -y '%s'}\n";
	static const char *usrfmt = "%s[exec] (%s) {xde-style -s -t -r -u '%s'}\n";
	static const char *mixfmt = "%s[exec] (%s) {xde-style -s -t -r '%s'}\n";
	const char *fmt;

	switch (which) {
	case XdeStyleSystem:
		fmt = sysfmt;
		break;
	case XdeStyleUser:
		fmt = usrfmt;
		break;
	case XdeStyleMixed:
	default:
		fmt = mixfmt;
		break;
	}

	if ((dir = opendir(dname))) {
		struct dirent *d;
		struct stat st;
		char *file;
		int len;

		xde_increase_indent(ctx);
		while ((d = readdir(dir))) {
			if (d->d_name[0] == '.')
				continue;
			len = strlen(dname) + strlen(d->d_name) + 16;
			file = calloc(len, sizeof(*file));
			strcpy(file, dname);
			strcat(file, "/");
			strcat(file, d->d_name);
			if (lstat(file, &st)) {
				EPRINTF("%s: %s\n", file, strerror(errno));
				free(file);
				continue;
			}
			switch (which) {
			case XdeStyleMixed:
			{
				static const char *fname = "/xde/themerc";

				if (!S_ISDIR(st.st_mode)) {
					DPRINTF("%s: not file or directory\n", file);
					free(file);
					continue;
				}
				strcat(file, fname);
				if (stat(file, &st)) {
					EPRINTF("%s: %s\n", file, strerror(errno));
					free(file);
					continue;
				}
				if (!S_ISREG(st.st_mode)) {
					DPRINTF("%s: not a file\n", file);
					free(file);
					continue;
				}
				break;
			}
			case XdeStyleSystem:
			case XdeStyleUser:
			default:
			{
				static const char *fname = "/stylerc";

				if (!S_ISLNK(st.st_mode)) {
					DPRINTF("%s: not symbolic link\n", file);
					free(file);
					continue;
				}
				if (stat(file, &st)) {
					EPRINTF("%s: %s\n", file, strerror(errno));
					free(file);
					continue;
				}
				if (S_ISDIR(st.st_mode)) {
					strcat(file, fname);
					if (stat(file, &st)) {
						EPRINTF("%s: %s\n", file, strerror(errno));
						free(file);
						continue;
					}
					if (!S_ISREG(st.st_mode)) {
						DPRINTF("%s: not a file\n", file);
						free(file);
						continue;
					}
				} else if (!S_ISREG(st.st_mode)) {
					DPRINTF("%s: not file or directory\n", file);
					free(file);
					continue;
				}
				break;
			}
			}
			text = g_list_append(text, g_strdup_printf(fmt, ctx->indent, d->d_name, d->d_name));
			free(file);
		}
		xde_decrease_indent(ctx);
		closedir(dir);
		text = g_list_sort(text, xde_string_compare);

	} else
		DPRINTF("%s: %s\n", dname, strerror(errno));
	return (text);
}

static GList *
xde_themes(MenuContext *ctx)
{
	static const char *sysdir = "/usr/share/fluxbox/styles";
	static const char *usr = "/.fluxbox/styles";
	char *usrdir, *string;
	GList *text = NULL, *sysent, *usrent;
	const char *home;
	int len;

	sysent = xde_theme_entries(ctx, sysdir, XdeStyleSystem);

	home = getenv("HOME") ?: "~";
	len = strlen(home) + 1 + strlen(usr) + 1;
	usrdir = calloc(len, sizeof(*usrdir));
	strcpy(usrdir, home);
	strcat(usrdir, usr);

	usrent = xde_theme_entries(ctx, usrdir, XdeStyleUser);

	if (!sysent && !usrent) {
		free(usrdir);
		return (text);
	}

	string = g_strdup_printf("%s[submenu] (Themes) {Choose a theme...}\n", ctx->indent);
	text = g_list_append(text, string);
	if (sysent)
		text = g_list_concat(text, sysent);
	if (sysent && usrent) {
		xde_increase_indent(ctx);
		text = g_list_append(text, g_strdup_printf("%s[nop] (————————————) {}\n", ctx->indent));
		xde_decrease_indent(ctx);
	}
	if (usrent)
		text = g_list_concat(text, usrent);
	string = g_strdup_printf("%s[end]\n", ctx->indent);
	text = g_list_append(text, string);
	return (text);
}

static GList *
xde_style_entries(MenuContext *ctx, const char *dname, Which which)
{
	GList *text = NULL;
	DIR *dir;
	static const char *sysfmt = "%s[exec] (%s) {xde-style -s -r -y '%s'}\n";
	static const char *usrfmt = "%s[exec] (%s) {xde-style -s -r -u '%s'}\n";
	static const char *mixfmt = "%s[exec] (%s) {xde-style -s -r '%s'}\n";
	const char *fmt;

	switch (which) {
	case XdeStyleSystem:
		fmt = sysfmt;
		break;
	case XdeStyleUser:
	default:
		fmt = usrfmt;
		break;
	case XdeStyleMixed:
		fmt = mixfmt;
		break;
	}

	if ((dir = opendir(dname))) {
		static const char *fname = "/stylerc";
		struct dirent *d;
		struct stat st;
		char *file;
		int len;

		xde_increase_indent(ctx);
		while ((d = readdir(dir))) {
			if (d->d_name[0] == '.')
				continue;
			len = strlen(dname) + strlen(d->d_name) + strlen(fname) + 2;
			file = calloc(len, sizeof(*file));
			strcpy(file, dname);
			strcat(file, "/");
			strcat(file, d->d_name);
			if (lstat(file, &st)) {
				EPRINTF("%s: %s\n", file, strerror(errno));
				free(file);
				continue;
			}
			if (S_ISDIR(st.st_mode)) {
				strcat(file, fname);
				if (lstat(file, &st)) {
					EPRINTF("%s: %s\n", file, strerror(errno));
					free(file);
					continue;
				}
				if (!S_ISREG(st.st_mode)) {
					DPRINTF("%s: not a file\n", file);
					free(file);
					continue;
				}
			} else if (!S_ISREG(st.st_mode)) {
				DPRINTF("%s: not file or directory\n", file);
				free(file);
				continue;
			}
			text = g_list_append(text, g_strdup_printf(fmt, ctx->indent, d->d_name, d->d_name));
			free(file);
		}
		xde_decrease_indent(ctx);
		closedir(dir);
		text = g_list_sort(text, xde_string_compare);

	} else
		DPRINTF("%s: %s\n", dname, strerror(errno));
	return (text);
}

/**
 * There are two styles divided by a separator: user styles and system styles.  For user styles, the
 * styles are contained in the ${_XDE_WM_SYSDIR:-/usr/share/fluxbox}/styles directory and the  user
 * styles are contained in the ${_XDE_SM_USRDIR:-~/.fluxbox/styles.
 */
static GList *
xde_styles(MenuContext *ctx)
{
	static const char *sysdir = "/usr/share/fluxbox/styles";
	static const char *usr = "/.fluxbox/styles";
	char *usrdir, *string;
	GList *text = NULL, *sysent, *usrent;
	const char *home;
	int len;

	sysent = xde_style_entries(ctx, sysdir, XdeStyleSystem);

	home = getenv("HOME") ? : "~";
	len = strlen(home) + 1 + strlen(usr) + 1;
	usrdir = calloc(len, sizeof(*usrdir));
	strcpy(usrdir, home);
	strcat(usrdir, usr);

	usrent = xde_style_entries(ctx, usrdir, XdeStyleUser);

	if (!sysent && !usrent) {
		free(usrdir);
		return (text);
	}
	string = g_strdup_printf("%s[submenu] (Styles) {Choose a style...}\n", ctx->indent);
	text = g_list_append(text, string);
	if (sysent)
		text = g_list_concat(text, sysent);
	if (sysent && usrent) {
		xde_increase_indent(ctx);
		text = g_list_append(text, g_strdup_printf("%s[nop] (————————————) {}\n", ctx->indent));
		xde_decrease_indent(ctx);
	}
	if (usrent)
		text = g_list_concat(text, usrent);
	string = g_strdup_printf("%s[end]\n", ctx->indent);
	text = g_list_append(text, string);
	return (text);
}

MenuContext xde_menu_ops = {
	.name = "fluxbox",
	.version = VERSION,
	.tree = NULL,
	.level = 0,
	.iconflags = 0
		| GTK_ICON_LOOKUP_NO_SVG
//		| GTK_ICON_LOOKUP_FORCE_SVG
//		| GTK_ICON_LOOKUP_USE_BUILTIN
//		| GTK_ICON_LOOKUP_GENERIC_FALLBACK
//		| GTK_ICON_LOOKUP_FORCE_SIZE
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

