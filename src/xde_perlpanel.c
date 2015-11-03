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

#if 1
	if (file) {
		icon = calloc(strlen(file) + 4, sizeof(*icon));
		strcpy(icon, " <");
		strcat(icon, file);
		strcat(icon, ">");
	} else
		icon = strdup("");
#else
	icon = strdup("");
#endif
	free(file);
	return (icon);
}

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
	char *esc1, *esc2;
	char *icon;

	esc1 = xde_character_escape(name, ')');
	esc2 = xde_character_escape(name, '}');
	icon = xde_wrap_icon(xde_get_icon2(ctx, "start-here", "folder"));

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

	s = g_strdup_printf("%s%s\n", ctx->indent, "[begin] (Fluxbox)");
	text = g_list_append(text, s);
	text = g_list_concat(text, entries);
	xde_increase_indent(ctx);
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));

	text = g_list_concat(text, ctx->wmm.wmspec(ctx));

	icon = xde_wrap_icon(xde_get_icon(ctx, "gnome-lockscreen"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Lock screen) {xlock}", icon);
	text = g_list_append(text, s);
	free(icon);
#if 1
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-execute"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[commanddialog] (Fluxbox Command)", icon);
	text = g_list_append(text, s);
	free(icon);
#endif
#if 1
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-redo-ltr"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[reconfig] (Reload config)", icon);
	text = g_list_append(text, s);
	free(icon);
#endif
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[restart] (Restart) {}", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_wrap_icon(xde_get_icon(ctx, "help-about"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (About) {(fluxbox -v; fluxbox -info | sed 1d) | gxmessage -file - -center}", icon);
	text = g_list_append(text, s);
	free(icon);
	if (options.filename) {
		icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
		s = g_strdup_printf("%s%s%s%s%s%s%s%s%s\n", ctx->indent, "[exec] (Refresh Menu) {xde-menugen -format", ctx->format, " -desktop ", ctx->desktop, " -launch -o ", options.filename, "}", icon);
		text = g_list_append(text, s);
		free(icon);
	}
	text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exit] (Exit)", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
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

	s = g_strdup_printf("%s%s\n", ctx->indent, "[separator]");
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
	char *icon = NULL;

	if (!(dir = gmenu_tree_header_get_directory(hdr)))
		return (text);
	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, ')');
	esc2 = xde_character_escape(name, '}');
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, "folder", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG|
				GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = xde_wrap_icon(icon);
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
	char *icon = NULL;

	name = gmenu_tree_directory_get_name(dir);
	esc1 = xde_character_escape(name, ')');
	esc2 = xde_character_escape(name, '}');
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, "folder", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	icon = xde_wrap_icon(icon);
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
	char *appid;

	info = gmenu_tree_entry_get_app_info(ent);
	name = g_app_info_get_name(G_APP_INFO(info));
	esc1 = xde_character_escape(name, ')');

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
	esc2 = xde_character_escape(cmd, '}');
	icon = xde_wrap_icon(icon);
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
	return xde_alias_simple(ctx, als);
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

	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-quit"));
	s = g_strdup_printf("%s[submenu] (Window Managers) {Window Managers}%s\n",
			    ctx->indent, icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-refresh"));
	s = g_strdup_printf("%s[restart] (Restart)%s\n", ctx->indent, icon);
	text = g_list_append(text, s);
	free(icon);
	xsessions = xde_get_xsessions();
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		char *esc1;

		if (strncasecmp(xsess->key, ctx->name, strlen(ctx->name)) == 0)
			continue;
		icon = xde_get_entry_icon(ctx, xsess->entry, "preferences-system-windows",
				"metacity", GET_ENTRY_ICON_FLAG_XPM|GET_ENTRY_ICON_FLAG_PNG);
		icon = xde_wrap_icon(icon);
		esc1 = xde_character_escape(xsess->name, ')');
		s = g_strdup_printf("%s[restart] (Start %s) {xdg-launch --pointer -X %s}%s\n",
				    ctx->indent, esc1, xsess->key, icon);
		text = g_list_append(text, s);
		free(esc1);
		free(icon);
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
xde_theme_entries(MenuContext *ctx, const char *dname, Which which, const char *fname)
{
	GList *list = NULL;
	DIR *dir;

	if ((dir = opendir(dname))) {
		struct dirent *d;
		struct stat st;
		char *file;
		int len;

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
				fname = "/xde/themerc";

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
			list = g_list_append(list, strdup(d->d_name));
			free(file);
		}
		closedir(dir);
		list = g_list_sort(list, xde_string_compare);
	} else
		DPRINTF("%s: %s\n", dname, strerror(errno));
	return (list);
}

static GList *
xde_themes(MenuContext *ctx)
{
	static const char *sysfmt = "%s[exec] (%s) {xde-style -s -t -r -y '%s'}%s\n";
	static const char *usrfmt = "%s[exec] (%s) {xde-style -s -t -r -u '%s'}%s\n";
	static const char *mixfmt = "%s[exec] (%s) {xde-style -s -t -r '%s'}%s\n";
	static const char *sysdir = "/usr/share/themes";
	static const char *usr = "/.config/perlpanel/styles";
	static const char *fname = "/xde/themerc";
	char *usrdir, *s;
	GList *text = NULL, *sysent, *usrent, *style;
	const char *home;
	char *icon;
	int len;

	sysent = xde_theme_entries(ctx, sysdir, XdeStyleSystem, fname);

	home = getenv("HOME") ?: "~";
	len = strlen(home) + 1 + strlen(usr) + 1;
	usrdir = calloc(len, sizeof(*usrdir));
	strcpy(usrdir, home);
	strcat(usrdir, usr);

	usrent = xde_theme_entries(ctx, usrdir, XdeStyleUser, fname);
	free(usrdir);

	if (!sysent && !usrent)
		return (text);

	icon = xde_wrap_icon(xde_get_icon(ctx, "style"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Themes) {Choose a theme...}", icon);
	text = g_list_append(text, s);

	(void) mixfmt;

	if (sysent) {
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
xde_gtk_themes(MenuContext *ctx)
{
	static const char *sysfmt = "xde-style -s -t -r -y '%s'";
	static const char *usrfmt = "xde-style -s -t -r -u '%s'";
	static const char *mixfmt = "xde-style -s -t -r '%s'";
	static const char *sysdir = "/usr/share/themes";
	static const char *usr = "/.config/perlpanel/styles";
	static const char *fname = "/xde/themerc";
	char *usrdir;
	GtkMenuItem *item = NULL, *entry;
	GList *sysent, *usrent;
	GtkWidget *menu, *image = NULL;
	GdkPixbuf *pixbuf = NULL;
	const char *home;
	char *icon;
	int len;

	sysent = xde_theme_entries(ctx, sysdir, XdeStyleSystem, fname);

	home = getenv("HOME") ? : "~";
	len = strlen(home) + 1 + strlen(usr) + 1;
	usrdir = calloc(len, sizeof(*usrdir));
	strcpy(usrdir, home);
	strcat(usrdir, usr);

	usrent = xde_theme_entries(ctx, usrdir, XdeStyleUser, fname);
	free(usrdir);

	if (!sysent && !usrent)
		return (item);

	menu = gtk_menu_new();
	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	gtk_menu_item_set_label(item, "Themes");
	if ((icon = xde_wrap_icon(xde_get_icon(ctx, "style"))))
		pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL);
	if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	gtk_menu_item_set_submenu(item, menu);

	(void) mixfmt;

	if (sysent) {
		GList *style;

		for (style = sysent; style; style = style->next) {
			char *name = style->data;
			char *cmd = g_strdup_printf(sysfmt, name);

			entry = GTK_MENU_ITEM(gtk_image_menu_item_new());
			gtk_menu_item_set_label(entry, name);
			if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
				gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(entry), image);
			gtk_menu_append(menu, GTK_WIDGET(entry));
			g_signal_connect_data(G_OBJECT(entry), "activate",
					      G_CALLBACK(xde_entry_activated), cmd,
					      &xde_entry_disconnect, 0);
			style->data = NULL;
			free(name);
		}
		g_list_free(sysent);
	}
	if (sysent && usrent) {
		entry = ctx->gtk.ops.separator(ctx, NULL);
		gtk_menu_append(menu, GTK_WIDGET(entry));
	}
	if (usrent) {
		GList *style;

		for (style = usrent; style; style = style->next) {
			char *name = style->data;
			char *cmd = g_strdup_printf(usrfmt, name);

			entry = GTK_MENU_ITEM(gtk_image_menu_item_new());
			gtk_menu_item_set_label(entry, name);
			if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
				gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(entry), image);
			gtk_menu_append(menu, GTK_WIDGET(entry));
			g_signal_connect_data(G_OBJECT(entry), "activate",
					      G_CALLBACK(xde_entry_activated), cmd,
					      &xde_entry_disconnect, 0);
			style->data = NULL;
			free(name);
		}
		g_list_free(usrent);
	}
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	return (item);
}

static GList *
xde_style_entries(MenuContext *ctx, const char *dname, Which which, const char *fname)
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
		struct dirent *d;
		struct stat st;
		char *file, *path;
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
			path = strdup(file);
			if (lstat(file, &st)) {
				EPRINTF("%s: %s\n", file, strerror(errno));
				free(path);
				free(file);
				continue;
			}
			if (S_ISDIR(st.st_mode)) {
				strcat(file, fname);
				if (lstat(file, &st)) {
					DPRINTF("%s: %s\n", file, strerror(errno));
					free(path);
					free(file);
					continue;
				}
				if (!S_ISREG(st.st_mode)) {
					DPRINTF("%s: not a file\n", file);
					free(path);
					free(file);
					continue;
				}
			} else if (!S_ISREG(st.st_mode)) {
				DPRINTF("%s: not file or directory\n", file);
				free(path);
				free(file);
				continue;
			}
#if 1
			text = g_list_append(text, g_strdup_printf("%s[style] (%s) {%s}\n", ctx->indent, d->d_name, path));
			(void) fmt;
#else
			text = g_list_append(text, g_strdup_printf(fmt, ctx->indent, d->d_name, d->d_name));
#endif
			free(path);
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
xde_styles(MenuContext *ctx)
{
	static const char *sysdir = "/usr/share/themes";
	static const char *usr = "/.config/perlpanel/styles";
	static const char *fname = "/xde/themerc";
	char *usrdir, *s;
	GList *text = NULL, *sysent, *usrent;
	const char *home;
	char *icon;
	int len;

	sysent = xde_style_entries(ctx, sysdir, XdeStyleSystem, fname);

	home = getenv("HOME") ? : "~";
	len = strlen(home) + 1 + strlen(usr) + 1;
	usrdir = calloc(len, sizeof(*usrdir));
	strcpy(usrdir, home);
	strcat(usrdir, usr);

	usrent = xde_style_entries(ctx, usrdir, XdeStyleUser, fname);

	if (!sysent && !usrent) {
		free(usrdir);
		return (text);
	}
	icon = xde_wrap_icon(xde_get_icon(ctx, "style"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Styles) {Choose a style...}", icon);
	text = g_list_append(text, s);
	if (sysent)
		text = g_list_concat(text, sysent);
	if (sysent && usrent) {
		xde_increase_indent(ctx);
		text = g_list_concat(text, ctx->wmm.ops.separator(ctx, NULL));
		xde_decrease_indent(ctx);
	}
	if (usrent)
		text = g_list_concat(text, usrent);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
	free(icon);
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
	char *icon, *s;
	GList *text = NULL;

	icon = xde_wrap_icon(xde_get_icon(ctx, "preferences-desktop"));
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

	/* FIXME: perlpanel does not support workspaces command */
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

	icon = xde_wrap_icon(xde_get_icon(ctx, ctx->name));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (PerlPanel)", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
#if 0
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
#endif
	text = g_list_concat(text, ctx->wmm.config(ctx));
	text = g_list_concat(text, ctx->wmm.themes(ctx));
	text = g_list_concat(text, ctx->wmm.styles(ctx));
#if 1
	s = g_strdup_printf("%s%s\n", ctx->indent, "[submenu] (Backgrounds) {Set the Background}");
	text = g_list_append(text, s);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[exec] (Random Background) {fbsetbg -r /usr/share/fluxbox/backgrounds}");
	text = g_list_append(text, s);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
#endif
	text = g_list_concat(text, ctx->wmm.wkspcs(ctx));
#if 0
	s = g_strdup_printf("%s%s\n", ctx->indent, "[sub] (Processes) <!procinfo.pl>");
	text = g_list_append(text, s);
#endif
	icon = xde_wrap_icon(xde_get_icon(ctx, "applications-utilities"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[submenu] (Tools)", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_increase_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[exec] (Window name) {xprop WM_CLASS|cut -d \\\" -f 2|gxmessage -file - -center}");
	text = g_list_append(text, s);
	icon = xde_wrap_icon(xde_get_icon(ctx, "applets-screenshooter"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Screenshot - JPG) {import screenshot.jpg && display -resize 50% screenshot.jpg}", icon);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Screenshot - PNG) {import screenshot.png && display -resize 50% screenshot.png}", icon);
	text = g_list_append(text, s);
	free(icon);
	icon = xde_wrap_icon(xde_get_icon(ctx, "gtk-execute"));
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Run) {fbrun -font 10x20 -fg grey -bg black -title run}", icon);
	text = g_list_append(text, s);
	s = g_strdup_printf("%s%s%s\n", ctx->indent, "[exec] (Run Command) {bbrun -a -w}", icon);
	text = g_list_append(text, s);
	free(icon);
	xde_decrease_indent(ctx);
	s = g_strdup_printf("%s%s\n", ctx->indent, "[end]");
	text = g_list_append(text, s);
#if 1
	icon = xde_wrap_icon(xde_get_icon(ctx, "preferences-system-windows"));
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
#endif
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
	.name = "perlpanel",
	.format = "perlpanel",
	.desktop = "XDE",
	.version = VERSION,
	.tree = NULL,
	.level = 0,
	.iconflags = 0
//		| GTK_ICON_LOOKUP_NO_SVG
//		| GTK_ICON_LOOKUP_FORCE_SVG
//		| GTK_ICON_LOOKUP_USE_BUILTIN
//		| GTK_ICON_LOOKUP_GENERIC_FALLBACK
//		| GTK_ICON_LOOKUP_FORCE_SIZE
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
