/*****************************************************************************

 Copyright (c) 2008-2022  Monavacon Limited <http://www.monavacon.com/>
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

/** @section Headers
  * @{ */

#ifndef __XDE_MENU_H__
#define __XDE_MENU_H__

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#endif

#ifdef HAVE_CONFIG_H
#include "autoconf.h"
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
#include <wordexp.h>
#include <execinfo.h>
#include <math.h>
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
#ifdef VNC_SUPPORTED
#include <X11/extensions/Xvnc.h>
#endif
#if 0
#include <X11/extensions/scrnsaver.h>
#endif
#include <X11/extensions/dpms.h>
#if 0
#include <X11/extensions/xf86misc.h>
#endif
#include <X11/XKBlib.h>
#ifdef STARTUP_NOTIFICATION
#define SN_API_NOT_YET_FROZEN
#include <libsn/sn.h>
#endif
#if 0
#include <X11/Xdmcp.h>
#endif
#if 0
#include <X11/Xauth.h>
#endif
#include <X11/SM/SMlib.h>
#include <gio/gio.h>
#include <gio/gdesktopappinfo.h>
#include <glib.h>
#include <glib-unix.h>
#include <gdk/gdkx.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <cairo.h>

#define WNCK_I_KNOW_THIS_IS_UNSTABLE
#include <libwnck/libwnck.h>

#define GMENU_I_KNOW_THIS_IS_UNSTABLE
#include <gmenu-tree.h>

#include <pwd.h>
#include <fontconfig/fontconfig.h>
#include <pango/pangofc-fontmap.h>

#ifdef _GNU_SOURCE
#include <getopt.h>
#endif

#ifndef HAVE_GNOME_MENUS_3
#define GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED	1 << 4
#define GMENU_TREE_FLAGS_SORT_DISPLAY_NAME	1 << 5
#endif

/** @} */

/** @section Preamble
  * @{ */

#define XPRINTF(_args...) do { } while (0)

#define DPRINTF(_num, _args...) do { if (options.debug >= _num) { \
		fprintf(stderr, NAME ": D: %12s: +%4d : %s() : ", __FILE__, __LINE__, __func__); \
		fprintf(stderr, _args); fflush(stderr); } } while (0)

#define EPRINTF(_args...) do { \
		fprintf(stderr, NAME ": E: %12s: +%4d : %s() : ", __FILE__, __LINE__, __func__); \
		fprintf(stderr, _args); fflush(stderr); } while (0)

#define OPRINTF(_num, _args...) do { if (options.debug >= _num || options.output > _num) { \
		fprintf(stdout, NAME ": I: "); \
		fprintf(stdout, _args); fflush(stdout); } } while (0)

#define PTRACE(_num) do { if (options.debug >= _num || options.output >= _num) { \
		fprintf(stderr, NAME ": T: %12s: +%4d : %s()\n", __FILE__, __LINE__, __func__); \
		fflush(stderr); } } while (0)

extern void dumpstack(const char *file, const int line, const char *func);

#undef EXIT_SUCCESS
#undef EXIT_FAILURE
#undef EXIT_SYNTAXERR

#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1
#define EXIT_SYNTAXERR	2

#define GTK_EVENT_STOP		TRUE
#define GTK_EVENT_PROPAGATE	FALSE

extern const char *program;

#define XA_PREFIX		"_XDE_MENU"
#define XA_SELECTION_NAME	XA_PREFIX "_S%d"
#define XA_NET_DESKTOP_LAYOUT	"_NET_DESKTOP_LAYOUT_S%d"
#if 0
#define LOGO_NAME		"start-here"
#else
#define LOGO_NAME		"arch-logo"
#endif

extern int saveArgc;
extern char **saveArgv;

#define RESNAME "xde-menu"
#define RESCLAS "XDE-Menu"
#define RESTITL "XDG Compliant Menu"

#define APPDFLT	"/usr/share/X11/app-defaults/" RESCLAS

extern int cmdArgc;
extern char **cmdArgv;

/** @} */

/** @section Globals and Structures
  * @{ */

extern Atom _XA_GTK_READ_RCFILES;

extern Atom _XA_NET_ACTIVE_WINDOW;
extern Atom _XA_NET_CLIENT_LIST;
extern Atom _XA_NET_CLIENT_LIST_STACKING;
extern Atom _XA_NET_CURRENT_DESKTOP;
extern Atom _XA_NET_DESKTOP_LAYOUT;
extern Atom _XA_NET_DESKTOP_NAMES;
extern Atom _XA_NET_NUMBER_OF_DESKTOPS;

extern Atom _XA_WIN_AREA;
extern Atom _XA_WIN_AREA_COUNT;
extern Atom _XA_WIN_CLIENT_LIST;
extern Atom _XA_WIN_DESKTOP_BUTTON_PROXY;
extern Atom _XA_WIN_FOCUS;
extern Atom _XA_WIN_WORKSPACE;
extern Atom _XA_WIN_WORKSPACE_COUNT;

extern Atom _XA_WM_DESKTOP;

extern Atom _XA_ESETROOT_PMAP_ID;
extern Atom _XA_XROOTPMAP_ID;

extern Atom _XA_XDE_ICON_THEME_NAME;		/* XXX */
extern Atom _XA_XDE_THEME_NAME;
extern Atom _XA_XDE_WM_CLASS;
extern Atom _XA_XDE_WM_CMDLINE;
extern Atom _XA_XDE_WM_COMMAND;
extern Atom _XA_XDE_WM_ETCDIR;
extern Atom _XA_XDE_WM_HOST;
extern Atom _XA_XDE_WM_HOSTNAME;
extern Atom _XA_XDE_WM_ICCCM_SUPPORT;
extern Atom _XA_XDE_WM_ICON;
extern Atom _XA_XDE_WM_ICONTHEME;		/* XXX */
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

extern Atom _XA_PREFIX_REFRESH;
extern Atom _XA_PREFIX_RESTART;
extern Atom _XA_PREFIX_POPMENU;
extern Atom _XA_PREFIX_EDITOR;

typedef enum {
	CommandDefault,			/* just generate WM root menu */
	CommandMenugen,			/* just generate WM root menu */
	CommandMonitor,			/* run a new instance with monitoring */
	CommandQuit,			/* ask running instance to quit */
	CommandRestart,			/* ask running instance to restart */
	CommandRefresh,			/* ask running instance to refresh menu */
	CommandPopMenu,			/* ask running instance to pop menu */
	CommandEditor,			/* ask running instance to pop editor */
	CommandHelp,			/* print usage info and exit */
	CommandVersion,			/* print version info and exit */
	CommandCopying,			/* print copying info and exit */
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

typedef enum {
	UseScreenDefault,		/* default screen by button */
	UseScreenActive,		/* screen with active window */
	UseScreenFocused,		/* screen with focused window */
	UseScreenPointer,		/* screen with pointer */
	UseScreenSpecified,		/* specified screen */
} UseScreen;

typedef enum {
	PositionDefault,		/* default position */
	PositionPointer,		/* position at pointer */
	PositionCenter,			/* center of monitor */
	PositionTopLeft,		/* top left of work area */
	PositionBottomRight,		/* bottom right of work area */
	PositionSpecified,		/* specified position (X geometry) */
} MenuPosition;

typedef enum {
	WindowOrderDefault,
	WindowOrderClient,
	WindowOrderStacking,
} WindowOrder;

typedef enum {
	SortByDefault,			/* default sorting */
	SortByRecent,			/* sort from most recent */
	SortByFavorite,			/* sort from most frequent */
} Sorting;

typedef enum {
	IncludeDefault,			/* default things */
	IncludeDocs,			/* documents (files) only */
	IncludeApps,			/* applications only */
	IncludeBoth,			/* both documents and applications */
} Include;

typedef enum {
	OrganizeDefault,
	OrganizeNone,
	OrganizeDate,
	OrganizeFreq,
	OrganizeGroup,
	OrganizeContent,
	OrganizeApp,
} Organize;

typedef enum {
	PopupPager,			/* desktop pager feedback */
	PopupTasks,			/* task list feedback */
	PopupCycle,			/* window cycling feedback */
	PopupSetBG,			/* workspace background feedback */
	PopupStart,			/* startup notification feedback */
	PopupInput,			/* desktop input manager */
	PopupLast,
} PopupType;

typedef struct {
	int mask, x, y;
	unsigned int w, h;
} XdeGeometry;

typedef struct {
	char *exec;
	char *resopts;
	char *options;
	Bool notify;
} Terminal;

typedef struct {
	int debug;
	int output;
	char *display;
	int screen;
	int monitor;
	Time timeout;
	unsigned iconsize;
	double fontsize;
	int border;
	char *wmname;
	char *format;
	Style style;
	char *desktop;
	char *rootmenu;
	char *menufile;
	char *theme;
	char *itheme;
	char *runhist;
	char *recapps;
	char *recently;
	char *recent;
	int maximum;
	char *menu;
	char *keypress;
	Bool keyboard;
	Bool pointer;
	int button;
	Time timestamp;
	UseScreen which;
	MenuPosition where;
	XdeGeometry geom;
	WindowOrder order;
	char *filename;
	Bool replace;
	Bool systray;
	int treeflags;
	Bool normal;
	Bool hidden;
	Bool minimized;
	Bool monitors;
	Bool workspaces;
	Bool activate;
	Bool raise;
	Bool restore;
	Command command;
	Bool tooltips;
	char *clientId;
	char *saveFile;
	Bool fileout;
	Bool noicons;
	Bool launch;
	Bool generate;
	Bool actions;
	Bool exit;
	char *termname;
	char *terminal;
	char *termresn;
} Options;

#define XDE_MENU_FLAG_DIEONERR		(1<< 0)
#define XDE_MENU_FLAG_FILEOUT		(1<< 1)
#define XDE_MENU_FLAG_NOICONS		(1<< 2)
#define XDE_MENU_FLAG_LAUNCH		(1<< 3)
#define XDE_MENU_FLAG_TRAY		(1<< 4)
#define XDE_MENU_FLAG_GENERATE		(1<< 5)
#define XDE_MENU_FLAG_TOOLTIPS		(1<< 6)
#define XDE_MENU_FLAG_ACTIONS		(1<< 7)
#define XDE_MENU_FLAG_UNIQUE		(1<< 8)
#define XDE_MENU_FLAG_EXCLUDED		(1<< 9)
#define XDE_MENU_FLAG_NODISPLAY		(1<<10)
#define XDE_MENU_FLAG_UNALLOCATED	(1<<11)
#define XDE_MENU_FLAG_EMPTY		(1<<12)
#define XDE_MENU_FLAG_SEPARATORS	(1<<13)
#define XDE_MENU_FLAG_SORT		(1<<14)

typedef struct MenuContext MenuContext;

struct MenuContext {
	void *handle;
	const char *name;
	const char *format;
	const char *wmname;
	const char *desktop;
	const char *version;
	struct {
		const char *sysdir;
		const char *usrdir;
		const char *subdir;
		const char *fname;
		const char *suffix;
	} styles;
	GMenuTree *tree;
	GHashTable *xsessions;
	GtkMenu *menu;
	int level;
	char *indent;
	GtkIconLookupFlags iconflags;
	GList *stack;
	struct {
		GList *output;
		char *(*wrap) (MenuContext *ctx, char *icon);
		GList *(*create) (MenuContext *ctx, Style style, const char *name);
		GList *(*appmenu) (MenuContext *ctx, GList *entries, const char *name);
		GList *(*rootmenu) (MenuContext *ctx, GList *entries);
		GList *(*build) (MenuContext *ctx, GMenuTreeItemType type, gpointer item);
		struct {
			GList *(*menu) (MenuContext *ctx, GMenuTreeDirectory *menu);
			GList *(*actions) (MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info);
			GList *(*directory) (MenuContext *ctx, GMenuTreeDirectory *dir);
			GList *(*header) (MenuContext *ctx, GMenuTreeHeader *hdr);
			GList *(*separator) (MenuContext *ctx, GMenuTreeSeparator *sep);
			GList *(*entry) (MenuContext *ctx, GMenuTreeEntry *ent);
			GList *(*alias) (MenuContext *ctx, GMenuTreeAlias *als);
			GList *(*action) (MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info,
					  const char *action);
			GList *(*pin) (MenuContext *ctx);
		} ops;
		GList *(*wmmenu) (MenuContext *ctx);
		GList *(*styles) (MenuContext *ctx);
		GList *(*themes) (MenuContext *ctx);
		GList *(*config) (MenuContext *ctx);
		GList *(*wkspcs) (MenuContext *ctx);
		GList *(*wmspec) (MenuContext *ctx);
	} wmm;
	struct {
		GtkMenu *output;
		GtkMenu *(*create) (MenuContext *ctx, Style style, const char *name);
		GtkMenu *(*appmenu) (MenuContext *ctx, GtkMenu *entries, const char *name);
		GtkMenu *(*rootmenu) (MenuContext *ctx, GtkMenu *entries);
		GtkMenuItem *(*build) (MenuContext *ctx, GMenuTreeItemType type, gpointer item);
		struct {
			GtkMenu *(*menu) (MenuContext *ctx, GMenuTreeDirectory *menu);
			GtkMenu *(*actions) (MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info);
			GtkMenuItem *(*directory) (MenuContext *ctx, GMenuTreeDirectory *dir);
			GtkMenuItem *(*header) (MenuContext *ctx, GMenuTreeHeader *hdr);
			GtkMenuItem *(*separator) (MenuContext *ctx, GMenuTreeSeparator *sep);
			GtkMenuItem *(*entry) (MenuContext *ctx, GMenuTreeEntry *ent);
			GtkMenuItem *(*alias) (MenuContext *ctx, GMenuTreeAlias *als);
			GtkMenuItem *(*action) (MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info,
						const char *action);
			GtkMenuItem *(*pin) (MenuContext *ctx);
		} ops;
		GtkMenuItem *(*wmmenu) (MenuContext *ctx);
		GtkMenuItem *(*styles) (MenuContext *ctx);
		GtkMenuItem *(*themes) (MenuContext *ctx);
		GtkMenuItem *(*config) (MenuContext *Ctx);
		GtkMenuItem *(*wkspcs) (MenuContext *ctx);
		GtkMenuItem *(*wmspec) (MenuContext *ctx);
	} gtk;
};

extern Display *dpy;
extern GdkDisplay *disp;

struct XdeScreen;
typedef struct XdeScreen XdeScreen;
struct XdeMonitor;
typedef struct XdeMonitor XdeMonitor;
struct XdePopup;
typedef struct XdePopup XdePopup;

struct XdePopup {
	PopupType type;			/* popup type */
	GtkWidget *popup;		/* popup window */
	GtkWidget *content;		/* content of popup window */
	GtkListStore *model;		/* model for icon-view content */
	int seqcount;			/* number of sequences in store */
	unsigned timer;			/* drop popup timer */
	Bool inside;			/* pointer inside popup */
	Bool keyboard;			/* have a keyboard grab */
	Bool pointer;			/* have a pointer grab */
	Bool popped;			/* popup is popped */
	GdkModifierType mask;
};

struct XdeMonitor {
	int index;			/* monitor number */
	XdeScreen *xscr;		/* screen */
	int current;			/* current desktop for this monitor */
	GdkRectangle geom;		/* geometry of the monitor */
	struct {
		GList *oldlist;		/* clients for this monitor (old gnome) */
		GList *clients;		/* clients for this monitor */
		GList *stacked;		/* clients for this monitor (stacked) */
		struct {
			GdkWindow *old;	/* active window (previous) */
			GdkWindow *now;	/* active window (current) */
		} active;
	};
};

struct XdeScreen {
	int index;			/* screen number */
	GdkDisplay *disp;		/* gdk display */
	GdkScreen *scrn;		/* gdk screen */
	GdkWindow *root;		/* gdk root window */
	WnckScreen *wnck;		/* wnck screen */
	gint nmon;			/* number of monitors */
	XdeMonitor *mons;		/* monitors for this screen */
	Bool mhaware;			/* multi-head aware NetWM */
	char *theme;			/* XDE theme name */
	char *itheme;			/* XDE icon theme name */
	Window selwin;			/* selection owner window */
	Atom atom;			/* selection atom for this screen */
	Window laywin;			/* desktop layout selection owner */
	Atom prop;			/* dekstop layout selection atom */
	int width, height;		/* dimensions of screen */
	int current;			/* current desktop for this screen */
	char *wmname;			/* window manager name (adjusted) */
	Bool goodwm;			/* is the window manager usable? */
	MenuContext *context;		/* menu context for screen */
	struct {
		GList *oldlist;		/* clients for this screen (old gnome) */
		GList *clients;		/* clients for this screen */
		GList *stacked;		/* clients for this screen (stacked) */
		struct {
			GdkWindow *old;	/* active window (previous) */
			GdkWindow *now;	/* active window (current) */
		} active;
	};
	GtkWidget* ttwindow;		/* tooltip window for status icon */
	GtkStatusIcon *icon;		/* system tray status icon this screen */
};

extern Terminal terminals[];
extern Options options;

extern XdeScreen *screens;

extern char *xdg_data_home;
extern char *xdg_data_dirs;
extern char *xdg_data_path;
extern char *xdg_data_last;

extern char *xdg_config_home;
extern char *xdg_config_dirs;
extern char *xdg_config_path;
extern char *xdg_config_last;

typedef struct {
	char *key;
	char *file;
	char *name;
	GKeyFile *entry;
	GDesktopAppInfo *info;
} XdeXsession;

#define GET_ENTRY_ICON_FLAG_XPM	(1<<0)
#define GET_ENTRY_ICON_FLAG_PNG (1<<1)
#define GET_ENTRY_ICON_FLAG_SVG (1<<2)
#define GET_ENTRY_ICON_FLAG_JPG (1<<3)
#define GET_ENTRY_ICON_FLAG_GIF (1<<4)
#define GET_ENTRY_ICON_FLAG_TIF (1<<5)

/** @} */

/** @section Function Declarations
  * @{ */

int xde_reset_indent(MenuContext *ctx, int level);
char *xde_increase_indent(MenuContext *ctx);
char *xde_decrease_indent(MenuContext *ctx);
char *xde_character_escape(const char *string, char special);
gint xde_string_compare(gconstpointer a, gconstpointer b);

char *xde_get_icons(MenuContext *ctx, const char **inames);
char *xde_get_icon(MenuContext *ctx, const char *iname);
char *xde_get_icon2(MenuContext *ctx, const char *iname1, const char *iname2);
gboolean xde_test_icon_ext(MenuContext *ctx, const char *path, int flags);
char *xde_get_entry_icon(MenuContext *ctx, GKeyFile *entry, GIcon *gicon, const char *dflt1, const char *dflt2,
			 int flags);
char *xde_get_action_icon(MenuContext *ctx, GKeyFile *entry, const char *action, GIcon *gicon, const char *dflt1,
			  const char *dflt2, int flags);
char *xde_get_app_icon(MenuContext *ctx, GDesktopAppInfo *app, GIcon *gicon, const char *dflt1, const char *dflt2,
		       int flags);

char *xde_get_command(GDesktopAppInfo *app, const char *appid, const char *icon);
char *xde_get_action(GDesktopAppInfo *app, const char *appid, const char *icon, const char *action);

GList *xde_get_xsessions(MenuContext *ctx);
void xde_free_xsessions(GList *list);
GList *xde_create_simple(MenuContext *ctx, Style style, const char *name);
GList *xde_build_simple(MenuContext *ctx, GMenuTreeItemType type, gpointer item);
GList *xde_menu_simple(MenuContext *ctx, GMenuTreeDirectory *menu);
GList *xde_actions_simple(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info);
GList *xde_alias_simple(MenuContext *ctx, GMenuTreeAlias *als);

GList *xde_common_get_styles(MenuContext *ctx, const char *dname, const char *fname, const char *suffix);
GList *xde_common_find_themes(MenuContext *ctx, GList *styles);
GList *xde_common_get_themes(MenuContext *ctx);

GtkMenu *xde_gtk_get_xsessions(void);
void xde_gtk_free_xsessions(GtkMenu *list);
GtkMenu *xde_gtk_create_simple(MenuContext *ctx, Style style, const char *name);
GtkMenu *xde_gtk_common_appmenu(MenuContext *ctx, GtkMenu *entries, const char *name);
GtkMenu *xde_gtk_common_rootmenu(MenuContext *ctx, GtkMenu *entries);
GtkMenuItem *xde_gtk_build_simple(MenuContext *ctx, GMenuTreeItemType type, gpointer item);
GtkMenu *xde_gtk_common_menu(MenuContext *ctx, GMenuTreeDirectory *menu);
GtkMenu *xde_gtk_common_actions(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info);
GtkMenuItem *xde_gtk_common_separator(MenuContext *ctx, GMenuTreeSeparator *sep);
GtkMenuItem *xde_gtk_common_header(MenuContext *ctx, GMenuTreeHeader *hdr);
GtkMenuItem *xde_gtk_common_directory(MenuContext *ctx, GMenuTreeDirectory *dir);
GtkMenuItem *xde_gtk_common_entry(MenuContext *ctx, GMenuTreeEntry *ent);
GtkMenuItem *xde_gtk_common_alias(MenuContext *ctx, GMenuTreeAlias *als);
GtkMenuItem *xde_gtk_common_action(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info,
				   const char *action);
GtkMenuItem *xde_gtk_common_pin(MenuContext *ctx);
GtkMenuItem *xde_gtk_common_wmmenu(MenuContext *ctx);
GtkMenuItem *xde_gtk_common_themes(MenuContext *ctx);
GtkMenuItem *xde_gtk_styles_simple(MenuContext *ctx);
GtkMenuItem *xde_gtk_themes_simple(MenuContext *ctx);
GtkMenuItem *xde_gtk_common_wmspec(MenuContext *ctx);
GtkMenuItem *xde_gtk_common_wkspcs(MenuContext *ctx);

void xde_entry_activated(GtkMenuItem *menuitem, gpointer user_data);
void xde_entry_disconnect(gpointer data, GClosure *closure);

/** @} */

#endif				/* __XDE_MENU_H__ */

// vim: set sw=8 tw=80 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS fo+=tcqlorn foldmarker=@{,@} foldmethod=marker:
