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

#ifndef __XDE_MENU_H__
#define __XDE_MENU_H__

#ifdef HAVE_CONFIG_H
#include "autoconf.h"
#endif

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <syslog.h>
#include <sys/utsname.h>

#include <assert.h>
#include <locale.h>
#include <langinfo.h>
#include <stdarg.h>
#include <strings.h>
#include <regex.h>
#include <pwd.h>
#include <dlfcn.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#ifdef XRANDR
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/randr.h>
#endif
#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif
#ifdef STARTUP_NOTIFICATION
#define SN_API_NOT_YET_FROZEN
#include <libsn/sn.h>
#endif
#include <X11/SM/SMlib.h>
#include <glib.h>
#include <gdk/gdkx.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <cairo.h>

#define WNCK_I_KNOW_THIS_IS_UNSTABLE
#include <libwnck/libwnck.h>

#define GMENU_I_KNOW_THIS_IS_UNSTABLE
#include <gmenu-tree.h>

#ifdef _GNU_SOURCE
#include <getopt.h>
#endif

#define XPRINTF(args...) do { } while (0)
#define OPRINTF(args...) do { if (options.output > 1) { \
	fprintf(stderr, "I: "); \
	fprintf(stderr, args); \
	fflush(stderr); } } while (0)
#define DPRINTF(args...) do { if (options.debug) { \
	fprintf(stderr, "D: %s +%d %s(): ", __FILE__, __LINE__, __func__); \
	fprintf(stderr, args); \
	fflush(stderr); } } while (0)
#define EPRINTF(args...) do { \
	fprintf(stderr, "E: %s +%d %s(): ", __FILE__, __LINE__, __func__); \
	fprintf(stderr, args); \
	fflush(stderr);   } while (0)
#define WPRINTF(args...) do { \
	fprintf(stderr, "W: %s +%d %s(): ", __FILE__, __LINE__, __func__); \
	fprintf(stderr, args); \
	fflush(stderr);   } while (0)
#define DPRINT() do { if (options.debug) { \
	fprintf(stderr, "D: %s +%d %s()\n", __FILE__, __LINE__, __func__); \
	fflush(stderr); } } while (0)

#undef EXIT_SUCCESS
#undef EXIT_FAILURE
#undef EXIT_SYNTAXERR

#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1
#define EXIT_SYNTAXERR	2

extern int saveArgc;
extern char **saveArgv;

extern Atom _XA_XDE_ICON_THEME_NAME;	/* XXX */
extern Atom _XA_XDE_THEME_NAME;
extern Atom _XA_XDE_WM_CLASS;
extern Atom _XA_XDE_WM_CMDLINE;
extern Atom _XA_XDE_WM_COMMAND;
extern Atom _XA_XDE_WM_ETCDIR;
extern Atom _XA_XDE_WM_HOST;
extern Atom _XA_XDE_WM_HOSTNAME;
extern Atom _XA_XDE_WM_ICCCM_SUPPORT;
extern Atom _XA_XDE_WM_ICON;
extern Atom _XA_XDE_WM_ICONTHEME;	/* XXX */
extern Atom _XA_XDE_WM_INFO;
extern Atom _XA_XDE_WM_MENU;
extern Atom _XA_XDE_WM_NAME;
extern Atom _XA_XDE_WM_NETWM_SUPPORT;
extern Atom _XA_XDE_WM_PID;
extern Atom _XA_XDE_WM_PRVDIR;
extern Atom _XA_XDE_WM_RCFILE;
extern Atom _XA_XDE_WM_REDIR_SUPPORT;
extern Atom _XA_XDE_WM_STYLE;
extern Atom _XA_XDE_WM_STYLENAME;
extern Atom _XA_XDE_WM_SYSDIR;
extern Atom _XA_XDE_WM_THEME;
extern Atom _XA_XDE_WM_THEMEFILE;
extern Atom _XA_XDE_WM_USRDIR;
extern Atom _XA_XDE_WM_VERSION;

extern Atom _XA_GTK_READ_RCFILES;
extern Atom _XA_MANAGER;

typedef enum {
	CommandDefault,
	CommandRun,
	CommandQuit,
	CommandReplace,
	CommandHelp,
	CommandVersion,
	CommandCopying,
} Command;

typedef enum {
	StyleFullmenu,
	StyleAppmenu,
	StyleSubmenu,
	StyleEntries,
} Style;

typedef enum {
	XdeStyleSystem,
	XdeStyleUser,
	XdeStyleMixed,
} Which;

typedef struct {
	int debug;
	int output;
	Command command;
	char *format;
	Style style;
	char *desktop;
	char *charset;
	char *language;
	char *locale;
	char *rootmenu;
	Bool dieonerr;
	Bool fileout;
	char *filename;
	Bool noicons;
	char *theme;
	Bool launch;
	char *clientId;
	char *saveFile;
	char *runhist;
	char *recapps;
	char *recently;
	char *recent;
	char *keep;
	char *menu;
	char *display;
} Options;

extern Options options;
extern Options defaults;

typedef struct MenuContext MenuContext;

struct MenuContext {
	void *handle;
	char *name;
	char *desktop;
	char *version;
	GMenuTree *tree;
	int level;
	char *indent;
	GtkIconLookupFlags iconflags;
	GList *output;
	GList *(*create) (MenuContext *ctx, Style style, const char *name);
	GList *(*wmmenu) (MenuContext *ctx);	/* output the window manager menu */
	GList *(*appmenu) (MenuContext *ctx, GList *entries, const char *name);
	GList *(*rootmenu) (MenuContext *ctx, GList *entries);
	GList *(*build) (MenuContext *ctx, GMenuTreeItemType type, gpointer item);
	struct {
		GList *(*menu) (MenuContext *ctx, GMenuTreeDirectory *menu);
		GList *(*directory) (MenuContext *ctx, GMenuTreeDirectory *dir);
		GList *(*header) (MenuContext *ctx, GMenuTreeHeader *hdr);
		GList *(*separator) (MenuContext *ctx, GMenuTreeSeparator *sep);
		GList *(*entry) (MenuContext *ctx, GMenuTreeEntry *ent);
		GList *(*alias) (MenuContext *ctx, GMenuTreeAlias *als);
	} ops;
	GList *(*themes) (MenuContext *ctx);
	GList *(*styles) (MenuContext *ctx);
};

typedef struct {
	int index;
	GdkDisplay *disp;
	GdkScreen *scrn;
	GdkWindow *root;
	WnckScreen *wnck;
	char *theme;
	char *itheme;
	Window selwin;
	Atom atom;
	char *wmname;
	Bool goodwm;
	MenuContext *context;
} XdeScreen;

extern XdeScreen *screens;

extern char *xdg_data_home;
extern char *xdg_data_dirs;
extern char *xdg_data_path;
extern char *xdg_data_last;

extern char *xdg_config_home;
extern char *xdg_config_dirs;
extern char *xdg_config_path;
extern char *xdg_config_last;

extern GMenuTree *tree;

typedef struct {
	char *key;
	char *name;
	GKeyFile *entry;
} XdeXsession;

#define GET_ENTRY_ICON_FLAG_XPM	(1<<0)
#define GET_ENTRY_ICON_FLAG_PNG (1<<1)
#define GET_ENTRY_ICON_FLAG_SVG (1<<2)
#define GET_ENTRY_ICON_FLAG_JPG (1<<3)
#define GET_ENTRY_ICON_FLAG_GIF (1<<4)
#define GET_ENTRY_ICON_FLAG_TIF (1<<5)

int xde_reset_indent(MenuContext *ctx, int level);
char *xde_increase_indent(MenuContext *ctx);
char *xde_decrease_indent(MenuContext *ctx);
char *xde_character_escape(const char *string, char special);
gint xde_string_compare(gconstpointer a, gconstpointer b);

char *xde_get_icons(MenuContext *ctx, const char *inames[]);
char *xde_get_icon(MenuContext *ctx, const char *iname);
char *xde_get_icon2(MenuContext *ctx, const char *iname1, const char *iname2);
gboolean xde_test_icon_ext(MenuContext *ctx, const char *path, int flags);
char *xde_get_entry_icon(MenuContext *ctx, GKeyFile *entry, const char *dflt1, const char *dflt2, int flags);
char *xde_get_app_icon(MenuContext *ctx, GDesktopAppInfo *app, const char *dflt1, const char *dflt2, int flags);

GList *xde_get_xsessions(void);
void xde_free_xsessions(GList *list);
GList *xde_create_simple(MenuContext *ctx, Style style, const char *name);
GList *xde_build_simple(MenuContext *ctx, GMenuTreeItemType type, gpointer item);
GList *xde_menu_simple(MenuContext *ctx, GMenuTreeDirectory *menu);
GList *xde_alias_simple(MenuContext *ctx, GMenuTreeAlias *als);

#endif				/* __XDE_MENU_H__ */

// vim: set sw=8 tw=80 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS foldmarker=@{,@} foldmethod=marker:
