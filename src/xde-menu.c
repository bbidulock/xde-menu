/*****************************************************************************

 Copyright (c) 2008-2016  Monavacon Limited <http://www.monavacon.com/>
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

#include "xde-menu.h"

/** @} */

/** @section Preamble
  * @{ */

void
dumpstack(const char *file, const int line, const char *func)
{
	void *buffer[32];
	int nptr;
	char **strings;
	int i;

	if ((nptr = backtrace(buffer, 32)) && (strings = backtrace_symbols(buffer, nptr)))
		for (i = 0; i < nptr; i++)
			fprintf(stderr, NAME ": E: %12s +%4d : %s() : \t%s\n", file, line, func, strings[i]);
}

const char *program = NAME;

int saveArgc;
char **saveArgv;

SmcConn smcConn = NULL;

int cmdArgc;
char **cmdArgv;

/** @} */

/** @section Globals and Structures
  * @{ */

Atom _XA_GTK_READ_RCFILES;

Atom _XA_NET_ACTIVE_WINDOW;
Atom _XA_NET_CLIENT_LIST;
Atom _XA_NET_CLIENT_LIST_STACKING;
Atom _XA_NET_CURRENT_DESKTOP;
Atom _XA_NET_DESKTOP_LAYOUT;
Atom _XA_NET_DESKTOP_NAMES;
Atom _XA_NET_NUMBER_OF_DESKTOPS;

Atom _XA_WIN_AREA;
Atom _XA_WIN_AREA_COUNT;
Atom _XA_WIN_CLIENT_LIST;
Atom _XA_WIN_DESKTOP_BUTTON_PROXY;
Atom _XA_WIN_FOCUS;
Atom _XA_WIN_WORKSPACE;
Atom _XA_WIN_WORKSPACE_COUNT;

Atom _XA_WM_DESKTOP;

Atom _XA_ESETROOT_PMAP_ID;
Atom _XA_XROOTPMAP_ID;

Atom _XA_XDE_ICON_THEME_NAME;		/* XXX */
Atom _XA_XDE_THEME_NAME;
Atom _XA_XDE_WM_CLASS;
Atom _XA_XDE_WM_CMDLINE;
Atom _XA_XDE_WM_COMMAND;
Atom _XA_XDE_WM_ETCDIR;
Atom _XA_XDE_WM_HOST;
Atom _XA_XDE_WM_HOSTNAME;
Atom _XA_XDE_WM_ICCCM_SUPPORT;
Atom _XA_XDE_WM_ICON;
Atom _XA_XDE_WM_ICONTHEME;		/* XXX */
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

Atom _XA_PREFIX_REFRESH;
Atom _XA_PREFIX_RESTART;
Atom _XA_PREFIX_POPMENU;
Atom _XA_PREFIX_EDITOR;

#if 0
static Atom _XA_NET_STARTUP_INFO;
static Atom _XA_NET_STARTUP_INFO_BEGIN;
#endif				/* STARTUP_NOTIFICATION */

Options options = {
	.debug = 0,
	.output = 1,
	.display = NULL,
	.screen = -1,
	.monitor = -1,
	.timeout = 1000,
	.iconsize = 48,
	.fontsize = 12.0,
	.border = 3,
	.wmname = NULL,
	.format = NULL,
	.style = StyleFullmenu,
	.desktop = NULL,
	.rootmenu = NULL,
	.menufile = NULL,
	.theme = NULL,
	.itheme = NULL,
	.runhist = NULL,
	.recapps = NULL,
	.recently = NULL,
	.recent = NULL,
	.maximum = 50,
	.menu = "applications",
	.keypress = NULL,
	.keyboard = False,
	.pointer = False,
	.button = 0,
	.timestamp = CurrentTime,
	.which = UseScreenDefault,
	.where = PositionDefault,
	.geom = {
		 .mask = 0,
		 .x = 0,
		 .y = 0,
		 .w = 0,
		 .h = 0,
		 },
	.order = WindowOrderDefault,
	.filename = NULL,
	.replace = False,
	.systray = False,
	.treeflags = 0,
	.normal = False,
	.hidden = False,
	.minimized = False,
	.monitors = False,
	.workspaces = False,
	.activate = True,
	.raise = False,
	.command = CommandDefault,
	.tooltips = False,
	.clientId = NULL,
	.saveFile = NULL,
	.fileout = False,
	.noicons = False,
	.launch = True,
	.generate = True,
	.actions = False,
	.exit = False,
};

Display *dpy = NULL;
GdkDisplay *disp = NULL;

XdeScreen *screens = NULL;

/** @} */

/** @section Deferred Actions
  * @{ */

/** @} */

/** @section Finding Screens and Monitors
  * @{ */

/** @brief find the specified monitor
  *
  * Either specified with options.screen and options.monitor, or if the DISPLAY
  * environment variable specifies a screen, use that screen; otherwise, return
  * NULL.
  */
static XdeMonitor *
find_specific_monitor(void)
{
	XdeMonitor *xmon = NULL;
	int nscr = gdk_display_get_n_screens(disp);
	XdeScreen *xscr;

	if (0 <= options.screen && options.screen < nscr) {
		/* user specified a valid screen number */
		xscr = screens + options.screen;
		if (0 <= options.monitor && options.monitor < xscr->nmon)
			xmon = xscr->mons + options.monitor;
	}
	return (xmon);
}

/** @brief find the screen of window with the focus
  */
static XdeMonitor *
find_focus_monitor(void)
{
	XdeMonitor *xmon = NULL;
	XdeScreen *xscr;
	GdkScreen *scrn;
	GdkWindow *win;
	Window focus = None;
	int revert_to, m;

	XGetInputFocus(dpy, &focus, &revert_to);
	if (focus != PointerRoot && focus != None) {
		win = gdk_x11_window_foreign_new_for_display(disp, focus);
		if (win) {
			scrn = gdk_window_get_screen(win);
			xscr = screens + gdk_screen_get_number(scrn);
			m = gdk_screen_get_monitor_at_window(scrn, win);
			g_object_unref(win);
			xmon = xscr->mons + m;
		}
	}
	return (xmon);
}

static XdeMonitor *
find_pointer_monitor(void)
{
	XdeMonitor *xmon = NULL;
	XdeScreen *xscr = NULL;
	GdkScreen *scrn = NULL;
	int m, x = 0, y = 0;

	gdk_display_get_pointer(disp, &scrn, &x, &y, NULL);
	if (scrn) {
		xscr = screens + gdk_screen_get_number(scrn);
		m = gdk_screen_get_monitor_at_point(scrn, x, y);
		xmon = xscr->mons + m;
	}
	return (xmon);
}

static XdeMonitor *
find_monitor(void)
{
	XdeMonitor *xmon = NULL;

	switch (options.which) {
	case UseScreenDefault:
		if (options.button) {
			if ((xmon = find_pointer_monitor()))
				return (xmon);
			if ((xmon = find_focus_monitor()))
				return (xmon);
		} else {
			if ((xmon = find_focus_monitor()))
				return (xmon);
			if ((xmon = find_pointer_monitor()))
				return (xmon);
		}
		break;
	case UseScreenActive:
		break;
	case UseScreenFocused:
		if ((xmon = find_focus_monitor()))
			return (xmon);
		break;
	case UseScreenPointer:
		if ((xmon = find_pointer_monitor()))
			return (xmon);
		break;
	case UseScreenSpecified:
		if ((xmon = find_specific_monitor()))
			return (xmon);
		break;
	}

	if (!xmon)
		xmon = screens->mons;
	return (xmon);
}

/** @} */

/** @section Menu Positioning
  * @{ */

static gboolean
position_pointer(GtkWidget *widget, XdeMonitor *xmon, gint *x, gint *y)
{
	PTRACE(5);
	gdk_display_get_pointer(disp, NULL, x, y, NULL);
	return TRUE;
}

static gboolean
position_center_monitor(GtkWidget *widget, XdeMonitor *xmon, gint *x, gint *y)
{
	GtkRequisition req;

	PTRACE(5);
	gtk_widget_get_requisition(widget, &req);

	*x = xmon->geom.x + (xmon->geom.width - req.width) / 2;
	*y = xmon->geom.y + (xmon->geom.height - req.height) / 2;

	return TRUE;
}

static gboolean
position_topleft_workarea(GtkWidget *widget, XdeMonitor *xmon, gint *x, gint *y)
{
#if 1
	WnckWorkspace *wkspc;

	/* XXX: not sure this is what we want... */
	wkspc = wnck_screen_get_active_workspace(xmon->xscr->wnck);
	*x = wnck_workspace_get_viewport_x(wkspc);
	*y = wnck_workspace_get_viewport_y(wkspc);
#else
	GdkScreen *scr;
	GdkRectangle rect;
	gint px, py, nmon;

	PTRACE(5);
	gdk_display_get_pointer(disp, &scr, &px, &py, NULL);
	nmon = gdk_screen_get_monitor_at_point(scr, px, py);
	gdk_screen_get_monitor_geometry(scr, nmon, &rect);

	*x = rect.x;
	*y = rect.y;
#endif

	return TRUE;
}

static gboolean
position_bottomright_workarea(GtkWidget *widget, XdeMonitor *xmon, gint *x, gint *y)
{
#if 1
	WnckWorkspace *wkspc;
	GtkRequisition req;

	/* XXX: not sure this is what we want... */
	wkspc = wnck_screen_get_active_workspace(xmon->xscr->wnck);
	gtk_widget_get_requisition(widget, &req);
	*x = wnck_workspace_get_viewport_x(wkspc) + wnck_workspace_get_width(wkspc) - req.width;
	*y = wnck_workspace_get_viewport_y(wkspc) + wnck_workspace_get_height(wkspc) - req.height;
#else
	GdkScreen *scrn;
	GdkRectangle rect;
	gint px, py, nmon;
	GtkRequisition req;

	PTRACE(5);
	gdk_display_get_pointer(disp, &scrn, &px, &py, NULL);
	nmon = gdk_screen_get_monitor_at_point(scrn, px, py);
	gdk_screen_get_monitor_geometry(scrn, nmon, &rect);
	gtk_widget_get_requisition(widget, &req);

	*x = rect.x + rect.width - req.width;
	*y = rect.y + rect.height - req.height;
#endif

	return TRUE;
}

static gboolean
position_specified(GtkWidget *widget, XdeMonitor *xmon, gint *x, gint *y)
{
	int x1, y1, sw, sh;

	sw = xmon->xscr->width;
	sh = xmon->xscr->height;
	DPRINTF(1, "screen width = %d\n", sw);
	DPRINTF(1, "screen height = %d\n", sh);

	x1 = (options.geom.mask & XNegative) ? sw - options.geom.x : options.geom.x;
	y1 = (options.geom.mask & YNegative) ? sh - options.geom.y : options.geom.y;

	DPRINTF(1, "geometry x1 = %d\n", x1);
	DPRINTF(1, "geometry y1 = %d\n", y1);
	DPRINTF(1, "geometry w = %d\n", options.geom.w);
	DPRINTF(1, "geometry h = %d\n", options.geom.h);

	if (!(options.geom.mask & (WidthValue | HeightValue))) {
		*x = x1;
		*y = y1;
	} else {
		GtkAllocation alloc = { 0, };
		int x2, y2;

		gtk_widget_realize(widget);
		gtk_widget_get_allocation(widget, &alloc);
		x2 = x1 + options.geom.w;
		y2 = y1 + options.geom.h;
		DPRINTF(1, "geometry x2 = %d\n", x2);
		DPRINTF(1, "geometry y2 = %d\n", y2);

		if (x1 + alloc.width < sw)
			*x = x1;
		else if (x2 - alloc.width > 0)
			*x = x2 - alloc.width;
		else
			*x = 0;

		if (y2 + alloc.height < sh)
			*y = y2;
		else if (y1 - alloc.height > 0)
			*y = y1 - alloc.height;
		else
			*y = 0;
	}
	DPRINTF(1, "placing window at +%d+%d\n", *x, *y);
	return TRUE;
}

void
position_widget(GtkWidget *widget, gint *x, gint *y, XdeMonitor *xmon)
{
	if (options.button) {
		position_pointer(widget, xmon, x, y);
		return;
	}
	switch (options.where) {
	case PositionDefault:
	default:
		position_center_monitor(widget, xmon, x, y);
		break;
	case PositionPointer:
		position_pointer(widget, xmon, x, y);
		break;
	case PositionCenter:
		position_center_monitor(widget, xmon, x, y);
		break;
	case PositionTopLeft:
		position_topleft_workarea(widget, xmon, x, y);
		break;
	case PositionBottomRight:
		position_bottomright_workarea(widget, xmon, x, y);
		break;
	case PositionSpecified:
		position_specified(widget, xmon, x, y);
		break;
	}
}

void
position_menu(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer user_data)
{
	XdeMonitor *xmon = user_data;

	if (push_in)
		*push_in = FALSE;
	position_widget(GTK_WIDGET(menu), x, y, xmon);
}

/** @} */

/** @section Setting and Getting Arguments
  * @{ */

/** @section Setting Arguments
  * @{ */

static const char *show_bool(Bool value);
static const char *show_which(UseScreen which);
static const char *show_where(MenuPosition where);

#if 1
static void
set_scmon(long scmon)
{
	options.monitor = (short) ((scmon >> 0) & 0xffff);
	options.screen = (short) ((scmon >> 16) & 0xffff);
	DPRINTF(1, "options.monitor = %d\n", options.monitor);
	DPRINTF(1, "options.screen = %d\n", options.screen);
}

static void
set_flags(long flags)
{
#if 1
	options.fileout = (flags & XDE_MENU_FLAG_FILEOUT) ? True : False;
	DPRINTF(1, "options.fileout = %s\n", show_bool(options.fileout));
	options.noicons = (flags & XDE_MENU_FLAG_NOICONS) ? True : False;
	DPRINTF(1, "options.noicons = %s\n", show_bool(options.noicons));
	options.launch = (flags & XDE_MENU_FLAG_LAUNCH) ? True : False;
	DPRINTF(1, "options.launch = %s\n", show_bool(options.launch));
#endif
	options.systray = (flags & XDE_MENU_FLAG_TRAY) ? True : False;
	DPRINTF(1, "options.systray = %s\n", show_bool(options.systray));
#if 1
	options.generate = (flags & XDE_MENU_FLAG_GENERATE) ? True : False;
	DPRINTF(1, "options.generate = %s\n", show_bool(options.generate));
#endif
	options.tooltips = (flags & XDE_MENU_FLAG_TOOLTIPS) ? True : False;
	DPRINTF(1, "options.tooltips = %s\n", show_bool(options.tooltips));
#if 1
	options.actions = (flags & XDE_MENU_FLAG_ACTIONS) ? True : False;
	DPRINTF(1, "options.actions = %s\n", show_bool(options.actions));
#endif
#if 1
	if (flags & XDE_MENU_FLAG_EXCLUDED)
		options.treeflags |= GMENU_TREE_FLAGS_INCLUDE_EXCLUDED;
	else
		options.treeflags &= ~GMENU_TREE_FLAGS_INCLUDE_EXCLUDED;
	if (flags & XDE_MENU_FLAG_NODISPLAY)
		options.treeflags |= GMENU_TREE_FLAGS_INCLUDE_NODISPLAY;
	else
		options.treeflags &= ~GMENU_TREE_FLAGS_INCLUDE_NODISPLAY;
	if (flags & XDE_MENU_FLAG_UNALLOCATED)
		options.treeflags |= GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED;
	else
		options.treeflags &= ~GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED;
	if (flags & XDE_MENU_FLAG_EMPTY)
		options.treeflags |= GMENU_TREE_FLAGS_SHOW_EMPTY;
	else
		options.treeflags &= ~GMENU_TREE_FLAGS_SHOW_EMPTY;
	if (flags & XDE_MENU_FLAG_SEPARATORS)
		options.treeflags |= GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS;
	else
		options.treeflags &= ~GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS;
	if (flags & XDE_MENU_FLAG_SORT)
		options.treeflags |= GMENU_TREE_FLAGS_SORT_DISPLAY_NAME;
	else
		options.treeflags &= ~GMENU_TREE_FLAGS_SORT_DISPLAY_NAME;
#endif
	options.button = (flags >> 16) & 0x0f;
	DPRINTF(1, "options.button = %d\n", options.button);
	options.which = (flags >> 20) & 0x0f;
	DPRINTF(1, "options.which = %s\n", show_which(options.which));
	options.screen = (flags >> 24) & 0x0f;
	DPRINTF(1, "options.screen = %d\n", options.screen);
	options.where = (flags >> 28) & 0x0f;
}

static void
set_word1(long word1)
{
	options.geom.mask &= ~(WidthValue|HeightValue);
	options.geom.w = (word1 >> 0) & 0x07fff;
	options.geom.mask |= ((word1 >> 15) & 0x01) ? WidthValue : 0;
	options.geom.h = (word1 >> 16) & 0x07fff;
	options.geom.mask |= ((word1 >> 31) & 0x01) ? HeightValue : 0;
}

static void
set_word2(long word2)
{
	options.geom.mask &= ~(XValue|YValue|XNegative|YNegative);
	options.geom.x = (word2 >> 0) & 0x03fff;
	options.geom.mask |= ((word2 >> 14) & 0x01) ? XValue : 0;
	options.geom.mask |= ((word2 >> 15) & 0x01) ? XNegative : 0;
	options.geom.y = (word2 >> 16) & 0x03fff;
	options.geom.mask |= ((word2 >> 30) & 0x01) ? YValue : 0;
	options.geom.mask |= ((word2 >> 31) & 0x01) ? YNegative : 0;
	DPRINTF(1, "options.where = %s\n", show_where(options.where));
}
#endif

/** @} */

/** @section Getting Arguments
  * @{ */

#if 1
static long
get_scmon(void)
{
	long scmon = 0;

	scmon |= ((long) (options.monitor & 0xffff) << 0);
	scmon |= ((long) (options.screen & 0xffff) << 16);
	DPRINTF(1, "options.monitor = %d\n", options.monitor);
	DPRINTF(1, "options.screen = %d\n", options.screen);
	return (scmon);
}

static long
get_flags(void)
{
	long flags = 0;

#if 1
	DPRINTF(1, "options.fileout = %s\n", show_bool(options.fileout));
	if (options.fileout)
		flags |= XDE_MENU_FLAG_FILEOUT;
	DPRINTF(1, "options.noicons = %s\n", show_bool(options.noicons));
	if (options.noicons)
		flags |= XDE_MENU_FLAG_NOICONS;
	DPRINTF(1, "options.launch = %s\n", show_bool(options.launch));
	if (options.launch)
		flags |= XDE_MENU_FLAG_LAUNCH;
#endif
	DPRINTF(1, "options.systray = %s\n", show_bool(options.systray));
	if (options.systray)
		flags |= XDE_MENU_FLAG_TRAY;
#if 1
	DPRINTF(1, "options.generate = %s\n", show_bool(options.generate));
	if (options.generate)
		flags |= XDE_MENU_FLAG_GENERATE;
#endif
	DPRINTF(1, "options.tooltips = %s\n", show_bool(options.tooltips));
	if (options.tooltips)
		flags |= XDE_MENU_FLAG_TOOLTIPS;
#if 1
	DPRINTF(1, "options.actions = %s\n", show_bool(options.actions));
	if (options.actions)
		flags |= XDE_MENU_FLAG_ACTIONS;
#endif
#if 1
	if (options.treeflags & GMENU_TREE_FLAGS_INCLUDE_EXCLUDED)
		flags |= XDE_MENU_FLAG_EXCLUDED;
	if (options.treeflags & GMENU_TREE_FLAGS_INCLUDE_NODISPLAY)
		flags |= XDE_MENU_FLAG_NODISPLAY;
	if (options.treeflags & GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED)
		flags |= XDE_MENU_FLAG_UNALLOCATED;
	if (options.treeflags & GMENU_TREE_FLAGS_SHOW_EMPTY)
		flags |= XDE_MENU_FLAG_EMPTY;
	if (options.treeflags & GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS)
		flags |= XDE_MENU_FLAG_SEPARATORS;
	if (options.treeflags & GMENU_TREE_FLAGS_SORT_DISPLAY_NAME)
		flags |= XDE_MENU_FLAG_SORT;
#endif
	DPRINTF(1, "options.button = %d\n", options.button);
	flags |= ((long) (options.button & 0x0f) << 16);
	DPRINTF(1, "options.which = %s\n", show_which(options.which));
	flags |= ((long) (options.which & 0x0f) << 20);
	DPRINTF(1, "options.screen = %d\n", options.screen);
	flags |= ((long) (options.screen & 0x0f) << 24);
	DPRINTF(1, "options.where = %s\n", show_where(options.where));
	flags |= ((long) (options.where & 0x0f) << 28);
	return (flags);
}

static long
get_word1(void)
{
	long word1 = 0;

	word1 |= ((long) (options.geom.w & 0x07fff) << 0);
	word1 |= ((long) ((options.geom.mask & WidthValue) ? 1 : 0) << 15);
	word1 |= ((long) (options.geom.h & 0x07fff) << 16);
	word1 |= ((long) ((options.geom.mask & HeightValue) ? 1 : 0) << 31);
	return (word1);
}

static long
get_word2(void)
{
	long word2 = 0;

	word2 |= ((long) (options.geom.x & 0x03fff) << 0);
	word2 |= ((long) ((options.geom.mask & XValue) ? 1 : 0) << 14);
	word2 |= ((long) ((options.geom.mask & XNegative) ? 1 : 0) << 15);
	word2 |= ((long) (options.geom.y & 0x03fff) << 16);
	word2 |= ((long) ((options.geom.mask & YValue) ? 1 : 0) << 30);
	word2 |= ((long) ((options.geom.mask & YNegative) ? 1 : 0) << 31);
	return (word2);
}
#endif

/** @} */

GMainLoop *loop = NULL;

static void
mainloop(void)
{
	if (options.display)
		gtk_main();
	else
		g_main_loop_run(loop);
}

static void
mainloop_quit(void)
{
	if (options.display)
		gtk_main_quit();
	else
		g_main_loop_quit(loop);
}

/** @} */

/** @section Background Theme Handling
  * @{ */

/** @} */

/** @section Popup Window Event Handlers
  * @{ */

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

char *
xde_get_icons(MenuContext *ctx, const char **inames)
{
	GtkIconTheme *theme;
	GtkIconInfo *info;
	const gchar *name;
	char *file = NULL;
	const char **iname;

	if ((theme = gtk_icon_theme_get_default())) {
		for (iname = inames; *iname; iname++) {
			DPRINTF(1, "Testing icon for name: %s\n", *iname);
			if ((info = gtk_icon_theme_lookup_icon(theme, *iname, 16, ctx->iconflags))) {
				if ((name = gtk_icon_info_get_filename(info)))
					file = strdup(name);
				else
					DPRINTF(1, "No file for icon name: %s\n", *iname);
				gtk_icon_info_free(info);
			} else
				DPRINTF(1, "Could not find icon name: %s\n", *iname);
			if (file) {
				DPRINTF(1, "File for icon name '%s' is %s\n", *iname, file);
				break;
			}
			DPRINTF(1, "Failed to find icon name: %s\n", *iname);
		}
	}
	return (file);
}

char *
xde_get_icon(MenuContext *ctx, const char *iname)
{
	const char *inames[2];

	inames[0] = iname;
	inames[1] = NULL;
	return xde_get_icons(ctx, inames);
}

char *
xde_get_icon2(MenuContext *ctx, const char *iname1, const char *iname2)
{
	const char *inames[3];

	if ((inames[0] = iname1)) {
		inames[1] = iname2;
		inames[2] = NULL;
	} else {
		inames[0] = iname2;
		inames[1] = NULL;
		inames[2] = NULL;
	}
	return xde_get_icons(ctx, inames);
}

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
xde_get_entry_icon(MenuContext *ctx, GKeyFile *entry, GIcon *gicon, const char *dflt1,
		   const char *dflt2, int flags)
{
	char *file = NULL;
	const char **inames;
	char *icon, *wmcl = NULL, *tryx = NULL, *exec = NULL;
	int i = 0;

	inames = calloc(16, sizeof(*inames));

	if ((icon = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_ICON, NULL))) {
		char *base, *p;

		if (icon[0] == '/' && !access(icon, R_OK) && xde_test_icon_ext(ctx, icon, flags)) {
			DPRINTF(1, "going with full icon path %s\n", icon);
			file = strdup(icon);
			g_free(icon);
			g_free(inames);
			return (file);
		}
		base = icon;
		*strchrnul(base, ' ') = '\0';
		if ((p = strrchr(base, '/')))
			base = p + 1;
		if ((p = strrchr(base, '.')))
			*p = '\0';
		inames[i++] = strdup(base);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
		g_free(icon);
	} else {
		if ((wmcl = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
						  G_KEY_FILE_DESKTOP_KEY_STARTUP_WM_CLASS, NULL))) {
			inames[i++] = wmcl;
			DPRINTF(1, "Choice %d for icon name: %s\n", i, wmcl);
		}
		if ((tryx = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
						  G_KEY_FILE_DESKTOP_KEY_TRY_EXEC, NULL))) {
			char *base, *p;

			base = tryx;
			*strchrnul(base, ' ') = '\0';
			if ((p = strrchr(base, '/')))
				base = p + 1;
			if ((p = strrchr(base, '.')))
				*p = '\0';
			inames[i++] = strdup(base);
			DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
			g_free(tryx);
		} else if ((exec = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
							 G_KEY_FILE_DESKTOP_KEY_EXEC, NULL))) {
			char *base, *p;

			base = exec;
			*strchrnul(base, ' ') = '\0';
			if ((p = strrchr(base, '/')))
				base = p + 1;
			if ((p = strrchr(base, '.')))
				*p = '\0';
			inames[i++] = strdup(base);
			DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
			g_free(exec);
		}
	}
	if (gicon) {
		char *gname;

		inames[i++] = gname = g_icon_to_string(gicon);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, gname);
	}
	if (dflt1) {
		inames[i++] = strdup(dflt1);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, dflt1);
	}
	if (dflt2) {
		inames[i++] = strdup(dflt2);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, dflt2);
	}
	inames[i++] = NULL;
	file = xde_get_icons(ctx, inames);
	g_strfreev((gchar **) inames);
	return (file);
}

char *
xde_get_action_icon(MenuContext *ctx, GKeyFile *entry, const char *action, GIcon *gicon,
		    const char *dflt1, const char *dflt2, int flags)
{
	char *file = NULL;
	const char **inames;
	char *icon, *wmcl = NULL, *tryx = NULL, *exec = NULL, *aicon, *group;
	int i = 0;

	aicon = xde_get_entry_icon(ctx, entry, gicon, dflt1, dflt2, flags);
	if (!action)
		return (aicon);

	inames = calloc(16, sizeof(*inames));
	group = g_strdup_printf("Desktop Action %s", action);
	if ((icon = g_key_file_get_string(entry, group, G_KEY_FILE_DESKTOP_KEY_ICON, NULL))) {
		char *base, *p;

		if (icon[0] == '/' && !access(icon, R_OK) && xde_test_icon_ext(ctx, icon, flags)) {
			DPRINTF(1, "going with full icon path %s\n", icon);
			file = strdup(icon);
			g_free(icon);
			g_free(inames);
			g_free(group);
			g_free(aicon);
			return (file);
		}
		base = icon;
		*strchrnul(base, ' ') = '\0';
		if ((p = strrchr(base, '/')))
			base = p + 1;
		if ((p = strrchr(base, '.')))
			*p = '\0';
		inames[i++] = strdup(base);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
		g_free(icon);
	} else {
		if ((wmcl = g_key_file_get_string(entry, group, G_KEY_FILE_DESKTOP_KEY_STARTUP_WM_CLASS, NULL))) {
			inames[i++] = wmcl;
			DPRINTF(1, "Choice %d for icon name; %s\n", i, wmcl);
		}
		if ((tryx = g_key_file_get_string(entry, group, G_KEY_FILE_DESKTOP_KEY_TRY_EXEC, NULL))) {
			char *base, *p;

			base = tryx;
			*strchrnul(base, ' ') = '\0';
			if ((p = strrchr(base, '/')))
				base = p + 1;
			if ((p = strrchr(base, '.')))
				*p = '\0';
			inames[i++] = strdup(base);
			DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
			g_free(tryx);
		} else if ((exec = g_key_file_get_string(entry, group, G_KEY_FILE_DESKTOP_KEY_EXEC, NULL))) {
			char *base, *p;

			base = exec;
			*strchrnul(base, ' ') = '\0';
			if ((p = strrchr(base, '/')))
				base = p + 1;
			if ((p = strrchr(base, '.')))
				*p = '\0';
			inames[i++] = strdup(base);
			DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
			g_free(exec);
		}
	}
	if (aicon) {
		char *base, *p;

		base = aicon;
		*strchrnul(base, ' ') = '\0';
		if ((p = strrchr(base, '/')))
			base = p + 1;
		if ((p = strrchr(base, '.')))
			*p = '\0';
		inames[i++] = strdup(base);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
		g_free(aicon);
	}
	if (gicon) {
		char *gname;

		inames[i++] = gname = g_icon_to_string(gicon);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, gname);
	}
	if (dflt1) {
		inames[i++] = strdup(dflt1);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, dflt1);
	}
	if (dflt2) {
		inames[i++] = strdup(dflt2);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, dflt2);
	}
	inames[i++] = NULL;
	file = xde_get_icons(ctx, inames);
	g_strfreev((gchar **) inames);
	g_free(group);
	return (file);
}

char *
xde_get_app_icon(MenuContext *ctx, GDesktopAppInfo *app, GIcon *gicon, const char *dflt1,
		 const char *dflt2, int flags)
{
	char *file = NULL;
	const char **inames;
	char *icon, *wmcl = NULL, *tryx = NULL, *exec = NULL;
	int i = 0;

	inames = calloc(16, sizeof(*inames));

	if ((icon = g_desktop_app_info_get_string(app, G_KEY_FILE_DESKTOP_KEY_ICON))) {
		char *base, *p;

		if (icon[0] == '/' && !access(icon, R_OK) && xde_test_icon_ext(ctx, icon, flags)) {
			DPRINTF(1, "going with full icon path %s\n", icon);
			file = strdup(icon);
			g_free(icon);
			g_free(inames);
			return (file);
		}
		base = icon;
		*strchrnul(base, ' ') = '\0';
		if ((p = strrchr(base, '/')))
			base = p + 1;
		if ((p = strrchr(base, '.')))
			*p = '\0';
		inames[i++] = strdup(base);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
		g_free(icon);
	} else {
		if ((wmcl = g_desktop_app_info_get_string(app, G_KEY_FILE_DESKTOP_KEY_STARTUP_WM_CLASS))) {
			inames[i++] = wmcl;
			DPRINTF(1, "Choice %d for icon name: %s\n", i, wmcl);
		}
		if ((tryx = g_desktop_app_info_get_string(app, G_KEY_FILE_DESKTOP_KEY_TRY_EXEC))) {
			char *base, *p;

			base = tryx;
			*strchrnul(base, ' ') = '\0';
			if ((p = strrchr(base, '/')))
				base = p + 1;
			if ((p = strrchr(base, '.')))
				*p = '\0';
			inames[i++] = strdup(base);
			DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
			g_free(tryx);
		} else if ((exec = g_desktop_app_info_get_string(app, G_KEY_FILE_DESKTOP_KEY_EXEC))) {
			char *base, *p;

			base = exec;
			*strchrnul(base, ' ') = '\0';
			if ((p = strrchr(base, '/')))
				base = p + 1;
			if ((p = strrchr(base, '.')))
				*p = '\0';
			inames[i++] = strdup(base);
			DPRINTF(1, "Choice %d for icon name: %s\n", i, base);
			g_free(exec);
		}
	}
	if (gicon) {
		char *gname;

		inames[i++] = gname = g_icon_to_string(gicon);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, gname);
	}
	if (dflt1) {
		inames[i++] = strdup(dflt1);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, dflt1);
	}
	if (dflt2) {
		inames[i++] = strdup(dflt2);
		DPRINTF(1, "Choice %d for icon name: %s\n", i, dflt2);
	}
	inames[i++] = NULL;
	file = xde_get_icons(ctx, inames);
	g_strfreev((gchar **) inames);
	return (file);
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
	for (n = 0, pos = dirs; pos < end; n++, *strchrnul(pos, ':') = '\0', pos += strlen(pos) + 1) ;
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

static void
xde_do_subst(char *cmd, const char *chars, const char *str)
{
	int len = 0;
	char *p;

	DPRINTF(1, "starting %s at %s:%d (cmd %s, char %s, str %s)\n",
		__FUNCTION__, __FILE__, __LINE__, cmd, chars, str);
	len = str ? strlen(str) : 0;
	for (p = cmd; (p = strchr(p, '%')); p++) {
		if (*(p - 1) != '%' && strspn(p + 1, chars)) {
			memmove(p + len, p + 2, strlen(p + 2) + 1);
			memcpy(p, str, len);
			p += len - 1;
		}
	}
}

static void
xde_subst_command(char *cmd, const char *appid, const char *icon, const char *name, const char *wmclass)
{
	int len;
	char *p;

	xde_do_subst(cmd, "i", icon);
	xde_do_subst(cmd, "c", name);
	xde_do_subst(cmd, "C", wmclass);
	xde_do_subst(cmd, "k", NULL);	/* appid */
	xde_do_subst(cmd, "uU", NULL);	/* url */
	xde_do_subst(cmd, "fF", NULL);	/* file */
	xde_do_subst(cmd, "dDnNvm", NULL);
#if 0
	xde_do_subst(cmd, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", NULL);
#endif
	xde_do_subst(cmd, "%", "%");
	if ((len = strspn(cmd, " \t")))
		memmove(cmd, cmd + len, strlen(cmd + len));
	if (((p = strrchr(cmd, ' ')) && strspn(p, " \t") == strlen(p)) ||
	    ((p = strrchr(cmd, '\t')) && strspn(p, " \t") == strlen(p)))
		*p = '\0';
}

char *
xde_get_command(GDesktopAppInfo *info, const char *appid, const char *icon)
{
	char *cmd, *wmclass;
	const char *name, *exec;
	gboolean terminal;

	name = g_app_info_get_name(G_APP_INFO(info));
	exec = g_app_info_get_commandline(G_APP_INFO(info));
	wmclass = g_desktop_app_info_get_string(info, G_KEY_FILE_DESKTOP_KEY_STARTUP_WM_CLASS);
	terminal = g_desktop_app_info_get_boolean(info, G_KEY_FILE_DESKTOP_KEY_TERMINAL);

	if (!exec)
		return (NULL);
	if (!(cmd = calloc(2048, sizeof(*cmd))))
		return (cmd);
	if (terminal) {
		if (wmclass) {
			snprintf(cmd, 1024, "xterm -name \"%s\" -T \"%%c\" -e ", wmclass);
		} else {
			/* A little more to be done here: we should set WMCLASS to xterm
			   to assist the DE.  SLIENT should be set to zero. */
			strncat(cmd, "xterm -T \"%c\" -e ", 1024);
			wmclass = "xterm";
		}
	}
	strncat(cmd, exec, 1024);
	xde_subst_command(cmd, appid, icon, name, wmclass);
	return (cmd);
}

char *
xde_get_action_exec(GDesktopAppInfo *info, const char *action)
{
	char *aexec = NULL;
	const char *exec, *path;

	if ((path = g_desktop_app_info_get_filename(info))) {
		GKeyFile *file = g_key_file_new();
		char *group = g_strdup_printf("Desktop Action %s", action);

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		aexec = g_key_file_get_string(file, group, G_KEY_FILE_DESKTOP_KEY_EXEC, NULL);
		if (!aexec)
			EPRINTF("no exec entry for [%s] in %s\n", group, path);
		g_key_file_unref(file);
		g_free(group);
	} else
		EPRINTF("could not get path to action %s\n", action);
	if (!aexec && (exec = g_app_info_get_commandline(G_APP_INFO(info))))
		aexec = strdup(exec);
	return (aexec);
}

char *
xde_get_action(GDesktopAppInfo *info, const char *appid, const char *icon, const char *action)
{
	char *cmd, *wmclass, *aexec = NULL;
	const char *name;
	gboolean terminal;

	if (!(aexec = xde_get_action_exec(info, action)))
		return (NULL);

	name = g_desktop_app_info_get_action_name(info, action);

	if (!(cmd = calloc(2048, sizeof(*cmd)))) {
		g_free(aexec);
		return (cmd);
	}
	terminal = g_desktop_app_info_get_boolean(info, G_KEY_FILE_DESKTOP_KEY_TERMINAL);
	wmclass = g_desktop_app_info_get_string(info, G_KEY_FILE_DESKTOP_KEY_STARTUP_WM_CLASS);
	if (terminal) {
		if (wmclass) {
			snprintf(cmd, 1024, "xterm -name \"%s\" -T \"%%c\" -e ", wmclass);
		} else {
			/* A little more to be done here: we should set WMCLASS to xterm
			   to assist the DE.  SLIENT should be set to zero. */
			strncat(cmd, "xterm -T \"%c\" -e ", 1024);
			wmclass = "xterm";
		}
	}
	strncat(cmd, aexec, 1024);
	g_free(aexec);
	xde_subst_command(cmd, appid, icon, name, wmclass);
	return (cmd);
}

static GKeyFile *
xde_get_xsession_entry(const char *key, const char *file)
{
	GKeyFile *entry;

	if (!file) {
		EPRINTF("file was NULL!\n");
		return (NULL);
	}
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
	DPRINTF(1, "got xsession file: %s (%s)\n", key, file);
	return (entry);
}

static gboolean
xde_bad_xsession(const char *appid, GKeyFile *entry)
{
	gchar *name, *exec, *tryexec, *binary;

	if (!(name = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NAME, NULL))) {
		DPRINTF(1, "%s: no Name\n", appid);
		return TRUE;
	}
	g_free(name);
	if (!(exec = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_EXEC, NULL))) {
		DPRINTF(1, "%s: no Exec\n", appid);
		return TRUE;
	}
	if (g_key_file_get_boolean(entry, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_HIDDEN, NULL)) {
		DPRINTF(1, "%s: is Hidden\n", appid);
		return TRUE;
	}
#if 0
	/* NoDisplay is often used to hide XSession desktop entries from the application
	   menu and does not indicate that it should not be displayed as an XSession
	   entry. */

	if (g_key_file_get_boolean(entry, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY, NULL)) {
		DPRINTF(1, "%s: is NoDisplay\n", appid);
		return TRUE;
	}
#endif
	if ((tryexec = g_key_file_get_string(entry, G_KEY_FILE_DESKTOP_GROUP,
					     G_KEY_FILE_DESKTOP_KEY_TRY_EXEC, NULL))) {
		binary = g_strdup(tryexec);
		g_free(tryexec);
	} else {
		char *p;

		/* parse the first word of the exec statement and see whether it is
		   executable or can be found in PATH */
		binary = g_strdup(exec);
		if ((p = strpbrk(binary, " \t")))
			*p = '\0';

	}
	g_free(exec);
	if (binary[0] == '/') {
		if (access(binary, X_OK)) {
			DPRINTF(1, "%s: %s: %s\n", appid, binary, strerror(errno));
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
			// DPRINTF(1, "%s: %s: %s\n", appid, file,
			// strerror(errno));
		}
		free(path);
		if (!execok) {
			DPRINTF(1, "%s: %s: not executable\n", appid, binary);
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
xde_find_xsessions(MenuContext *ctx)
{
	char **xdg_dirs, **dirs;
	int i, n = 0;
	static const char *suffix = ".desktop";
	static const int suflen = 8;

	if (ctx->xsessions)
		return (ctx->xsessions);

	if (!(xdg_dirs = xde_get_xsession_dirs(&n)) || !n)
		return (ctx->xsessions);

	ctx->xsessions = g_hash_table_new_full(g_str_hash, g_str_equal,
					       xde_xsession_key_free, xde_xsession_value_free);

	/* go through them backward */
	for (i = n - 1, dirs = &xdg_dirs[i]; i >= 0; i--, dirs--) {
		char *file, *p;
		DIR *dir;
		struct dirent *d;
		int len;
		char *key;

		if (!(dir = opendir(*dirs))) {
			DPRINTF(1, "%s: %s\n", *dirs, strerror(errno));
			continue;
		}
		while ((d = readdir(dir))) {
			if (d->d_name[0] == '.')
				continue;
			if (!(p = strstr(d->d_name, suffix)) || p[suflen]) {
				DPRINTF(1, "%s: no %s suffix\n", d->d_name, suffix);
				continue;
			}
			len = strlen(*dirs) + strlen(d->d_name) + 2;
			file = calloc(len, sizeof(*file));
			strcpy(file, *dirs);
			strcat(file, "/");
			strcat(file, d->d_name);
			key = strdup(d->d_name);
			*strstr(key, suffix) = '\0';
			g_hash_table_replace(ctx->xsessions, key, file);
		}
		closedir(dir);
	}
	for (i = 0; i < n; i++)
		free(xdg_dirs[i]);
	free(xdg_dirs);
	return (ctx->xsessions);
}

static gint
xde_xsession_compare(gconstpointer a, gconstpointer b)
{
	const XdeXsession *A = a;
	const XdeXsession *B = b;

	return strcasecmp(A->name, B->name);
}

GList *
xde_get_xsessions(MenuContext *ctx)
{
	GList *result = NULL;
	GHashTable *xsessions;

	if (!(xsessions = xde_find_xsessions(ctx))) {
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
	while (g_hash_table_iter_next(&xiter, (gpointer *) &key, (gpointer *) &file)) {
		GKeyFile *entry;
		XdeXsession *xsession;
		GDesktopAppInfo *info;

		if (!(entry = xde_get_xsession_entry(key, file))) {
			DPRINTF(1, "could not get xsession entry for %s and %s\n", key, file);
			continue;
		}
		if (xde_bad_xsession(key, entry)) {
			DPRINTF(1, "bad xsession entry for %s and %s\n", key, file);
			g_key_file_free(entry);
			continue;
		}
		g_key_file_set_string(entry, G_KEY_FILE_DESKTOP_GROUP, G_KEY_FILE_DESKTOP_KEY_TYPE, "Application");
		if (!(info = g_desktop_app_info_new_from_keyfile(entry))) {
			DPRINTF(1, "could not get info for %s and %s\n", key, file);
			g_key_file_free(entry);
			continue;
		}
		xsession = calloc(1, sizeof(*xsession));
		xsession->key = g_strdup(key);
		xsession->file = g_strdup(file);
		xsession->name = g_strdup(g_app_info_get_name(G_APP_INFO(info)));
		xsession->entry = g_key_file_ref(entry);
		xsession->info = info;
		result = g_list_prepend(result, xsession);
	}
	return g_list_sort(result, &xde_xsession_compare);
}

static void
xde_xsession_free(gpointer data)
{
	XdeXsession *xsess = data;

	g_free(xsess->key);
	g_free(xsess->file);
	g_free(xsess->name);
	g_key_file_free(xsess->entry);
	g_object_unref(xsess->info);
	free(xsess);
}

void
xde_free_xsessions(GList *list)
{
	g_list_free_full(list, &xde_xsession_free);
}

int
xde_reset_indent(MenuContext *ctx, int level)
{
	int old = ctx->level, i, chars;

	ctx->level = level;
	chars = ctx->level << 1;
	ctx->indent = realloc(ctx->indent, chars + 1);
	for (i = 0; i < chars; i++)
		ctx->indent[i] = ' ';
	ctx->indent[chars] = '\0';
	return old;
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
	chars = ctx->level << 1;
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
	fprintf(file, "Terminal=%s\n", g_desktop_app_info_get_string(info, "Terminal") ? "true" : "false");

	display_level(file, level);
	fprintf(file, "Path=%s\n", gmenu_tree_entry_get_desktop_file_path(entry));
	display_level(file, level);
	fprintf(file, "Id=%s\n", gmenu_tree_entry_get_desktop_file_id(entry));
	display_level(file, level);
	fprintf(file, "Excluded=%s\n", gmenu_tree_entry_get_is_excluded(entry) ? "true" : "false");
	display_level(file, level);
	fprintf(file, "NoDisplay=%s\n", gmenu_tree_entry_get_is_nodisplay_recurse(entry) ? "true" : "false");
	display_level(file, level);
	fprintf(file, "Unallocated=%s\n", gmenu_tree_entry_get_is_unallocated(entry) ? "true" : "false");

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
display_directory(FILE *file, GMenuTreeDirectory *directory, int level)
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
		char *iname = g_icon_to_string(icon);

		display_level(file, level + 1);
		fprintf(file, "Icon=%s\n", iname);
		g_free(iname);
	}
	display_level(file, level + 1);
	fprintf(file, "Path=%s\n", gmenu_tree_directory_get_desktop_file_path(directory));
	display_level(file, level + 1);
	fprintf(file, "Id=%s\n", gmenu_tree_directory_get_menu_id(directory));
	display_level(file, level + 1);
	fprintf(file, "NoDisplay=%s\n", gmenu_tree_directory_get_is_nodisplay(directory) ? "true" : "false");

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
	GList *menu = NULL;

	if (!(directory = gmenu_tree_get_root_directory(ctx->tree))) {
		EPRINTF("could not get root directory\n");
		return (menu);
	}
	ctx->level = 0;
	xde_increase_indent(ctx);
	menu = ctx->wmm.ops.menu(ctx, directory);
	xde_decrease_indent(ctx);
	switch (style) {
	case StyleFullmenu:
	default:
		menu = ctx->wmm.rootmenu(ctx, menu);
		break;
	case StyleAppmenu:
		if (!name)
			name = gmenu_tree_directory_get_name(directory);
		menu = ctx->wmm.appmenu(ctx, menu, name);
		break;
	case StyleEntries:
		/* do nothing */
		break;
	}
	menu = g_list_concat(ctx->wmm.output, menu);
	ctx->wmm.output = NULL;
	return (menu);
}

GtkMenu *
xde_gtk_create_simple(MenuContext *ctx, Style style, const char *name)
{
	GMenuTreeDirectory *directory;
	GtkMenu *menu = NULL;

	if (!(directory = gmenu_tree_get_root_directory(ctx->tree))) {
		EPRINTF("could not get root directory\n");
		return (menu);
	}
	ctx->level = 0;
	menu = ctx->gtk.ops.menu(ctx, directory);
	switch (style) {
	case StyleFullmenu:
	default:
		menu = ctx->gtk.rootmenu(ctx, menu);
		break;
	case StyleAppmenu:
		if (!name)
			name = gmenu_tree_directory_get_name(directory);
		menu = ctx->gtk.appmenu(ctx, menu, name);
		break;
	case StyleEntries:
		/* do nothing */
		break;
	}
	return (menu);
}

GtkMenu *
xde_gtk_common_appmenu(MenuContext *ctx, GtkMenu *entries, const char *name)
{
	GtkWidget *image, *item, *menu;
	GdkPixbuf *pixbuf = NULL;
	char *icon;

	menu = gtk_menu_new();
	item = gtk_image_menu_item_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), GTK_WIDGET(entries));
	if (name)
		gtk_menu_item_set_label(GTK_MENU_ITEM(item), name);
	if ((icon = xde_get_icon2(ctx, LOGO_NAME, "folder")) &&
	    (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	gtk_menu_append(menu, item);
	gtk_widget_show_all(item);
	gtk_widget_show_all(menu);
	return (GTK_MENU(menu));
}

GtkMenu *
xde_gtk_common_rootmenu(MenuContext *ctx, GtkMenu *entries)
{
	GtkMenu *menu = entries;
	GtkWidget *item, *image;

	if ((item = GTK_WIDGET(ctx->gtk.ops.pin(ctx)))) {
		gtk_menu_prepend(menu, item);
	}
	if ((item = GTK_WIDGET(xde_gtk_common_separator(ctx, NULL)))) {
		gtk_menu_append(menu, item);
		gtk_widget_show_all(item);
	}
	if ((item = (GtkWidget *) ctx->gtk.wmspec(ctx))) {
		gtk_menu_append(menu, item);
		gtk_widget_show_all(item);
		if ((item = GTK_WIDGET(xde_gtk_common_separator(ctx, NULL)))) {
			gtk_menu_append(menu, item);
			gtk_widget_show_all(item);
		}
	}
	if ((item = gtk_image_menu_item_new())) {
		gtk_menu_item_set_label(GTK_MENU_ITEM(item), "Run");
		if ((image = gtk_image_new_from_icon_name("gtk-execute", GTK_ICON_SIZE_MENU)))
			gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(xde_entry_activated), "xde-run");
		gtk_menu_append(menu, item);
		gtk_widget_show_all(item);
		if ((item = GTK_WIDGET(xde_gtk_common_separator(ctx, NULL)))) {
			gtk_menu_append(menu, item);
			gtk_widget_show_all(item);
		}
	}
	if ((item = gtk_image_menu_item_new())) {
		gtk_menu_item_set_label(GTK_MENU_ITEM(item), "Exit");
		if ((image = gtk_image_new_from_icon_name("system-log-out", GTK_ICON_SIZE_MENU)))
			gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(xde_entry_activated), "xde-logout");
		gtk_menu_append(menu, item);
		gtk_widget_show_all(item);
	}
	return (menu);
}

GList *
xde_build_simple(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
{
	GList *text = NULL;

	switch (type) {
	case GMENU_TREE_ITEM_INVALID:
		break;
	case GMENU_TREE_ITEM_DIRECTORY:
		if (ctx->wmm.ops.directory)
			text = ctx->wmm.ops.directory(ctx, item);
		break;
	case GMENU_TREE_ITEM_ENTRY:
		if (ctx->wmm.ops.entry)
			text = ctx->wmm.ops.entry(ctx, item);
		break;
	case GMENU_TREE_ITEM_SEPARATOR:
		if (ctx->wmm.ops.separator)
			text = ctx->wmm.ops.separator(ctx, item);
		break;
	case GMENU_TREE_ITEM_HEADER:
		if (ctx->wmm.ops.header)
			text = ctx->wmm.ops.header(ctx, item);
		break;
	case GMENU_TREE_ITEM_ALIAS:
		if (ctx->wmm.ops.alias)
			text = ctx->wmm.ops.alias(ctx, item);
		break;
	}
	return (text);
}

GtkMenuItem *
xde_gtk_build_simple(MenuContext *ctx, GMenuTreeItemType type, gpointer item)
{
	GtkMenuItem *entry = NULL;

	switch (type) {
	case GMENU_TREE_ITEM_INVALID:
		break;
	case GMENU_TREE_ITEM_DIRECTORY:
		if (ctx->gtk.ops.directory)
			entry = ctx->gtk.ops.directory(ctx, item);
		break;
	case GMENU_TREE_ITEM_ENTRY:
		if (ctx->gtk.ops.entry)
			entry = ctx->gtk.ops.entry(ctx, item);
		break;
	case GMENU_TREE_ITEM_SEPARATOR:
		if (ctx->gtk.ops.separator)
			entry = ctx->gtk.ops.separator(ctx, item);
		break;
	case GMENU_TREE_ITEM_HEADER:
		if (ctx->gtk.ops.header)
			entry = ctx->gtk.ops.header(ctx, item);
		break;
	case GMENU_TREE_ITEM_ALIAS:
		if (ctx->gtk.ops.alias)
			entry = ctx->gtk.ops.alias(ctx, item);
		break;
	}
	return (entry);
}

GList *
xde_menu_simple(MenuContext *ctx, GMenuTreeDirectory *menu)
{
	GMenuTreeItemType type;
	GMenuTreeIter *iter;
	GList *text = NULL, *item;

	iter = gmenu_tree_directory_iter(menu);

	xde_increase_indent(ctx);
	while ((type = gmenu_tree_iter_next(iter)) != GMENU_TREE_ITEM_INVALID) {
		switch (type) {
		case GMENU_TREE_ITEM_INVALID:
		default:
			break;
		case GMENU_TREE_ITEM_DIRECTORY:
			if ((item = ctx->wmm.build(ctx, type, gmenu_tree_iter_get_directory(iter))))
				text = g_list_concat(text, item);
			continue;
		case GMENU_TREE_ITEM_ENTRY:
			if ((item = ctx->wmm.build(ctx, type, gmenu_tree_iter_get_entry(iter))))
				text = g_list_concat(text, item);
			continue;
		case GMENU_TREE_ITEM_SEPARATOR:
			if ((item = ctx->wmm.build(ctx, type, gmenu_tree_iter_get_separator(iter))))
				text = g_list_concat(text, item);
			continue;
		case GMENU_TREE_ITEM_HEADER:
			if ((item = ctx->wmm.build(ctx, type, gmenu_tree_iter_get_header(iter))))
				text = g_list_concat(text, item);
			continue;
		case GMENU_TREE_ITEM_ALIAS:
			if ((item = ctx->wmm.build(ctx, type, gmenu_tree_iter_get_alias(iter))))
				text = g_list_concat(text, item);
			continue;
		}
		break;
	}
	xde_decrease_indent(ctx);
	return (text);
}

void
selection_done(GtkMenuShell *menushell, gpointer user_data)
{
#if 0
	/* no don't do this: do not recreate the menu with each pop */
	OPRINTF(1, "Selection done: exiting\n");
	if (!gtk_menu_get_tearoff_state(GTK_MENU(menushell)))
		mainloop_quit();
#endif
}

static gboolean
application_button_press(GtkWidget *item, GdkEvent *event, gpointer user_data)
{
	GdkEventButton *ev = (typeof(ev)) event;
	gchar *cmd;

	OPRINTF(1, "Menu item [%s] button press\n", gtk_menu_item_get_label(GTK_MENU_ITEM(item)));
	if (ev->button != 1)
		return GTK_EVENT_PROPAGATE;
	cmd = g_strdup(user_data);
	gtk_menu_shell_activate_item(GTK_MENU_SHELL(gtk_widget_get_parent(item)), item, TRUE);
	xde_entry_activated(GTK_MENU_ITEM(item), cmd);	/* XXX */
	g_free(cmd);
	return GTK_EVENT_STOP;
}

static void
application_select(GtkItem * item, gpointer user_data)
{
	GtkWidget *menu;

	OPRINTF(1, "Menu item [%s] selected\n", gtk_menu_item_get_label(GTK_MENU_ITEM(item)));
	g_object_set_data(G_OBJECT(item), "application", user_data);
	if ((menu = gtk_widget_get_parent(GTK_WIDGET(item))))
		g_object_set_data(G_OBJECT(menu), "selected-item", item);
}

static void
application_deselect(GtkItem * item, gpointer user_data)
{
	GtkWidget *menu;

	OPRINTF(1, "Menu item [%s] deselected\n", gtk_menu_item_get_label(GTK_MENU_ITEM(item)));
	if ((menu = gtk_widget_get_parent(GTK_WIDGET(item))))
		g_object_set_data(G_OBJECT(menu), "selected-item", NULL);
}

static gboolean
application_menu_key_press(GtkWidget *menu, GdkEvent *event, gpointer user_data)
{
	GdkEventKey *ev = (typeof(ev)) event;
	GtkWidget *item;
	gchar *cmd;

	OPRINTF(1, "Application menu key press\n");
	if (!(item = g_object_get_data(G_OBJECT(menu), "selected-item"))) {
		OPRINTF(1, "No selected item!\n");
		return GTK_EVENT_PROPAGATE;
	}
	if (GTK_IS_MENU_ITEM(item))
		OPRINTF(1, "Menu item [%s] key press\n", gtk_menu_item_get_label(GTK_MENU_ITEM(item)));
	if (!(cmd = g_object_get_data(G_OBJECT(item), "command"))) {
		OPRINTF(1, "No selected command!\n");
		return GTK_EVENT_PROPAGATE;
	}
	if (ev->keyval == GDK_KEY_Return) {
		OPRINTF(1, "Menu key press [Return]\n");
		cmd = g_strdup(cmd);
		gtk_menu_shell_activate_item(GTK_MENU_SHELL(menu), GTK_WIDGET(item), TRUE);
		xde_entry_activated(GTK_MENU_ITEM(item), cmd);	/* XXX */
		g_free(cmd);
		return GTK_EVENT_STOP;
	}
	return GTK_EVENT_PROPAGATE;
}

GtkMenu *
xde_gtk_common_menu(MenuContext *ctx, GMenuTreeDirectory *gmenu)
{
	GMenuTreeItemType type;
	GMenuTreeIter *iter;
	GtkMenu *menu;
	GtkMenuItem *item;

	ctx->stack = g_list_prepend(ctx->stack, gmenu);

	iter = gmenu_tree_directory_iter(gmenu);
	menu = GTK_MENU(gtk_menu_new());

	while ((type = gmenu_tree_iter_next(iter)) != GMENU_TREE_ITEM_INVALID) {
		switch (type) {
		case GMENU_TREE_ITEM_INVALID:
		default:
			break;
		case GMENU_TREE_ITEM_DIRECTORY:
			if ((item = ctx->gtk.build(ctx, type, gmenu_tree_iter_get_directory(iter)))) {
				gtk_menu_append(menu, GTK_WIDGET(item));
				gtk_widget_show_all(GTK_WIDGET(item));
			}
			continue;
		case GMENU_TREE_ITEM_ENTRY:
			if ((item = ctx->gtk.build(ctx, type, gmenu_tree_iter_get_entry(iter)))) {
				gtk_menu_append(menu, GTK_WIDGET(item));
				gtk_widget_show_all(GTK_WIDGET(item));
			}
			continue;
		case GMENU_TREE_ITEM_SEPARATOR:
			if ((item = ctx->gtk.build(ctx, type, gmenu_tree_iter_get_separator(iter)))) {
				gtk_menu_append(menu, GTK_WIDGET(item));
				gtk_widget_show_all(GTK_WIDGET(item));
			}
			continue;
		case GMENU_TREE_ITEM_HEADER:
			if ((item = ctx->gtk.build(ctx, type, gmenu_tree_iter_get_header(iter)))) {
				gtk_menu_append(menu, GTK_WIDGET(item));
				gtk_widget_show_all(GTK_WIDGET(item));
			}
			continue;
		case GMENU_TREE_ITEM_ALIAS:
			if ((item = ctx->gtk.build(ctx, type, gmenu_tree_iter_get_alias(iter)))) {
				gtk_menu_append(menu, GTK_WIDGET(item));
				gtk_widget_show_all(GTK_WIDGET(item));
			}
			continue;
		}
		break;
	}

	ctx->stack = g_list_delete_link(ctx->stack, ctx->stack);

	gtk_widget_show_all(GTK_WIDGET(menu));
	g_signal_connect(G_OBJECT(menu), "selection_done", G_CALLBACK(selection_done), NULL);
	g_signal_connect(G_OBJECT(menu), "key_press_event", G_CALLBACK(application_menu_key_press), NULL);
	return (menu);
}

GList *
xde_actions_simple(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info)
{
	GList *text = NULL;
	const gchar *const *actions;

	actions = g_desktop_app_info_list_actions(info);
	if (!actions || !*actions)
		return (text);
	xde_increase_indent(ctx);
	for (; actions && *actions; actions++) {
		GList *item;

		if ((item = ctx->wmm.ops.action(ctx, ent, info, *actions)))
			text = g_list_concat(text, item);
	}
	xde_decrease_indent(ctx);
	return (text);
}

GtkMenu *
xde_gtk_common_actions(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info)
{
	GtkMenu *menu = NULL;
	const gchar *const *actions;

	actions = g_desktop_app_info_list_actions(info);
	if (!actions || !*actions)
		return (menu);
	menu = GTK_MENU(gtk_menu_new());
	g_signal_connect(G_OBJECT(menu), "selection_done", G_CALLBACK(selection_done), NULL);
	g_signal_connect(G_OBJECT(menu), "key_press_event", G_CALLBACK(application_menu_key_press), NULL);
	for (; actions && *actions; actions++) {
		GtkMenuItem *item;

		if ((item = ctx->gtk.ops.action(ctx, ent, info, *actions)))
			gtk_menu_append(menu, GTK_WIDGET(item));
	}
	return (menu);
}

GtkMenuItem *
xde_gtk_common_separator(MenuContext *ctx, GMenuTreeSeparator *sep)
{
	GtkMenuItem *item = NULL;

	item = GTK_MENU_ITEM(gtk_separator_menu_item_new());
	return (item);
}

GtkMenuItem *
xde_gtk_common_header(MenuContext *ctx, GMenuTreeHeader *hdr)
{
	GMenuTreeDirectory *dir;
	GtkMenuItem *item = NULL;
	const char *name, *path;
	GdkPixbuf *pixbuf = NULL;
	GtkWidget *image;
	GIcon *gicon = NULL;
	char *icon;

	if (!(dir = gmenu_tree_header_get_directory(hdr)))
		return (item);
	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	if ((name = gmenu_tree_directory_get_name(dir)))
		gtk_menu_item_set_label(item, name);
	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, gicon, "folder", "unknown",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	if (icon && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	if (GTK_IS_BIN(item)) {
		GtkWidget *child = gtk_bin_get_child(GTK_BIN(item));

		if (GTK_IS_LABEL(child)) {
			gchar *markup;
			gint xpad = 0, ypad = 0;

			markup = g_markup_printf_escaped("<b><u>%s</u></b>", name);
			gtk_label_set_markup(GTK_LABEL(child), markup);
			g_free(markup);
			gtk_misc_set_alignment(GTK_MISC(child), 0.5, 0.5);
			gtk_misc_get_padding(GTK_MISC(child), &xpad, &ypad);
			if (ypad < 3)
				ypad = 3;
			gtk_misc_set_padding(GTK_MISC(child), xpad, ypad);
		}
	}
	return (item);
}

GtkMenuItem *
xde_gtk_common_directory(MenuContext *ctx, GMenuTreeDirectory *dir)
{
	GtkMenuItem *item = NULL;
	GtkMenu *menu;
	const char *name, *path, *value;
	GdkPixbuf *pixbuf = NULL;
	GtkWidget *image;
	GIcon *gicon = NULL;
	char *icon;

	if (!(menu = ctx->gtk.ops.menu(ctx, dir)))
		return (item);
	if (gmenu_tree_directory_get_is_nodisplay(dir)) {
		DPRINTF(1, "directory %s is no display\n", gmenu_tree_directory_get_menu_id(dir));
		return (item);
	}
	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	if ((name = gmenu_tree_directory_get_name(dir)))
		gtk_menu_item_set_label(item, name);
	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	if ((path = gmenu_tree_directory_get_desktop_file_path(dir))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_entry_icon(ctx, file, gicon, "folder", "unknown",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "folder", "unknown");
	gicon = gmenu_tree_directory_get_icon(dir);
	if (icon && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	gtk_menu_item_set_submenu(item, GTK_WIDGET(menu));

	if (options.debug) {
		gchar **markup = calloc(16, sizeof(*markup));
		char *myicon = NULL;
		char *tip;
		int i = 0;

		if (name)
			markup[i++] = g_markup_printf_escaped("<b>Name:</b> %s", name);
		if ((value = gmenu_tree_directory_get_generic_name(dir)))
			markup[i++] = g_markup_printf_escaped("<b>GenericName:</b> %s", value);
		if ((value = gmenu_tree_directory_get_comment(dir)))
			markup[i++] = g_markup_printf_escaped("<b>Comment:</b> %s", value);
		if (gicon && (myicon = g_icon_to_string(gicon)))
			markup[i++] = g_markup_printf_escaped("<b>Icon:</b> %s", myicon);
		if ((value = gmenu_tree_directory_get_menu_id(dir)))
			markup[i++] = g_markup_printf_escaped("<b>menuid:</b> %s", value);
		if ((value = gmenu_tree_directory_get_desktop_file_path(dir)))
			markup[i++] = g_markup_printf_escaped("<b>file:</b> %s", value);
		if (icon)
			markup[i++] = g_markup_printf_escaped("<b>icon_file:</b> %s", icon);

		tip = g_strjoinv("\n", markup);
		gtk_widget_set_tooltip_markup(GTK_WIDGET(item), tip);
		g_free(tip);
		g_strfreev(markup);
		g_free(myicon);
	} else if ((value = gmenu_tree_directory_get_comment(dir))) {
		gtk_widget_set_tooltip_text(GTK_WIDGET(item), value);
	}
	g_free(icon);
	return (item);
}

void
xde_entry_activated(GtkMenuItem *menuitem, gpointer user_data)
{
	char *cmd, *exec;
	int result;

	if ((cmd = user_data)) {
		exec = g_strdup_printf("%s &", cmd);
		DPRINTF(1, "executing: system(\"%s\")\n", exec);
		if ((result = system(cmd)) == -1) ;
		free(exec);
	} else
		EPRINTF("no command to execute!\n");
}

void
xde_entry_disconnect(gpointer data, GClosure *closure)
{
	free(data);
}

GtkMenuItem *
xde_gtk_common_entry(MenuContext *ctx, GMenuTreeEntry *ent)
{
	GtkMenuItem *item = NULL;
	GDesktopAppInfo *info;
	GdkPixbuf *pixbuf = NULL;
	GtkWidget *image = NULL;
	GtkMenu *menu;
	const char *name, *value;
	char *p, *icon, *appid, *cmd;
	GIcon *gicon = NULL;

	if (!(info = gmenu_tree_entry_get_app_info(ent)) || g_desktop_app_info_get_is_hidden(info)
	    || g_desktop_app_info_get_nodisplay(info) || !g_desktop_app_info_get_show_in(info, NULL)
	    || !g_app_info_should_show(G_APP_INFO(info)))
		return (item);
	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	if ((name = g_app_info_get_name(G_APP_INFO(info))))
		gtk_menu_item_set_label(item, name);
	if ((appid = strdup(gmenu_tree_entry_get_desktop_file_id(ent)))
	    && (p = strstr(appid, ".desktop")))
		*p = '\0';
	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	icon = xde_get_app_icon(ctx, info, gicon, "exec", "unknown",
				GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
				GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
	gicon = g_app_info_get_icon(G_APP_INFO(info));
	if (options.launch)
		cmd = g_strdup_printf("xdg-launch --pointer %s", appid);
	else
		cmd = xde_get_command(info, appid, icon);
	if (icon && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	if (options.tooltips || options.debug) {
		gchar **markup = calloc(16, sizeof(*markup));
		char *myicon = NULL;
		char *tip;
		int i = 0;

		if ((value = g_app_info_get_name(G_APP_INFO(info))))
			markup[i++] = g_markup_printf_escaped("<b>Name:</b> %s", value);
		if ((value = g_desktop_app_info_get_generic_name(info)))
			markup[i++] = g_markup_printf_escaped("<b>GenericName:</b> %s", value);
		if ((value = g_app_info_get_description(G_APP_INFO(info))))
			markup[i++] = g_markup_printf_escaped("<b>Comment:</b> %s", value);
		if ((value = g_app_info_get_commandline(G_APP_INFO(info))))
			markup[i++] = g_markup_printf_escaped("<b>Exec:</b> %s", value);
		if (gicon && (myicon = g_icon_to_string(gicon)))
			markup[i++] = g_markup_printf_escaped("<b>Icon:</b> %s", myicon);
		if ((value = g_desktop_app_info_get_categories(info)))
			markup[i++] = g_markup_printf_escaped("<b>Categories:</b> %s", value);
		if (appid)
			markup[i++] = g_markup_printf_escaped("<b>appid:</b> %s", appid);
		if ((value = gmenu_tree_entry_get_desktop_file_path(ent)))
			markup[i++] = g_markup_printf_escaped("<b>file:</b> %s", value);
		if (icon)
			markup[i++] = g_markup_printf_escaped("<b>icon_file:</b> %s", icon);

		tip = g_strjoinv("\n", markup);
		gtk_widget_set_tooltip_markup(GTK_WIDGET(item), tip);
		g_free(tip);
		g_strfreev(markup);
		g_free(myicon);
	} else if ((value = g_app_info_get_description(G_APP_INFO(info)))) {
		gtk_widget_set_tooltip_text(GTK_WIDGET(item), value);
	}
	if (options.actions && (menu = ctx->gtk.ops.actions(ctx, ent, info))) {
#if 0
		gtk_menu_prepend(menu, GTK_WIDGET(item));
		item = GTK_MENU_ITEM(gtk_image_menu_item_new());
		if (name)
			gtk_menu_item_set_label(item, name);
		if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
			gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
		gtk_menu_item_set_submenu(item, GTK_WIDGET(menu));
#else
		gtk_menu_item_set_submenu(item, GTK_WIDGET(menu));
		gtk_widget_show(GTK_WIDGET(menu));
		gtk_widget_add_events(GTK_WIDGET(item), GDK_ALL_EVENTS_MASK);
		g_signal_connect_data(G_OBJECT(item), "button_press_event",
				      G_CALLBACK(application_button_press), strdup(cmd), xde_entry_disconnect, 0);
		g_signal_connect_data(G_OBJECT(item), "select",
				      G_CALLBACK(application_select), strdup(cmd), xde_entry_disconnect, 0);
		g_signal_connect_data(G_OBJECT(item), "deselect",
				      G_CALLBACK(application_deselect), cmd, xde_entry_disconnect, 0);
		g_object_set_data(G_OBJECT(item), "command", cmd);
#endif
	} else
		g_signal_connect_data(G_OBJECT(item), "activate",
				      G_CALLBACK(xde_entry_activated), cmd, xde_entry_disconnect, 0);
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	free(appid);
	return (item);
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
		text = ctx->wmm.build(ctx, type, gmenu_tree_alias_get_aliased_directory(als));
		break;
	case GMENU_TREE_ITEM_ENTRY:
		text = ctx->wmm.build(ctx, type, gmenu_tree_alias_get_aliased_entry(als));
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

GtkMenuItem *
xde_gtk_common_alias(MenuContext *ctx, GMenuTreeAlias *als)
{
	GMenuTreeItemType type;
	GtkMenuItem *item = NULL;

	switch ((type = gmenu_tree_alias_get_aliased_item_type(als))) {
	case GMENU_TREE_ITEM_INVALID:
		break;
	case GMENU_TREE_ITEM_DIRECTORY:
		item = ctx->gtk.build(ctx, type, gmenu_tree_alias_get_aliased_directory(als));
		break;
	case GMENU_TREE_ITEM_ENTRY:
		item = ctx->gtk.build(ctx, type, gmenu_tree_alias_get_aliased_entry(als));
		break;
	case GMENU_TREE_ITEM_SEPARATOR:
		break;
	case GMENU_TREE_ITEM_HEADER:
		break;
	case GMENU_TREE_ITEM_ALIAS:
		break;
	}
	return (item);
}

GtkMenuItem *
xde_gtk_common_action(MenuContext *ctx, GMenuTreeEntry *ent, GDesktopAppInfo *info, const char *action)
{
	GtkMenuItem *item = NULL;
	GdkPixbuf *pixbuf = NULL;
	GtkWidget *image = NULL;
	const char *name, *value, *path;
	char *p, *appid, *icon, *cmd;
	GIcon *gicon = NULL;

	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	if ((name = g_desktop_app_info_get_action_name(info, action)))
		gtk_menu_item_set_label(item, name);
	if ((appid = strdup(gmenu_tree_entry_get_desktop_file_id(ent)))
	    && (p = strstr(appid, ".desktop")))
		*p = '\0';
	if (ctx->stack)
		gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
	if ((path = gmenu_tree_entry_get_desktop_file_path(ent))) {
		GKeyFile *file = g_key_file_new();

		g_key_file_load_from_file(file, path, G_KEY_FILE_NONE, NULL);
		icon = xde_get_action_icon(ctx, file, action, gicon, "exec", "unknown",
					   GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					   GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		g_key_file_unref(file);
	} else
		icon = xde_get_icon2(ctx, "exec", "unknown");
	gicon = g_app_info_get_icon(G_APP_INFO(info));
	if (options.launch)
		cmd = g_strdup_printf("xdg-launch --pointer --action='%s' %s", action, appid);
	else
		cmd = xde_get_action(info, appid, icon, action);
	if (icon && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	g_signal_connect_data(G_OBJECT(item), "activate", G_CALLBACK(xde_entry_activated), cmd,
			      &xde_entry_disconnect, 0);

	if (options.tooltips || options.debug) {
		gchar **markup = calloc(16, sizeof(*markup));
		char *myicon = NULL, *exec;
		char *tip;
		int i = 0;

		if (action)
			markup[i++] = g_markup_printf_escaped("<b>Action:</b> %s", action);
		if (name || (name = g_app_info_get_name(G_APP_INFO(info))))
			markup[i++] = g_markup_printf_escaped("<b>Name:</b> %s", name);
		if ((value = g_desktop_app_info_get_generic_name(info)))
			markup[i++] = g_markup_printf_escaped("<b>GenericName:</b> %s", value);
		if ((value = g_app_info_get_description(G_APP_INFO(info))))
			markup[i++] = g_markup_printf_escaped("<b>Comment:</b> %s", value);
		if ((exec = xde_get_action_exec(info, action))) {
			markup[i++] = g_markup_printf_escaped("<b>Exec:</b> %s", exec);
			g_free(exec);
		}
		if (gicon && (myicon = g_icon_to_string(gicon)))
			markup[i++] = g_markup_printf_escaped("<b>Icon:</b> %s", myicon);
		if ((value = g_desktop_app_info_get_categories(info)))
			markup[i++] = g_markup_printf_escaped("<b>Categories:</b> %s", value);
		if (appid)
			markup[i++] = g_markup_printf_escaped("<b>appid:</b> %s", appid);
		if ((value = gmenu_tree_entry_get_desktop_file_path(ent)))
			markup[i++] = g_markup_printf_escaped("<b>file:</b> %s", value);
		if (icon)
			markup[i++] = g_markup_printf_escaped("<b>icon_file:</b> %s", icon);

		tip = g_strjoinv("\n", markup);
		gtk_widget_set_tooltip_markup(GTK_WIDGET(item), tip);
		g_free(tip);
		g_strfreev(markup);
		g_free(myicon);
	}
	free(icon);
	free(appid);
	return (item);
}

GtkMenuItem *
xde_gtk_common_pin(MenuContext *ctx)
{
	GtkMenuItem *item = NULL;

	item = GTK_MENU_ITEM(gtk_tearoff_menu_item_new());
	gtk_widget_show_all(GTK_WIDGET(item));
	return (item);
}

GtkMenuItem *
xde_gtk_common_wmmenu(MenuContext *ctx)
{
	GtkWidget *menu = NULL, *image, *item;
	GtkMenuItem *result = NULL;
	GList *xsessions, *xsession;
	GdkPixbuf *pixbuf = NULL;
	char *icon;

	menu = gtk_menu_new();
	result = GTK_MENU_ITEM(gtk_image_menu_item_new());
	gtk_menu_item_set_submenu(result, menu);
	gtk_menu_item_set_label(result, "Window Managers");
	if ((icon = xde_get_icon(ctx, "gtk-quit")) &&
	    (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(result), image);
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	item = gtk_image_menu_item_new();
	gtk_menu_append(menu, item);
	gtk_widget_show_all(item);
	gtk_menu_item_set_label(GTK_MENU_ITEM(item), "Restart");
	if ((icon = xde_get_icon(ctx, "gtk-refresh")) &&
	    (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL)) &&
	    (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(result), image);
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	xsessions = xde_get_xsessions(ctx);
	for (xsession = xsessions; xsession; xsession = xsession->next) {
		XdeXsession *xsess = xsession->data;
		const char *value;
		char *cmd;
		GIcon *gicon = NULL;

		if (strncasecmp(xsess->key, ctx->name, strlen(ctx->name)) == 0)
			continue;
		item = gtk_image_menu_item_new();
		if (ctx->stack)
			gicon = gmenu_tree_directory_get_icon(ctx->stack->data);
		gtk_widget_show_all(item);
		gtk_menu_item_set_label(GTK_MENU_ITEM(item), xsess->name);
		icon = xde_get_entry_icon(ctx, xsess->entry, gicon, "preferences-system-windows",
					  "metacity",
					  GET_ENTRY_ICON_FLAG_XPM | GET_ENTRY_ICON_FLAG_PNG |
					  GET_ENTRY_ICON_FLAG_JPG | GET_ENTRY_ICON_FLAG_SVG);
		gicon = g_app_info_get_icon(G_APP_INFO(xsess->info));
		if (options.launch)
			cmd = g_strdup_printf("xdg-launch --pointer -X %s", xsess->key);
		else
			cmd = xde_get_command(xsess->info, xsess->key, icon);
		if (icon && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL))
		    && (image = gtk_image_new_from_pixbuf(pixbuf)))
			gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
		if (pixbuf) {
			g_object_unref(pixbuf);
			pixbuf = NULL;
		}
		g_signal_connect_data(G_OBJECT(item), "activate", G_CALLBACK(xde_entry_activated), cmd,
				      &xde_entry_disconnect, 0);

		if (options.tooltips || options.debug) {
			gchar **markup = calloc(16, sizeof(*markup));
			char *myicon = NULL;
			char *tip;
			int i = 0;

			if (xsess->name)
				markup[i++] = g_markup_printf_escaped("<b>Name:</b> %s", xsess->name);
			if ((value = g_desktop_app_info_get_generic_name(xsess->info)))
				markup[i++] = g_markup_printf_escaped("<b>GenericName:</b> %s", value);
			if ((value = g_app_info_get_description(G_APP_INFO(xsess->info))))
				markup[i++] = g_markup_printf_escaped("<b>Comment:</b> %s", value);
			if ((value = g_app_info_get_commandline(G_APP_INFO(xsess->info))))
				markup[i++] = g_markup_printf_escaped("<b>Exec:</b> %s", value);
			if (gicon && (myicon = g_icon_to_string(gicon)))
				markup[i++] = g_markup_printf_escaped("<b>Icon:</b> %s", myicon);
			if ((value = g_desktop_app_info_get_categories(xsess->info)))
				markup[i++] = g_markup_printf_escaped("<b>Categories:</b> %s", value);
			if (xsess->key)
				markup[i++] = g_markup_printf_escaped("<b>appid:</b> %s", xsess->key);
			if (xsess->file)
				markup[i++] = g_markup_printf_escaped("<b>file:</b> %s", xsess->file);
			if (icon)
				markup[i++] = g_markup_printf_escaped("<b>icon_file:</b> %s", icon);

			tip = g_strjoinv("\n", markup);
			gtk_widget_set_tooltip_markup(item, tip);
			g_free(tip);
			g_strfreev(markup);
			g_free(myicon);
		} else if ((value = g_app_info_get_description(G_APP_INFO(xsess->info)))) {
			gtk_widget_set_tooltip_text(item, value);
		}
		free(icon);
		gtk_menu_append(menu, item);
		gtk_widget_show_all(item);
		DPRINTF(1, "got xsession %s\n", xsess->name);
	}
	gtk_widget_show_all(menu);
	gtk_widget_show_all(GTK_WIDGET(result));
	return (result);
}

GList *
xde_common_get_styles(MenuContext *ctx, const char *dname, const char *fname, const char *suffix)
{
	GList *list = NULL;
	struct dirent *d;
	DIR *dir;

	if (!(dir = opendir(dname))) {
		DPRINTF(1, "%s: %s\n", dname, strerror(errno));
		return (list);
	}
	while ((d = readdir(dir))) {
		char *file, *p, *name;
		struct stat st;
		int len;

		if (d->d_name[0] == '.')
			continue;
		len = strlen(dname) + strlen(d->d_name) + strlen(fname) + 2;
		file = calloc(len, sizeof(*file));
		strcpy(file, dname);
		strcat(file, "/");
		strcat(file, d->d_name);
		if (stat(file, &st)) {
			EPRINTF("%s: %s\n", file, strerror(errno));
			free(file);
			continue;
		}
		if (S_ISREG(st.st_mode)) {
			/* filename must end in suffix when specified */
			if (suffix && suffix[0]
			    && (!(p = strstr(d->d_name, suffix)) || p[strlen(suffix)])) {
				DPRINTF(1, "%s has no %s suffix\n", d->d_name, suffix);
				free(file);
				continue;
			}
		} else if (!S_ISDIR(st.st_mode)) {
			DPRINTF(1, "%s: not file or directory\n", file);
			free(file);
			continue;
		} else {
			strcat(file, fname);
			if (stat(file, &st)) {
				DPRINTF(1, "%s: %s\n", file, strerror(errno));
				free(file);
				continue;
			}
			if (!S_ISREG(st.st_mode)) {
				DPRINTF(1, "%s: not a file\n", file);
				free(file);
				continue;
			}
		}
		DPRINTF(1, "got file name %s\n", file);
		name = strdup(d->d_name);
		if (suffix && suffix[0] && (p = strstr(d->d_name, suffix)) && !p[strlen(suffix)])
			*p = '\0';
		list = g_list_append(list, name);
		free(file);
	}
	closedir(dir);
	list = g_list_sort(list, xde_string_compare);
	return (list);
}

/** @brief Get the list of XDE themes.
  * @param ctx  The current menu generation context.
  * @return (GList *) Pointer to list of XDE themes.
  *
  * For window managers that do not support styles, simply return the list of
  * XDE themes.  For these window managers the style will not change, however
  * the XDE theme (backgound images, XDE utility theme) will change properly.
  */
GList *
xde_common_get_themes(MenuContext *ctx)
{
	static const char *suffix = "/xde/theme.ini";
	static const char *subdir = "/themes/";
	GList *list = NULL;
	char *p;

	for (p = xdg_data_path; p < xdg_data_last; p += strlen(p) + 1) {
		int len = strlen(p) + strlen(subdir) + 1;
		char *dirname = calloc(len, sizeof(*dirname));
		struct dirent *d;
		struct stat st;
		DIR *dir;

		strcpy(dirname, p);
		strcat(dirname, subdir);
		if (!(dir = opendir(dirname))) {
			free(dirname);
			continue;
		}
		while ((d = readdir(dir))) {
			char *file;

			if (d->d_name[0] == '.')
				continue;
			len = strlen(dirname) + strlen(d->d_name) + strlen(suffix) + 1;
			file = calloc(len, sizeof(*file));
			strcpy(file, dirname);
			strcat(file, d->d_name);
			strcat(file, suffix);
			if (stat(file, &st)) {
				DPRINTF(1, "%s: %s\n", file, strerror(errno));
				free(file);
				continue;
			}
			if (!S_ISREG(st.st_mode)) {
				DPRINTF(1, "%s: not a file\n", file);
				free(file);
				continue;
			}
			list = g_list_append(list, strdup(d->d_name));
			free(file);
		}
		closedir(dir);
		free(dirname);
	}
	list = g_list_sort(list, xde_string_compare);
	return (list);
}

/** @brief Find the list of XDE themes corresponding to WM styles.
  * @param ctx  The current menu generation context.
  * @param styles  The list of supported WM styles (consumed).
  * @return (GList *) Pointer to list of XDE themes.
  *
  * Find the list of XDE themes that are supported by the window manager.  Pass
  * the list of supported WM style names and this function will return the names
  * in the list that re also supported XDE themes.  This function is used to
  * generated XDE theme menus for window managers that support styles.
  */
GList *
xde_common_find_themes(MenuContext *ctx, GList *styles)
{
	static const char *suffix = "/xde/theme.ini";
	static const char *subdir = "/themes/";
	GList *list = NULL, *style;

	for (style = styles; style; style = style->next) {
		char *copy, *theme, *dir, *p;
		int tlen;

		/* careful, icewm style names may have a path component */
		copy = theme = strdup(style->data);
		free(style->data);
		style->data = NULL;
		if ((p = strrchr(theme, '/')))
			*p = '\0';
		if ((p = strchr(theme, '/')))
			theme = p + 1;
		tlen = strlen(subdir) + strlen(theme) + strlen(suffix) + 1;
		for (dir = xdg_data_path; dir < xdg_data_last; dir += strlen(dir) + 1) {
			int len = strlen(dir) + tlen + 1;
			char *file;
			struct stat st;

			file = calloc(len, sizeof(*file));
			strcpy(file, dir);
			strcat(file, subdir);
			strcat(file, theme);
			strcat(file, suffix);
			if (stat(file, &st)) {
				DPRINTF(1, "%s: %s\n", file, strerror(errno));
				free(file);
				continue;
			}
			if (!S_ISREG(st.st_mode)) {
				DPRINTF(1, "%s: not a file\n", file);
				free(file);
				continue;
			}
			DPRINTF(1, "found theme file %s\n", file);
			free(file);
			list = g_list_append(list, strdup(theme));
			free(copy);
			break;
		}
	}
	g_list_free(styles);
	list = g_list_sort(list, xde_string_compare);
	return (list);
}

GtkMenuItem *
xde_gtk_common_themes(MenuContext *ctx)
{
	GList *themes, *theme;
	GtkWidget *menu, *image = NULL;
	GtkMenuItem *item = NULL;
	GdkPixbuf *pixbuf = NULL;
	char *icon;

	themes = xde_common_get_themes(ctx);
	menu = gtk_menu_new();
	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	gtk_menu_item_set_label(item, "Themes");
	if ((icon = xde_get_icon(ctx, "style")))
		pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL);
	if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	gtk_menu_item_set_submenu(item, menu);

	for (theme = themes; theme; theme = theme->next) {
		char *name = theme->data;
		char *cmd = g_strdup_printf("xde-style -s -t -r '%s'", name);
		GtkMenuItem *entry = GTK_MENU_ITEM(gtk_image_menu_item_new());

		gtk_menu_item_set_label(entry, name);
		if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
			gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(entry), image);
		gtk_menu_append(menu, GTK_WIDGET(entry));
		gtk_widget_show_all(GTK_WIDGET(entry));
		g_signal_connect_data(G_OBJECT(entry), "activate",
				      G_CALLBACK(xde_entry_activated), cmd, &xde_entry_disconnect, 0);
		theme->data = NULL;
		free(name);
	}
	g_list_free(themes);
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	gtk_widget_show_all(menu);
	gtk_widget_show_all(GTK_WIDGET(item));
	return (item);
}

GtkMenuItem *
xde_gtk_styles_simple(MenuContext *ctx)
{
	static const char *sysfmt = "xde-style -s -t -r -y '%s'";
	static const char *usrfmt = "xde-style -s -t -r -u '%s'";
	static const char *mixfmt = "xde-style -s -t -r '%s'";
	char *sysdir, *usrdir;
	GtkMenuItem *item = NULL, *entry;
	GList *sysent, *usrent;
	GtkWidget *menu, *image = NULL;
	GdkPixbuf *pixbuf = NULL;
	char *icon;

	sysdir = g_strdup_printf("%s%s", ctx->styles.sysdir, ctx->styles.subdir);
	usrdir = g_strdup_printf("%s%s%s", getenv("HOME"), ctx->styles.usrdir, ctx->styles.subdir);

	sysent = xde_common_get_styles(ctx, sysdir, ctx->styles.fname, ctx->styles.suffix);
	usrent = xde_common_get_styles(ctx, usrdir, ctx->styles.fname, ctx->styles.suffix);

	g_free(sysdir);
	g_free(usrdir);

	if (!sysent && !usrent)
		return (item);

	(void) mixfmt;

	menu = gtk_menu_new();
	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	gtk_menu_item_set_label(item, "Styles");
	if ((icon = xde_get_icon(ctx, "style")))
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
			gtk_widget_show_all(GTK_WIDGET(entry));
			g_signal_connect_data(G_OBJECT(entry), "activate",
					      G_CALLBACK(xde_entry_activated), cmd, &xde_entry_disconnect, 0);
			style->data = NULL;
			free(name);
		}
		g_list_free(sysent);
	}
	if (sysent && usrent) {
		entry = ctx->gtk.ops.separator(ctx, NULL);
		gtk_menu_append(menu, GTK_WIDGET(entry));
		gtk_widget_show_all(GTK_WIDGET(entry));
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
			gtk_widget_show_all(GTK_WIDGET(entry));
			g_signal_connect_data(G_OBJECT(entry), "activate",
					      G_CALLBACK(xde_entry_activated), cmd, &xde_entry_disconnect, 0);
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
	gtk_widget_show_all(menu);
	gtk_widget_show_all(GTK_WIDGET(item));
	return (item);

}

GtkMenuItem *
xde_gtk_themes_simple(MenuContext *ctx)
{
	static const char *sysfmt = "xde-style -s -t -r -y '%s'";
	static const char *usrfmt = "xde-style -s -t -r -u '%s'";
	static const char *mixfmt = "xde-style -s -t -r '%s'";
	char *sysdir, *usrdir;
	GtkMenuItem *item = NULL, *entry;
	GList *sysent, *usrent;
	GtkWidget *menu, *image = NULL;
	GdkPixbuf *pixbuf = NULL;
	char *icon;

	sysdir = g_strdup_printf("%s%s", ctx->styles.sysdir, ctx->styles.subdir);
	usrdir = g_strdup_printf("%s%s%s", getenv("HOME"), ctx->styles.usrdir, ctx->styles.subdir);

	sysent = xde_common_get_styles(ctx, sysdir, ctx->styles.fname, ctx->styles.suffix);
	usrent = xde_common_get_styles(ctx, usrdir, ctx->styles.fname, ctx->styles.suffix);

	sysent = xde_common_find_themes(ctx, sysent);
	usrent = xde_common_find_themes(ctx, usrent);

	g_free(sysdir);
	g_free(usrdir);

	if (!sysent && !usrent)
		return (item);

	(void) mixfmt;

	menu = gtk_menu_new();
	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	gtk_menu_item_set_label(item, "Themes");
	if ((icon = xde_get_icon(ctx, "style")))
		pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL);
	if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	gtk_menu_item_set_submenu(item, menu);

	if (sysent) {
		GList *theme;

		for (theme = sysent; theme; theme = theme->next) {
			char *name = theme->data;
			char *cmd = g_strdup_printf(sysfmt, name);

			entry = GTK_MENU_ITEM(gtk_image_menu_item_new());
			gtk_menu_item_set_label(entry, name);
			if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
				gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(entry), image);
			gtk_menu_append(menu, GTK_WIDGET(entry));
			gtk_widget_show_all(GTK_WIDGET(entry));
			g_signal_connect_data(G_OBJECT(entry), "activate",
					      G_CALLBACK(xde_entry_activated), cmd, &xde_entry_disconnect, 0);
			theme->data = NULL;
			free(name);
		}
		g_list_free(sysent);
	}
	if (sysent && usrent) {
		entry = ctx->gtk.ops.separator(ctx, NULL);
		gtk_menu_append(menu, GTK_WIDGET(entry));
		gtk_widget_show_all(GTK_WIDGET(entry));
	}
	if (usrent) {
		GList *theme;

		for (theme = usrent; theme; theme = theme->next) {
			char *name = theme->data;
			char *cmd = g_strdup_printf(usrfmt, name);

			entry = GTK_MENU_ITEM(gtk_image_menu_item_new());
			gtk_menu_item_set_label(entry, name);
			if (pixbuf && (image = gtk_image_new_from_pixbuf(pixbuf)))
				gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(entry), image);
			gtk_menu_append(menu, GTK_WIDGET(entry));
			gtk_widget_show_all(GTK_WIDGET(entry));
			g_signal_connect_data(G_OBJECT(entry), "activate",
					      G_CALLBACK(xde_entry_activated), cmd, &xde_entry_disconnect, 0);
			theme->data = NULL;
			free(name);
		}
		g_list_free(usrent);
	}
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	gtk_widget_show_all(menu);
	gtk_widget_show_all(GTK_WIDGET(item));
	return (item);
}

GtkMenuItem *
xde_gtk_common_wmspec(MenuContext *ctx)
{
	GtkWidget *image, *menu;
	GtkMenuItem *item, *part;
	GdkPixbuf *pixbuf = NULL;
	const char *inames[4] = { ctx->name, "preferences-system-windows", "metacity", NULL };
	char *icon;

	menu = gtk_menu_new();
	item = (GtkMenuItem *) gtk_image_menu_item_new();
	gtk_menu_item_set_submenu(item, menu);
	gtk_menu_item_set_label(item, ctx->wmname);
	if ((icon = xde_get_icons(ctx, inames))
	    && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL))
	    && (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	gtk_widget_show_all(GTK_WIDGET(menu));
	gtk_widget_show_all(GTK_WIDGET(item));
	DPRINTF(1, "calling \"config\"\n");
	if ((part = ctx->gtk.config(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF(1, "calling \"themes\"\n");
	if ((part = ctx->gtk.themes(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF(1, "calling \"styles\"\n");
	if ((part = ctx->gtk.styles(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF(1, "calling \"wkspcs\"\n");
	if ((part = ctx->gtk.wkspcs(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF(1, "calling \"wmmenu\"\n");
	if ((part = ctx->gtk.wmmenu(ctx)))
		gtk_menu_append(menu, GTK_WIDGET(part));
	DPRINTF(1, "done\n");
	if (pixbuf) {
		g_object_unref(pixbuf);
		pixbuf = NULL;
	}
	free(icon);
	return (GTK_MENU_ITEM(item));
}

static XdeMonitor *find_monitor(void);

void
workspace_activate(GtkMenuItem *item, gpointer user_data)
{
	OPRINTF(1, "Menu item [%s] activated\n", gtk_menu_item_get_label(GTK_MENU_ITEM(item)));
	wnck_workspace_activate(user_data, gtk_get_current_event_time());
}

void
window_activate(GtkMenuItem *item, gpointer user_data)
{
	WnckWindow *win = user_data;
	WnckWorkspace *work = wnck_window_get_workspace(win);

	OPRINTF(1, "Menu item [%s] activated\n", gtk_menu_item_get_label(GTK_MENU_ITEM(item)));
	wnck_workspace_activate(work, gtk_get_current_event_time());
	wnck_window_activate(win, gtk_get_current_event_time());
}

void
add_workspace(GtkMenuItem *item, gpointer user_data)
{
	WnckScreen *wnck = user_data;
	int count;

	if ((count = wnck_screen_get_workspace_count(wnck)) && count < 32)
		wnck_screen_change_workspace_count(wnck, count + 1);
}

void
del_workspace(GtkMenuItem *item, gpointer user_data)
{
	WnckScreen *wnck = user_data;
	int count;

	if ((count = wnck_screen_get_workspace_count(wnck)) && count > 1)
		wnck_screen_change_workspace_count(wnck, count - 1);
}

GtkMenuItem *
xde_gtk_common_wkspcs(MenuContext *ctx)
{
	XdeMonitor *xmon;
	WnckScreen *wnck;
	GtkWidget *image, *menu, *sep;
	GtkMenuItem *item;
	GdkPixbuf *pixbuf = NULL;
	GList *workspaces, *workspace;
	GList *windows, *window;
	GSList *group = NULL;
	WnckWorkspace *active;
	int anum;
	char *icon;

	xmon = find_monitor();
	wnck = xmon->xscr->wnck;
	wnck_screen_force_update(wnck);
	menu = gtk_menu_new();
	item = GTK_MENU_ITEM(gtk_image_menu_item_new());
	gtk_menu_item_set_submenu(item, menu);
	gtk_menu_item_set_label(item, "Workspace List");
	if ((icon = xde_get_icon(ctx, "preferences-desktop-display"))
	    && (pixbuf = gdk_pixbuf_new_from_file_at_size(icon, 16, 16, NULL))
	    && (image = gtk_image_new_from_pixbuf(pixbuf)))
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	gtk_widget_show_all(menu);
	gtk_widget_show_all(GTK_WIDGET(item));
	workspaces = wnck_screen_get_workspaces(wnck);
	windows = wnck_screen_get_windows(wnck);
	active = wnck_screen_get_active_workspace(wnck);
	anum = wnck_workspace_get_number(active);
	{
		GtkWidget *item, *submenu, *icon;
		int window_count = 0;

		icon = gtk_image_new_from_icon_name("preferences-system-windows", GTK_ICON_SIZE_MENU);
		item = gtk_image_menu_item_new_with_label("Iconified Windows");
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
		gtk_menu_append(menu, item);
		gtk_widget_show(item);

		submenu = gtk_menu_new();

		for (window = windows; window; window = window->next) {
			GdkPixbuf *pixbuf;
			const char *wname;
			char *label, *p;
			WnckWindow *win;
			GtkWidget *witem, *image;

			win = window->data;
			if (wnck_window_is_skip_tasklist(win))
				continue;
			if (wnck_window_is_pinned(win))
				continue;
			if (!wnck_window_is_minimized(win))
				continue;
			wname = wnck_window_get_name(win);
			witem = gtk_image_menu_item_new();
			label = g_strdup(wname);
			if ((p = strstr(label, " - GVIM")))
				*p = '\0';
			if ((p = strstr(label, " - VIM")))
				*p = '\0';
			if ((p = strstr(label, " - Mozilla Firefox")))
				*p = '\0';
			if (strlen(label) > 44) {
				strcpy(label + 41, "...");
				gtk_widget_set_tooltip_text(witem, wname);
			}
			p = label;
			label = g_strdup_printf(" ○ %s", p);
			g_free(p);
			gtk_menu_item_set_label(GTK_MENU_ITEM(witem), wname);
			pixbuf = wnck_window_get_mini_icon(win);
			if ((image = gtk_image_new_from_pixbuf(pixbuf)))
				gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(witem), image);
			gtk_menu_append(submenu, witem);
			gtk_widget_show(witem);
			g_signal_connect(G_OBJECT(witem), "activate", G_CALLBACK(window_activate), win);
			window_count++;
		}
		if (window_count) {
			gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);
			gtk_widget_show(submenu);
			gtk_widget_set_sensitive(item, TRUE);
		} else {
			gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);
			gtk_widget_show(submenu);
			gtk_widget_set_sensitive(item, FALSE);
		}
	}
	sep = gtk_separator_menu_item_new();
	gtk_menu_append(menu, sep);
	gtk_widget_show(sep);
	for (workspace = workspaces; workspace; workspace = workspace->next) {
		int wnum, len;
		const char *name;
		WnckWorkspace *work;
		GtkWidget *item, *submenu, *title, *icon;
		char *label, *wkname, *p;
		int window_count = 0;

		work = workspace->data;
		wnum = wnck_workspace_get_number(work);
		name = wnck_workspace_get_name(work);
		wkname = strdup(name);
		while ((p = strrchr(wkname, ' ')) && p[1] == '\0')
			*p = '\0';
		for (p = wkname; *p == ' '; p++) ;
		len = strlen(p);
		if (len < 6 || strspn(p, " 0123456789") == len)
			label = g_strdup_printf("Workspace %s", p);
		else
			label = g_strdup_printf("[%d] %s", wnum + 1, p);
		free(wkname);
#if 1
		(void) group;
		(void) anum;
		icon = gtk_image_new_from_icon_name("preferences-system-windows", GTK_ICON_SIZE_MENU);
		item = gtk_image_menu_item_new_with_label(label);
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
#else
		item = gtk_radio_menu_item_new_with_label(group, label);
		group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(item));
		if (wnum == anum)
			gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);
		else
			gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), FALSE);
#endif
		gtk_menu_append(menu, item);
		gtk_widget_show(item);

		submenu = gtk_menu_new();

#if 1
		icon = gtk_image_new_from_icon_name("preferences-desktop-display", GTK_ICON_SIZE_MENU);
#if 0
		p = label;
		label = g_strdup_printf("%s ——", p);
		g_free(p);
#endif
		title = gtk_image_menu_item_new_with_label(label);
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(title), icon);
		gtk_menu_append(submenu, title);
		gtk_widget_show(title);
		g_signal_connect(G_OBJECT(title), "activate", G_CALLBACK(workspace_activate), work);
		sep = gtk_separator_menu_item_new();
		gtk_menu_append(submenu, sep);
		gtk_widget_show(sep);
		window_count++;
#endif
		g_free(label);

		for (window = windows; window; window = window->next) {
			GdkPixbuf *pixbuf;
			const char *wname;
			char *label;
			WnckWindow *win;
			GtkWidget *witem, *image;

			win = window->data;
			if (!wnck_window_is_on_workspace(win, work))
				continue;
			if (wnck_window_is_skip_tasklist(win))
				continue;
			if (wnck_window_is_pinned(win))
				continue;
			if (wnck_window_is_minimized(win))
				continue;
			wname = wnck_window_get_name(win);
			witem = gtk_image_menu_item_new();
			label = g_strdup(wname);
			if ((p = strstr(label, " - GVIM")))
				*p = '\0';
			if ((p = strstr(label, " - VIM")))
				*p = '\0';
			if ((p = strstr(label, " - Mozilla Firefox")))
				*p = '\0';
			if (strlen(label) > 44) {
				strcpy(label + 41, "...");
				gtk_widget_set_tooltip_text(witem, wname);
			}
			p = label;
			label = g_strdup_printf(" ● %s", p);
			g_free(p);
			gtk_menu_item_set_label(GTK_MENU_ITEM(witem), label);
			g_free(label);
			pixbuf = wnck_window_get_mini_icon(win);
			if ((image = gtk_image_new_from_pixbuf(pixbuf)))
				gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(witem), image);
			gtk_menu_append(submenu, witem);
			gtk_widget_show(witem);
			g_signal_connect(G_OBJECT(witem), "activate", G_CALLBACK(window_activate), win);
			window_count++;
		}
		if (window_count) {
			gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);
			gtk_widget_show(submenu);
			gtk_widget_set_sensitive(item, TRUE);
		} else {
			gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);
			gtk_widget_hide(submenu);
			gtk_widget_set_sensitive(item, FALSE);
		}
	}
	sep = gtk_separator_menu_item_new();
	gtk_menu_append(menu, sep);
	gtk_widget_show(sep);
	{
		GtkWidget *item, *submenu, *icon;
		int window_count = 0;

		icon = gtk_image_new_from_icon_name("preferences-system-windows", GTK_ICON_SIZE_MENU);
		item = gtk_image_menu_item_new_with_label("All Workspaces");
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
		gtk_menu_append(menu, item);
		gtk_widget_show(item);

		submenu = gtk_menu_new();

		for (window = windows; window; window = window->next) {
			GdkPixbuf *pixbuf;
			const char *wname;
			WnckWindow *win;
			GtkWidget *witem, *image;

			win = window->data;
			if (wnck_window_is_skip_tasklist(win))
				continue;
			if (!wnck_window_is_pinned(win))
				continue;
			if (wnck_window_is_minimized(win))
				continue;
			wname = wnck_window_get_name(win);
			witem = gtk_image_menu_item_new_with_label(wname);
			pixbuf = wnck_window_get_mini_icon(win);
			if ((image = gtk_image_new_from_pixbuf(pixbuf)))
				gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(witem), image);
			gtk_menu_append(submenu, witem);
			gtk_widget_show(witem);
			g_signal_connect(G_OBJECT(witem), "activate", G_CALLBACK(window_activate), win);
			window_count++;
		}
		if (window_count) {
			gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);
			gtk_widget_show(submenu);
			gtk_widget_set_sensitive(item, TRUE);
		} else {
			gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);
			gtk_widget_hide(submenu);
			gtk_widget_set_sensitive(item, FALSE);
		}
	}
	sep = gtk_separator_menu_item_new();
	gtk_menu_append(menu, sep);
	gtk_widget_show(sep);
	{
		GtkWidget *item, *icon;
		int count;

		icon = gtk_image_new_from_icon_name("preferences-desktop-display", GTK_ICON_SIZE_MENU);
		item = gtk_image_menu_item_new_with_label("Append a workspace");
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
		gtk_menu_append(menu, item);
		gtk_widget_show(item);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(add_workspace), wnck);
		gtk_widget_set_sensitive(item, ((count = wnck_screen_get_workspace_count(wnck)) && count < 32));

		icon = gtk_image_new_from_icon_name("preferences-desktop-display", GTK_ICON_SIZE_MENU);
		item = gtk_image_menu_item_new_with_label("Remove last workspace");
		gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), icon);
		gtk_menu_append(menu, item);
		gtk_widget_show(item);
		g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(del_workspace), wnck);
		gtk_widget_set_sensitive(item, ((count = wnck_screen_get_workspace_count(wnck)) && count > 1));
	}

	gtk_widget_show_all(menu);
	return (item);
}

static GMenuTree *
get_menu(void)
{
	GMenuTree *tree;

	if (options.desktop)
		setenv("XDG_CURRENT_DESKTOP", options.desktop, TRUE);

	if (!(tree = gmenu_tree_new_for_path(options.rootmenu, options.treeflags)))
		EPRINTF("could not look up menu %s\n", options.rootmenu);
	return (tree);
}

static void
xde_menu_free(gpointer data)
{
	g_free(data);
}

static void
menu_tree_changed(GMenuTree *tree, gpointer user_data)
{
	MenuContext *ctx = user_data;
	GList *menu;
	FILE *file = stdout;

	if (!gmenu_tree_load_sync(tree, NULL)) {
		EPRINTF("could not sync menu %s\n", options.rootmenu);
		return;
	}
	if (ctx->xsessions) {
		g_hash_table_destroy(ctx->xsessions);
		ctx->xsessions = NULL;
	}
	DPRINTF(1, "calling create!\n");
	menu = ctx->wmm.create(ctx, options.style, NULL);
	DPRINTF(1, "done create!\n");
	if (options.menufile) {
		if (!(file = fopen(options.menufile, "w"))) {
			EPRINTF("cannot open %s for writing\n", options.menufile);
			g_list_free_full(menu, &xde_menu_free);
			return;
		}
	}
	g_list_foreach(menu, print_line, file);
	if (file && file != stdout)
		fclose(file);
	g_list_free_full(menu, &xde_menu_free);
	if (ctx->menu) {
		g_object_unref(ctx->menu);
		ctx->menu = NULL;
	}
}

static void
fork_and_exit(void)
{
	pid_t pid = getpid();

	if ((pid = fork()) < 0) {
		EPRINTF("%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (!pid)
		/* child continues */
		return;
	/* parent exits */
	exit(EXIT_SUCCESS);
}

static void
make_menu(void)
{
	GMenuTree *tree;

	if (!(tree = get_menu())) {
		EPRINTF("could not allocate menu tree\n");
		exit(EXIT_FAILURE);
	}
#if 0
	{
		GMenuTreeDirectory *directory;

		(void) print_line;
		fprintf(stdout, "Path=%s\n", gmenu_tree_get_canonical_menu_path(tree));
		if ((directory = gmenu_tree_get_root_directory(tree))) {
			display_directory(stdout, directory, 0);
		}
	}
#else
	{
		MenuContext *ctx;

		(void) display_directory;
		if (!(ctx = screens[0].context)) {
			EPRINTF("no menu context for screen 0\n");
			exit(EXIT_FAILURE);
		}
		ctx->stack = NULL;
		ctx->tree = tree;
		ctx->level = 0;
		ctx->indent = calloc(64, sizeof(*ctx->indent));
		ctx->xsessions = NULL;
		g_signal_connect(G_OBJECT(tree), "changed", G_CALLBACK(menu_tree_changed), ctx);
		menu_tree_changed(tree, ctx);
		if (options.exit)
			fork_and_exit();
	}
#endif
}

static MenuContext *wm_menu_context(const char *name);

static void
menu_generate(void)
{
	GMenuTree *tree;
	MenuContext *ctx;

	if (!options.wmname) {
		EPRINTF("need window manager name for menugen option\n");
		exit(EXIT_FAILURE);
	}
	if (!(ctx = wm_menu_context(options.wmname))) {
		EPRINTF("could not get menu context for %s\n", options.wmname);
		exit(EXIT_FAILURE);
	}
	if (!(tree = get_menu())) {
		EPRINTF("could not allocat menu tree\n");
		exit(EXIT_FAILURE);
	}
	ctx->stack = NULL;
	ctx->tree = tree;
	ctx->level = 0;
	ctx->indent = calloc(64, sizeof(*ctx->indent));
	menu_tree_changed(tree, ctx);
	if (options.exit)
		fork_and_exit();
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
make_menu(void)
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
	DPRINTF(1, "attempting to dlopen %s\n", dlfile);
	if ((handle = dlopen(dlfile, RTLD_NOW | RTLD_LOCAL))) {
		DPRINTF(1, "dlopen of %s succeeded\n", dlfile);
		if ((ops = dlsym(handle, "xde_menu_ops")))
			ops->handle = handle;
		else
			EPRINTF("could not find symbol xde_menu_ops");
	} else
		EPRINTF("dlopen of %s failed: %s\n", dlfile, dlerror());
	return ops;
}

static void
menu_pop(XdeScreen *xscr)
{
	MenuContext *ctx;
	GMenuTree *tree;
	GtkMenu *menu;

	if (!(tree = get_menu())) {
		EPRINTF("could not allocate menu tree\n");
		exit(EXIT_FAILURE);
	}
	if (!(ctx = xscr->context)) {
		EPRINTF("no menu context for screen %d\n", xscr->index);
		exit(EXIT_FAILURE);
	}
	ctx->stack = NULL;
	ctx->tree = tree;
	ctx->level = 0;
	ctx->indent = calloc(64, sizeof(*ctx->indent));

	if (!gmenu_tree_load_sync(tree, NULL)) {
		EPRINTF("could not sync menu %s\n", options.rootmenu);
		return;
	}
	DPRINTF(1, "calling create!\n");
	menu = ctx->gtk.create(ctx, options.style, NULL);
	DPRINTF(1, "done create!\n");
	g_signal_connect(G_OBJECT(menu), "selection_done", G_CALLBACK(selection_done), NULL);
	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, position_menu, find_monitor(),
		       options.button, options.timestamp);
}

static void
menu_show(XdeScreen *xscr)
{
	MenuContext *ctx;
	GMenuTree *tree;

	if (!(ctx = xscr->context)) {
		EPRINTF("no menu context for screen %d\n", xscr->index);
		return;
	}
	if (!ctx->menu) {
		if (!(tree = ctx->tree)) {
			EPRINTF("no menu tree for context for screen %d\n", xscr->index);
			return;
		}
		DPRINTF(1, "poping the GTK+ menu for button %d\n", options.button);
		if (!gmenu_tree_load_sync(tree, NULL)) {
			EPRINTF("could not sync menu %s\n", options.rootmenu);
			return;
		}
		DPRINTF(1, "calling create!\n");
		if (!(ctx->menu = ctx->gtk.create(ctx, options.style, NULL))) {
			EPRINTF("could not create menu for style %u\n", options.style);
			return;
		}
		// g_object_ref(ctx->menu);
		DPRINTF(1, "done create!\n");
	}
	gtk_menu_popup(GTK_MENU(ctx->menu), NULL, NULL, position_menu, find_monitor(),
		       options.button, options.timestamp);
	return;
}

/** @section Popup Window Event Handlers
  * @{ */

#if 1
static gboolean
stop_popup_timer(XdePopup *xpop)
{
	PTRACE(5);
	if (xpop->timer) {
		DPRINTF(1, "stopping popup timer\n");
		g_source_remove(xpop->timer);
		xpop->timer = 0;
		return TRUE;
	}
	return FALSE;
}

static void
release_grabs(XdePopup *xpop)
{
	PTRACE(5);
	if (xpop->pointer) {
#if 0
		/* will be broken when window unmaps */
		DPRINTF(1, "ungrabbing pointer\n");
		gdk_display_pointer_ungrab(disp, GDK_CURRENT_TIME);
#endif
		xpop->pointer = False;
	}
	if (xpop->keyboard) {
#if 0
		/* will be broken when window unmaps */
		DPRINTF(1, "ungrabbing keyboard\n");
		gdk_display_keyboard_ungrab(disp, GDK_CURRENT_TIME);
#endif
		xpop->keyboard = False;
	}
}

static void
drop_popup(XdePopup *xpop)
{
	PTRACE(5);
	if (xpop->popped) {
		stop_popup_timer(xpop);
		release_grabs(xpop);
		gtk_widget_hide(xpop->popup);
		xpop->popped = False;
	}
}

static gboolean
workspace_timeout(gpointer user)
{
	XdePopup *xpop = user;

	DPRINTF(1, "popup timeout!\n");
	drop_popup(xpop);
	xpop->timer = 0;
	return G_SOURCE_REMOVE;
}

static gboolean
start_popup_timer(XdePopup *xpop)
{
	PTRACE(5);
	if (xpop->timer)
		return FALSE;
	DPRINTF(1, "starting popup timer\n");
	xpop->timer = g_timeout_add(options.timeout, workspace_timeout, xpop);
	return TRUE;
}

void
restart_popup_timer(XdePopup *xpop)
{
	DPRINTF(1, "restarting popup timer\n");
	stop_popup_timer(xpop);
	start_popup_timer(xpop);
}

#if 0
static void
show_popup(XdeScreen *xscr, XdePopup *xpop, gboolean grab_p, gboolean grab_k)
{
	GdkGrabStatus status;
	Window win;

	if (!xpop->popup)
		return;
	DPRINTF(1, "popping the window\n");
	gdk_display_get_pointer(disp, NULL, NULL, NULL, &xpop->mask);
	stop_popup_timer(xpop);
	if (xpop->popped)
		gtk_window_reshow_with_initial_size(GTK_WINDOW(xpop->popup));
	else {
		if (xpop->type == PopupStart) {
			gtk_window_set_default_size(GTK_WINDOW(xpop->popup), -1, -1);
			gtk_widget_set_size_request(GTK_WIDGET(xpop->popup), -1, -1);
		}
		gtk_window_set_screen(GTK_WINDOW(xpop->popup), gdk_display_get_screen(disp, xscr->index));
		gtk_window_set_position(GTK_WINDOW(xpop->popup), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_window_present(GTK_WINDOW(xpop->popup));
		gtk_widget_show_now(GTK_WIDGET(xpop->popup));
		xpop->popped = True;
	}
	win = GDK_WINDOW_XID(xpop->popup->window);

	if (grab_p && !xpop->pointer) {
		GdkEventMask mask =
		    GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK |
		    GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK |
		    GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK;
		XSetInputFocus(dpy, win, RevertToPointerRoot, CurrentTime);
		status = gdk_pointer_grab(xpop->popup->window, TRUE, mask, NULL, NULL, GDK_CURRENT_TIME);
		switch (status) {
		case GDK_GRAB_SUCCESS:
			DPRINTF(1, "pointer grabbed\n");
			xpop->pointer = True;
			break;
		case GDK_GRAB_ALREADY_GRABBED:
			DPRINTF(1, "pointer already grabbed\n");
			break;
		case GDK_GRAB_INVALID_TIME:
			EPRINTF("pointer grab invalid time\n");
			break;
		case GDK_GRAB_NOT_VIEWABLE:
			EPRINTF("pointer grab on unviewable window\n");
			break;
		case GDK_GRAB_FROZEN:
			EPRINTF("pointer grab on frozen pointer\n");
			break;
		}
	}
	if (grab_k && !xpop->keyboard) {
		XSetInputFocus(dpy, win, RevertToPointerRoot, CurrentTime);
		status = gdk_keyboard_grab(xpop->popup->window, TRUE, GDK_CURRENT_TIME);
		switch (status) {
		case GDK_GRAB_SUCCESS:
			DPRINTF(1, "keyboard grabbed\n");
			xpop->keyboard = True;
			break;
		case GDK_GRAB_ALREADY_GRABBED:
			DPRINTF(1, "keyboard already grabbed\n");
			break;
		case GDK_GRAB_INVALID_TIME:
			EPRINTF("keyboard grab invalid time\n");
			break;
		case GDK_GRAB_NOT_VIEWABLE:
			EPRINTF("keyboard grab on unviewable window\n");
			break;
		case GDK_GRAB_FROZEN:
			EPRINTF("keyboard grab on frozen keyboard\n");
			break;
		}
	}
	// if (!xpop->keyboard || !xpop->pointer)
	if (!(xpop->mask & ~(GDK_LOCK_MASK | GDK_BUTTON1_MASK | GDK_BUTTON2_MASK | GDK_BUTTON3_MASK)))
		if (!xpop->inside)
			start_popup_timer(xpop);
}

/** @section Popup Window GDK Events
  * @{ */

#define PASSED_EVENT_MASK (KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|SubstructureNotifyMask|SubstructureRedirectMask)

static GdkFilterReturn
event_handler_KeyPress(Display *dpy, XEvent *xev, XdePopup *xpop)
{
	PTRACE(5);
	if (options.debug > 1) {
		fprintf(stderr, "==> KeyPress: %p\n", xpop);
		fprintf(stderr, "    --> send_event = %s\n", xev->xkey.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%lx\n", xev->xkey.window);
		fprintf(stderr, "    --> root = 0x%lx\n", xev->xkey.root);
		fprintf(stderr, "    --> subwindow = 0x%lx\n", xev->xkey.subwindow);
		fprintf(stderr, "    --> time = %lu\n", xev->xkey.time);
		fprintf(stderr, "    --> x = %d\n", xev->xkey.x);
		fprintf(stderr, "    --> y = %d\n", xev->xkey.y);
		fprintf(stderr, "    --> x_root = %d\n", xev->xkey.x_root);
		fprintf(stderr, "    --> y_root = %d\n", xev->xkey.y_root);
		fprintf(stderr, "    --> state = 0x%08x\n", xev->xkey.state);
		fprintf(stderr, "    --> keycode = %u\n", xev->xkey.keycode);
		fprintf(stderr, "    --> same_screen = %s\n", xev->xkey.same_screen ? "true" : "false");
		fprintf(stderr, "<== KeyPress: %p\n", xpop);
	}
	if (!xev->xkey.send_event) {
		XEvent ev = *xev;

		start_popup_timer(xpop);
		ev.xkey.window = ev.xkey.root;
		XSendEvent(dpy, ev.xkey.root, True, PASSED_EVENT_MASK, &ev);
		XFlush(dpy);
		return GDK_FILTER_CONTINUE;
	}
	return GDK_FILTER_REMOVE;
}

static GdkFilterReturn
event_handler_KeyRelease(Display *dpy, XEvent *xev, XdePopup *xpop)
{
	PTRACE(5);
	if (options.debug > 1) {
		fprintf(stderr, "==> KeyRelease: %p\n", xpop);
		fprintf(stderr, "    --> send_event = %s\n", xev->xkey.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%lx\n", xev->xkey.window);
		fprintf(stderr, "    --> root = 0x%lx\n", xev->xkey.root);
		fprintf(stderr, "    --> subwindow = 0x%lx\n", xev->xkey.subwindow);
		fprintf(stderr, "    --> time = %lu\n", xev->xkey.time);
		fprintf(stderr, "    --> x = %d\n", xev->xkey.x);
		fprintf(stderr, "    --> y = %d\n", xev->xkey.y);
		fprintf(stderr, "    --> x_root = %d\n", xev->xkey.x_root);
		fprintf(stderr, "    --> y_root = %d\n", xev->xkey.y_root);
		fprintf(stderr, "    --> state = 0x%08x\n", xev->xkey.state);
		fprintf(stderr, "    --> keycode = %u\n", xev->xkey.keycode);
		fprintf(stderr, "    --> same_screen = %s\n", xev->xkey.same_screen ? "true" : "false");
		fprintf(stderr, "<== KeyRelease: %p\n", xpop);
	}
	if (!xev->xkey.send_event) {
		XEvent ev = *xev;

		// start_popup_timer(xpop);
		ev.xkey.window = ev.xkey.root;
		XSendEvent(dpy, ev.xkey.root, True, PASSED_EVENT_MASK, &ev);
		XFlush(dpy);
		return GDK_FILTER_CONTINUE;
	}
	return GDK_FILTER_REMOVE;
}

static GdkFilterReturn
event_handler_ButtonPress(Display *dpy, XEvent *xev, XdePopup *xpop)
{
	PTRACE(5);
	if (options.debug > 1) {
		fprintf(stderr, "==> ButtonPress: %p\n", xpop);
		fprintf(stderr, "    --> send_event = %s\n", xev->xbutton.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%lx\n", xev->xbutton.window);
		fprintf(stderr, "    --> root = 0x%lx\n", xev->xbutton.root);
		fprintf(stderr, "    --> subwindow = 0x%lx\n", xev->xbutton.subwindow);
		fprintf(stderr, "    --> time = %lu\n", xev->xbutton.time);
		fprintf(stderr, "    --> x = %d\n", xev->xbutton.x);
		fprintf(stderr, "    --> y = %d\n", xev->xbutton.y);
		fprintf(stderr, "    --> x_root = %d\n", xev->xbutton.x_root);
		fprintf(stderr, "    --> y_root = %d\n", xev->xbutton.y_root);
		fprintf(stderr, "    --> state = 0x%08x\n", xev->xbutton.state);
		fprintf(stderr, "    --> button = %u\n", xev->xbutton.button);
		fprintf(stderr, "    --> same_screen = %s\n", xev->xbutton.same_screen ? "true" : "false");
		fprintf(stderr, "<== ButtonPress: %p\n", xpop);
	}
	if (!xev->xbutton.send_event) {
		XEvent ev = *xev;

		if (ev.xbutton.button == 4 || ev.xbutton.button == 5) {
			if (!xpop->inside)
				start_popup_timer(xpop);
			DPRINTF(1, "ButtonPress = %d passing to root window\n", ev.xbutton.button);
			ev.xbutton.window = ev.xbutton.root;
			XSendEvent(dpy, ev.xbutton.root, True, PASSED_EVENT_MASK, &ev);
			XFlush(dpy);
		}
		return GDK_FILTER_CONTINUE;
	}
	return GDK_FILTER_REMOVE;
}

static GdkFilterReturn
event_handler_ButtonRelease(Display *dpy, XEvent *xev, XdePopup *xpop)
{
	PTRACE(5);
	if (options.debug > 1) {
		fprintf(stderr, "==> ButtonRelease: %p\n", xpop);
		fprintf(stderr, "    --> send_event = %s\n", xev->xbutton.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%lx\n", xev->xbutton.window);
		fprintf(stderr, "    --> root = 0x%lx\n", xev->xbutton.root);
		fprintf(stderr, "    --> subwindow = 0x%lx\n", xev->xbutton.subwindow);
		fprintf(stderr, "    --> time = %lu\n", xev->xbutton.time);
		fprintf(stderr, "    --> x = %d\n", xev->xbutton.x);
		fprintf(stderr, "    --> y = %d\n", xev->xbutton.y);
		fprintf(stderr, "    --> x_root = %d\n", xev->xbutton.x_root);
		fprintf(stderr, "    --> y_root = %d\n", xev->xbutton.y_root);
		fprintf(stderr, "    --> state = 0x%08x\n", xev->xbutton.state);
		fprintf(stderr, "    --> button = %u\n", xev->xbutton.button);
		fprintf(stderr, "    --> same_screen = %s\n", xev->xbutton.same_screen ? "true" : "false");
		fprintf(stderr, "<== ButtonRelease: %p\n", xpop);
	}
	if (!xev->xbutton.send_event) {
		XEvent ev = *xev;

		if (ev.xbutton.button == 4 || ev.xbutton.button == 5) {
			// start_popup_timer(xpop);
			DPRINTF(1, "ButtonRelease = %d passing to root window\n", ev.xbutton.button);
			ev.xbutton.window = ev.xbutton.root;
			XSendEvent(dpy, ev.xbutton.root, True, PASSED_EVENT_MASK, &ev);
			XFlush(dpy);
		}
		return GDK_FILTER_CONTINUE;
	}
	return GDK_FILTER_REMOVE;
}

static const char *
show_mode(int mode)
{
	PTRACE(5);
	switch (mode) {
	case NotifyNormal:
		return ("NotifyNormal");
	case NotifyGrab:
		return ("NotifyGrab");
	case NotifyUngrab:
		return ("NotifyUngrab");
	case NotifyWhileGrabbed:
		return ("NotifyWhileGrabbed");
	}
	return NULL;
}

static const char *
show_detail(int detail)
{
	PTRACE(5);
	switch (detail) {
	case NotifyAncestor:
		return ("NotifyAncestor");
	case NotifyVirtual:
		return ("NotifyVirtual");
	case NotifyInferior:
		return ("NotifyInferior");
	case NotifyNonlinear:
		return ("NotifyNonlinear");
	case NotifyNonlinearVirtual:
		return ("NotifyNonlinearVirtual");
	case NotifyPointer:
		return ("NotifyPointer");
	case NotifyPointerRoot:
		return ("NotifyPointerRoot");
	case NotifyDetailNone:
		return ("NotifyDetailNone");
	}
	return NULL;
}

static GdkFilterReturn
event_handler_EnterNotify(Display *dpy, XEvent *xev, XdePopup *xpop)
{
	PTRACE(5);
	if (options.debug > 1) {
		fprintf(stderr, "==> EnterNotify: %p\n", xpop);
		fprintf(stderr, "    --> send_event = %s\n", xev->xcrossing.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%lx\n", xev->xcrossing.window);
		fprintf(stderr, "    --> root = 0x%lx\n", xev->xcrossing.root);
		fprintf(stderr, "    --> subwindow = 0x%lx\n", xev->xcrossing.subwindow);
		fprintf(stderr, "    --> time = %lu\n", xev->xcrossing.time);
		fprintf(stderr, "    --> x = %d\n", xev->xcrossing.x);
		fprintf(stderr, "    --> y = %d\n", xev->xcrossing.y);
		fprintf(stderr, "    --> x_root = %d\n", xev->xcrossing.x_root);
		fprintf(stderr, "    --> y_root = %d\n", xev->xcrossing.y_root);
		fprintf(stderr, "    --> mode = %s\n", show_mode(xev->xcrossing.mode));
		fprintf(stderr, "    --> detail = %s\n", show_detail(xev->xcrossing.detail));
		fprintf(stderr, "    --> same_screen = %s\n", xev->xcrossing.same_screen ? "true" : "false");
		fprintf(stderr, "    --> focus = %s\n", xev->xcrossing.focus ? "true" : "false");
		fprintf(stderr, "    --> state = 0x%08x\n", xev->xcrossing.state);
		fprintf(stderr, "<== EnterNotify: %p\n", xpop);
	}
	if (xev->xcrossing.mode == NotifyNormal) {
		if (!xpop->inside) {
			DPRINTF(1, "entered popup\n");
			stop_popup_timer(xpop);
			xpop->inside = True;
		}
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
event_handler_LeaveNotify(Display *dpy, XEvent *xev, XdePopup *xpop)
{
	PTRACE(5);
	if (options.debug > 1) {
		fprintf(stderr, "==> LeaveNotify: %p\n", xpop);
		fprintf(stderr, "    --> send_event = %s\n", xev->xcrossing.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%lx\n", xev->xcrossing.window);
		fprintf(stderr, "    --> root = 0x%lx\n", xev->xcrossing.root);
		fprintf(stderr, "    --> subwindow = 0x%lx\n", xev->xcrossing.subwindow);
		fprintf(stderr, "    --> time = %lu\n", xev->xcrossing.time);
		fprintf(stderr, "    --> x = %d\n", xev->xcrossing.x);
		fprintf(stderr, "    --> y = %d\n", xev->xcrossing.y);
		fprintf(stderr, "    --> x_root = %d\n", xev->xcrossing.x_root);
		fprintf(stderr, "    --> y_root = %d\n", xev->xcrossing.y_root);
		fprintf(stderr, "    --> mode = %s\n", show_mode(xev->xcrossing.mode));
		fprintf(stderr, "    --> detail = %s\n", show_detail(xev->xcrossing.detail));
		fprintf(stderr, "    --> same_screen = %s\n", xev->xcrossing.same_screen ? "true" : "false");
		fprintf(stderr, "    --> focus = %s\n", xev->xcrossing.focus ? "true" : "false");
		fprintf(stderr, "    --> state = 0x%08x\n", xev->xcrossing.state);
		fprintf(stderr, "<== LeaveNotify: %p\n", xpop);
	}
	if (xev->xcrossing.mode == NotifyNormal) {
		if (xpop->inside) {
			DPRINTF(1, "left popup\n");
			start_popup_timer(xpop);
			xpop->inside = False;
		}
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
event_handler_FocusIn(Display *dpy, XEvent *xev, XdePopup *xpop)
{
	PTRACE(5);
	if (options.debug > 1) {
		fprintf(stderr, "==> FocusIn: %p\n", xpop);
		fprintf(stderr, "    --> send_event = %s\n", xev->xfocus.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%lx\n", xev->xfocus.window);
		fprintf(stderr, "    --> mode = %s\n", show_mode(xev->xfocus.mode));
		fprintf(stderr, "    --> detail = %s\n", show_detail(xev->xfocus.detail));
		fprintf(stderr, "<== FocusIn: %p\n", xpop);
	}
	switch (xev->xfocus.mode) {
	case NotifyNormal:
	case NotifyUngrab:
		DPRINTF(1, "focused popup\n");
		break;
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
event_handler_FocusOut(Display *dpy, XEvent *xev, XdePopup *xpop)
{
	PTRACE(5);
	if (options.debug > 1) {
		fprintf(stderr, "==> FocusOut: %p\n", xpop);
		fprintf(stderr, "    --> send_event = %s\n", xev->xfocus.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%lx\n", xev->xfocus.window);
		fprintf(stderr, "    --> mode = %s\n", show_mode(xev->xfocus.mode));
		fprintf(stderr, "    --> detail = %s\n", show_detail(xev->xfocus.detail));
		fprintf(stderr, "<== FocusOut: %p\n", xpop);
	}
	switch (xev->xfocus.mode) {
	case NotifyNormal:
	case NotifyGrab:
	case NotifyWhileGrabbed:
		DPRINTF(1, "unfocused popup\n");
		if (!xpop->keyboard) {
			DPRINTF(1, "no grab or focus\n");
			start_popup_timer(xpop);
		}
		break;
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
popup_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;
	XdePopup *xpop = data;

	PTRACE(5);
	switch (xev->type) {
	case KeyPress:
		return event_handler_KeyPress(dpy, xev, xpop);
	case KeyRelease:
		return event_handler_KeyRelease(dpy, xev, xpop);
	case ButtonPress:
		return event_handler_ButtonPress(dpy, xev, xpop);
	case ButtonRelease:
		return event_handler_ButtonRelease(dpy, xev, xpop);
	case EnterNotify:
		return event_handler_EnterNotify(dpy, xev, xpop);
	case LeaveNotify:
		return event_handler_LeaveNotify(dpy, xev, xpop);
	case FocusIn:
		return event_handler_FocusIn(dpy, xev, xpop);
	case FocusOut:
		return event_handler_FocusOut(dpy, xev, xpop);
	}
	return GDK_FILTER_CONTINUE;
}

void
set_current_desktop(XdeScreen *xscr, int index, Time timestamp)
{
	Window root = RootWindow(dpy, xscr->index);
	XEvent ev;

	PTRACE(5);
	ev.xclient.type = ClientMessage;
	ev.xclient.serial = 0;
	ev.xclient.send_event = False;
	ev.xclient.display = dpy;
	ev.xclient.window = root;
	ev.xclient.message_type = _XA_NET_CURRENT_DESKTOP;
	ev.xclient.format = 32;
	ev.xclient.data.l[0] = index;
	ev.xclient.data.l[1] = timestamp;
	ev.xclient.data.l[2] = 0;
	ev.xclient.data.l[3] = 0;
	ev.xclient.data.l[4] = 0;

	XSendEvent(dpy, root, False, SubstructureNotifyMask | SubstructureRedirectMask, &ev);
}
#endif

/** @} */

/** @section Popup Window GTK Events
  * @{ */

#if 0
/** @brief grab broken event handler
  *
  * Generated when a pointer or keyboard grab is broken.  On X11, this happens
  * when a grab window becomes unviewable (i.e. it or one of its ancestors is
  * unmapped), or if the same application grabs the pointer or keyboard again.
  * Note that implicity grabs (which are initiated by button presses (or
  * grabbed key presses?)) can also cause GdkEventGrabBroken events.
  */
static gboolean
grab_broken_event(GtkWidget *widget, GdkEvent *event, gpointer user)
{
	XdePopup *xpop = user;
	GdkEventGrabBroken *ev = (typeof(ev)) event;

	PTRACE(5);
	if (ev->keyboard) {
		DPRINTF(1, "keyboard grab was broken\n");
		xpop->keyboard = False;
		/* IF we lost a keyboard grab, it is because another hot-key was pressed,
		   either doing something else or moving to another desktop.  Start the
		   timeout in this case. */
		start_popup_timer(xpop);
	} else {
		DPRINTF(1, "pointer grab was broken\n");
		xpop->pointer = False;
		/* If we lost a pointer grab, it is because somebody clicked on another
		   window.  In this case we want to drop the popup altogether.  This will
		   break the keyboard grab if any. */
		drop_popup(xpop);
	}
	if (ev->implicit) {
		DPRINTF(1, "broken grab was implicit\n");
	} else {
		DPRINTF(1, "broken grab was explicit\n");
	}
	if (ev->grab_window) {
		DPRINTF(1, "we broke the grab\n");
	} else {
		DPRINTF(1, "another application broke the grab\n");
	}
	return TRUE;		/* event handled */
}

static void
window_realize(GtkWidget *popup, gpointer xpop)
{
	gdk_window_add_filter(popup->window, popup_handler, xpop);
	// gdk_window_set_override_redirect(popup->window, TRUE);
	// gdk_window_set_accept_focus(popup->window, FALSE);
	// gdk_window_set_focus_on_map(popup->window, FALSE);
}

static gboolean
button_press_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
	return GTK_EVENT_PROPAGATE;
}

static gboolean
button_release_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
	return GTK_EVENT_PROPAGATE;
}

static gboolean
enter_notify_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
#if 0
	/* currently done by event handler, but considering grab */
	stop_popup_timer(xpop);
	xpop->inside = True;
#endif
	return GTK_EVENT_PROPAGATE;
}

static gboolean
focus_in_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
	return GTK_EVENT_PROPAGATE;
}

static gboolean
focus_out_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
	return GTK_EVENT_PROPAGATE;
}

static void
grab_focus(GtkWidget *widget, gpointer xpop)
{
}

static gboolean
key_press_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
	return GTK_EVENT_PROPAGATE;
}

static gboolean
key_release_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
	GdkEventKey *ev = (typeof(ev)) event;

	if (ev->is_modifier) {
		DPRINTF(1, "released key is modifier: dropping popup\n");
		drop_popup(xpop);
	}
	return GTK_EVENT_PROPAGATE;
}

static gboolean
leave_notify_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
#if 0
	/* currently done by event handler, but considering grab */
	start_popup_timer(xpop);
	xpop->inside = False;
#endif
	return GTK_EVENT_PROPAGATE;
}

static gboolean
map_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
	return GTK_EVENT_PROPAGATE;
}

static gboolean
scroll_event(GtkWidget *widget, GdkEvent *event, gpointer xpop)
{
	return GTK_EVENT_PROPAGATE;
}

static gboolean
visibility_notify_event(GtkWidget *popup, GdkEvent *event, gpointer xpop)
{
	GdkEventVisibility *ev = (typeof(ev)) event;

	switch (ev->state) {
	case GDK_VISIBILITY_FULLY_OBSCURED:
	case GDK_VISIBILITY_PARTIAL:
		gdk_window_raise(popup->window);
		break;
	case GDK_VISIBILITY_UNOBSCURED:
		/* good */
		break;
	}
	return GTK_EVENT_PROPAGATE;	/* event not fully handled */
}
#endif

/** @} */

#endif

/** @} */

/** @section Startup Notification Handling
  * @{ */

#if 0

static Bool
parse_startup_id(const char *id, char **launcher_p, char **launchee_p, char **hostname_p,
		 pid_t *pid_p, long *sequence_p, long *timestamp_p)
{
	long sequence = 0, timestamp = 0;
	pid_t pid = 0;
	const char *p;
	char *endptr = NULL, *s;

	do {
		const char *q;
		char *tmp;

		p = q = id;
		if (!(p = strchr(q, '/')))
			break;
		if (launcher_p)
			*launcher_p = strndup(q, p - q);
		q = p + 1;
		if (!(p = strchr(q, '/')))
			break;
		if (launchee_p) {
			*launchee_p = strndup(q, p - q);
			for (s = *launchee_p; *s; s++)
				if (*s == '|')
					*s = '/';
		}
		q = p + 1;
		if (!(p = strchr(q, '-')))
			break;
		tmp = strndup(q, p - q);
		pid = strtoul(tmp, &endptr, 10);
		free(tmp);
		if (endptr && *endptr)
			break;
		if (pid_p)
			*pid_p = pid;
		q = p + 1;
		if (!(p = strchr(q, '-')))
			break;
		tmp = strndup(q, p - q);
		sequence = strtoul(tmp, &endptr, 10);
		free(tmp);
		if (endptr && *endptr)
			break;
		if (sequence_p)
			*sequence_p = sequence;
		q = p + 1;
		if (!(p = strstr(q, "_TIME")))
			break;
		if (hostname_p)
			*hostname_p = strndup(q, p - q);
		q = p + 5;
		timestamp = strtoul(q, &endptr, 10);
		if (endptr && *endptr)
			break;
		if (timestamp_p)
			*timestamp_p = timestamp;
		return (True);
	}
	while (0);

	if (!timestamp && (p = strstr(id, "_TIME"))) {
		timestamp = strtoul(p + 5, &endptr, 10);
		if (!endptr || !*endptr)
			if (timestamp_p)
				*timestamp_p = timestamp;
	}
	return (False);
}

static Sequence *
find_sequence(XdeScreen *xscr, const char *id)
{
	GList *list;

	for (list = xscr->sequences; list; list = list->next) {
		Sequence *seq = list->data;

		if (!strcmp(id, sn_startup_sequence_get_id(seq->seq)))
			return (seq);
	}
	return (NULL);
}

void
del_sequence(XdePopup *xpop, Sequence *seq)
{
	gtk_list_store_remove(xpop->model, &seq->iter);
	*seq->list = g_list_remove(*seq->list, seq);
	free(seq->launcher);
	free(seq->launchee);
	free(seq->hostname);
	sn_startup_sequence_unref(seq->seq);
	seq->seq = NULL;
	if (seq->info) {
		g_object_unref(G_OBJECT(seq->info));
		seq->info = NULL;
	}
	free(seq);
	xpop->seqcount--;
	if (xpop->seqcount <= 0)
		drop_popup(xpop);
}

static gboolean
seq_timeout(gpointer data)
{
	Sequence *seq = data;
	XdePopup *xpop = seq->xpop;

	del_sequence(xpop, seq);
	return G_SOURCE_REMOVE;	/* remove event source */
}

void
rem_sequence(XdeScreen *xscr, Sequence *seq)
{
	g_timeout_add(options.timeout, seq_timeout, seq);
}

void
cha_sequence(XdeScreen *xscr, Sequence *seq)
{
	GdkPixbuf *pixbuf = NULL;
	const char *appid, *name = NULL, *desc = NULL, *tip;
	char *markup, *aid, *p;
	XdePopup *xpop = seq->xpop;

	if ((appid = sn_startup_sequence_get_application_id(seq->seq))) {
		if (!(p = strrchr(appid, '.')) || strcmp(p, ".desktop"))
			aid = g_strdup_printf("%s.desktop", appid);
		else
			aid = g_strdup(appid);
		seq->info = g_desktop_app_info_new(aid);
		g_free(aid);
	}
	if (!pixbuf)
		pixbuf = get_sequence_pixbuf(seq);
	if (!pixbuf)
		pixbuf = get_icons(g_app_info_get_icon(G_APP_INFO(seq->info)), NULL);
	if (!name)
		name = sn_startup_sequence_get_name(seq->seq);
	if (!name && seq->info)
		name = g_app_info_get_display_name(G_APP_INFO(seq->info));
	if (!name && seq->info)
		name = g_app_info_get_name(G_APP_INFO(seq->info));
	if (!name && seq->info)
		name = g_desktop_app_info_get_generic_name(seq->info);
	if (!name)
		name = sn_startup_sequence_get_wmclass(seq->seq);
	if (!name && seq->info)
		name = g_desktop_app_info_get_startup_wm_class(seq->info);
	if (!name)
		if ((name = sn_startup_sequence_get_binary_name(seq->seq)))
			if (strrchr(name, '/'))
				name = strrchr(name, '/');
	if (!name)
		if ((name = seq->launchee))
			if (strrchr(name, '/'))
				name = strrchr(name, '/');
	if (!desc)
		desc = sn_startup_sequence_get_description(seq->seq);
	if (!desc && seq->info)
		desc = g_app_info_get_description(G_APP_INFO(seq->info));
	markup = g_markup_printf_escaped("<span font=\"%.1f\"><b>%s</b>\n%s</span>", options.fontsize, name ? : "", desc ? : "");
	/* for now, ellipsize later */
	tip = desc;
	/* *INDENT-OFF* */
	gtk_list_store_set(xpop->model, &seq->iter,
			0, pixbuf,
			1, name,
			2, desc,
			3, markup,
			4, tip,
			5, seq,
			-1);
	/* *INDENT-ON* */
	g_object_unref(pixbuf);
	g_free(markup);
}

Sequence *
add_sequence(XdeScreen *xscr, const char *id, SnStartupSequence *sn_seq)
{
	Sequence *seq;
	Time timestamp;
	XdeMonitor *xmon;
	XdePopup *xpop;
	int screen;

	if ((seq = calloc(1, sizeof(*seq)))) {
		seq->screen = xscr->index;
		seq->monitor = 0;
		seq->seq = sn_seq;
		sn_startup_sequence_ref(sn_seq);
		seq->sequence = -1;
		seq->timestamp = -1;
		parse_startup_id(id, &seq->launcher, &seq->launchee, &seq->hostname,
				 &seq->pid, &seq->sequence, &seq->timestamp);
		if (seq->launcher && !strcmp(seq->launcher, "xdg-launch") && seq->sequence != -1)
			seq->monitor = seq->sequence;
		if (!seq->timestamp)
			if ((timestamp = sn_startup_sequence_get_timestamp(sn_seq)) != -1)
				seq->timestamp = timestamp;
		if ((screen = sn_startup_sequence_get_screen(sn_seq)) != -1) {
			seq->screen = screen;
			xscr = screens + screen;
		}
		seq->list = &xscr->sequences;
		xscr->sequences = g_list_append(xscr->sequences, seq);
		xmon = xscr->mons + seq->monitor;
		xpop = &xmon->start;
		gtk_list_store_append(xpop->model, &seq->iter);
		xpop->seqcount++;
		seq->xpop = xpop;

		cha_sequence(xscr, seq);

		show_popup(xscr, xpop, FALSE, FALSE);
	}
	return (seq);
}

#endif				/* STARTUP_NOTIFICATION */

/** @} */

/** @section Session Management
  * @{ */

#if 1
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

#if 1
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

#if 1
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

#if 1
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
	   restart it in the current session.  The RestartNever(3) style specifies that the
	   client does not wish to be restarted in the next session. */
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
clientSaveYourselfCB(SmcConn smcConn, SmPointer data, int saveType, Bool shutdown, int interactStyle, Bool fast)
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
	mainloop_quit();
}

static void
clientSaveCompleteCB(SmcConn smcConn, SmPointer data)
{
	if (saving_yourself) {
		saving_yourself = False;
		mainloop_quit();
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
	mainloop_quit();
}

static unsigned long clientCBMask = SmcSaveYourselfProcMask |
    SmcDieProcMask | SmcSaveCompleteProcMask | SmcShutdownCancelledProcMask;

static SmcCallbacks clientCBs = {
	.save_yourself = {.callback = &clientSaveYourselfCB,.client_data = NULL,},
	.die = {.callback = &clientDieCB,.client_data = NULL,},
	.save_complete = {.callback = &clientSaveCompleteCB,.client_data = NULL,},
	.shutdown_cancelled = {.callback = &clientShutdownCancelledCB,.client_data = NULL,},
};
#endif

/** @} */

/** @section X Resources
  * @{ */

/** @section Putting X Resources
  * @{ */

void
put_nc_resource(XrmDatabase xrdb, const char *prefix, const char *resource, const char *value)
{
	static char specifier[64];

	snprintf(specifier, sizeof(specifier), "%s.%s", prefix, resource);
	XrmPutStringResource(&xrdb, specifier, value);
}

void
put_resource(XrmDatabase xrdb, const char *resource, char *value)
{
	put_nc_resource(xrdb, RESCLAS, resource, value);
	g_free(value);
}

char *
putXrmColor(const GdkColor * color)
{
	return gdk_color_to_string(color);
}

char *
putXrmFont(const PangoFontDescription * font)
{
	return pango_font_description_to_string(font);
}

char *
putXrmInt(int integer)
{
	return g_strdup_printf("%d", integer);
}

char *
putXrmUint(unsigned int integer)
{
	return g_strdup_printf("%u", integer);
}

char *
putXrmTime(Time time)
{
	return g_strdup_printf("%lu", time);
}

char *
putXrmBlanking(unsigned int integer)
{
	switch (integer) {
	case DontPreferBlanking:
		return g_strdup("DontPreferBlanking");
	case PreferBlanking:
		return g_strdup("PreferBlanking");
	case DefaultBlanking:
		return g_strdup("DefaultBlanking");
	default:
		return g_strdup_printf("%u", integer);
	}
}

char *
putXrmExposures(unsigned int integer)
{
	switch (integer) {
	case DontAllowExposures:
		return g_strdup("DontAllowExposures");
	case AllowExposures:
		return g_strdup("AllowExposures");
	case DefaultExposures:
		return g_strdup("DefaultExposures");
	default:
		return g_strdup_printf("%u", integer);
	}
}

char *
putXrmButton(unsigned int integer)
{
	switch (integer) {
	case Button1:
		return g_strdup("Button1");
	case Button2:
		return g_strdup("Button2");
	case Button3:
		return g_strdup("Button3");
	case Button4:
		return g_strdup("Button4");
	case Button5:
		return g_strdup("Button5");
	default:
		return g_strdup_printf("%u", integer);
	}
}

char *
putXrmPowerLevel(unsigned integer)
{
	switch (integer) {
	case DPMSModeOn:
		return g_strdup("DPMSModeOn");
	case DPMSModeStandby:
		return g_strdup("DPMSModeStandby");
	case DPMSModeSuspend:
		return g_strdup("DPMSModeSuspend");
	case DPMSModeOff:
		return g_strdup("DPMSModeOff");
	default:
		return putXrmUint(integer);
	}
}

char *
putXrmDouble(double floating)
{
	return g_strdup_printf("%f", floating);
}

char *
putXrmBool(Bool boolean)
{
	return g_strdup(boolean ? "true" : "false");
}

char *
putXrmString(const char *string)
{
	return g_strdup(string);
}

char *
putXrmWhich(UseScreen which, int screen)
{
	switch (which) {
	case UseScreenDefault:
		return g_strdup("default");
	case UseScreenActive:
		return g_strdup("active");
	case UseScreenFocused:
		return g_strdup("focused");
	case UseScreenPointer:
		return g_strdup("pointer");
	case UseScreenSpecified:
		return putXrmInt(screen);
	}
	return (NULL);
}

char *
putXrmXGeometry(XdeGeometry *geom)
{
	char *wh = NULL, *xy = NULL, *result = NULL;

	if (geom->mask & (WidthValue | HeightValue))
		wh = g_strdup_printf("%ux%u", geom->w, geom->h);
	if (geom->mask & (XValue | YValue))
		xy = g_strdup_printf("%c%d%c%d",
				     (geom->mask & XNegative) ? '-' : '+', geom->x,
				     (geom->mask & YNegative) ? '-' : '+', geom->y);
	if (wh && xy) {
		result = g_strconcat(wh, xy, NULL);
		g_free(wh);
		g_free(xy);
	} else if (wh) {
		result = wh;
	} else if (xy) {
		result = xy;
	}
	return (result);
}

char *
putXrmWhere(MenuPosition where, XdeGeometry *geom)
{
	switch (where) {
	case PositionDefault:
		return g_strdup("default");
	case PositionCenter:
		return g_strdup("center");
	case PositionTopLeft:
		return g_strdup("topleft");
	case PositionPointer:
		return g_strdup("pointer");
	case PositionBottomRight:
		return g_strdup("bottomright");
	case PositionSpecified:
		return putXrmXGeometry(geom);
	}
	return (NULL);
}

char *
putXrmOrder(WindowOrder order)
{
	switch (order) {
	case WindowOrderDefault:
		return g_strdup("default");
	case WindowOrderClient:
		return g_strdup("client");
	case WindowOrderStacking:
		return g_strdup("stacking");
	}
	return (NULL);
}

void
put_resources(void)
{
	char *usrdb;
	XrmDatabase rdb = NULL;
	Display *dpy;
	char *val;

	if (!options.display)
		return;

	usrdb = g_build_filename(g_get_user_config_dir(), RESNAME, "rc", NULL);

	if (!(dpy = XOpenDisplay(NULL))) {
		EPRINTF("could not open display %s\n", options.display);
		exit(EXIT_FAILURE);
	}
	rdb = XrmGetDatabase(dpy);
	if (!rdb) {
		DPRINTF(1, "no resource manager database allocated\n");
		return;
	}
	if ((val = putXrmInt(options.debug)))
		put_resource(rdb, "debug", val);
	if ((val = putXrmInt(options.output)))
		put_resource(rdb, "verbose", val);
	/* put a bunch of resources */
	if ((val = putXrmTime(options.timeout)))
		put_resource(rdb, "timeout", val);
	if ((val = putXrmUint(options.iconsize)))
		put_resource(rdb, "iconsize", val);
	if ((val = putXrmDouble(options.fontsize)))
		put_resource(rdb, "fontsize", val);
	if ((val = putXrmInt(options.border)))
		put_resource(rdb, "border", val);

	if ((val = putXrmString(options.rootmenu)))
		put_resource(rdb, "rootmenu", val);
	if ((val = putXrmBool(options.fileout)))
		put_resource(rdb, "fileout", val);
	if ((val = putXrmString(options.menufile)))
		put_resource(rdb, "menufile", val);
	if ((val = putXrmString(options.filename)))
		put_resource(rdb, "filename", val);
	if ((val = putXrmBool(options.noicons)))
		put_resource(rdb, "noicons", val);
	if ((val = putXrmString(options.theme)))
		put_resource(rdb, "theme", val);
	if ((val = putXrmString(options.itheme)))
		put_resource(rdb, "icontheme", val);
	if ((val = putXrmBool(options.launch)))
		put_resource(rdb, "launch", val);
	if ((val = putXrmString(options.runhist)))
		put_resource(rdb, "runhist", val);
	if ((val = putXrmString(options.recapps)))
		put_resource(rdb, "recapps", val);
	if ((val = putXrmString(options.recently)))
		put_resource(rdb, "recently", val);
	if ((val = putXrmString(options.recent)))
		put_resource(rdb, "recent", val);
	if ((val = putXrmInt(options.maximum)))
		put_resource(rdb, "maximum", val);
	if ((val = putXrmString(options.menu)))
		put_resource(rdb, "menu", val);
	if ((val = putXrmUint(options.button)))
		put_resource(rdb, "button", val);
	if ((val = putXrmString(options.keypress)))
		put_resource(rdb, "keypress", val);
	if ((val = putXrmWhich(options.which, options.screen)))
		put_resource(rdb, "which", val);
	if ((val = putXrmWhere(options.where, &options.geom)))
		put_resource(rdb, "where", val);
	if ((val = putXrmBool(options.normal)))
		put_resource(rdb, "normal", val);
	if ((val = putXrmBool(options.hidden)))
		put_resource(rdb, "hidden", val);
	if ((val = putXrmBool(options.minimized)))
		put_resource(rdb, "minimized", val);
	if ((val = putXrmBool(options.monitors)))
		put_resource(rdb, "allmonitors", val);
	if ((val = putXrmBool(options.workspaces)))
		put_resource(rdb, "allworkspaces", val);
	if ((val = putXrmBool(options.activate)))
		put_resource(rdb, "activate", val);
	if ((val = putXrmBool(options.raise)))
		put_resource(rdb, "raise", val);
	if ((val = putXrmBool(options.systray)))
		put_resource(rdb, "systray", val);
	if ((val = putXrmBool(options.generate)))
		put_resource(rdb, "generate", val);
	if ((val = putXrmBool(options.treeflags & GMENU_TREE_FLAGS_INCLUDE_EXCLUDED)))
		put_resource(rdb, "excluded", val);
	if ((val = putXrmBool(options.treeflags & GMENU_TREE_FLAGS_INCLUDE_NODISPLAY)))
		put_resource(rdb, "nodisplay", val);
	if ((val = putXrmBool(options.treeflags & GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED)))
		put_resource(rdb, "unallocated", val);
	if ((val = putXrmBool(options.treeflags & GMENU_TREE_FLAGS_SHOW_EMPTY)))
		put_resource(rdb, "empty", val);
	if ((val = putXrmBool(options.treeflags & GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS)))
		put_resource(rdb, "separators", val);
	if ((val = putXrmBool(options.treeflags & GMENU_TREE_FLAGS_SORT_DISPLAY_NAME)))
		put_resource(rdb, "sort", val);
	if ((val = putXrmBool(options.tooltips)))
		put_resource(rdb, "tooltips", val);
	if ((val = putXrmBool(options.actions)))
		put_resource(rdb, "actions", val);
	if ((val = putXrmBool(options.exit)))
		put_resource(rdb, "exit", val);
	XrmPutFileDatabase(rdb, usrdb);
	XrmSetDatabase(dpy, rdb);
	XrmDestroyDatabase(rdb);
	XCloseDisplay(dpy);
	g_free(usrdb);
}

/** @} */

/** @section Putting Key File
  * @{ */

void
put_keyfile(void)
{
#if 0
	char *val, buf[256] = { 0, };

	if (!file) {
		EPRINTF("no key file!\n");
		return;
	}
	if (support.Keyboard) {
		int i, j;

		g_key_file_set_integer(file, KFG_Keyboard,
				       KFK_Keyboard_KeyClickPercent, state.Keyboard.key_click_percent);
		g_key_file_set_integer(file, KFG_Keyboard, KFK_Keyboard_BellPercent, state.Keyboard.bell_percent);
		g_key_file_set_integer(file, KFG_Keyboard, KFK_Keyboard_BellPitch, state.Keyboard.bell_pitch);
		g_key_file_set_integer(file, KFG_Keyboard,
				       KFK_Keyboard_BellDuration, state.Keyboard.bell_duration);
		g_key_file_set_integer(file, KFG_Keyboard, KFK_Keyboard_LEDMask, state.Keyboard.led_mask);
		g_key_file_set_boolean(file, KFG_Keyboard,
				       KFK_Keyboard_GlobalAutoRepeat, state.Keyboard.global_auto_repeat);
		for (i = 0, j = 0; i < 32; i++, j += 2)
			snprintf(buf + j, sizeof(buf) - j, "%02X", state.Keyboard.auto_repeats[i]);
		g_key_file_set_value(file, KFG_Keyboard, KFK_Keyboard_AutoRepeats, buf);
	}
	if (support.Pointer) {
		g_key_file_set_integer(file, KFG_Pointer,
				       KFK_Pointer_AccelerationDenominator, state.Pointer.accel_denominator);
		g_key_file_set_integer(file, KFG_Pointer,
				       KFK_Pointer_AccelerationNumerator, state.Pointer.accel_numerator);
		g_key_file_set_integer(file, KFG_Pointer, KFK_Pointer_Threshold, state.Pointer.threshold);
	}
	if (support.ScreenSaver) {
		if ((val = putXrmExposures(state.ScreenSaver.allow_exposures))) {
			g_key_file_set_value(file, KFG_ScreenSaver, KFK_ScreenSaver_AllowExposures, val);
			g_free(val);
		}
		g_key_file_set_integer(file, KFG_ScreenSaver,
				       KFK_ScreenSaver_Interval, state.ScreenSaver.interval);
		if ((val = putXrmBlanking(state.ScreenSaver.prefer_blanking))) {
			g_key_file_set_value(file, KFG_ScreenSaver, KFK_ScreenSaver_PreferBlanking, val);
			g_free(val);
		}
		g_key_file_set_integer(file, KFG_ScreenSaver, KFK_ScreenSaver_Timeout, state.ScreenSaver.timeout);
	}
	if (support.DPMS) {
		if ((val = putXrmPowerLevel(state.DPMS.power_level))) {
			g_key_file_set_value(file, KFG_DPMS, KFK_DPMS_PowerLevel, val);
			g_free(val);
		}
		g_key_file_set_boolean(file, KFG_DPMS, KFK_DPMS_State, state.DPMS.state ? TRUE : FALSE);
		g_key_file_set_integer(file, KFG_DPMS, KFK_DPMS_StandbyTimeout, state.DPMS.standby);
		g_key_file_set_integer(file, KFG_DPMS, KFK_DPMS_SuspendTimeout, state.DPMS.suspend);
		g_key_file_set_integer(file, KFG_DPMS, KFK_DPMS_OffTimeout, state.DPMS.off);
	}
	if (support.XKeyboard) {
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_MouseKeysDfltBtn, state.XKeyboard.desc->ctrls->mk_dflt_btn);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_RepeatKeysEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbRepeatKeysMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_SlowKeysEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbSlowKeysMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_BounceKeysEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbBounceKeysMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_StickyKeysEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbStickyKeysMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_MouseKeysEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbMouseKeysMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_MouseKeysAccelEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbMouseKeysAccelMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_AccessXKeysEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbAccessXKeysMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_AccessXTimeoutMaskEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbAccessXTimeoutMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_AccessXFeedbackMaskEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbAccessXFeedbackMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_AudibleBellMaskEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbAudibleBellMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_Overlay1MaskEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbOverlay1Mask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_Overlay2MaskEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbOverlay2Mask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_IgnoreGroupLockModsEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbIgnoreGroupLockMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_GroupsWrapEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbGroupsWrapMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_InternalModsEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbInternalModsMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_IgnoreLockModsEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbIgnoreLockModsMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_PerKeyRepeatEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbPerKeyRepeatMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_ControlsEnabledEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbControlsEnabledMask ? TRUE : FALSE);
		g_key_file_set_boolean(file, KFG_XKeyboard,
				       KFK_XKeyboard_AccessXOptionsEnabled,
				       state.XKeyboard.desc->ctrls->enabled_ctrls &
				       XkbAccessXOptionsMask ? TRUE : FALSE);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_RepeatDelay, state.XKeyboard.desc->ctrls->repeat_delay);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_RepeatInterval, state.XKeyboard.desc->ctrls->repeat_interval);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_SlowKeysDelay, state.XKeyboard.desc->ctrls->slow_keys_delay);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_DebounceDelay, state.XKeyboard.desc->ctrls->debounce_delay);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_MouseKeysDelay, state.XKeyboard.desc->ctrls->mk_delay);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_MouseKeysInterval, state.XKeyboard.desc->ctrls->mk_interval);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_MouseKeysTimeToMax,
				       state.XKeyboard.desc->ctrls->mk_time_to_max);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_MouseKeysMaxSpeed, state.XKeyboard.desc->ctrls->mk_max_speed);
		g_key_file_set_integer(file, KFG_XKeyboard,
				       KFK_XKeyboard_MouseKeysCurve, state.XKeyboard.desc->ctrls->mk_curve);
	}
#endif
}

/** @} */

/** @section Getting X Resources
  * @{ */

const char *
get_nc_resource(XrmDatabase xrdb, const char *res_name, const char *res_class, const char *resource)
{
	char *type;
	static char name[64];
	static char clas[64];
	XrmValue value = { 0, NULL };

	snprintf(name, sizeof(name), "%s.%s", res_name, resource);
	snprintf(clas, sizeof(clas), "%s.%s", res_class, resource);
	if (XrmGetResource(xrdb, name, clas, &type, &value)) {
		if (value.addr && *(char *) value.addr) {
			DPRINTF(1, "{%s:%s}:\t\t%s\n", name, clas, value.addr);
			return (const char *) value.addr;
		} else
			DPRINTF(1, "{%s|%s}:\t\t%s\n", name, clas, value.addr);
	} else
		DPRINTF(1, "{%s|%s}:\t\t\n", name, clas);
	return (NULL);
}

const char *
get_wm_resource(XrmDatabase xrdb, const char *res_name, const char *res_class, const char *resource)
{
	char *type;
	static char name[64];
	static char clas[64];
	XrmValue value = { 0, NULL };

	if (!options.wmname)
		return (NULL);
	snprintf(name, sizeof(name), "%s.%s.%s", res_name, options.wmname, resource);
	snprintf(clas, sizeof(clas), "%s.%s.%s", res_class, options.wmname, resource);
	if (XrmGetResource(xrdb, name, clas, &type, &value)) {
		if (value.addr && *(char *) value.addr) {
			DPRINTF(1, "{%s:%s}:\t\t%s\n", name, clas, value.addr);
			return (const char *) value.addr;
		} else
			DPRINTF(1, "{%s|%s}:\t\t%s\n", name, clas, value.addr);
	} else
		DPRINTF(1, "{%s|%s}:\t\t\n", name, clas);
	return (NULL);
}

const char *
get_resource(XrmDatabase xrdb, const char *resource, const char *dflt)
{
	const char *value;

	if (!(value = get_wm_resource(xrdb, RESNAME, RESCLAS, resource)))
		if (!(value = get_nc_resource(xrdb, RESNAME, RESCLAS, resource)))
			value = dflt;
	return (value);
}

Bool
getXrmColor(const char *val, GdkColor ** color)
{
	GdkColor c, *p;

	if (gdk_color_parse(val, &c) && (p = calloc(1, sizeof(*p)))) {
		*p = c;
		free(*color);
		*color = p;
		return True;
	}
	EPRINTF("could not parse color '%s'\n", val);
	return False;
}

Bool
getXrmFont(const char *val, PangoFontDescription ** face)
{
	FcPattern *pattern;
	PangoFontDescription *font;

	if ((pattern = FcNameParse((FcChar8 *) val))) {
		if ((font = pango_fc_font_description_from_pattern(pattern, True))) {
			pango_font_description_free(*face);
			*face = font;
			DPRINTF(1, "Font description is: %s\n", pango_font_description_to_string(font));
			return True;
		}
		FcPatternDestroy(pattern);
	}
	EPRINTF("could not parse font descriptikon '%s'\n", val);
	return False;
}

Bool
getXrmInt(const char *val, int *integer)
{
	char *endptr = NULL;
	int value;

	value = strtol(val, &endptr, 0);
	if (endptr && !*endptr) {
		*integer = value;
		return True;
	}
	return False;
}

Bool
getXrmUint(const char *val, unsigned int *integer)
{
	char *endptr = NULL;
	unsigned int value;

	value = strtoul(val, &endptr, 0);
	if (endptr && !*endptr) {
		*integer = value;
		return True;
	}
	return False;
}

Bool
getXrmTime(const char *val, Time *time)
{
	char *endptr = NULL;
	unsigned int value;

	value = strtoul(val, &endptr, 0);
	if (endptr && !*endptr) {
		*time = value;
		return True;
	}
	return False;
}

Bool
getXrmBlanking(const char *val, unsigned int *integer)
{
	if (!strcasecmp(val, "DontPreferBlanking")) {
		*integer = DontPreferBlanking;
		return True;
	}
	if (!strcasecmp(val, "PreferBlanking")) {
		*integer = PreferBlanking;
		return True;
	}
	if (!strcasecmp(val, "DefaultBlanking")) {
		*integer = DefaultBlanking;
		return True;
	}
	return getXrmUint(val, integer);
}

Bool
getXrmExposures(const char *val, unsigned int *integer)
{
	if (!strcasecmp(val, "DontAllowExposures")) {
		*integer = DontAllowExposures;
		return True;
	}
	if (!strcasecmp(val, "AllowExposures")) {
		*integer = AllowExposures;
		return True;
	}
	if (!strcasecmp(val, "DefaultExposures")) {
		*integer = DefaultExposures;
		return True;
	}
	return getXrmUint(val, integer);
}

Bool
getXrmButton(const char *val, unsigned int *integer)
{
	if (!strcasecmp(val, "Button1")) {
		*integer = 1;
		return True;
	}
	if (!strcasecmp(val, "Button2")) {
		*integer = 2;
		return True;
	}
	if (!strcasecmp(val, "Button3")) {
		*integer = 3;
		return True;
	}
	if (!strcasecmp(val, "Button4")) {
		*integer = 4;
		return True;
	}
	if (!strcasecmp(val, "Button5")) {
		*integer = 5;
		return True;
	}
	return getXrmUint(val, integer);
}

Bool
getXrmPowerLevel(const char *val, unsigned int *integer)
{
	if (!strcasecmp(val, "DPMSModeOn")) {
		*integer = DPMSModeOn;
		return True;
	}
	if (!strcasecmp(val, "DPMSModeStandby")) {
		*integer = DPMSModeStandby;
		return True;
	}
	if (!strcasecmp(val, "DPMSModeSuspend")) {
		*integer = DPMSModeSuspend;
		return True;
	}
	if (!strcasecmp(val, "DPMSModeOff")) {
		*integer = DPMSModeOff;
		return True;
	}
	return getXrmUint(val, integer);
}

Bool
getXrmDouble(const char *val, double *floating)
{
	const struct lconv *lc = localeconv();
	char radix, *copy = strdup(val);

	if ((radix = lc->decimal_point[0]) != '.' && strchr(copy, '.'))
		*strchr(copy, '.') = radix;

	*floating = strtod(copy, NULL);
	DPRINTF(1, "Got decimal value %s, translates to %f\n", val, *floating);
	free(copy);
	return True;
}

Bool
getXrmBool(const char *val, Bool *boolean)
{
	int len;

	if ((len = strlen(val))) {
		if (!strncasecmp(val, "true", len)) {
			*boolean = True;
			return True;
		}
		if (!strncasecmp(val, "false", len)) {
			*boolean = False;
			return True;
		}
	}
	EPRINTF("could not parse boolean'%s'\n", val);
	return False;
}

Bool
getXrmString(const char *val, char **string)
{
	char *tmp;

	if ((tmp = strdup(val))) {
		free(*string);
		*string = tmp;
		return True;
	}
	return False;
}

Bool
getXrmWhich(const char *val, UseScreen *which, int *screen)
{
	if (!strcasecmp(val, "default")) {
		*which = UseScreenDefault;
		return True;
	}
	if (!strcasecmp(val, "active")) {
		*which = UseScreenActive;
		return True;
	}
	if (!strcasecmp(val, "focused")) {
		*which = UseScreenFocused;
		return True;
	}
	if (!strcasecmp(val, "pointer")) {
		*which = UseScreenPointer;
		return True;
	}
	if (getXrmInt(val, screen)) {
		*which = UseScreenSpecified;
		return True;
	}
	return False;
}

Bool
getXrmXGeometry(const char *val, XdeGeometry *geom)
{
	int mask, x = 0, y = 0;
	unsigned int w = 0, h = 0;

	mask = XParseGeometry(val, &x, &y, &w, &h);
	if (!(mask & XValue) || !(mask & YValue))
		return False;
	geom->mask = mask;
	geom->x = x;
	geom->y = y;
	geom->w = w;
	geom->h = h;
	return True;
}

Bool
getXrmWhere(const char *val, MenuPosition *where, XdeGeometry *geom)
{
	if (!strcasecmp(val, "default")) {
		*where = PositionDefault;
		return True;
	}
	if (!strcasecmp(val, "center")) {
		*where = PositionCenter;
		return True;
	}
	if (!strcasecmp(val, "topleft")) {
		*where = PositionTopLeft;
		return True;
	}
	if (!strcasecmp(val, "bottomright")) {
		*where = PositionBottomRight;
		return True;
	}
	if (getXrmXGeometry(val, geom)) {
		*where = PositionSpecified;
		return True;
	}
	return False;
}

Bool
getXrmOrder(const char *val, WindowOrder *order)
{
	if (!strcasecmp(val, "default")) {
		*order = WindowOrderDefault;
		return True;
	}
	if (!strcasecmp(val, "client")) {
		*order = WindowOrderClient;
		return True;
	}
	if (!strcasecmp(val, "stacking")) {
		*order = WindowOrderStacking;
		return True;
	}
	return False;
}

static void
get_resources(void)
{
	XrmDatabase rdb;
	const char *val;
	char *usrdflt;
	Bool flag = False;

	PTRACE(5);
	XrmInitialize();
	if (getenv("DISPLAY")) {
		Display *dpy;

		if (!(dpy = XOpenDisplay(NULL))) {
			EPRINTF("could not open display %s\n", getenv("DISPLAY"));
			exit(EXIT_FAILURE);
		}
		rdb = XrmGetDatabase(dpy);
		if (!rdb)
			DPRINTF(1, "no resource manager database allocated\n");
		XCloseDisplay(dpy);
	}
	if (options.filename) {
		DPRINTF(1, "merging config from %s\n", options.filename);
		if (!XrmCombineFileDatabase(options.filename, &rdb, False))
			DPRINTF(1, "could not open rcfile %s\n", options.filename);
	}
	usrdflt = g_build_filename(g_get_user_config_dir(), RESNAME, "rc", NULL);
	if (!options.filename || strcmp(options.filename, usrdflt)) {
		DPRINTF(1, "merging config from %s\n", usrdflt);
		if (!XrmCombineFileDatabase(usrdflt, &rdb, False))
			DPRINTF(1, "could not open rcfile %s\n", usrdflt);
	}
	g_free(usrdflt);
	DPRINTF(1, "merging config from %s\n", APPDFLT);
	if (!XrmCombineFileDatabase(APPDFLT, &rdb, False))
		DPRINTF(1, "could not open rcfile %s\n", APPDFLT);
	if (!rdb) {
		DPRINTF(1, "no resource manager database found\n");
		rdb = XrmGetStringDatabase("");
	}
	if ((val = get_resource(rdb, "debug", NULL)))
		getXrmInt(val, &options.debug);
	if ((val = get_resource(rdb, "verbose", NULL)))
		getXrmInt(val, &options.output);
	/* get a bunch of resources */
	if ((val = get_resource(rdb, "timeout", "1000")))
		getXrmTime(val, &options.timeout);
	if ((val = get_resource(rdb, "iconsize", "48")))
		getXrmUint(val, &options.iconsize);
	if ((val = get_resource(rdb, "fontsize", "12.0")))
		getXrmDouble(val, &options.fontsize);
	if ((val = get_resource(rdb, "border", "3")))
		getXrmInt(val, &options.border);

	if ((val = get_resource(rdb, "rootmenu", NULL)))
		getXrmString(val, &options.rootmenu);
	if ((val = get_resource(rdb, "fileout", NULL)))
		getXrmBool(val, &options.fileout);
	if ((val = get_resource(rdb, "menufile", NULL)))
		getXrmString(val, &options.menufile);
	if ((val = get_resource(rdb, "filename", NULL)))
		getXrmString(val, &options.filename);
	if ((val = get_resource(rdb, "noicons", NULL)))
		getXrmBool(val, &options.noicons);
	if ((val = get_resource(rdb, "theme", NULL)))
		getXrmString(val, &options.theme);
	if ((val = get_resource(rdb, "icontheme", NULL)))
		getXrmString(val, &options.itheme);
	if ((val = get_resource(rdb, "launch", NULL)))
		getXrmBool(val, &options.launch);
	if ((val = get_resource(rdb, "runhist", NULL)))
		getXrmString(val, &options.runhist);
	if ((val = get_resource(rdb, "recapps", NULL)))
		getXrmString(val, &options.recapps);
	if ((val = get_resource(rdb, "recently", NULL)))
		getXrmString(val, &options.recently);
	if ((val = get_resource(rdb, "recent", NULL)))
		getXrmString(val, &options.recent);
	if ((val = get_resource(rdb, "maximum", "50")))
		getXrmInt(val, &options.maximum);
	if ((val = get_resource(rdb, "menu", NULL)))
		getXrmString(val, &options.menu);
	if ((val = get_resource(rdb, "button", NULL)))
		getXrmInt(val, &options.button);
	if ((val = get_resource(rdb, "keypress", NULL)))
		getXrmString(val, &options.keypress);
	if ((val = get_resource(rdb, "which", "default")))
		getXrmWhich(val, &options.which, &options.screen);
	if ((val = get_resource(rdb, "where", "default")))
		getXrmWhere(val, &options.where, &options.geom);
	if ((val = get_resource(rdb, "normal", "true")))
		getXrmBool(val, &options.normal);
	if ((val = get_resource(rdb, "hidden", "false")))
		getXrmBool(val, &options.hidden);
	if ((val = get_resource(rdb, "minimized", "false")))
		getXrmBool(val, &options.minimized);
	if ((val = get_resource(rdb, "allmonitors", "false")))
		getXrmBool(val, &options.monitors);
	if ((val = get_resource(rdb, "allworkspaces", "false")))
		getXrmBool(val, &options.workspaces);
	if ((val = get_resource(rdb, "activate", "true")))
		getXrmBool(val, &options.activate);
	if ((val = get_resource(rdb, "raise", "false")))
		getXrmBool(val, &options.raise);
	if ((val = get_resource(rdb, "systray", NULL)))
		getXrmBool(val, &options.systray);
	if ((val = get_resource(rdb, "generate", NULL)))
		getXrmBool(val, &options.generate);
	if ((val = get_resource(rdb, "excluded", NULL))) {
		if (getXrmBool(val, &flag)) {
			if (flag)
				options.treeflags |= GMENU_TREE_FLAGS_INCLUDE_EXCLUDED;
			else
				options.treeflags &= ~GMENU_TREE_FLAGS_INCLUDE_EXCLUDED;
		}
	}
	if ((val = get_resource(rdb, "nodisplay", NULL))) {
		if (getXrmBool(val, &flag)) {
			if (flag)
				options.treeflags |= GMENU_TREE_FLAGS_INCLUDE_NODISPLAY;
			else
				options.treeflags &= ~GMENU_TREE_FLAGS_INCLUDE_NODISPLAY;
		}
	}
	if ((val = get_resource(rdb, "unallocated", NULL))) {
		if (getXrmBool(val, &flag)) {
			if (flag)
				options.treeflags |= GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED;
			else
				options.treeflags &= ~GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED;
		}
	}
	if ((val = get_resource(rdb, "empty", NULL))) {
		if (getXrmBool(val, &flag)) {
			if (flag)
				options.treeflags |= GMENU_TREE_FLAGS_SHOW_EMPTY;
			else
				options.treeflags &= ~GMENU_TREE_FLAGS_SHOW_EMPTY;
		}
	}
	if ((val = get_resource(rdb, "separators", NULL))) {
		if (getXrmBool(val, &flag)) {
			if (flag)
				options.treeflags |= GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS;
			else
				options.treeflags &= ~GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS;
		}
	}
	if ((val = get_resource(rdb, "sort", NULL))) {
		if (getXrmBool(val, &flag)) {
			if (flag)
				options.treeflags |= GMENU_TREE_FLAGS_SORT_DISPLAY_NAME;
			else
				options.treeflags &= ~GMENU_TREE_FLAGS_SORT_DISPLAY_NAME;
		}
	}
	if ((val = get_resource(rdb, "tooltips", NULL)))
		getXrmBool(val, &options.tooltips);
	if ((val = get_resource(rdb, "actions", NULL)))
		getXrmBool(val, &options.actions);
	if ((val = get_resource(rdb, "exit", NULL)))
		getXrmBool(val, &options.exit);

	XrmDestroyDatabase(rdb);
}

/** @} */

/** @section Getting Key File
  * @{ */

void
get_keyfile(void)
{
}

/** @} */

/** @section System Tray Icon
  * @{ */

#if 1
static gboolean
button_press(GtkStatusIcon *icon, GdkEvent *event, gpointer user_data)
{
	XdeScreen *xscr = user_data;
	MenuContext *ctx;
	GMenuTree *tree;
	GdkEventButton *ev;
	int screen = 0;

	ev = (typeof(ev)) event;
	if (ev->button != 1)
		return GTK_EVENT_PROPAGATE;
	if (!(ctx = xscr->context)) {
		if (xscr->scrn)
			screen = gdk_screen_get_number(xscr->scrn);
		EPRINTF("no menu context for screen %d\n", screen);
		return GTK_EVENT_STOP;
	}
	if (!ctx->menu) {
		if (!(tree = ctx->tree)) {
			if (xscr->scrn)
				screen = gdk_screen_get_number(xscr->scrn);
			EPRINTF("no menu tree for context for screen %d\n", screen);
			return GTK_EVENT_STOP;
		}
		if (!gmenu_tree_load_sync(tree, NULL)) {
			EPRINTF("could not sync menu %s\n", options.rootmenu);
			return GTK_EVENT_STOP;
		}
		DPRINTF(1, "calling create!\n");
		if (!(ctx->menu = ctx->gtk.create(ctx, options.style, NULL))) {
			EPRINTF("could not create menu for style %u\n", options.style);
			return GTK_EVENT_STOP;
		}
		g_object_ref(ctx->menu);
		DPRINTF(1, "done create!\n");
	}
	gtk_menu_popup(ctx->menu, NULL, NULL, gtk_status_icon_position_menu, icon, ev->button, ev->time);
	return GTK_EVENT_STOP;
}

static void popup_show(XdeScreen *xscr);

static void
edit_selected(GtkMenuItem *item, gpointer user_data)
{
	popup_show(user_data);
}

static void
save_selected(GtkMenuItem *item, gpointer user_data)
{
#if 0
	edit_sav_values();
#endif
}

static void
popup_refresh(XdeScreen *xscr)
{
	/* asked to refresh the menu (as though there was a change) */
	MenuContext *ctx;
	GMenuTree *tree;

	if (!(ctx = xscr->context)) {
		EPRINTF("no menu context for screen %d\n", xscr->index);
		return;
	}
	if (!(tree = ctx->tree)) {
		EPRINTF("no menu tree for context\n");
		return;
	}
	DPRINTF(1, "refreshing the menus\n");
	menu_tree_changed(tree, ctx);
}

void
refresh_selected(GtkMenuItem *item, gpointer user_data)
{
	XdeScreen *xscr = user_data;

	popup_refresh(xscr);
	return;
}

void
about_selected(GtkMenuItem *item, gpointer user_data)
{
	gchar *authors[] = { "Brian F. G. Bidulock <bidulock@openss7.org>", NULL };
	gtk_show_about_dialog(NULL,
			      "authors", authors,
			      "comments", "An XDG compliant menu system.",
			      "copyright", "Copyright (c) 2013, 2014, 2015, 2016  OpenSS7 Corporation",
			      "license", "Do what thou wilt shall be the whole of the law.\n\n-- Aleister Crowley",
			      "logo-icon-name", LOGO_NAME,
			      "program-name", NAME,
			      "version", VERSION,
			      "website", "http://www.unexicon.com/",
			      "website-label", "Unexicon - Linux spun for telecom", NULL);
	return;
}

/** @brief restart
  *
  * We restart by executing ourselves with the same arguments that were provided
  * in the command that started us.  However, if we are running under session
  * management with restart hint SmRestartImmediately, the session manager will
  * restart us if we simply exit.
  */
static void
popup_restart(void)
{
	/* asked to restart (as though we were re-executed) */
	char **argv;
	int i;

	if (smcConn) {
		/* When running under a session manager, simply exit and the session
		   manager will restart us immediately. */
		exit(EXIT_SUCCESS);
	}

	argv = calloc(saveArgc + 1, sizeof(*argv));
	for (i = 0; i < saveArgc; i++)
		argv[i] = saveArgv[i];

	DPRINTF(1, "restarting\n");
	if (execvp(argv[0], argv) == -1)
		EPRINTF("%s: %s\n", argv[0], strerror(errno));
	return;
}

void
redo_selected(GtkMenuItem *item, gpointer user_data)
{
	popup_restart();
}

void
quit_selected(GtkMenuItem *item, gpointer user_data)
{
	mainloop_quit();
}

static void
popup_menu(GtkStatusIcon *icon, guint button, guint time, gpointer user_data)
{
	XdeScreen *xscr = user_data;
	GtkWidget *menu, *item;

	menu = gtk_menu_new();

	item = gtk_image_menu_item_new_from_stock("gtk-edit", NULL);
	g_signal_connect(item, "activate", G_CALLBACK(edit_selected), xscr);
	gtk_widget_show(item);
	gtk_menu_append(menu, item);

	item = gtk_image_menu_item_new_from_stock("gtk-save", NULL);
	g_signal_connect(item, "activate", G_CALLBACK(save_selected), xscr);
	gtk_widget_show(item);
	gtk_menu_append(menu, item);

	item = gtk_image_menu_item_new_from_stock("gtk-refresh", NULL);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(refresh_selected), xscr);
	gtk_widget_show(item);
	gtk_menu_append(menu, item);

	item = gtk_image_menu_item_new_from_stock("gtk-about", NULL);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(about_selected), xscr);
	gtk_widget_show(item);
	gtk_menu_append(menu, item);

	item = gtk_separator_menu_item_new();
	gtk_widget_show(item);
	gtk_menu_append(menu, item);

	item = gtk_image_menu_item_new_from_stock("gtk-redo", NULL);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(redo_selected), xscr);
	gtk_widget_show(item);
	gtk_menu_append(menu, item);

	item = gtk_image_menu_item_new_from_stock("gtk-quit", NULL);
	g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(quit_selected), xscr);
	gtk_widget_show(item);
	gtk_menu_append(menu, item);

	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, gtk_status_icon_position_menu, icon, button, time);
	return;
}

#if 0
void
present_popup(XdeScreen *xscr)
{
	if (!gtk_widget_get_mapped(xscr->ttwindow)) {
#if 0
		GdkEventMask mask =
		    GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK |
		    GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK |
		    GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK;
#endif
		gtk_window_set_position(GTK_WINDOW(xscr->ttwindow), GTK_WIN_POS_MOUSE);
		gtk_window_present(GTK_WINDOW(xscr->ttwindow));
		gtk_widget_show_now(GTK_WIDGET(xscr->ttwindow));
		gdk_window_focus(xscr->ttwindow->window, GDK_CURRENT_TIME);

#if 0
		gdk_keyboard_grab(xscr->ttwindow->window, TRUE, GDK_CURRENT_TIME);
		gdk_pointer_grab(xscr->ttwindow->window, FALSE, mask, NULL, NULL, GDK_CURRENT_TIME);
#endif
		stop_popup_timer(xscr);
		inside = TRUE;
	}
}
#endif

gboolean
query_tooltip(GtkStatusIcon *icon, gint x, gint y, gboolean keyboard_mode,
		 GtkTooltip *tooltip, gpointer user_data)
{
	XdeScreen *xscr = user_data;

	(void) xscr;
#if 0
	if (xscr->ttwindow) {
		present_popup(xscr);
		start_popup_timer(xscr);
		return FALSE;
	}
#endif
	return TRUE;		/* show it now */
}

#if 0
static void
popup_widget_realize(GtkWidget *popup, gpointer user)
{
	gdk_window_add_filter(popup->window, popup_handler, user);
	gdk_window_set_override_redirect(popup->window, TRUE);
	// gdk_window_set_accept_focus(popup->window, TRUE);
	// gdk_window_set_focus_on_map(popup->window, TRUE);
}
#endif

#if 0
static gboolean
popup_grab_broken_event(GtkWidget *widget, GdkEvent *event, gpointer user)
{
	XdeScreen *xscr = (typeof(xscr)) user;
	GdkEventGrabBroken *ev = (typeof(ev)) event;

	if (ev->keyboard) {
		start_popup_timer(xscr);
	} else {
		drop_popup(xscr);
	}
	return GTK_EVENT_STOP;	/* event handled */
}
#endif

void
systray_tooltip(XdeScreen *xscr)
{
#if 0
	GtkWidget *w, *h, *f, *s;

	if (xscr->ttwindow)
		return;

	w = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_widget_add_events(w, GDK_ALL_EVENTS_MASK);
	gtk_window_set_accept_focus(GTK_WINDOW(w), TRUE);
	gtk_window_set_focus_on_map(GTK_WINDOW(w), TRUE);
	// gtk_window_set_type_hint(GTK_WINDOW(w), GDK_WINDOW_TEMP);
	gtk_window_stick(GTK_WINDOW(w));
	gtk_window_set_keep_above(GTK_WINDOW(w), TRUE);

	h = gtk_hbox_new(FALSE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(h), 3);
	f = gtk_frame_new("Bell");
	gtk_container_set_border_width(GTK_CONTAINER(f), 3);
	gtk_frame_set_label_align(GTK_FRAME(f), 0.5, 0.5);
	gtk_box_pack_start(GTK_BOX(h), f, FALSE, FALSE, 0);
	s = gtk_vscale_new_with_range(0.0, 100.0, 1.0);
	gtk_scale_set_draw_value(GTK_SCALE(s), TRUE);
	gtk_scale_set_value_pos(GTK_SCALE(s), GTK_POS_TOP);
	g_signal_connect(G_OBJECT(s), "format-value", G_CALLBACK(format_value_percent), NULL);
	gtk_container_add(GTK_CONTAINER(f), s);
	gtk_widget_set_tooltip_markup(s, "\
Set the bell volume as a percentage of\n\
maximum volume: from 0% to 100%.");
#if 0
	g_signal_connect(G_OBJECT(s), "value-changed", G_CALLBACK(bell_percent_value_changed), NULL);
#endif
	controls.Icon.BellPercent = s;

	gtk_container_add(GTK_CONTAINER(w), h);
	gtk_widget_show_all(h);

	gtk_window_set_position(GTK_WINDOW(w), GTK_WIN_POS_MOUSE);
	gtk_container_set_border_width(GTK_CONTAINER(w), 3);
	gtk_window_set_default_size(GTK_WINDOW(w), -1, 200);
	gtk_widget_set_size_request(w, -1, 200);

#if 0
	g_signal_connect(G_OBJECT(w), "grab_broken_event", G_CALLBACK(popup_grab_broken_event), xscr);
#endif
	g_signal_connect(G_OBJECT(w), "realize", G_CALLBACK(popup_widget_realize), xscr);

	xscr->ttwindow = w;
#endif
}

static void
systray_show(XdeScreen *xscr)
{
	if (!xscr->icon) {
		xscr->icon = gtk_status_icon_new_from_icon_name(LOGO_NAME);
		gtk_status_icon_set_tooltip_text(xscr->icon, "Click for menu...");
		g_signal_connect(G_OBJECT(xscr->icon), "button_press_event", G_CALLBACK(button_press), xscr);
		g_signal_connect(G_OBJECT(xscr->icon), "popup_menu", G_CALLBACK(popup_menu), xscr);
		// g_signal_connect(xscr->icon, "query_tooltip", G_CALLBACK(query_tooltip), xscr);
		systray_tooltip(xscr);
	}
	gtk_status_icon_set_visible(xscr->icon, TRUE);
}

#endif

/** @} */

/** @section Event handlers
  * @{ */

/** @section libwnck Event handlers
  * @{ */

/** @section Workspace Events
  * @{ */

#if 1
#if 0
static Bool
good_window_manager(XdeScreen *xscr)
{
	PTRACE(5);
	/* ignore non fully compliant names */
	if (!xscr->wmname)
		return False;
	/* XXX: 2bwm(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "2bwm"))
		return True;
	/* XXX: adwm(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "adwm"))
		return True;
	/* XXX: awewm(1) does not really support desktops and is, therefore, not
	   supported.  (Welllll, it does.) */
	if (!strcasecmp(xscr->wmname, "aewm"))
		return True;
	/* XXX: afterstep(1) provides both workspaces and viewports (large desktops).
	   libwnck+ does not support these well, so when xde-pager detects that it is
	   running under afterstep(1), it does nothing.  (It has a desktop button proxy,
	   but it does not relay scroll wheel events by default.) */
	if (!strcasecmp(xscr->wmname, "afterstep"))
		return False;
	/* XXX: awesome(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "awesome"))
		return True;
	/* XXX: When running with bbkeys(1), blackbox(1) has its own window cycling
	   feedback.  When running under blackbox(1), xde-cycle does nothing. Otherwise,
	   blackbox(1) is largely supported and works well. */
	if (!strcasecmp(xscr->wmname, "blackbox"))
		return True;
	/* XXX: bspwm(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "bspwm"))
		return True;
	/* XXX: ctwm(1) is only GNOME/WinWM compliant and is not yet supported by
	   libwnck+.  Use etwm(1) instead.  xde-pager mitigates this somewhat, so it is
	   still listed as supported. */
	if (!strcasecmp(xscr->wmname, "ctwm"))
		return True;
	/* XXX: cwm(1) is supported, but it doesn't work that well because cwm(1) is not
	   placing _NET_WM_STATE on client windows, so libwnck+ cannot locate them and
	   will not provide contents in the pager. */
	if (!strcasecmp(xscr->wmname, "cwm"))
		return True;
	/* XXX: dtwm(1) is only OSF/Motif compliant and does support multiple desktops;
	   however, libwnck+ does not yet support OSF/Motif/CDE.  This is not mitigated
	   by xde-pager. */
	if (!strcasecmp(xscr->wmname, "dtwm"))
		return False;
	/* XXX: dwm(1) is barely ICCCM compliant.  It is not supported. */
	if (!strcasecmp(xscr->wmname, "dwm"))
		return False;
	/* XXX: echinus(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "echinus"))
		return True;
	/* XXX: etwm(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "etwm"))
		return True;
	/* XXX: failsafewm(1) has no desktops and is not supported. */
	if (!strcasecmp(xscr->wmname, "failsafewm"))
		return False;
	/* XXX: fluxbox(1) provides its own window cycling feedback.  When running under
	   fluxbox(1), xde-cycle does nothing. Otherwise, fluxbox(1) is supported and
	   works well. */
	if (!strcasecmp(xscr->wmname, "fluxbox"))
		return True;
	/* XXX: flwm(1) supports GNOME/WinWM but not EWMH/NetWM and is not currently
	   supported by libwnck+.  xde-pager mitigates this to some extent. */
	if (!strcasecmp(xscr->wmname, "flwm"))
		return True;
	/* XXX: fvwm(1) is supported and works well.  fvwm(1) provides a desktop button
	   proxy, but it needs the --noproxy option.  Viewports work better than on
	   afterstep(1) and behaviour is predictable. */
	if (!strcasecmp(xscr->wmname, "fvwm"))
		return True;
	/* XXX: herbstluftwm(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "herbstluftwm"))
		return True;
	/* XXX: i3(1) is supported; however, i3(1) does not support
	   _NET_NUMBER_OF_DESKTOPS, so only the current desktop is shown at any given
	   time, which makes it less effective. */
	if (!strcasecmp(xscr->wmname, "i3"))
		return True;
	/* XXX: icewm(1) provides its own pager on the panel, but does respect
	   _NET_DESKTOP_LAYOUT in some versions.  Although a desktop button proxy is
	   provided, older versions of icewm(1) will not proxy butt events sent by the
	   pager.  Use the version at https://github.com/bbidulock/icewm for best
	   results. */
	if (!strcasecmp(xscr->wmname, "icewm"))
		return True;
	/* XXX: jwm(1) provides its own pager on the panel, but does not respect or set
	   _NET_DESKTOP_LAYOUT, and key bindings are confused.  When xde-pager detects
	   that it is running under jwm(1) it will simply do nothing.  Otherwise, jwm(1)
	   is supported and works well. */
	if (!strcasecmp(xscr->wmname, "jwm"))
		return True;
	/* XXX: matwm2(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "matwm2"))
		return True;
	/* XXX: metacity(1) provides its own competent desktop switching feedback pop-up.
	   When xde-pager detects that it is running under metacity(1), it will simply do
	   nothing. */
	if (!strcasecmp(xscr->wmname, "metacity"))
		return True;
	/* XXX: mwm(1) only supports OSF/Motif and does not support multiple desktops. It
	   is not supported. */
	if (!strcasecmp(xscr->wmname, "mwm"))
		return False;
	/* XXX: mutter(1) has not been tested. */
	if (!strcasecmp(xscr->wmname, "mutter"))
		return True;
	/* XXX: openbox(1) provides its own meager desktop switching feedback pop-up.  It
	   does respect _NET_DESKTOP_LAYOUT but does not provide any of the contents of
	   the desktop. When both are running it is a little confusing, so when xde-pager
	   detects that it is running under openbox(1), it will simply do nothing. */
	if (!strcasecmp(xscr->wmname, "openbox"))
		return True;
	/* XXX: pekwm(1) provides its own broken desktop switching feedback pop-up;
	   however, it does not respect _NET_DESKTOP_LAYOUT and key bindings are
	   confused.  When xde-pager detects that it is running under pekwm(1), it will
	   simply do nothing. */
	if (!strcasecmp(xscr->wmname, "pekwm"))
		return True;
	/* XXX: spectrwm(1) is supported, but it doesn't work that well because, like
	   cwm(1), spectrwm(1) is not placing _NET_WM_STATE on client windows, so
	   libwnck+ cannot locate them and will not provide contents in the pager. */
	if (!strcasecmp(xscr->wmname, "spectrwm"))
		return True;
	/* XXX: twm(1) does not support multiple desktops and is not supported. */
	if (!strcasecmp(xscr->wmname, "twm"))
		return False;
	/* XXX: uwm(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "uwm"))
		return True;
	/* XXX: vtwm(1) is barely ICCCM compliant and currently unsupported: use etwm
	   instead. */
	if (!strcasecmp(xscr->wmname, "vtwm"))
		return False;
	/* XXX: waimea(1) is supported; however, waimea(1) defaults to triple-sized large
	   desktops in a 2x2 arrangement.  With large virtual desktops, libwnck+ gets
	   confused just as with afterstep(1).  fvwm(1) must be doing something right. It
	   appears to be _NET_DESKTOP_VIEWPORT, which is supposed to be set to the
	   viewport position of each desktop (and isn't).  Use the waimea at
	   https://github.com/bbidulock/waimea for a corrected version. */
	if (!strcasecmp(xscr->wmname, "waimea"))
		return True;
	/* XXX: wind(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "wind"))
		return True;
	/* XXX: wmaker(1) is supported and works well.  wmaker(1) has its own background
	   switcher and window cycling. */
	if (!strcasecmp(xscr->wmname, "wmaker"))
		return True;
	/* XXX: wmii(1) is supported and works well.  wmii(1) was stealing the focus back
	   from the pop-up, but this was fixed. */
	if (!strcasecmp(xscr->wmname, "wmii"))
		return True;
	/* XXX: wmx(1) is supported and works well. */
	if (!strcasecmp(xscr->wmname, "wmx"))
		return True;
	/* XXX: xdwm(1) does not support EWMH/NetWM for desktops. */
	if (!strcasecmp(xscr->wmname, "xdwm"))	/* XXX */
		return False;
	/* XXX: yeahwm(1) does not support EWMH/NetWM and is currently unsupported.  The
	   pager will simply not do anything while this window manager is running. */
	if (!strcasecmp(xscr->wmname, "yeahwm"))
		return False;
	return True;
}

static void setup_button_proxy(XdeScreen *xscr);
#endif

static void
window_manager_changed(WnckScreen *wnck, gpointer user)
{
	XdeScreen *xscr = user;
	const char *name;

	PTRACE(5);
	/* I suppose that what we should do here is set a timer and wait before doing
	   anything; however, I think that libwnck++ already does this (waits before even
	   giving us the signal). */
	wnck_screen_force_update(wnck);
	free(xscr->wmname);
	xscr->wmname = NULL;
	xscr->goodwm = False;
	/* FIXME: need to check and free tree, xsessions and menu in old context before
	   assigning a new one. */
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
	DPRINTF(1, "window manager is '%s'\n", xscr->wmname);
	DPRINTF(1, "window manager is %s\n", xscr->goodwm ? "usable" : "unusable");
	if (xscr->goodwm) {
		char *p;

		free(options.format);
		options.format = strdup(xscr->wmname);
		free(options.desktop);
		options.desktop = strdup(xscr->wmname);
		for (p = options.desktop; *p; p++)
			*p = toupper(*p);
	}
}

static void
workspace_destroyed(WnckScreen *wnck, WnckWorkspace *space, gpointer data)
{
	/* pager can handle this on its own */
}

static void
workspace_created(WnckScreen *wnck, WnckWorkspace *space, gpointer data)
{
	/* pager can handle this on its own */
}

static void
viewports_changed(WnckScreen *wnck, gpointer data)
{
	/* pager can handle this on its own */
}

static void
background_changed(WnckScreen *wnck, gpointer data)
{
	/* XXX: might have setbg do something here */
}

static void
active_workspace_changed(WnckScreen *wnck, WnckWorkspace *prev, gpointer data)
{
	/* XXX: should be handled by update_current_desktop */
}
#endif

/** @} */

/** @section Specific Window Events
  * @{ */

#if 1
static void
actions_changed(WnckWindow *window, WnckWindowActions changed, WnckWindowActions state, gpointer xscr)
{
}

static void
geometry_changed(WnckWindow *window, gpointer xscr)
{
}

static void
icon_changed(WnckWindow *window, gpointer xscr)
{
}

static void
name_changed(WnckWindow *window, gpointer xscr)
{
}

static void
state_changed(WnckWindow *window, WnckWindowState changed, WnckWindowState state, gpointer xscr)
{
}

static void
workspace_changed(WnckWindow *window, gpointer xscr)
{
}
#endif

/** @} */

/** @section Window Events
  * @{ */

#if 0
static WnckWorkspace *
same_desk(WnckScreen *wnck, WnckWindow *win1, WnckWindow *win2)
{
	WnckWorkspace *desk;

	if (((desk = wnck_window_get_workspace(win1)) && wnck_window_is_on_workspace(win2, desk)) ||
	    ((desk = wnck_window_get_workspace(win2)) && wnck_window_is_on_workspace(win1, desk)) ||
	    ((desk = wnck_screen_get_active_workspace(wnck)) &&
	     wnck_window_is_on_workspace(win2, desk) && wnck_window_is_on_workspace(win1, desk)))
		return (desk);
	return (NULL);
}

static gboolean
is_cyclic(WnckWorkspace *desk, WnckWindow *prev, WnckWindow *actv, GList *list)
{
	GList *l, *lprev = NULL, *lactv = NULL;

	for (l = list; l; l = l->next) {
		if (l->data == prev)
			lprev = l;
		if (l->data == actv)
			lactv = l;
	}
	if (lprev && lactv) {
		for (l = lprev->next ? : list; l; l = l->next ? : list) {
			WnckWindow *curr = l->data;

			if (l == lactv)
				return TRUE;
			if (!wnck_window_is_visible_on_workspace(curr, desk))
				continue;
			if (wnck_window_is_skip_tasklist(curr))
				continue;
			break;
		}
		for (l = lactv->next ? : list; l; l = l->next ? : list) {
			WnckWindow *curr = l->data;

			if (l == lprev)
				return TRUE;
			if (!wnck_window_is_visible_on_workspace(curr, desk))
				continue;
			if (wnck_window_is_skip_tasklist(curr))
				continue;
			break;
		}
	}
	return FALSE;
}

static XdeMonitor *
is_cycle(XdeScreen *xscr, WnckScreen *wnck, WnckWindow *prev, WnckWindow *actv)
{
	XdeMonitor *xmon = NULL;
	WnckWorkspace *desk;
	GdkWindow *wp, *wa;
	int mp, ma;

	if (!prev || !actv)
		return (NULL);
	if (prev == actv)
		return (NULL);
	wp = gdk_x11_window_foreign_new_for_display(disp, wnck_window_get_xid(prev));
	wa = gdk_x11_window_foreign_new_for_display(disp, wnck_window_get_xid(actv));
	if (!wp || !wa) {
		if (wp)
			g_object_unref(G_OBJECT(wp));
		if (wa)
			g_object_unref(G_OBJECT(wa));
		return (NULL);
	}
	mp = gdk_screen_get_monitor_at_window(xscr->scrn, wp);
	ma = gdk_screen_get_monitor_at_window(xscr->scrn, wa);
	if (mp != ma) {
		g_object_unref(G_OBJECT(wp));
		g_object_unref(G_OBJECT(wa));
		return (NULL);
	}
	xmon = &xscr->mons[ma];

	if (!(desk = same_desk(wnck, prev, actv)))
		return (NULL);
	if (options.order != WindowOrderStacking)
		if (is_cyclic(desk, prev, actv, wnck_screen_get_windows(wnck)))
			return (xmon);
	if (options.order != WindowOrderClient)
		if (is_cyclic(desk, prev, actv, wnck_screen_get_windows_stacked(wnck)))
			return (xmon);
	return (NULL);
}

/** @brief active window changed
  *
  * The active window changing only affects the cycling window.  We should only
  * pop the cycle window when the window has cycled according to criteria.
  */
static void
active_window_changed(WnckScreen *wnck, WnckWindow *prev, gpointer user)
{
	static const GdkModifierType buttons =
	    (GDK_BUTTON1_MASK | GDK_BUTTON2_MASK | GDK_BUTTON3_MASK | GDK_BUTTON4_MASK | GDK_BUTTON5_MASK);
	static const GdkModifierType dontcare = (GDK_SHIFT_MASK | GDK_LOCK_MASK | GDK_RELEASE_MASK);
	XdeScreen *xscr = user;
	XdeMonitor *xmon = NULL;
	GdkModifierType mask = 0;
	WnckWindow *actv;
	int i;

	if (!options.show.cycle)
		return;
	gdk_display_get_pointer(disp, NULL, NULL, NULL, &mask);
	/* if button down, do nothing */
	if (mask & buttons)
		return;
	if (mask & ~(buttons | dontcare)) {
		actv = wnck_screen_get_active_window(wnck);
		if (actv && prev)
			xmon = is_cycle(xscr, wnck, prev, actv);
	}
	if (!xmon) {
		for (i = 0; i < xscr->nmon; i++) {
			stop_popup_timer(&xscr->mons[i].cycle);
			drop_popup(&xscr->mons[i].cycle);
		}
		return;
	}
	if (xscr->cycle)
		show_popup(xscr, &xmon->cycle, TRUE, TRUE);
	return;
}
#endif

static void
clients_changed(WnckScreen *wnck, XdeScreen *xscr)
{
}

static void
application_closed(WnckScreen *wnck, WnckApplication * app, gpointer xscr)
{
	clients_changed(wnck, xscr);
}

static void
application_opened(WnckScreen *wnck, WnckApplication * app, gpointer xscr)
{
	clients_changed(wnck, xscr);
}

static void
class_group_closed(WnckScreen *wnck, WnckClassGroup * class_group, gpointer xscr)
{
	clients_changed(wnck, xscr);
}

static void
class_group_opened(WnckScreen *wnck, WnckClassGroup * class_group, gpointer xscr)
{
	clients_changed(wnck, xscr);
}

static void
window_closed(WnckScreen *wnck, WnckWindow *window, gpointer xscr)
{
	clients_changed(wnck, xscr);
}

static void
window_opened(WnckScreen *wnck, WnckWindow *window, gpointer xscr)
{
	g_signal_connect(G_OBJECT(window), "actions_changed", G_CALLBACK(actions_changed), xscr);
	g_signal_connect(G_OBJECT(window), "geometry_changed", G_CALLBACK(geometry_changed), xscr);
	g_signal_connect(G_OBJECT(window), "icon_changed", G_CALLBACK(icon_changed), xscr);
	g_signal_connect(G_OBJECT(window), "name_changed", G_CALLBACK(name_changed), xscr);
	g_signal_connect(G_OBJECT(window), "state_changed", G_CALLBACK(state_changed), xscr);
	g_signal_connect(G_OBJECT(window), "workspace_changed", G_CALLBACK(workspace_changed), xscr);
	clients_changed(wnck, xscr);
}

static void
window_stacking_changed(WnckScreen *wnck, gpointer xscr)
{
	clients_changed(wnck, xscr);
}

static void
showing_desktop_changed(WnckScreen *wnck, gpointer xscr)
{
}

/** @} */

/** @} */

/** @section X Event Handlers
  * @{ */

#if 0
static void
sn_handler(SnMonitorEvent *event, void *data)
{
	SnStartupSequence *sn_seq = NULL;
	XdeScreen *xscr = data;
	Sequence *seq;
	const char *id;

	sn_seq = sn_monitor_event_get_startup_sequence(event);

	id = sn_startup_sequence_get_id(sn_seq);
	switch (sn_monitor_event_get_type(event)) {
	case SN_MONITOR_EVENT_INITIATED:
		add_sequence(xscr, id, sn_seq);
		break;
	case SN_MONITOR_EVENT_CHANGED:
		if ((seq = find_sequence(xscr, id)))
			cha_sequence(xscr, seq);
		break;
	case SN_MONITOR_EVENT_COMPLETED:
	case SN_MONITOR_EVENT_CANCELED:
		if ((seq = find_sequence(xscr, id)))
			rem_sequence(xscr, seq);
		break;
	}
}
#endif				/* STARTUP_NOTIFICATION */

#if 0
/** @brief refresh desktop
  *
  * The current desktop has changed for the screen.  Update the root pixmaps for
  * the screen.  Whether the window manager is multihead aware can be determined
  * by checking the mhaware boolean on the screen structure.
  */
static void
refresh_desktop(XdeScreen *xscr)
{
	GdkWindow *root = gdk_screen_get_root_window(xscr->scrn);
	GdkColormap *cmap = gdk_drawable_get_colormap(GDK_DRAWABLE(root));
	GdkPixmap *pixmap;
	cairo_t *cr;
	XdeMonitor *xmon;
	XdeImage *im;
	XdePixmap *pm;
	int d, m;
	Pixmap pmap;

	/* render the current desktop on the screen */
	pmap = get_temporary_pixmap(xscr);
	DPRINTF(1, "using temporary pixmap (0x%08lx)\n", pmap);
	DPRINTF(1, "creating temporary pixmap contents\n");
	pixmap = gdk_pixmap_foreign_new_for_display(disp, pmap);
	gdk_drawable_set_colormap(GDK_DRAWABLE(pixmap), cmap);
	cr = gdk_cairo_create(GDK_DRAWABLE(pixmap));
	for (m = 0, xmon = xscr->mons; m < xscr->nmon; m++, xmon++) {
		DPRINTF(1, "adding monitor %d to pixmap\n", m);
		d = xmon->current;
		DPRINTF(1, "monitor %d current destop is %d\n", m, d);
		if ((im = xscr->backdrops[d]) && (im->pixbuf || im->file)) {
			DPRINTF(1, "monitor %d desktop %d has an image\n", m, d);
			for (pm = im->pixmaps; pm; pm = pm->next) {
				if (pm->geom.width == xmon->geom.width && pm->geom.height == xmon->geom.height)
					break;
			}
			if (!pm && !im->pixbuf) {
				DPRINTF(1, "creating pixbuf from file %s\n", im->file);
				im->pixbuf = gdk_pixbuf_new_from_file(im->file, NULL);
			}
			if (!pm && im->pixbuf) {
				GdkPixbuf *scaled;
				cairo_t *cr;

				DPRINTF(1, "allocating a new pixmap for image\n");
				pm = calloc(1, sizeof(*pm));
				pm->refs = 1;
				pm->index = im->index;
				if ((pm->next = im->pixmaps))
					pm->next->pprev = &pm->next;
				pm->pprev = &im->pixmaps;
				im->pixmaps = pm;
				pm->geom = xmon->geom;
				pm->pixmap =
				    gdk_pixmap_new(GDK_DRAWABLE(root), xmon->geom.width, xmon->geom.height, -1);
				gdk_drawable_set_colormap(GDK_DRAWABLE(pm->pixmap), cmap);
				cr = gdk_cairo_create(GDK_DRAWABLE(pm->pixmap));
				/* FIXME: tiling and other things.... */
				scaled = gdk_pixbuf_scale_simple(im->pixbuf,
								 pm->geom.width,
								 pm->geom.height, GDK_INTERP_BILINEAR);
				gdk_cairo_set_source_pixbuf(cr, scaled, 0, 0);
				cairo_paint(cr);
				cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
				cairo_destroy(cr);
				g_object_unref(scaled);
				if (im->pixbuf && im->file) {
					g_object_unref(im->pixbuf);
					im->pixbuf = NULL;
					/* save some resident memory */
				}
			} else
				DPRINTF(1, "using existing pixmap for image\n");
			gdk_cairo_rectangle(cr, &xmon->geom);
			if (pm) {
				DPRINTF(1, "painting pixmap into screen image\n");
				gdk_cairo_set_source_pixmap(cr, pm->pixmap, 0, 0);
				cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
				cairo_paint(cr);
			} else {
				/* FIXME: use color for desktop */
				DPRINTF(1, "painting color into screen image\n");
				cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
				cairo_paint(cr);
			}
		} else {
			DPRINTF(1, "monitor %d desktop %d has no image\n", m, d);
		}
	}
	cairo_destroy(cr);
	DPRINTF(1, "installing pixmap 0x%08lx as root pixmap\n", pmap);
	XChangeProperty(GDK_DISPLAY_XDISPLAY(disp), GDK_WINDOW_XID(root), _XA_XROOTPMAP_ID,
			XA_PIXMAP, 32, PropModeReplace, (unsigned char *) &pmap, 1);
	gdk_window_set_back_pixmap(root, pixmap, FALSE);
	gdk_window_clear(root);
	if (xscr->pixmap) {
		DPRINTF(1, "killing old unused temporary pixmap 0x%08lx\n", xscr->pixmap);
		XKillClient(GDK_DISPLAY_XDISPLAY(disp), xscr->pixmap);
	}
	xscr->pixmap = pmap;
}

/** @brief refresh monitor
  *
  * The current view for a multi-head aware window manager has changed.  Update
  * the background for the monitor.
  */
static void
refresh_monitor(XdeMonitor *xmon)
{
	PTRACE(5);
	/* for now */
	refresh_desktop(xmon->xscr);
}
#endif

static void
update_client_list(XdeScreen *xscr, Atom prop)
{
#if 0
	Window root = RootWindow(dpy, xscr->index);
	Atom actual = None;
	int format = 0;
	unsigned long nitems = 0, after = 0, num;
	unsigned long *data = NULL;
	GdkWindow *window;
	GdkWindowState state;
	GList *oldlist = NULL, **moldlist;
	GList *clients = NULL, **mclients;
	GList *stacked = NULL, **mstacked;
	GList *l;
	int i, m;

	if (prop == None || prop == _XA_WIN_CLIENT_LIST) {
	      try_harder1:
		if (XGetWindowProperty(dpy, root, _XA_WIN_CLIENT_LIST, 0L, 16,
				       False, XA_CARDINAL, &actual, &format,
				       &nitems, &after, (unsigned char **) &data)
		    == Success && format == 32) {
			if (after) {
				num += ((after + 1) >> 2);
				if (data) {
					XFree(data);
					data = NULL;
				}
				goto try_harder1;
			}
			for (i = 0; i < nitems; i++)
				if ((window = gdk_x11_window_foreign_new_for_display(disp, data[i])))
					oldlist = g_list_append(oldlist, window);
			if (data)
				XFree(data);
		}
	}
	if (prop == None || prop == _XA_NET_CLIENT_LIST) {
	      try_harder2:
		if (XGetWindowProperty(dpy, root, _XA_NET_CLIENT_LIST, 0L, 16,
				       False, XA_WINDOW, &actual, &format,
				       &nitems, &after, (unsigned char **) &data)
		    == Success && format == 32) {
			if (after) {
				num += ((after + 1) >> 2);
				if (data) {
					XFree(data);
					data = NULL;
				}
				goto try_harder2;
			}
			for (i = 0; i < nitems; i++)
				if ((window = gdk_x11_window_foreign_new_for_display(disp, data[i])))
					clients = g_list_append(clients, window);
			if (data)
				XFree(data);
		}
	}
	if (prop == None || prop == _XA_NET_CLIENT_LIST_STACKING) {
	      try_harder3:
		if (XGetWindowProperty(dpy, root, _XA_NET_CLIENT_LIST, 0L, 16,
				       False, XA_WINDOW, &actual, &format,
				       &nitems, &after, (unsigned char **) &data)
		    == Success && format == 32) {
			if (after) {
				num += ((after + 1) >> 2);
				if (data) {
					XFree(data);
					data = NULL;
				}
				goto try_harder3;
			}
			for (i = 0; i < nitems; i++)
				if ((window = gdk_x11_window_foreign_new_for_display(disp, data[i])))
					stacked = g_list_append(stacked, window);
			if (data)
				XFree(data);
		}
	}
	moldlist = calloc(xscr->nmon, sizeof(*moldlist));
	for (i = 0; i < xscr->nmon; i++) {
		for (l = oldlist; l; l = l->next) {
			window = l->data;
			state = gdk_window_get_state(window);
			if (state & (GDK_WINDOW_STATE_WITHDRAWN | GDK_WINDOW_STATE_ICONIFIED))
				continue;
			m = gdk_screen_get_monitor_at_window(xscr->scrn, window);
			g_object_ref(G_OBJECT(window));
			moldlist[m] = g_list_append(moldlist[m], window);
		}
	}
	mclients = calloc(xscr->nmon, sizeof(*mclients));
	for (i = 0; i < xscr->nmon; i++) {
		for (l = clients; l; l = l->next) {
			window = l->data;
			state = gdk_window_get_state(window);
			if (state & (GDK_WINDOW_STATE_WITHDRAWN | GDK_WINDOW_STATE_ICONIFIED))
				continue;
			m = gdk_screen_get_monitor_at_window(xscr->scrn, window);
			g_object_ref(G_OBJECT(window));
			mclients[m] = g_list_append(mclients[m], window);
		}
	}
	mstacked = calloc(xscr->nmon, sizeof(*mstacked));
	for (i = 0; i < xscr->nmon; i++) {
		for (l = stacked; l; l = l->next) {
			window = l->data;
			state = gdk_window_get_state(window);
			if (state & (GDK_WINDOW_STATE_WITHDRAWN | GDK_WINDOW_STATE_ICONIFIED))
				continue;
			m = gdk_screen_get_monitor_at_window(xscr->scrn, window);
			g_object_ref(G_OBJECT(window));
			mstacked[m] = g_list_append(mstacked[m], window);
		}
	}
#endif
}

static void
update_screen_active_window(XdeScreen *xscr)
{
}

static void
update_monitor_active_window(XdeMonitor *xmon)
{
}

static void
update_active_window(XdeScreen *xscr, Atom prop)
{
	Window root = RootWindow(dpy, xscr->index);
	Atom actual = None;
	int format = 0;
	unsigned long nitems = 0, after = 0;
	unsigned long *data = NULL;
	int i, j = 0, *x;
	Window *active;
	GdkWindow **window;
	XdeMonitor *xmon;

	PTRACE(5);
	active = calloc(xscr->nmon + 1, sizeof(*active));
	window = calloc(xscr->nmon + 1, sizeof(*window));

	if (prop == None || prop == _XA_WIN_FOCUS) {
		if (XGetWindowProperty(dpy, root, _XA_WIN_FOCUS,
				       0, 64, False, XA_CARDINAL, &actual, &format,
				       &nitems, &after, (unsigned char **) &data) == Success &&
		    format == 32 && nitems >= 1 && data) {
			active[0] = data[0];
			if (nitems > 1 && nitems == xscr->nmon) {
				xscr->mhaware = True;
				x = &i;
			} else
				x = &j;
			for (i = 0; i < nitems; i++)
				active[i + 1] = data[*x];
			XFree(data);
		}
	}
	if (prop == None || prop == _XA_NET_ACTIVE_WINDOW) {
		if (XGetWindowProperty(dpy, root, _XA_NET_ACTIVE_WINDOW,
				       0, 64, False, XA_WINDOW, &actual, &format,
				       &nitems, &after, (unsigned char **) &data) == Success &&
		    format == 32 && nitems >= 1 && data) {
			active[0] = data[0];
			if (nitems > 1 && nitems == xscr->nmon) {
				xscr->mhaware = True;
				x = &i;
			} else
				x = &j;
			for (i = 0; i < nitems; i++)
				active[i + 1] = data[*x];
			XFree(data);
		}
	}
	window[0] = gdk_x11_window_foreign_new_for_display(disp, active[0]);
	if (xscr->active.now != window[0]) {
		if (xscr->active.old)
			g_object_unref(xscr->active.old);
		xscr->active.old = xscr->active.now;
		xscr->active.now = window[0];
		update_screen_active_window(xscr);
	}
	for (i = 0, xmon = xscr->mons; i < xscr->nmon; i++, xmon++) {
		if ((window[i + 1] = gdk_x11_window_foreign_new_for_display(disp, active[i + 1]))) {
			if ((i != gdk_screen_get_monitor_at_window(xscr->scrn, window[i + 1]))) {
				g_object_unref(G_OBJECT(window[i + 1]));
				window[i + 1] = NULL;
				continue;
			}
			if (xmon->active.old)
				g_object_unref(xscr->active.old);
			xscr->active.old = xscr->active.now;
			xscr->active.now = window[i + 1];
			update_monitor_active_window(xmon);
		}
	}
	free(active);
	free(window);
}

static void
update_screen_size(XdeScreen *xscr, int new_width, int new_height)
{
}

static void
create_monitor(XdeScreen *xscr, XdeMonitor *xmon, int m)
{
	memset(xmon, 0, sizeof(*xmon));
	xmon->index = m;
	xmon->xscr = xscr;
	gdk_screen_get_monitor_geometry(xscr->scrn, m, &xmon->geom);
}

static void
delete_monitor(XdeScreen *xscr, XdeMonitor *mon, int m)
{
}

static void
update_monitor(XdeScreen *xscr, XdeMonitor *mon, int m)
{
	gdk_screen_get_monitor_geometry(xscr->scrn, m, &mon->geom);
}

#if 0
static void
update_root_pixmap(XdeScreen *xscr, Atom prop)
{
	Window root = RootWindow(dpy, xscr->index);
	Atom actual = None;
	int format = 0;
	unsigned long nitems = 0, after = 0;
	unsigned long *data = NULL;
	Pixmap pmap = None;

	PTRACE(5);
	if (prop == None || prop == _XA_ESETROOT_PMAP_ID) {
		if (XGetWindowProperty
		    (dpy, root, _XA_ESETROOT_PMAP_ID, 0, 1, False, AnyPropertyType, &actual,
		     &format, &nitems, &after, (unsigned char **) &data) == Success
		    && format == 32 && actual && nitems >= 1 && data) {
			pmap = data[0];
		}
		if (data) {
			XFree(data);
			data = NULL;
		}
	}
	if (prop == None || prop == _XA_XROOTPMAP_ID) {
		if (XGetWindowProperty
		    (dpy, root, _XA_XROOTPMAP_ID, 0, 1, False, AnyPropertyType, &actual,
		     &format, &nitems, &after, (unsigned char **) &data) == Success
		    && format == 32 && actual && nitems >= 1 && data) {
			pmap = data[0];
		}
		if (data) {
			XFree(data);
			data = NULL;
		}
	}
	if (pmap && xscr->pixmap != pmap) {
		DPRINTF(1, "root pixmap changed from 0x%08lx to 0x%08lx\n", xscr->pixmap, pmap);
		xscr->pixmap = pmap;
		/* FIXME: do more */
		/* Adjust the style of the desktop to use the pixmap specified by
		   _XROOTPMAP_ID as the background.  Uses GTK+ 2.0 styles to do this. The
		   root _XROOTPMAP_ID must be retrieved before calling this function for
		   it to work correctly.  */
	}
}
#endif

#if 0
static void
update_current_desktop(XdeScreen *xscr, Atom prop)
{
	Window root = RootWindow(dpy, xscr->index);
	Atom actual = None;
	int format = 0;
	unsigned long nitems = 0, after = 0, i, j = 0, *x;
	unsigned long *data = NULL;
	XdeMonitor *xmon;
	unsigned long *current;

	PTRACE(5);
	current = calloc(xscr->nmon + 1, sizeof(*current));

	if (prop == None || prop == _XA_WM_DESKTOP) {
		if (XGetWindowProperty(dpy, root, _XA_WM_DESKTOP, 0, 64, False,
				       XA_CARDINAL, &actual, &format, &nitems, &after,
				       (unsigned char **) &data) == Success &&
		    format == 32 && actual && nitems >= 1 && data) {
			current[0] = data[0];
			x = (xscr->mhaware = (nitems >= xscr->nmon)) ? &i : &j;
			for (i = 0; i < xscr->nmon; i++)
				current[i + 1] = data[*x];
		}
		if (data) {
			XFree(data);
			data = NULL;
		}
	}
	if (prop == None || prop == _XA_WIN_WORKSPACE) {
		if (XGetWindowProperty(dpy, root, _XA_WIN_WORKSPACE, 0, 64, False,
				       XA_CARDINAL, &actual, &format, &nitems, &after,
				       (unsigned char **) &data) == Success &&
		    format == 32 && actual && nitems >= 1 && data) {
			current[0] = data[0];
			x = (xscr->mhaware = (nitems >= xscr->nmon)) ? &i : &j;
			for (i = 0; i < xscr->nmon; i++)
				current[i + 1] = data[*x];
		}
		if (data) {
			XFree(data);
			data = NULL;
		}
	}
	if (prop == None || prop == _XA_NET_CURRENT_DESKTOP) {
		if (XGetWindowProperty(dpy, root, _XA_NET_CURRENT_DESKTOP, 0, 64, False,
				       XA_CARDINAL, &actual, &format, &nitems, &after,
				       (unsigned char **) &data) == Success &&
		    format == 32 && actual && nitems >= 1 && data) {
			current[0] = data[0];
			x = (xscr->mhaware = (nitems >= xscr->nmon)) ? &i : &j;
			for (i = 0; i < xscr->nmon; i++)
				current[i + 1] = data[*x];
		}
		if (data) {
			XFree(data);
			data = NULL;
		}
	}
	/* There are two things to do when the workspace changes: */
	/* First off, drop any cycle or task windows that we have open. */
	/* Second, queue deferred action to refresh pixmaps on the desktop. */
	/* Third, pop the pager window. */
	if (xscr->current != current[0]) {
		xscr->current = current[0];
		if (xscr->setbg)
			add_deferred_refresh_desktop(xscr);
		DPRINTF(1, "Current desktop for screen %d changed.\n", xscr->index);
		if (xscr->pager) {
		}
	}
	for (i = 0, xmon = xscr->mons; i < xscr->nmon; i++, xmon++) {
		if (xmon->current != current[i + 1]) {
			xmon->current = current[i + 1];
			if (xscr->setbg)
				add_deferred_refresh_monitor(xmon);
			DPRINTF(1, "Current view for monitor %d chaged.\n", xmon->index);
			if (xscr->pager) {
			}
		}
	}
	free(current);
}

static GdkFilterReturn
proxy_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;
	XdeScreen *xscr = (typeof(xscr)) data;
	int num;

	PTRACE(5);
	if (!xscr) {
		EPRINTF("xscr is NULL\n");
		exit(EXIT_FAILURE);
	}
	switch (xev->type) {
	case ButtonPress:
		if (options.debug) {
			fprintf(stderr, "==> ButtonPress: %p\n", xscr);
			fprintf(stderr, "    --> send_event = %s\n", xev->xbutton.send_event ? "true" : "false");
			fprintf(stderr, "    --> window = 0x%lx\n", xev->xbutton.window);
			fprintf(stderr, "    --> root = 0x%lx\n", xev->xbutton.root);
			fprintf(stderr, "    --> subwindow = 0x%lx\n", xev->xbutton.subwindow);
			fprintf(stderr, "    --> time = %lu\n", xev->xbutton.time);
			fprintf(stderr, "    --> x = %d\n", xev->xbutton.x);
			fprintf(stderr, "    --> y = %d\n", xev->xbutton.y);
			fprintf(stderr, "    --> x_root = %d\n", xev->xbutton.x_root);
			fprintf(stderr, "    --> y_root = %d\n", xev->xbutton.y_root);
			fprintf(stderr, "    --> state = 0x%08x\n", xev->xbutton.state);
			fprintf(stderr, "    --> button = %u\n", xev->xbutton.button);
			fprintf(stderr, "    --> same_screen = %s\n", xev->xbutton.same_screen ? "true" : "false");
			fprintf(stderr, "<== ButtonPress: %p\n", xscr);
		}
		switch (xev->xbutton.button) {
		case 4:
			update_current_desktop(xscr, None);
			num = (xscr->current - 1 + xscr->desks) % xscr->desks;
#if 0
			set_current_desktop(xscr, num, xev->xbutton.time);
			return GDK_FILTER_REMOVE;
#else
			(void) num;
			break;
#endif
		case 5:
			update_current_desktop(xscr, None);
			num = (xscr->current + 1 + xscr->desks) % xscr->desks;
#if 0
			set_current_desktop(xscr, num, xev->xbutton.time);
			return GDK_FILTER_REMOVE;
#else
			(void) num;
			break;
#endif
		}
		return GDK_FILTER_CONTINUE;
	case ButtonRelease:
		if (options.debug > 1) {
			fprintf(stderr, "==> ButtonRelease: %p\n", xscr);
			fprintf(stderr, "    --> send_event = %s\n", xev->xbutton.send_event ? "true" : "false");
			fprintf(stderr, "    --> window = 0x%lx\n", xev->xbutton.window);
			fprintf(stderr, "    --> root = 0x%lx\n", xev->xbutton.root);
			fprintf(stderr, "    --> subwindow = 0x%lx\n", xev->xbutton.subwindow);
			fprintf(stderr, "    --> time = %lu\n", xev->xbutton.time);
			fprintf(stderr, "    --> x = %d\n", xev->xbutton.x);
			fprintf(stderr, "    --> y = %d\n", xev->xbutton.y);
			fprintf(stderr, "    --> x_root = %d\n", xev->xbutton.x_root);
			fprintf(stderr, "    --> y_root = %d\n", xev->xbutton.y_root);
			fprintf(stderr, "    --> state = 0x%08x\n", xev->xbutton.state);
			fprintf(stderr, "    --> button = %u\n", xev->xbutton.button);
			fprintf(stderr, "    --> same_screen = %s\n", xev->xbutton.same_screen ? "true" : "false");
			fprintf(stderr, "<== ButtonRelease: %p\n", xscr);
		}
		return GDK_FILTER_CONTINUE;
	case PropertyNotify:
		if (options.debug > 2) {
			char *name = NULL;

			fprintf(stderr, "==> PropertyNotify:\n");
			fprintf(stderr, "    --> window = 0x%08lx\n", xev->xproperty.window);
			fprintf(stderr, "    --> atom = %s\n", (name = XGetAtomName(dpy, xev->xproperty.atom)));
			fprintf(stderr, "    --> time = %ld\n", xev->xproperty.time);
			fprintf(stderr, "    --> state = %s\n",
				(xev->xproperty.state == PropertyNewValue) ? "NewValue" : "Delete");
			fprintf(stderr, "<== PropertyNotify:\n");
			if (name)
				XFree(name);
		}
		return GDK_FILTER_CONTINUE;
	}
	EPRINTF("wrong message type for handler %d on window 0x%08lx\n", xev->type, xev->xany.window);
	return GDK_FILTER_CONTINUE;
}

static void
refresh_layout(XdeScreen *xscr)
{
	if (options.show.pager) {
		unsigned int w, h, f, wmax, hmax;
		int i;

		w = xscr->width * xscr->cols;
		h = xscr->height * xscr->rows;
		for (i = 0; i < xscr->nmon; i++) {
			XdeMonitor *xmon = &xscr->mons[i];

			wmax = (xmon->geom.width * 8) / 10;
			hmax = (xmon->geom.height * 8) / 10;
			for (f = 10; w > wmax * f || h > hmax * f; f++) ;
			if (xmon->pager.popup)
				gtk_window_set_default_size(GTK_WINDOW(xmon->pager.popup), w / f, h / f);
		}
	}
	if (options.show.setbg) {
		int n, d;

		/* redistribute images over desktops */
		DPRINTF(1, "There are %d desktops\n", xscr->ndsk);
		for (d = 0; d < xscr->ndsk; d++) {
			DPRINTF(1, "Attempting to unref image %d (desktops is %p)\n", d, xscr->backdrops + d);
			xde_image_unref(xscr->backdrops + d);
		}
		d = xscr->ndsk = xscr->desks;
		DPRINTF(1, "Reallocating %d desktops\n", (int) d);
		xscr->backdrops = realloc(xscr->backdrops, d * sizeof(*xscr->backdrops));
		memset(xscr->backdrops, 0, d * sizeof(*xscr->backdrops));
		if (xscr->nimg)
			for (n = 0, d = 0; d < xscr->ndsk; d++, n = (n + 1) % xscr->nimg) {
				DPRINTF(1, "desktop %d assigned source image %d\n", d, n);
				xde_image_ref((xscr->backdrops[d] = xscr->sources[n]));
			}
		refresh_desktop(xscr);
	}
}
#endif

#if 0
static void
update_layout(XdeScreen *xscr, Atom prop)
{
	Window root = RootWindow(dpy, xscr->index);
	Atom actual = None;
	int format = 0, num, desks = xscr->desks;
	unsigned long nitems = 0, after = 0;
	unsigned long *data = NULL;
	Bool propok = False, layout_changed = False, number_changed = False;

	PTRACE(5);
	if (prop == None || prop == _XA_NET_DESKTOP_LAYOUT) {
		if (XGetWindowProperty
		    (dpy, root, _XA_NET_DESKTOP_LAYOUT, 0, 4, False, AnyPropertyType, &actual,
		     &format, &nitems, &after, (unsigned char **) &data) == Success
		    && format == 32 && actual && nitems >= 4 && data) {
			if (xscr->cols != (int) data[1] || xscr->rows != (int) data[2]) {
				xscr->cols = data[1];
				xscr->rows = data[2];
				layout_changed = True;
			}
		}
		if (data) {
			XFree(data);
			data = NULL;
		}
		propok = True;
	}
	if (prop == None || prop == _XA_WIN_WORKSPACE_COUNT) {
		if (XGetWindowProperty
		    (dpy, root, _XA_WIN_WORKSPACE_COUNT, 0, 1, False, XA_CARDINAL, &actual,
		     &format, &nitems, &after, (unsigned char **) &data) == Success
		    && format == 32 && actual && nitems >= 1 && data) {
			if (xscr->desks != (int) data[0]) {
				xscr->desks = data[0];
				number_changed = True;
			}
		}
		if (data) {
			XFree(data);
			data = NULL;
		}
		propok = True;
	}
	if (prop == None || prop == _XA_NET_NUMBER_OF_DESKTOPS) {
		if (XGetWindowProperty
		    (dpy, root, _XA_NET_NUMBER_OF_DESKTOPS, 0, 1, False, XA_CARDINAL, &actual,
		     &format, &nitems, &after, (unsigned char **) &data) == Success
		    && format == 32 && actual && nitems >= 1 && data) {
			if (xscr->desks != (int) data[0]) {
				xscr->desks = data[0];
				number_changed = True;
			}
		}
		if (data) {
			XFree(data);
			data = NULL;
		}
		propok = True;
	}
	if (!propok)
		EPRINTF("wrong property passed\n");

	if (number_changed) {
		if (xscr->desks <= 0)
			xscr->desks = 1;
		if (xscr->desks > 64)
			xscr->desks = 64;
		if (xscr->desks == desks)
			number_changed = False;
	}
	if (layout_changed || number_changed) {
		if (xscr->rows <= 0 && xscr->cols <= 0) {
			xscr->rows = 1;
			xscr->cols = 0;
		}
		if (xscr->cols > xscr->desks) {
			xscr->cols = xscr->desks;
			xscr->rows = 1;
		}
		if (xscr->rows > xscr->desks) {
			xscr->rows = xscr->desks;
			xscr->cols = 1;
		}
		if (xscr->cols == 0)
			for (num = xscr->desks; num > 0; xscr->cols++, num -= xscr->rows) ;
		if (xscr->rows == 0)
			for (num = xscr->desks; num > 0; xscr->rows++, num -= xscr->cols) ;
#if 0
		// refresh_layout(xscr); /* XXX: should be deferred */
		add_deferred_refresh_layout(xscr);
#endif
	}
}
#endif

static void
update_icon_theme(XdeScreen *xscr, Atom prop)
{
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
				char *rc_string;

				rc_string = g_strdup_printf("gtk-icon-theme-name=\"%s\"", list[0]);
				gtk_rc_parse_string(rc_string);
				g_free(rc_string);
				if (!xscr->itheme || strcmp(xscr->itheme, list[0])) {
					free(xscr->itheme);
					xscr->itheme = strdup(list[0]);
					changed = True;
				}
			}
			if (list)
				XFreeStringList(list);
		} else {
			char *name = NULL;

			EPRINTF("could not get text list for %s property\n", (name = XGetAtomName(dpy, prop)));
			if (name)
				XFree(name);
		}
		if (xtp.value)
			XFree(xtp.value);
	} else {
		char *name = NULL;

		DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
		if (name)
			XFree(name);
	}
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
		DPRINTF(1, "New icon theme is %s\n", xscr->itheme);
		/* FIXME: do something more about it. */
	}
}

static void
update_theme(XdeScreen *xscr, Atom prop)
{
	Window root = RootWindow(dpy, xscr->index);
	XTextProperty xtp = { NULL, };
	Bool changed = False;
	GtkSettings *set;

	PTRACE(5);
	gtk_rc_reparse_all();
	if (!prop || prop == _XA_GTK_READ_RCFILES)
		prop = _XA_XDE_THEME_NAME;
	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		char **list = NULL;
		int strings = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, &list, &strings) == Success) {
			if (strings >= 1) {
				char *rc_string;

				rc_string = g_strdup_printf("gtk-theme-name=\"%s\"", list[0]);
				gtk_rc_parse_string(rc_string);
				g_free(rc_string);
				if (!xscr->theme || strcmp(xscr->theme, list[0])) {
					free(xscr->theme);
					xscr->theme = strdup(list[0]);
					changed = True;
				}
			}
			if (list)
				XFreeStringList(list);
		} else {
			char *name = NULL;

			EPRINTF("could not get text list for %s property\n", (name = XGetAtomName(dpy, prop)));
			if (name)
				XFree(name);
		}
		if (xtp.value)
			XFree(xtp.value);
	} else {
		char *name = NULL;

		DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
		if (name)
			XFree(name);
	}
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
		DPRINTF(1, "New theme is %s\n", xscr->theme);
		/* FIXME: do something more about it. */
#if 0
		if (options.show.setbg)
			read_theme(xscr);
#endif
	} else
		DPRINTF(1, "No change in current theme %s\n", xscr->theme);
}

static void
update_screen(XdeScreen *xscr)
{
#if 0
	if (options.show.setbg)
		update_root_pixmap(xscr, None);
	update_layout(xscr, None);
	update_current_desktop(xscr, None);
#endif
	update_theme(xscr, None);
	update_icon_theme(xscr, None);
}

static void
refresh_screen(XdeScreen *xscr, GdkScreen *scrn)
{
	XdeMonitor *mon;
	int m, nmon, width, height, index;

	index = gdk_screen_get_number(scrn);
	if (xscr->index != index) {
		EPRINTF("Arrrghhh! screen index changed from %d to %d\n", xscr->index, index);
		xscr->index = index;
	}
	if (xscr->scrn != scrn) {
		DPRINTF(1, "Arrrghhh! screen pointer changed from %p to %p\n", xscr->scrn, scrn);
		xscr->scrn = scrn;
	}
	width = gdk_screen_get_width(scrn);
	height = gdk_screen_get_height(scrn);
	DPRINTF(1, "Screen %d dimensions are %dx%d\n", index, width, height);
	if (xscr->width != width || xscr->height != height) {
		DPRINTF(1, "Screen %d dimensions changed %dx%d -> %dx%d\n", index,
			xscr->width, xscr->height, width, height);
		/* FIXME: reset size of screen */
		update_screen_size(xscr, width, height);
		xscr->width = width;
		xscr->height = height;
	}
	nmon = gdk_screen_get_n_monitors(scrn);
	DPRINTF(1, "Reallocating %d monitors\n", nmon);
	xscr->mons = realloc(xscr->mons, nmon * sizeof(*xscr->mons));
	if (nmon > xscr->nmon) {
		DPRINTF(1, "Screen %d number of monitors increased from %d to %d\n", index, xscr->nmon, nmon);
		for (m = xscr->nmon; m < nmon; m++) {
			mon = xscr->mons + m;
			create_monitor(xscr, mon, m);
		}
	} else if (nmon < xscr->nmon) {
		DPRINTF(1, "Screen %d number of monitors decreased from %d to %d\n", index, xscr->nmon, nmon);
		for (m = nmon; m < xscr->nmon; m++) {
			mon = xscr->mons + m;
			delete_monitor(xscr, mon, m);
		}
	}
	if (nmon != xscr->nmon)
		xscr->nmon = nmon;
	for (m = 0, mon = xscr->mons; m < nmon; m++, mon++)
		update_monitor(xscr, mon, m);
	update_screen(xscr);
}

/** @brief monitors changed
  *
  * Emitted when the number, size or position of the monitors attached to the screen change.  The
  * number and/or size of monitors belonging to a screen have changed.  This may be as a result of
  * RANDR or XINERAMA changes.  Walk through the monitors and adjust the necessary parameters.
  */
static void
monitors_changed(GdkScreen *scrn, gpointer user_data)
{
	XdeScreen *xscr = user_data;

	wnck_screen_force_update(xscr->wnck);
	refresh_screen(xscr, scrn);
#if 0
	refresh_layout(xscr);
	if (options.show.setbg)
		read_theme(xscr);
#endif
}

/** @brief screen size changed
  *
  * The size (pixel width or height) of the screen changed.  This may be as a result of RANDR or
  * XINERAMA changes.  Walk through the screen and the monitors on the screen and adjust the
  * necessary parameters.
  */
static void
size_changed(GdkScreen *scrn, gpointer user_data)
{
	XdeScreen *xscr = user_data;

	wnck_screen_force_update(xscr->wnck);
	refresh_screen(xscr, scrn);
#if 0
	refresh_layout(xscr);
	if (options.show.setbg)
		read_theme(xscr);
#endif
}

static void
popup_show(XdeScreen *xscr)
{
	menu_show(xscr);
}

static GdkFilterReturn
event_handler_ClientMessage(XEvent *xev)
{
	XdeScreen *xscr = NULL;
	int s, nscr = ScreenCount(dpy);
	Atom type = xev->xclient.message_type;
	char *name = NULL;

	PTRACE(5);
	for (s = 0; s < nscr; s++)
		if (xev->xclient.window == RootWindow(dpy, s)) {
			xscr = screens + s;
			break;
		}
	if (!xscr) {
#if 0
		if (type != _XA_NET_STARTUP_INFO && type != _XA_NET_STARTUP_INFO_BEGIN)
#endif
			EPRINTF("could not find screen for client message %s with window 0%08lx\n",
				name ? : (name = XGetAtomName(dpy, type)), xev->xclient.window);
		xscr = screens;
	}
	if (options.debug > 1) {
		fprintf(stderr, "==> ClientMessage: %p\n", xscr);
		fprintf(stderr, "    --> window = 0x%08lx\n", xev->xclient.window);
		fprintf(stderr, "    --> message_type = %s\n", name ? : (name = XGetAtomName(dpy, type)));
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
			for (i = 0; i < 5; i++)
				fprintf(stderr, " %08lx", xev->xclient.data.l[i]);
			fprintf(stderr, "\n");
			break;
		}
		fprintf(stderr, "<== ClientMessage: %p\n", xscr);
	}
	if (name) {
		XFree(name);
		name = NULL;
	}
	if (type == _XA_GTK_READ_RCFILES) {
		update_theme(xscr, type);
		update_icon_theme(xscr, type);
		return GDK_FILTER_REMOVE;	/* event handled */
	} else if (type == _XA_PREFIX_REFRESH) {
		set_scmon(xev->xclient.data.l[1]);
		set_flags(xev->xclient.data.l[2]);
		set_word1(xev->xclient.data.l[3]);
		set_word2(xev->xclient.data.l[4]);
		popup_refresh(xscr);
		return GDK_FILTER_REMOVE;
	} else if (type == _XA_PREFIX_RESTART) {
		set_scmon(xev->xclient.data.l[1]);
		set_flags(xev->xclient.data.l[2]);
		set_word1(xev->xclient.data.l[3]);
		set_word2(xev->xclient.data.l[4]);
		popup_restart();
		return GDK_FILTER_REMOVE;
	} else if (type == _XA_PREFIX_POPMENU) {
		set_scmon(xev->xclient.data.l[1]);
		set_flags(xev->xclient.data.l[2]);
		set_word1(xev->xclient.data.l[3]);
		set_word2(xev->xclient.data.l[4]);
		menu_show(xscr);
		return GDK_FILTER_REMOVE;
	} else if (type == _XA_PREFIX_EDITOR) {
		set_scmon(xev->xclient.data.l[1]);
		set_flags(xev->xclient.data.l[2]);
		set_word1(xev->xclient.data.l[3]);
		set_word2(xev->xclient.data.l[4]);
		popup_show(xscr);
		return GDK_FILTER_REMOVE;
	}
#if 0
	if (type == _XA_NET_STARTUP_INFO) {
		return sn_display_process_event(sn_dpy, xev);
	} else if (type == _XA_NET_STARTUP_INFO_BEGIN) {
		return sn_display_process_event(sn_dpy, xev);
	}
#endif
	return GDK_FILTER_CONTINUE;	/* event not handled */
}

static GdkFilterReturn
client_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;

	PTRACE(5);
	switch (xev->type) {
	case ClientMessage:
		return event_handler_ClientMessage(xev);
	}
	EPRINTF("wrong message type for handler %d\n", xev->type);
	return GDK_FILTER_CONTINUE;	/* event not handled, continue processing */
}

static GdkFilterReturn
event_handler_SelectionClear(XEvent *xev, XdeScreen *xscr)
{
	PTRACE(5);
	if (options.debug > 1) {
		char *name = NULL;

		fprintf(stderr, "==> SelectionClear: %p\n", xscr);
		fprintf(stderr, "    --> send_event = %s\n", xev->xselectionclear.send_event ? "true" : "false");
		fprintf(stderr, "    --> window = 0x%08lx\n", xev->xselectionclear.window);
		fprintf(stderr, "    --> selection = %s\n", (name = XGetAtomName(dpy, xev->xselectionclear.selection)));
		fprintf(stderr, "    --> time = %lu\n", xev->xselectionclear.time);
		fprintf(stderr, "<== SelectionClear: %p\n", xscr);
		if (name)
			XFree(name);
	}
	if (xscr && xev->xselectionclear.window == xscr->selwin) {
		XDestroyWindow(dpy, xscr->selwin);
		EPRINTF("selection cleared, exiting\n");
#if 1
		if (smcConn) {
			/* Care must be taken where if we are running under a session
			   manager. We set the restart hint to SmRestartImmediately which
			   means that the session manager will re-execute us if we exit.
			   We should really request a local shutdown. */
			SmcRequestSaveYourself(smcConn, SmSaveLocal, True, SmInteractStyleNone, False, False);
			return GDK_FILTER_CONTINUE;
		}
		exit(EXIT_SUCCESS);
#endif
		mainloop_quit();
		return GDK_FILTER_REMOVE;
	}
	if (xscr && xev->xselectionclear.window == xscr->laywin) {
		XDestroyWindow(dpy, xscr->laywin);
		xscr->laywin = None;
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
selwin_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;
	XdeScreen *xscr = data;

	PTRACE(5);
	switch (xev->type) {
	case SelectionClear:
		return event_handler_SelectionClear(xev, xscr);
	}
	EPRINTF("wrong message type for handler %d\n", xev->type);
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
laywin_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;
	XdeScreen *xscr = data;

	PTRACE(5);
	if (!xscr) {
		EPRINTF("xscr is NULL\n");
		exit(EXIT_FAILURE);
	}
	switch (xev->type) {
	case SelectionClear:
		return event_handler_SelectionClear(xev, xscr);
	}
	EPRINTF("wrong message type for handler %d\n", xev->type);
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
event_handler_PropertyNotify(XEvent *xev, XdeScreen *xscr)
{
	Atom atom;

	PTRACE(5);
	if (options.debug > 2) {
		char *name = NULL;

		fprintf(stderr, "==> PropertyNotify:\n");
		fprintf(stderr, "    --> window = 0x%08lx\n", xev->xproperty.window);
		fprintf(stderr, "    --> atom = %s\n", (name = XGetAtomName(dpy, xev->xproperty.atom)));
		fprintf(stderr, "    --> time = %ld\n", xev->xproperty.time);
		fprintf(stderr, "    --> state = %s\n",
			(xev->xproperty.state == PropertyNewValue) ? "NewValue" : "Delete");
		fprintf(stderr, "<== PropertyNotify:\n");
		if (name)
			XFree(name);
	}
	atom = xev->xproperty.atom;
	if (xev->xproperty.state == PropertyNewValue) {
		if (atom == _XA_XDE_THEME_NAME || atom == _XA_XDE_WM_THEME) {
			update_theme(xscr, atom);
			return GDK_FILTER_REMOVE;	/* event handled */
		} else if (atom == _XA_XDE_ICON_THEME_NAME || atom == _XA_XDE_WM_ICONTHEME) {
			update_icon_theme(xscr, atom);
			return GDK_FILTER_REMOVE;	/* event handled */
#if 0
		} else if (atom == _XA_NET_DESKTOP_LAYOUT) {
			update_layout(xscr, atom);
		} else if (atom == _XA_NET_NUMBER_OF_DESKTOPS) {
			update_layout(xscr, atom);
		} else if (atom == _XA_WIN_WORKSPACE_COUNT) {
			update_layout(xscr, atom);
#endif
#if 0
		} else if (atom == _XA_NET_CURRENT_DESKTOP) {
			update_current_desktop(xscr, atom);
		} else if (atom == _XA_WIN_WORKSPACE) {
			update_current_desktop(xscr, atom);
		} else if (atom == _XA_WM_DESKTOP) {
			update_current_desktop(xscr, atom);
#endif
#if 0
		} else if (atom == _XA_XROOTPMAP_ID) {
			update_root_pixmap(xscr, atom);
		} else if (atom == _XA_ESETROOT_PMAP_ID) {
			update_root_pixmap(xscr, atom);
#endif
		} else if (atom == _XA_NET_ACTIVE_WINDOW) {
			update_active_window(xscr, atom);
#if 0
		} else if (atom == _XA_NET_CLIENT_LIST) {
			update_client_list(xscr, atom);
		} else if (atom == _XA_NET_CLIENT_LIST_STACKING) {
			update_client_list(xscr, atom);
#endif
		} else if (atom == _XA_WIN_FOCUS) {
			update_active_window(xscr, atom);
#if 0
		} else if (atom == _XA_WIN_CLIENT_LIST) {
			update_client_list(xscr, atom);
#endif
		}
	}
	return GDK_FILTER_CONTINUE;	/* event not handled */
}

static GdkFilterReturn
root_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	XEvent *xev = (typeof(xev)) xevent;
	XdeScreen *xscr = data;

	PTRACE(5);
	switch (xev->type) {
	case PropertyNotify:
		return event_handler_PropertyNotify(xev, xscr);
	}
	return GDK_FILTER_CONTINUE;
}

static GdkFilterReturn
events_handler(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{
	return GDK_FILTER_CONTINUE;
}

int
handler(Display *display, XErrorEvent *xev)
{
	if (options.debug) {
		char msg[80], req[80], num[80], def[80];

		snprintf(num, sizeof(num), "%d", xev->request_code);
		snprintf(def, sizeof(def), "[request_code=%d]", xev->request_code);
		XGetErrorDatabaseText(dpy, NAME, num, def, req, sizeof(req));
		if (XGetErrorText(dpy, xev->error_code, msg, sizeof(msg)) != Success)
			msg[0] = '\0';
		fprintf(stderr, "X error %s(0x%08lx): %s\n", req, xev->resourceid, msg);
		dumpstack(__FILE__, __LINE__, __func__);
	}
	return (0);
}

int
iohandler(Display *display)
{
	dumpstack(__FILE__, __LINE__, __func__);
	exit(EXIT_FAILURE);
}

int (*oldhandler) (Display *, XErrorEvent *) = NULL;
int (*oldiohandler) (Display *) = NULL;

gboolean
hup_signal_handler(gpointer data)
{
	/* perform reload */
	return G_SOURCE_CONTINUE;
}

gboolean
int_signal_handler(gpointer data)
{
	exit(EXIT_SUCCESS);
	return G_SOURCE_CONTINUE;
}

gboolean
term_signal_handler(gpointer data)
{
	mainloop_quit();
	return G_SOURCE_CONTINUE;
}

/** @} */

/** @} */

/** @section Initialization
  * @{ */

static void
init_monitors(XdeScreen *xscr)
{
	XdeMonitor *xmon;
	int m;

	g_signal_connect(G_OBJECT(xscr->scrn), "monitors-changed", G_CALLBACK(monitors_changed), xscr);
	g_signal_connect(G_OBJECT(xscr->scrn), "size-changed", G_CALLBACK(size_changed), xscr);

	xscr->nmon = gdk_screen_get_n_monitors(xscr->scrn);
	xscr->mons = calloc(xscr->nmon, sizeof(*xscr->mons));
	for (m = 0, xmon = xscr->mons; m < xscr->nmon; m++, xmon++) {
		xmon->index = m;
		xmon->xscr = xscr;
		gdk_screen_get_monitor_geometry(xscr->scrn, m, &xmon->geom);
	}
}

static void
init_wnck(XdeScreen *xscr)
{
	WnckScreen *wnck = xscr->wnck = wnck_screen_get(xscr->index);

	g_signal_connect(G_OBJECT(wnck), "window_manager_changed", G_CALLBACK(window_manager_changed), xscr);
	g_signal_connect(G_OBJECT(wnck), "workspace_destroyed", G_CALLBACK(workspace_destroyed), xscr);
	g_signal_connect(G_OBJECT(wnck), "workspace_created", G_CALLBACK(workspace_created), xscr);
	g_signal_connect(G_OBJECT(wnck), "viewports_changed", G_CALLBACK(viewports_changed), xscr);
	g_signal_connect(G_OBJECT(wnck), "background_changed", G_CALLBACK(background_changed), xscr);
	g_signal_connect(G_OBJECT(wnck), "active_workspace_changed", G_CALLBACK(active_workspace_changed), xscr);
#if 0
	g_signal_connect(G_OBJECT(wnck), "active_window_changed", G_CALLBACK(active_window_changed), xscr);
#endif
	g_signal_connect(G_OBJECT(wnck), "application_closed", G_CALLBACK(application_closed), xscr);
	g_signal_connect(G_OBJECT(wnck), "application_opened", G_CALLBACK(application_opened), xscr);
	g_signal_connect(G_OBJECT(wnck), "class_group_closed", G_CALLBACK(class_group_closed), xscr);
	g_signal_connect(G_OBJECT(wnck), "class_group_opened", G_CALLBACK(class_group_opened), xscr);
	g_signal_connect(G_OBJECT(wnck), "window_closed", G_CALLBACK(window_closed), xscr);
	g_signal_connect(G_OBJECT(wnck), "window_opened", G_CALLBACK(window_opened), xscr);
	g_signal_connect(G_OBJECT(wnck), "window_stacking_changed", G_CALLBACK(window_stacking_changed), xscr);
	g_signal_connect(G_OBJECT(wnck), "showing_desktop_changed", G_CALLBACK(showing_desktop_changed), xscr);

	wnck_screen_force_update(wnck);
	window_manager_changed(wnck, xscr);
}

static gboolean
ifd_watch(GIOChannel *chan, GIOCondition cond, gpointer data)
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
	g_io_add_watch(chan, mask, ifd_watch, smcConn);
}

/*
 *  This startup function starts up the X11 protocol connection and initializes GTK+.  Note that the
 *  program can still be run from a console, in which case the "DISPLAY" environment variables should
 *  not be defined: in which case, we will not start up X11 at all.
 */
static void
startup(int argc, char *argv[])
{
	GdkAtom atom;
	GdkEventMask mask;
	GdkScreen *scrn;
	GdkWindow *root;
	char *file;
	int nscr;

	file = g_build_filename(g_get_home_dir(), ".gtkrc-2.0.xde", NULL);
	gtk_rc_add_default_file(file);
	g_free(file);

#if 1
	/* We can start session management without a display; however, we then need to
	   run a GLIB event loop instead of a GTK event loop.  */
	init_smclient();

	/* do not start up X11 connection unless DISPLAY is defined */
	if (!options.display) {
		loop = g_main_loop_new(NULL, FALSE);
		return;
	}
#endif

	gtk_init(&argc, &argv);

	disp = gdk_display_get_default();
	nscr = gdk_display_get_n_screens(disp);
	dpy = GDK_DISPLAY_XDISPLAY(disp);

	if (options.screen >= 0 && options.screen >= nscr) {
		EPRINTF("bad screen specified: %d\n", options.screen);
		exit(EXIT_FAILURE);
	}

#if 0
	sn_dpy = sn_display_new(dpy, NULL, NULL);
#endif

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
	gdk_display_add_client_message_filter(disp, atom, client_handler, NULL);
#if 1
	atom = gdk_atom_intern_static_string("_NET_DESKTOP_LAYOUT");
	_XA_NET_DESKTOP_LAYOUT = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_NET_CURRENT_DESKTOP");
	_XA_NET_CURRENT_DESKTOP = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_WIN_WORKSPACE");
	_XA_WIN_WORKSPACE = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("WM_DESKTOP");
	_XA_WM_DESKTOP = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_NET_DESKTOP_NAMES");
	_XA_NET_DESKTOP_NAMES = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_NET_NUMBER_OF_DESKTOPS");
	_XA_NET_NUMBER_OF_DESKTOPS = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_WIN_DESKTOP_BUTTON_PROXY");
	_XA_WIN_DESKTOP_BUTTON_PROXY = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_WIN_WORKSPACE_COUNT");
	_XA_WIN_WORKSPACE_COUNT = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_XROOTPMAP_ID");
	_XA_XROOTPMAP_ID = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("ESETROOT_PMAP_ID");
	_XA_ESETROOT_PMAP_ID = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_NET_ACTIVE_WINDOW");
	_XA_NET_ACTIVE_WINDOW = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_NET_CLIENT_LIST");
	_XA_NET_CLIENT_LIST = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_NET_CLIENT_LIST_STACKING");
	_XA_NET_CLIENT_LIST_STACKING = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_WIN_FOCUS");
	_XA_WIN_FOCUS = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_WIN_CLIENT_LIST");
	_XA_WIN_CLIENT_LIST = gdk_x11_atom_to_xatom_for_display(disp, atom);
#endif
#if 0
	atom = gdk_atom_intern_static_string("_NET_STARTUP_INFO");
	_XA_NET_STARTUP_INFO = gdk_x11_atom_to_xatom_for_display(disp, atom);
	gdk_display_add_client_message_filter(disp, atom, client_handler, NULL);

	atom = gdk_atom_intern_static_string("_NET_STARTUP_INFO_BEGIN");
	_XA_NET_STARTUP_INFO_BEGIN = gdk_x11_atom_to_xatom_for_display(disp, atom);
	gdk_display_add_client_message_filter(disp, atom, client_handler, NULL);
#endif				/* STARTUP_NOTIFICATION */
	atom = gdk_atom_intern_static_string("_WIN_AREA");
	_XA_WIN_AREA = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string("_WIN_AREA_COUNT");
	_XA_WIN_AREA_COUNT = gdk_x11_atom_to_xatom_for_display(disp, atom);

	atom = gdk_atom_intern_static_string(XA_PREFIX "_REFRESH");
	_XA_PREFIX_REFRESH = gdk_x11_atom_to_xatom_for_display(disp, atom);
	gdk_display_add_client_message_filter(disp, atom, client_handler, NULL);

	atom = gdk_atom_intern_static_string(XA_PREFIX "_RESTART");
	_XA_PREFIX_RESTART = gdk_x11_atom_to_xatom_for_display(disp, atom);
	gdk_display_add_client_message_filter(disp, atom, client_handler, NULL);

	atom = gdk_atom_intern_static_string(XA_PREFIX "_POPMENU");
	_XA_PREFIX_POPMENU = gdk_x11_atom_to_xatom_for_display(disp, atom);
	gdk_display_add_client_message_filter(disp, atom, client_handler, NULL);

	atom = gdk_atom_intern_static_string(XA_PREFIX "_EDITOR");
	_XA_PREFIX_EDITOR = gdk_x11_atom_to_xatom_for_display(disp, atom);
	gdk_display_add_client_message_filter(disp, atom, client_handler, NULL);

	scrn = gdk_display_get_default_screen(disp);
	root = gdk_screen_get_root_window(scrn);
	mask = gdk_window_get_events(root);
	mask |= GDK_PROPERTY_CHANGE_MASK | GDK_STRUCTURE_MASK | GDK_SUBSTRUCTURE_MASK;
	gdk_window_set_events(root, mask);

	wnck_set_client_type(WNCK_CLIENT_TYPE_PAGER);
}

XdeMonitor *
init_screens(Window selwin)
{
	XdeMonitor *xmon = NULL;
	XdeScreen *xscr;
	int s, nscr;

	nscr = gdk_display_get_n_screens(disp);
	screens = calloc(nscr, sizeof(*screens));

	if (selwin) {
		GdkWindow *sel;

		sel = gdk_x11_window_foreign_new_for_display(disp, selwin);
		gdk_window_add_filter(sel, selwin_handler, screens);
		g_object_unref(G_OBJECT(sel));
	}
	gdk_window_add_filter(NULL, events_handler, NULL);

	for (s = 0, xscr = screens; s < nscr; s++, xscr++) {
		xscr->index = s;
		if (selwin) {
			char selection[65] = { 0, };

			snprintf(selection, sizeof(selection), XA_SELECTION_NAME, s);
			xscr->atom = XInternAtom(dpy, selection, False);
			xscr->selwin = selwin;
		}
		xscr->scrn = gdk_display_get_screen(disp, s);
		xscr->root = gdk_screen_get_root_window(xscr->scrn);
		xscr->width = gdk_screen_get_width(xscr->scrn);
		xscr->height = gdk_screen_get_height(xscr->scrn);
#if 0
		xscr->ctx = sn_monitor_context_new(sn_dpy, s, &sn_handler, xscr, NULL);
#endif
		gdk_window_add_filter(xscr->root, root_handler, xscr);
		init_wnck(xscr);
		init_monitors(xscr);
#if 0
#if 0
		if (options.proxy)
			setup_button_proxy(xscr);
		if (options.show.setbg)
			update_root_pixmap(xscr, None);
#endif
		update_layout(xscr, None);
		update_current_desktop(xscr, None);
#endif
		update_theme(xscr, None);
		update_icon_theme(xscr, None);
#if 1
		update_active_window(xscr, None);
		update_client_list(xscr, None);
#endif
	}
	xmon = find_monitor();
	return (xmon);
}

Window
get_desktop_layout_selection(XdeScreen *xscr)
{
	Window root = RootWindow(dpy, xscr->index);
	char selection[64] = { 0, };
	GdkWindow *lay;
	Window owner;
	Atom atom;

	if (xscr->laywin)
		return None;

	xscr->laywin = XCreateSimpleWindow(dpy, root, 0, 0, 1, 1, 0, 0, 0);
	XSelectInput(dpy, xscr->laywin, StructureNotifyMask | SubstructureNotifyMask | PropertyChangeMask);
	lay = gdk_x11_window_foreign_new_for_display(disp, xscr->laywin);
	gdk_window_add_filter(lay, laywin_handler, xscr);
	snprintf(selection, sizeof(selection), XA_NET_DESKTOP_LAYOUT, xscr->index);
	atom = XInternAtom(dpy, selection, False);
	if (!(owner = XGetSelectionOwner(dpy, atom)))
		DPRINTF(1, "No owner for %s\n", selection);
	XSetSelectionOwner(dpy, atom, xscr->laywin, CurrentTime);
	XSync(dpy, False);

	if (xscr->laywin) {
		XEvent ev;

		ev.xclient.type = ClientMessage;
		ev.xclient.serial = 0;
		ev.xclient.send_event = False;
		ev.xclient.display = dpy;
		ev.xclient.window = root;
		ev.xclient.message_type = XInternAtom(dpy, "MANAGER", False);
		ev.xclient.format = 32;
		ev.xclient.data.l[0] = CurrentTime;
		ev.xclient.data.l[1] = atom;
		ev.xclient.data.l[2] = xscr->laywin;
		ev.xclient.data.l[3] = 0;
		ev.xclient.data.l[4] = 0;

		XSendEvent(dpy, root, False, StructureNotifyMask, &ev);
		XFlush(dpy);
	}
	return (owner);
}

static Window
get_selection(Bool replace, Window selwin)
{
	char selection[64] = { 0, };
	int s, nscr;
	Atom atom;
	Window owner, gotone = None;

	PTRACE(5);
	nscr = gdk_display_get_n_screens(disp);

	for (s = 0; s < nscr; s++) {
		snprintf(selection, sizeof(selection), XA_SELECTION_NAME, s);
		atom = XInternAtom(dpy, selection, False);
		if (!(owner = XGetSelectionOwner(dpy, atom)))
			DPRINTF(1, "No owner for %s\n", selection);
		if ((owner && replace) || (!owner && selwin)) {
			DPRINTF(1, "Setting owner of %s to 0x%08lx from 0x%08lx\n", selection, selwin, owner);
			XSetSelectionOwner(dpy, atom, selwin, CurrentTime);
			XSync(dpy, False);
			/* XXX: should do XIfEvent for owner window destruction */
		}
		if (!gotone && owner)
			gotone = owner;
	}
	if (replace) {
		if (gotone) {
			if (selwin)
				DPRINTF(1, "replacing running instance\n");
			else
				DPRINTF(1, "quitting running instance\n");
		} else {
			if (selwin)
				DPRINTF(1, "no running instance to replace\n");
			else
				DPRINTF(1, "no running instance to quit\n");
		}
		if (selwin) {
			XEvent ev = { 0, };
			Atom manager = XInternAtom(dpy, "MANAGER", False);
			GdkScreen *scrn;
			Window root;

			for (s = 0; s < nscr; s++) {
				scrn = gdk_display_get_screen(disp, s);
				root = GDK_WINDOW_XID(gdk_screen_get_root_window(scrn));
				snprintf(selection, sizeof(selection), XA_SELECTION_NAME, s);
				atom = XInternAtom(dpy, selection, False);

				ev.xclient.type = ClientMessage;
				ev.xclient.serial = 0;
				ev.xclient.send_event = False;
				ev.xclient.display = dpy;
				ev.xclient.window = root;
				ev.xclient.message_type = manager;
				ev.xclient.format = 32;
				ev.xclient.data.l[0] = CurrentTime;	/* FIXME */
				ev.xclient.data.l[1] = atom;
				ev.xclient.data.l[2] = selwin;
				ev.xclient.data.l[3] = 0;
				ev.xclient.data.l[4] = 0;

				XSendEvent(dpy, root, False, StructureNotifyMask, &ev);
				XFlush(dpy);
			}
		}
	} else if (gotone)
		DPRINTF(1, "not replacing running instance\n");
	return (gotone);
}

static void
do_generate(int argc, char *argv[])
{
	menu_generate();
}

static void
do_run(int argc, char *argv[])
{
	GdkScreen *scrn = gdk_display_get_default_screen(disp);
	GdkWindow *root = gdk_screen_get_root_window(scrn);
	Window selwin, owner, broadcast = GDK_WINDOW_XID(root);
	long mask = StructureNotifyMask | SubstructureNotifyMask | PropertyChangeMask;
	XdeMonitor *xmon;

	PTRACE(5);
	selwin = XCreateSimpleWindow(dpy, broadcast, 0, 0, 1, 1, 0, 0, 0);

	if ((owner = get_selection(options.replace, selwin))) {
		if (!options.replace) {
			XEvent ev = { 0, };

			XDestroyWindow(dpy, selwin);
			if (options.screen >= 0) {
				scrn = gdk_display_get_screen(disp, options.screen);
				root = gdk_screen_get_root_window(scrn);
			}
			broadcast = GDK_WINDOW_XID(root);
			switch (options.command) {
			default:
				EPRINTF("instance already running\n");
				exit(EXIT_FAILURE);
			case CommandRestart:
				DPRINTF(1, "instance running: asking it to restart\n");
				ev.xclient.type = ClientMessage;
				ev.xclient.serial = 0;
				ev.xclient.send_event = False;
				ev.xclient.display = dpy;
				ev.xclient.window = broadcast;
				ev.xclient.message_type = _XA_PREFIX_RESTART;
				ev.xclient.format = 32;
				ev.xclient.data.l[0] = options.timestamp;
				ev.xclient.data.l[1] = get_scmon();
				ev.xclient.data.l[2] = get_flags();
				ev.xclient.data.l[3] = get_word1();
				ev.xclient.data.l[4] = get_word2();
				XSendEvent(dpy, broadcast, False, mask, &ev);
				XSync(dpy, False);
				break;
			case CommandRefresh:
				DPRINTF(1, "instance running: asking it to refresh\n");
				ev.xclient.type = ClientMessage;
				ev.xclient.serial = 0;
				ev.xclient.send_event = False;
				ev.xclient.display = dpy;
				ev.xclient.window = broadcast;
				ev.xclient.message_type = _XA_PREFIX_REFRESH;
				ev.xclient.format = 32;
				ev.xclient.data.l[0] = options.timestamp;
				ev.xclient.data.l[1] = get_scmon();
				ev.xclient.data.l[2] = get_flags();
				ev.xclient.data.l[3] = get_word1();
				ev.xclient.data.l[4] = get_word2();
				XSendEvent(dpy, broadcast, False, mask, &ev);
				XSync(dpy, False);
				break;
			case CommandPopMenu:
				DPRINTF(1, "instance running: asking it to launch popmenu\n");
				ev.xclient.type = ClientMessage;
				ev.xclient.serial = 0;
				ev.xclient.send_event = False;
				ev.xclient.display = dpy;
				ev.xclient.window = broadcast;
				ev.xclient.message_type = _XA_PREFIX_POPMENU;
				ev.xclient.format = 32;
				ev.xclient.data.l[0] = options.timestamp;
				ev.xclient.data.l[1] = get_scmon();
				ev.xclient.data.l[2] = get_flags();
				ev.xclient.data.l[3] = get_word1();
				ev.xclient.data.l[4] = get_word2();
				XSendEvent(dpy, broadcast, False, mask, &ev);
				XSync(dpy, False);
				break;
			case CommandEditor:
				DPRINTF(1, "instance running: asking it to launch popmenu\n");
				ev.xclient.type = ClientMessage;
				ev.xclient.serial = 0;
				ev.xclient.send_event = False;
				ev.xclient.display = dpy;
				ev.xclient.window = broadcast;
				ev.xclient.message_type = _XA_PREFIX_EDITOR;
				ev.xclient.format = 32;
				ev.xclient.data.l[0] = options.timestamp;
				ev.xclient.data.l[1] = get_scmon();
				ev.xclient.data.l[2] = get_flags();
				ev.xclient.data.l[3] = get_word1();
				ev.xclient.data.l[4] = get_word2();
				XSendEvent(dpy, broadcast, False, mask, &ev);
				XSync(dpy, False);
				break;
			}
			exit(EXIT_SUCCESS);
		}
	}
	XSelectInput(dpy, selwin, mask);

	oldhandler = XSetErrorHandler(handler);
	oldiohandler = XSetIOErrorHandler(iohandler);

	xmon = init_screens(selwin);

	g_unix_signal_add(SIGTERM, &term_signal_handler, NULL);
	g_unix_signal_add(SIGINT, &int_signal_handler, NULL);
	g_unix_signal_add(SIGHUP, &hup_signal_handler, NULL);

	if (options.systray)
		systray_show(xmon->xscr);

	make_menu();

	if (options.command == CommandPopMenu)
		menu_pop(xmon->xscr);

	if (!options.exit && !options.replace) {
		switch (options.command) {
		case CommandRestart:
		case CommandRefresh:
		case CommandPopMenu:
		case CommandEditor:
			/* not expecting to run these ourselves */
			fork_and_exit();
			break;
		default:
			break;
		}
	}

	mainloop();
}

/** @brief Ask a running instance to quit.
  *
  * This is performed by checking for an owner of the selection and clearing the
  * selection if it exists.
  */
static void
do_quit(int argc, char *argv[])
{
	PTRACE(5);
	get_selection(True, None);
}

/** @} */

/** @section Main
  * @{ */

static void
copying(int argc, char *argv[])
{
	if (!options.output && !options.debug)
		return;
	(void) fprintf(stdout, "\
--------------------------------------------------------------------------------\n\
%1$s\n\
--------------------------------------------------------------------------------\n\
Copyright (c) 2008-2016  Monavacon Limited <http://www.monavacon.com/>\n\
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
Copyright (c) 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016  Monavacon Limited.\n\
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

static const char *
show_bool(Bool value)
{
	if (value)
		return ("true");
	return ("false");
}

#if 0
static const char *
show_order(WindowOrder order)
{
	switch (order) {
	case WindowOrderDefault:
		return ("default");
	case WindowOrderClient:
		return ("client");
	case WindowOrderStacking:
		return ("stacking");
	}
	return NULL;
}
#endif

static const char *
show_screen(int snum)
{
	static char screen[64] = { 0, };

	if (snum == -1)
		return ("None");
	snprintf(screen, sizeof(screen), "%d", snum);
	return (screen);
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
	case StyleSubmenu:
		return ("submenu");
	}
	return ("(unknown)");
}

static const char *
show_which(UseScreen which)
{
	switch (which) {
	case UseScreenDefault:
		return ("default");
	case UseScreenActive:
		return ("active");
	case UseScreenFocused:
		return ("focused");
	case UseScreenPointer:
		return ("pointer");
	case UseScreenSpecified:
		return show_screen(options.screen);
	}
	return NULL;
}

static const char *
show_where(MenuPosition where)
{
	static char position[128] = { 0, };

	switch (where) {
	case PositionDefault:
		return ("default");
	case PositionPointer:
		return ("pointer");
	case PositionCenter:
		return ("center");
	case PositionTopLeft:
		return ("topleft");
	case PositionBottomRight:
		return ("bottomright");
	case PositionSpecified:
		snprintf(position, sizeof(position), "%ux%u%c%d%c%d",
			 options.geom.w, options.geom.h,
			 (options.geom.mask & XNegative) ? '-' : '+', options.geom.x,
			 (options.geom.mask & YNegative) ? '-' : '+', options.geom.y);
		return (position);
	}
	return NULL;
}

const char *
show_include(Include include)
{
	switch (include) {
	case IncludeDefault:
	case IncludeDocs:
		return ("documents");
	case IncludeApps:
		return ("applications");
	case IncludeBoth:
		return ("both");
	}
	return NULL;
}

const char *
show_sorting(Sorting sorting)
{
	switch (sorting) {
	case SortByDefault:
	case SortByRecent:
		return ("recent");
	case SortByFavorite:
		return ("favorite");
	}
	return NULL;
}

const char *
show_organize(Organize organize)
{
	switch (organize) {
	case OrganizeDefault:
	case OrganizeNone:
		return ("none");
	case OrganizeDate:
		return ("date");
	case OrganizeFreq:
		return ("freq");
	case OrganizeGroup:
		return ("group");
	case OrganizeContent:
		return ("content");
	case OrganizeApp:
		return ("app");
	}
	return NULL;
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
    %1$s {-G|--menugen} [options]\n\
    %1$s {-P|--popmenu} [options]\n\
    %1$s {-m|--monitor} [options]\n\
    %1$s {-R|--replace} [options]\n\
    %1$s {-E|--refresh} [options]\n\
    %1$s {-S|--restart} [options]\n\
    %1$s {-q|--quit} [options]\n\
    %1$s {-h|--help} [options]\n\
    %1$s {-V|--version}\n\
    %1$s {-C|--copying}\n\
Command options:\n\
   [-G, --menugen]\n\
        generate a menu in foreground only\n\
    -P, --popmenu\n\
        pop the menu (on running or new instance)\n\
    -g, --monitor\n\
        generate a menu and monitor for changes and requests\n\
    -R, --replace\n\
        replace a running instance\n\
    -E, --refresh\n\
        ask a running instance to refresh the menus\n\
    -S, --restart\n\
        ask a running instance to reexecute itself\n\
    -q, --quit\n\
        ask a running instance to quit\n\
    -h, --help, -?, --?\n\
        print this usage information and exit\n\
    -V, --version\n\
        print version and exit\n\
    -C, --copying\n\
        print copying permission and exit\n\
Format options:\n\
    -w, --wmname WMNAME\n\
        specify the window manager name [default: %2$s]\n\
    -f, --format FORMAT\n\
        specify the menu format [default: %3$s]\n\
    -F, --fullmenu, -l, --nofullmenu\n\
        full menu or applications menu [default: %4$s]\n\
    -d, --desktop DESKTOP\n\
        desktop environment [default: %5$s]\n\
    -r, --root-menu MENU\n\
        root menu file [default: %6$s]\n\
    -o, --output [OUTPUT]\n\
        output file [default: %7$s]\n\
    --icons, -I, --noicons\n\
        place or do not place icons in menu [default: %8$s]\n\
    -t, --theme THEME\n\
        icon theme name to use [default: %9$s]\n\
    -L, --launch, -0, --nolaunch\n\
        use xde-launch to launch programs [default: %10$s]\n\
    -s, --style STYLE\n\
        fullmenu, appmenu, submenu or entries [default: %11$s]\n\
    -M, --menu MENU\n\
        filename stem of root menu filename [default: %12$s]\n\
    --excluded\n\
        include otherwise excluded applications [default: %13$s]\n\
    --nodisplay\n\
        include applications marked as no-dipslay [default: %14$s]\n\
    --unallocated\n\
        include applications already placed in menu [default: %15$s]\n\
    --empty\n\
        include empty submenus [default: %16$s]\n\
    --separators\n\
        include all (even extraneous) separators [default: %17$s]\n\
    --sort\n\
        sort entries by display name instead of name [default: %18$s]\n\
    --actions\n\
        provide submenu for actions [default: %19$s]\n\
    --tooltips\n\
        include verbose tooltips for application menu items [default: %25$s]\n\
Pop up menu options:\n\
    --screen SCREEN\n\
        specify the X11 screen for the menu [default: %27$s]\n\
    --Monitor MONITOR\n\
        specify the X11 monitor for the menu [default: %33$s]\n\
    -T, --timestamp TIMESTAMP\n\
        specify the button/keypress event timestamp [default: %22$lu]\n\
    -b, --button [BUTTON] | --pointer\n\
        specify the button pressed when popping menu [default: %20$u]\n\
    -k, --keypress [KEYSPEC] | --keyboard\n\
        specify the key sequence active when popping menu [default: %21$s]\n\
    -i, --which {default|active|focused|pointer|SCREEN}\n\
        specify on which screen to display the menu: [default: %23$s]\n\
        default - specify default selection algorithm\n\
        active  - the screen with the active window\n\
        focused - the screen with the window with the keyboard focus\n\
        pointer - the screen containing (or nearest) the pointer\n\
        SCREEN  - a specific screen number\n\
    -w, --where {default|pointer|center|topleft|bottomright|WHERE}\n\
        where to put menu: [default: %24$s]\n\
        default - specify default position algorithm\n\
        pointer - position the menu at the pointer\n\
        center  - center the menu in the current monitor\n\
        topleft - position menu at top left of work area on monitor\n\
        bottom  - position menu at bottom right of work area\n\
        WHERE   - beside or at a specific screen geometry\n\
General options:\n\
    --display DISPLAY\n\
        specify the X11 display [default: %26$s]\n\
    -c, --filename FILENAME\n\
        use a different configuration file [default: %34$s]\n\
    --notray\n\
        do not install a system tray icon [default: %28$s]\n\
    --nogenerate\n\
        do not generate window manager root menu [default: %29$s]\n\
    -x, --exit\n\
        exit main process after generating menu [default: %30$s]\n\
    -v, --verbose [LEVEL]\n\
        increment or set output verbosity LEVEL [default: %32$d]\n\
        this option may be repeated.\n\
    -D, --debug [LEVEL]\n\
        increment or set debug LEVEL [default: %31$d]\n\
", argv[0]
	, options.wmname
	, options.format
	, show_style(options.style)
	, options.desktop
	, options.rootmenu
	, options.menufile
	, show_bool(!options.noicons)
	, options.theme
	, show_bool(options.launch)
	, show_style(options.style)
	, options.menu
	, show_bool(options.treeflags & GMENU_TREE_FLAGS_INCLUDE_EXCLUDED)
	, show_bool(options.treeflags & GMENU_TREE_FLAGS_INCLUDE_NODISPLAY)
	, show_bool(options.treeflags & GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED)
	, show_bool(options.treeflags & GMENU_TREE_FLAGS_SHOW_EMPTY)
	, show_bool(options.treeflags & GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS)
	, show_bool(options.treeflags & GMENU_TREE_FLAGS_SORT_DISPLAY_NAME)
	, show_bool(options.actions)
	, options.button
	, options.keypress
	, options.timestamp
	, show_which(options.which)
	, show_where(options.where)
	, show_bool(options.tooltips)
	, options.display
	, show_screen(options.screen)
	, show_bool(!options.systray)
	, show_bool(!options.generate)
	, show_bool(options.exit)
	, options.debug
	, options.output
	, show_screen(options.monitor)
	, options.filename
);
	/* *INDENT-ON* */
}

static Bool
get_text_property(Display *dpy, Window root, Atom prop, char ***listp, int *stringsp)
{
	XTextProperty xtp = { NULL, };

	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		*listp = NULL;
		*stringsp = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, listp, stringsp) == Success)
			return True;
		else {
			char *name = NULL;

			DPRINTF(1, "could not get text list for %s property\n", (name = XGetAtomName(dpy, prop)));
			if (name)
				XFree(name);
		}
	} else {
		char *name = NULL;

		DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
		if (name)
			XFree(name);
	}
	return False;
}

static void
set_default_wmname(void)
{
	if (options.display) {
		Display *dpy;
		Window root;
		Atom prop;
		char **list = NULL;
		int strings = 0;

		if (!(dpy = XOpenDisplay(NULL))) {
			EPRINTF("could not open display %s\n", getenv("DISPLAY"));
			return;
		}
		root = RootWindow(dpy, 0);
		prop = XInternAtom(dpy, "_XDE_WM_NAME", False);
		if (get_text_property(dpy, root, prop, &list, &strings) && list) {
			options.wmname = strdup(list[0]);
			XFreeStringList(list);
		} else {
			char *name = NULL;

			DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
			if (name)
				XFree(name);
		}
		XCloseDisplay(dpy);
	} else
		DPRINTF(1, "cannot determine wmname without DISPLAY\n");
	if (options.wmname)
		DPRINTF(1, "assigned wmname as '%s'\n", options.wmname);
}

static void
set_default_format(void)
{
	if (options.display) {
		Display *dpy;
		Window root;
		Atom prop;
		char **list = NULL;
		int strings = 0;

		if (!(dpy = XOpenDisplay(NULL))) {
			EPRINTF("could not open display %s\n", getenv("DISPLAY"));
			return;
		}
		root = RootWindow(dpy, 0);
		prop = XInternAtom(dpy, "_XDE_WM_NAME", False);
		if (get_text_property(dpy, root, prop, &list, &strings) && list) {
			options.wmname = strdup(list[0]);
			XFreeStringList(list);
		} else {
			char *name = NULL;

			DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
			if (name)
				XFree(name);
		}
		XCloseDisplay(dpy);
	} else
		DPRINTF(1, "cannot determine wmname without DISPLAY\n");
	if (options.format)
		DPRINTF(1, "assigned format as '%s'\n", options.format);
}

static void
set_default_desktop(void)
{
	const char *env;
	char *p;

	if (!options.desktop || !strcmp(options.desktop, "XDE") || !options.wmname
	    || strcasecmp(options.wmname, options.desktop)) {
		if ((env = getenv("XDG_CURRENT_DESKTOP"))) {
			free(options.desktop);
			options.desktop = strdup(env);
		} else if (options.wmname) {
			free(options.desktop);
			options.desktop = strdup(options.wmname);
			for (p = options.desktop; *p; p++)
				*p = toupper(*p);
		} else if (!options.desktop) {
			options.desktop = strdup("XDE");
		}
	}
	if (options.desktop)
		DPRINTF(1, "assigned desktop as '%s'\n", options.desktop);
}

static void
set_default_output(void)
{
}

static void
set_default_theme(void)
{
}

static void
set_default_icon_theme(void)
{
}

static void
set_default_config(void)
{
	char *file;

	if (options.wmname)
		file = g_build_filename(g_get_user_config_dir(), RESNAME, options.wmname, "rc", NULL);
	else
		file = g_build_filename(g_get_user_config_dir(), RESNAME, "rc", NULL);
	options.filename = strdup(file);
	g_free(file);
}

static void
set_default_paths(void)
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
	DPRINTF(1, "Full data path is: '%s'\n", xdg_data_path);
	p = xdg_data_path;
	e = xdg_data_last;
	while ((p = strchrnul(p, ':')) < e)
		*p++ = '\0';
	DPRINTF(1, "Directories in forward order:\n");
	for (p = xdg_data_path; p < xdg_data_last; p += strlen(p) + 1) {
		DPRINTF(1, "\t%s\n", p);
	}
	DPRINTF(1, "Directories in reverse order:\n");
	for (p = xdg_find_str(xdg_data_last, xdg_data_path);
	     p >= xdg_data_path; p = xdg_find_str(p - 1, xdg_data_path)) {
		DPRINTF(1, "\t%s\n", p);
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
	DPRINTF(1, "Full config path is; '%s'\n", xdg_config_path);
	p = xdg_config_path;
	e = xdg_config_last;
	while ((p = strchrnul(p, ':')) < e)
		*p++ = '\0';
	DPRINTF(1, "Directories in forward order:\n");
	for (p = xdg_config_path; p < xdg_config_last; p += strlen(p) + 1) {
		DPRINTF(1, "\t%s\n", p);
	}
	DPRINTF(1, "Directories in reverse order:\n");
	for (p = xdg_find_str(xdg_config_last, xdg_config_path);
	     p >= xdg_config_path; p = xdg_find_str(p - 1, xdg_config_path)) {
		DPRINTF(1, "\t%s\n", p);
	}
}

static void
set_default_files(void)
{
	gchar *file;

	file = g_build_filename(g_get_user_config_dir(), "xde", "run-history", NULL);
	free(options.runhist);
	options.runhist = strdup(file);
	g_free(file);
	file = g_build_filename(g_get_user_config_dir(), "xde", "recent-applications", NULL);
	free(options.recapps);
	options.recapps = strdup(file);
	g_free(file);
	file = g_build_filename(g_get_user_data_dir(), "recently-used", NULL);
	if (access(file, R_OK | W_OK)) {
		g_free(file);
		file = g_build_filename(g_get_home_dir(), ".recently-used", NULL);
	}
	free(options.recently);
	options.recently = strdup(file);
	g_free(file);
}

/*
 * Set options in the "options" structure.  The defaults are determined by preset defaults,
 * environment variables and other startup information, but not information from the X Server.  All
 * options are set in this way, only the ones that depend on environment variables or other startup
 * information.
 */
static void
set_defaults(void)
{
	const char *env, *p, *q;
	char *endptr = NULL;
	int n, monitor;
	Time timestamp;

	if ((env = getenv("DISPLAY"))) {
		free(options.display);
		options.display = strdup(env);
		if (options.screen < 0 && (p = strrchr(options.display, '.'))
		    && (n = strspn(++p, "0123456789")) && *(p + n) == '\0')
			options.screen = atoi(p);
	}
	if ((env = getenv("XDG_CURRENT_DESKTOP"))) {
		free(options.desktop);
		options.desktop = strdup(env);
	}
	if ((env = getenv("DESKTOP_STARTUP_ID"))) {
		/* we can get the timestamp from the startup id */
		if ((p = strstr(env, "_TIME"))) {
			timestamp = strtoul(p + 5, &endptr, 10);
			if (endptr && *endptr)
				options.timestamp = timestamp;
		}
		/* we can get the monitor number from the startup id */
		if ((p = strstr(env, "xdg-launch/")) == env &&
		    (p = strchr(p + 11, '/')) && (p = strchr(p + 1, '-')) && (q = strchr(p + 1, '-'))) {
			monitor = strtoul(p, &endptr, 10);
			if (endptr == q)
				options.monitor = monitor;
		}
	}
	if ((env = getenv("XDE_DEBUG"))) {
		options.debug = atoi(env);
		options.output = options.debug + 1;
	}
	set_default_wmname();
	set_default_format();
	set_default_desktop();
	set_default_output();
	set_default_theme();
	set_default_icon_theme();
	set_default_config();
	set_default_paths();
	set_default_files();
}

static void
get_default_wmname(void)
{
	if (options.wmname) {
		DPRINTF(1, "option wmname is set to '%s'\n", options.wmname);
		return;
	}

	if (options.format) {
		char *p;

		free(options.wmname);
		options.wmname = strdup(options.format);
		if ((p = strstr(options.wmname, "old")) && !p[3])
			p[0] = '\0';
		for (p = options.wmname; *p; p++)
			*p = tolower(*p);
	}
	if (options.display) {
		Display *dpy = GDK_DISPLAY_XDISPLAY(disp);
		GdkScreen *scrn = gdk_display_get_default_screen(disp);
		GdkWindow *wind = gdk_screen_get_root_window(scrn);
		Window root = GDK_WINDOW_XID(wind);
		Atom prop = _XA_XDE_WM_NAME;
		char **list = NULL;
		int strings = 0;

		if (get_text_property(dpy, root, prop, &list, &strings)) {
			if (!options.wmname) {
				free(options.wmname);
				options.wmname = strdup(list[0]);
			} else if (strcmp(options.wmname, list[0]))
				DPRINTF(1, "default wmname %s different from actual %s\n",
					options.wmname, list[0]);
			if (list)
				XFreeStringList(list);
		} else {
			char *name = NULL;

			DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
			if (name)
				XFree(name);
		}
	} else
		EPRINTF("cannot determine wmname without DISPLAY\n");

	if (options.wmname)
		DPRINTF(1, "assigned wmname as '%s'\n", options.wmname);
}

static void
get_default_format(void)
{
	if (options.format) {
		DPRINTF(1, "option format is set to '%s'\n", options.format);
		return;
	}

	if (options.wmname) {
		char *p;

		free(options.format);
		options.format = strdup(options.wmname);
		for (p = options.format; *p; p++)
			*p = tolower(*p);
	}
	if (options.display) {
		GdkScreen *scrn = gdk_display_get_default_screen(disp);
		GdkWindow *wind = gdk_screen_get_root_window(scrn);
		Window root = GDK_WINDOW_XID(wind);
		Atom prop = _XA_XDE_WM_NAME;
		char **list = NULL;
		int strings = 0;

		if (get_text_property(dpy, root, prop, &list, &strings)) {
			if (!options.format) {
				free(options.format);
				options.format = strdup(list[0]);
			} else if (strcmp(options.format, list[0]))
				DPRINTF(1, "default format %s different from actual %s\n",
					options.format, list[0]);
			if (list)
				XFreeStringList(list);
		} else {
			char *name = NULL;

			DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
			if (name)
				XFree(name);
		}
	} else
		EPRINTF("cannot determine format without DISPLAY\n");

	if (options.format)
		DPRINTF(1, "assigned format as '%s'\n", options.format);
}

static void
get_default_desktop(void)
{
	XdeScreen *xscr = screens;
	const char *env;
	char *p;

	if (!options.desktop || !strcmp(options.desktop, "XDE") || !options.wmname
	    || strcasecmp(options.wmname, options.desktop)) {
		if ((env = getenv("XDG_CURRENT_DESKTOP"))) {
			free(options.desktop);
			options.desktop = strdup(env);
		} else if (options.wmname) {
			free(options.desktop);
			options.desktop = strdup(options.wmname);
			for (p = options.desktop; *p; p++)
				*p = toupper(*p);
		} else if (xscr && xscr->wmname) {
			free(options.desktop);
			options.desktop = strdup(xscr->wmname);
			for (p = options.desktop; *p; p++)
				*p = toupper(*p);
		} else if (!options.desktop) {
			options.desktop = strdup("XDE");
		}
	}
	if (options.desktop)
		DPRINTF(1, "assigned desktop as '%s'\n", options.desktop);
}

static void
get_default_output(void)
{
	if (options.menufile) {
		DPRINTF(1, "option output is set to '%s'\n", options.menufile);
		return;
	}
	if (options.display) {
		GdkScreen *scrn = gdk_display_get_default_screen(disp);
		GdkWindow *wind = gdk_screen_get_root_window(scrn);
		Window root = GDK_WINDOW_XID(wind);
		Atom prop = _XA_XDE_WM_MENU;
		char **list = NULL;
		int strings = 0;

		if (get_text_property(dpy, root, prop, &list, &strings)) {
			if (!options.menufile) {
				free(options.menufile);
				options.menufile = strdup(list[0]);
			} else if (strcmp(options.menufile, list[0]))
				DPRINTF(1, "default filename %s different from actual '%s'\n",
					options.menufile, list[0]);
			if (list)
				XFreeStringList(list);
		} else {
			char *name = NULL;

			DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
			DPRINTF(1, "chances are window manager does not have a root menu\n");
			if (name)
				XFree(name);
		}
	} else
		EPRINTF("cannot determine filename without DISPLAY\n");

	if (options.menufile)
		DPRINTF(1, "assigned filename as '%s'\n", options.menufile);
}

static void
get_default_theme(void)
{
	GdkScreen *scrn = gdk_display_get_default_screen(disp);
	GdkWindow *wind = gdk_screen_get_root_window(scrn);
	Window root = GDK_WINDOW_XID(wind);
	XTextProperty xtp = { NULL, };
	Bool changed = False;
	Atom prop = _XA_XDE_THEME_NAME;
	GtkSettings *set;

	gtk_rc_reparse_all();

	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		char **list = NULL;
		int strings = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, &list, &strings) == Success) {
			if (strings >= 1) {
				char *rc_string;

				rc_string = g_strdup_printf("gtk-theme-name=\"%s\"", list[0]);
				gtk_rc_parse_string(rc_string);
				g_free(rc_string);
				if (!options.theme || strcmp(options.theme, list[0])) {
					free(options.theme);
					options.theme = strdup(list[0]);
					changed = True;
				}
			}
			if (list)
				XFreeStringList(list);
		} else {
			char *name = NULL;

			EPRINTF("could not get text list for %s property\n", (name = XGetAtomName(dpy, prop)));
			if (name)
				XFree(name);
		}
		if (xtp.value)
			XFree(xtp.value);
	} else {
		char *name = NULL;

		DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
		if (name)
			XFree(name);
	}
	if ((set = gtk_settings_get_for_screen(scrn))) {
		GValue theme_v = G_VALUE_INIT;
		const char *theme;

		g_value_init(&theme_v, G_TYPE_STRING);
		g_object_get_property(G_OBJECT(set), "gtk-theme-name", &theme_v);
		theme = g_value_get_string(&theme_v);
		if (theme && (!options.theme || strcmp(options.theme, theme))) {
			free(options.theme);
			options.theme = strdup(theme);
			changed = True;
		}
		g_value_unset(&theme_v);
	}
	if (changed) {
		DPRINTF(1, "New theme is %s\n", options.theme);
	}
}

static void
get_default_icon_theme(void)
{
	GdkScreen *scrn = gdk_display_get_default_screen(disp);
	GdkWindow *wind = gdk_screen_get_root_window(scrn);
	Window root = GDK_WINDOW_XID(wind);
	XTextProperty xtp = { NULL, };
	Bool changed = False;
	Atom prop = _XA_XDE_ICON_THEME_NAME;
	GtkSettings *set;

	gtk_rc_reparse_all();

	if (XGetTextProperty(dpy, root, &xtp, prop)) {
		char **list = NULL;
		int strings = 0;

		if (Xutf8TextPropertyToTextList(dpy, &xtp, &list, &strings) == Success) {
			if (strings >= 1) {
				char *rc_string;

				rc_string = g_strdup_printf("gtk-icon-theme-name=\"%s\"", list[0]);
				gtk_rc_parse_string(rc_string);
				g_free(rc_string);
				if (!options.itheme || strcmp(options.itheme, list[0])) {
					free(options.itheme);
					options.itheme = strdup(list[0]);
					changed = True;
				}
			}
			if (list)
				XFreeStringList(list);
		} else {
			char *name = NULL;

			EPRINTF("could not get text list for %s property\n", (name = XGetAtomName(dpy, prop)));
			if (name)
				XFree(name);
		}
		if (xtp.value)
			XFree(xtp.value);
	} else {
		char *name = NULL;

		DPRINTF(1, "could not get %s for root 0x%lx\n", (name = XGetAtomName(dpy, prop)), root);
		if (name)
			XFree(name);
	}
	if ((set = gtk_settings_get_for_screen(scrn))) {
		GValue theme_v = G_VALUE_INIT;
		const char *itheme;

		g_value_init(&theme_v, G_TYPE_STRING);
		g_object_get_property(G_OBJECT(set), "gtk-icon-theme-name", &theme_v);
		itheme = g_value_get_string(&theme_v);
		if (itheme && (!options.itheme || strcmp(options.itheme, itheme))) {
			free(options.itheme);
			options.itheme = strdup(itheme);
			changed = True;
		}
		g_value_unset(&theme_v);
	}
	if (changed) {
		DPRINTF(1, "New icon theme is %s\n", options.itheme);
	}
}

static void
get_default_root(void)
{
	char *env, *dirs, *pfx, *p, *q, *d, *e;

	if (!options.menu) {
		free(options.menu);
		options.menu = strdup("applications");
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
	DPRINTF(1, "$XDG_CONFIG_HOME:$XDG_CONFIG_DIRS is '%s'\n", dirs);
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
	DPRINTF(1, "$XDG_MENU_PREFIX:$XDG_VENDOR_ID- is '%s'\n", pfx);
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
			DPRINTF(1, "Testing path: '%s'\n", path);
			if (access(path, R_OK) == 0) {
				free(options.rootmenu);
				options.rootmenu = path;
				break;
			}
			free(path);
		}
		if (options.rootmenu)
			break;
	}
	DPRINTF(1, "Default root menu is: '%s'\n", options.rootmenu);
	free(dirs);
	free(pfx);
}

static void
get_default_config(void)
{
	char *file;

	if (options.filename)
		return;
	if (options.wmname)
		file = g_build_filename(g_get_user_config_dir(), RESNAME, options.wmname, "rc", NULL);
	else
		file = g_build_filename(g_get_user_config_dir(), RESNAME, "rc", NULL);
	free(options.filename);
	options.filename = strdup(file);
	g_free(file);
}

static void
get_defaults(void)
{
	const char *p;
	int n;

	if (options.command == CommandDefault)
		options.command = CommandMenugen;
	if (options.display) {
		if (options.screen < 0 && (p = strrchr(options.display, '.'))
		    && (n = strspn(++p, "0123456789")) && *(p + n) == '\0')
			options.screen = atoi(p);
	}
	if (!options.hidden && !options.minimized)
		options.normal = True;
	get_default_root();
	get_default_wmname();
	get_default_format();
	get_default_desktop();
	get_default_output();
	get_default_theme();
	get_default_icon_theme();
	get_default_config();
}

int
main(int argc, char *argv[])
{
	Command command = CommandDefault;
	char *p;

	saveArgc = argc;
	saveArgv = g_strdupv(argv);

	setlocale(LC_ALL, "");

	set_defaults();

	get_resources();

	if (options.debug > 0) {
		char **arg;

		DPRINTF(1, "Command was:");
		for (arg = saveArgv; arg && *arg; arg++)
			fprintf(stderr, " %s", *arg);
		fprintf(stderr, "\n");
	}

	if ((p = strstr(argv[0], "-menugen")) && !p[8])
		options.command = CommandMenugen;
	else if ((p = strstr(argv[0], "-popmenu")) && !p[6])
		options.command = CommandPopMenu;
	else if ((p = strstr(argv[0], "-monitor")) && !p[8])
		options.command = CommandMonitor;
	else if ((p = strstr(argv[0], "-refresh")) && !p[8])
		options.command = CommandRefresh;
	else if ((p = strstr(argv[0], "-restart")) && !p[8])
		options.command = CommandRestart;
	else if ((p = strstr(argv[0], "-quit")) && !p[5])
		options.command = CommandQuit;

	while (1) {
		int c, val, len;
		char *endptr = NULL;

#ifdef _GNU_SOURCE
		int option_index = 0;
		/* *INDENT-OFF* */
		static struct option long_options[] = {
			{"display",		required_argument,	NULL,	 1 },
			{"screen",		required_argument,	NULL,	 4 },
			{"Monitor",		required_argument,	NULL,	 5 },

			{"timeout",		required_argument,	NULL,	'u'},
			{"iconsize",		required_argument,	NULL,	'z'},
			{"fontsize",		required_argument,	NULL,	'Z'},
			{"border",		required_argument,	NULL,	'B'},
			{"filename",		required_argument,	NULL,	'c'},
			{"timestamp",		required_argument,	NULL,	'T'},
			{"pointer",		no_argument,		NULL,	'p'},
			{"keyboard",		no_argument,		NULL,	'K'},
			{"keypress",		optional_argument,	NULL,	'k'},
			{"button",		required_argument,	NULL,	'b'},
			{"which",		required_argument,	NULL,	'i'},
			{"where",		required_argument,	NULL,	'W'},

			{"wmname",		required_argument,	NULL,	'w'},
			{"desktop",		required_argument,	NULL,	'd'},
			{"theme",		required_argument,	NULL,	't'},

			{"order",		required_argument,	NULL,	'O'},
			{"normal",		no_argument,		NULL,	'n'},
			{"hidden",		no_argument,		NULL,	'H'},
			{"minimized",		no_argument,		NULL,	'm'},
			{"all-monitors",	no_argument,		NULL,	'a'},
			{"all-workspaces",	no_argument,		NULL,	'A'},
			{"noactivate",		no_argument,		NULL,	'N'},
			{"raise",		no_argument,		NULL,	'U'},

			{"format",		required_argument,	NULL,	'f'},
			{"fullmenu",		no_argument,		NULL,	'F'},
			{"nofullmenu",		no_argument,		NULL,	'l'},
			{"root-menu",		required_argument,	NULL,	'r'},
			{"output",		optional_argument,	NULL,	'o'},
			{"icons",		no_argument,		NULL,    6 },
			{"noicons",		no_argument,		NULL,	'I'},
			{"launch",		no_argument,		NULL,	'L'},
			{"nolaunch",		no_argument,		NULL,	'0'},
			{"style",		required_argument,	NULL,	's'},
			{"menu",		required_argument,	NULL,	'M'},


			{"notray",		no_argument,		NULL,	 2 },
			{"nogenerate",		no_argument,		NULL,	 3 },

			{"menugen",		no_argument,		NULL,	'G'},
			{"monitor",		no_argument,		NULL,	'g'},
			{"popmenu",		no_argument,		NULL,	'P'},
			{"refresh",		no_argument,		NULL,	'E'},
			{"restart",		no_argument,		NULL,	'S'},
			{"replace",		no_argument,		NULL,	'R'},
			{"quit",		no_argument,		NULL,	'q'},

			{"excluded",		no_argument,		NULL,	 10},
			{"nodisplay",		no_argument,		NULL,	 11},
			{"unallocated",		no_argument,		NULL,	 12},
			{"empty",		no_argument,		NULL,	 13},
			{"separators",		no_argument,		NULL,	 14},
			{"sort",		no_argument,		NULL,	 15},
			{"actions",		no_argument,		NULL,	 17},

			{"clientId",		required_argument,	NULL,	'8'},
			{"restore",		required_argument,	NULL,	'9'},

			{"tooltips",		no_argument,		NULL,	 16},
			{"die-on-error",	no_argument,		NULL,	'e'},
			{"exit",		no_argument,		NULL,	'x'},
			{"debug",		optional_argument,	NULL,	'D'},
			{"verbose",		optional_argument,	NULL,	'v'},
			{"help",		no_argument,		NULL,	'h'},
			{"version",		no_argument,		NULL,	'V'},
			{"copying",		no_argument,		NULL,	'C'},
			{"?",			no_argument,		NULL,	'h'},
			{ 0, }
		};
		/* *INDENT-ON* */

		c = getopt_long_only(argc, argv, "u:z:Z:B:c:T:pKk::b:i:W:w:d:t:O:nHmaANUf:Flr:o::IL0sMGgPESRqexD::v::hVCH?",
				     long_options, &option_index);
#else				/* _GNU_SOURCE */
		c = getopt(argc, argv, "u:z:Z:B:c:T:pKk:b:i:W:w:d:t:O:nHmaANUf:Flr:o:IL0sMGgPESRqexD:vhVCH?");
#endif				/* _GNU_SOURCE */
		if (c == -1) {
			DPRINTF(1, "%s: done options processing\n", argv[0]);
			break;
		}
		switch (c) {
		case 0:
			goto bad_usage;

		case 1:	/* --display DISPLAY */
			setenv("DISPLAY", optarg, TRUE);
			free(options.display);
			options.display = strdup(optarg);
			break;
		case 4:	/* --screen SCREEN */
			val = strtoul(optarg, &endptr, 0);
			if (endptr && *endptr)
				goto bad_option;
			options.screen = val;
			break;
		case 5: /* --Monitor MONITOR */
			val = strtoul(optarg, &endptr, 0);
			if (endptr && *endptr)
				goto bad_option;
			options.monitor = val;
			break;

		case 'u':	/* -u, --timeout MILLISECONDS */
			val = strtoul(optarg, &endptr, 0);
			if (endptr && *endptr)
				goto bad_option;
			options.timeout = val;
			break;
		case 'z':	/* -z, --iconsize SIZE */
			val = strtoul(optarg, &endptr, 10);
			if (endptr && *endptr)
				goto bad_option;
			if (val < 12)
				val = 12;
			if (val > 64)
				val = 64;
			break;
		case 'Z':	/* -Z, --fontsize POINTS */
			options.fontsize = strtod(optarg, &endptr);
			if (endptr && *endptr)
				goto bad_option;
			break;
		case 'B':	/* -B, --border PIXELS */
			val = strtoul(optarg, &endptr, 0);
			if (endptr && *endptr)
				goto bad_option;
			if (val < 0 || val > 20)
				goto bad_option;
			options.border = val;
			break;
		case 'c':	/* -c, --filename FILENAME */
			free(options.filename);
			options.filename = strdup(optarg);
			break;

		case 'w':	/* --wmname, -w WMNAME */
			free(options.wmname);
			options.wmname = strdup(optarg);
			break;
		case 'f':	/* --format, -f FORMAT */
			free(options.format);
			options.format = strdup(optarg);
			break;
		case 'F':	/* -F, --fullmenu */
			options.style = StyleFullmenu;
			break;
		case 'l':	/* -l, --nofullmenu */
			options.style = StyleAppmenu;
			break;
		case 'd':	/* -d, --desktop DESKTOP */
			free(options.desktop);
			options.desktop = strdup(optarg);
			break;
		case 'r':	/* -r, --root-menu MENU */
			free(options.rootmenu);
			options.rootmenu = strdup(optarg);
			break;
		case 'o':	/* -o, --output [OUTPUT] */
			options.fileout = True;
			if (optarg != NULL) {
				free(options.menufile);
				options.menufile = strdup(optarg);
			}
			break;
		case 6:		/* --icons */
			options.noicons = False;
			break;
		case 'I':	/* -I, --noicons */
			options.noicons = True;
			break;
		case 't':	/* -t, --theme THEME */
			free(options.theme);
			options.theme = strdup(optarg);
			break;
		case 'L':	/* -L, --launch */
			options.launch = True;
			break;
		case '0':	/* -0, --nolaunch */
			options.launch = False;
			break;
		case 's':	/* -s, --style STYLE */
			if (!strncmp("fullmenu", optarg, strlen(optarg))) {
				options.style = StyleFullmenu;
				break;
			}
			if (!strncmp("appmenu", optarg, strlen(optarg))) {
				options.style = StyleAppmenu;
				break;
			}
			if (!strncmp("submenu", optarg, strlen(optarg))) {
				options.style = StyleSubmenu;
				break;
			}
			if (!strncmp("entries", optarg, strlen(optarg))) {
				options.style = StyleEntries;
				break;
			}
			goto bad_option;
		case 'M':	/* -M, --menu MENUS */
			free(options.menu);
			options.menu = strdup(optarg);
			break;

		case 'K':	/* -K, --keyboard */
			options.keyboard = True;
			options.pointer = False;
			options.button = 0;
			break;
		case 'p':	/* -p, --pointer */
			options.pointer = True;
			options.keyboard = False;
			if (!options.button)
				options.button = 1;
			break;

		case 'b':	/* -b, --button [BUTTON] */
			if (optarg) {
				val = strtoul(optarg, &endptr, 0);
				if (endptr && *endptr)
					goto bad_option;
				if (val < 0 || val > 8)
					goto bad_option;
			} else
				val = 1;
			if (val) {
				options.keyboard = False;
				options.pointer = True;
			} else {
				options.keyboard = True;
				options.pointer = False;
			}
			options.button = val;
			break;
		case 'k':	/* -k, --keypress [KEYSPEC] */
			if (options.command != CommandPopMenu)
				goto bad_option;
			options.button = 0;
			if (!optarg)
				break;
			free(options.keypress);
			options.keypress = strdup(optarg);
			break;
		case 'i':	/* -i, --which WHICH */
			if (options.which != UseScreenDefault)
				goto bad_option;
			if (!(len = strlen(optarg)))
				goto bad_option;
			if (!strncasecmp("default", optarg, len))
				options.which = UseScreenDefault;
			else if (!strncasecmp("active", optarg, len))
				options.which = UseScreenActive;
			else if (!strncasecmp("focused", optarg, len))
				options.which = UseScreenFocused;
			else if (!strncasecmp("pointer", optarg, len))
				options.which = UseScreenPointer;
			else {
				options.screen = strtoul(optarg, &endptr, 0);
				if (endptr && *endptr)
					goto bad_option;
				options.which = UseScreenSpecified;
			}
			break;
		case 'W':	/* -W, --where WHERE */
			if (options.where != PositionDefault)
				goto bad_option;
			if (!(len = strlen(optarg)))
				goto bad_option;
			if (!strncasecmp("default", optarg, len))
				options.where = PositionDefault;
			else if (!strncasecmp("pointer", optarg, len))
				options.where = PositionPointer;
			else if (!strncasecmp("center", optarg, len))
				options.where = PositionCenter;
			else if (!strncasecmp("topleft", optarg, len))
				options.where = PositionTopLeft;
			else if (!strncasecmp("bottomright", optarg, len))
				options.where = PositionBottomRight;
			else {
				int mask, x = 0, y = 0;
				unsigned int w = 0, h = 0;

				mask = XParseGeometry(optarg, &x, &y, &w, &h);
				if (!(mask & XValue) || !(mask & YValue))
					goto bad_option;
				options.where = PositionSpecified;
				options.geom.mask = mask;
				options.geom.x = x;
				options.geom.y = y;
				options.geom.w = w;
				options.geom.h = h;
			}
			break;
		case 'O':	/* -O, --order ORDERTYPE */
			if (options.order != WindowOrderDefault)
				goto bad_option;
			if (!(len = strlen(optarg)))
				goto bad_option;
			if (!strncasecmp("client", optarg, len))
				options.order = WindowOrderClient;
			else if (!strncasecmp("stacking", optarg, len))
				options.order = WindowOrderStacking;
			else
				goto bad_option;
			break;

		case 'T':	/* -T, --timestamp TIMESTAMP */
			options.timestamp = strtoul(optarg, &endptr, 0);
			if (endptr && *endptr)
				goto bad_option;
			break;

		case 'n':	/* -n, --normal */
			options.normal = True;
			break;
		case 'H':	/* -H, --hidden */
			options.hidden = True;
			break;
		case 'm':	/* -m, --minimized */
			options.minimized = True;
			break;
		case 'a':	/* -a, --all-monitors */
			options.monitors = True;
			break;
		case 'A':	/* -A, --all-workspaces */
			options.workspaces = True;
			break;
		case 'N':	/* -N, --noactivate */
			options.activate = False;
			break;
		case 'U':	/* -U, --raise */
			options.raise = True;
			break;

		case 2:	/* --notray */
			options.systray = False;
			break;
		case 3:	/* --nogenerate */
			if (options.command == CommandMenugen)
				goto bad_option;
			options.generate = False;
			break;

		case 10:	/* --excluded */
			options.treeflags ^= GMENU_TREE_FLAGS_INCLUDE_EXCLUDED;
			break;
		case 11:	/* --nodisplay */
			options.treeflags ^= GMENU_TREE_FLAGS_INCLUDE_NODISPLAY;
			break;
		case 12:	/* --unallocated */
			options.treeflags ^= GMENU_TREE_FLAGS_INCLUDE_UNALLOCATED;
			break;
		case 13:	/* --empty */
			options.treeflags ^= GMENU_TREE_FLAGS_SHOW_EMPTY;
			break;
		case 14:	/* --separators */
			options.treeflags ^= GMENU_TREE_FLAGS_SHOW_ALL_SEPARATORS;
			break;
		case 15:	/* --sort */
			options.treeflags ^= GMENU_TREE_FLAGS_SORT_DISPLAY_NAME;
			break;
		case 17:	/* --actions */
			options.actions = TRUE;
			break;

		case 'G':	/* -G, --menugen */
			if (options.command != CommandDefault)
				goto bad_command;
			if (command == CommandDefault)
				command = CommandMenugen;
			options.command = CommandMenugen;
			break;
		case 'P':	/* -P, --popmenu */
			if (options.command != CommandDefault)
				goto bad_command;
			if (command == CommandDefault)
				command = CommandPopMenu;
			options.command = CommandPopMenu;
			break;
		case 'g':	/* -g, --monitor */
			if (options.command != CommandDefault)
				goto bad_command;
			if (command == CommandDefault)
				command = CommandMonitor;
			options.command = CommandMonitor;
			break;
		case 'E':	/* -E, --refresh */
			if (options.command != CommandDefault)
				goto bad_command;
			if (command == CommandDefault)
				command = CommandRefresh;
			options.command = CommandRefresh;
			break;
		case 'S':	/* -S, --restart */
			if (options.command != CommandDefault)
				goto bad_command;
			if (command == CommandDefault)
				command = CommandRestart;
			options.command = CommandRestart;
			break;
		case 'q':	/* -q, --quit */
			if (options.command != CommandDefault)
				goto bad_command;
			if (command == CommandDefault)
				command = CommandQuit;
			options.command = CommandQuit;
			break;
		case 'R':	/* -R, --replace */
			options.replace = True;
			break;

		case '8':	/* -clientId CLIENTID */
			free(options.clientId);
			options.clientId = strdup(optarg);
			break;
		case '9':	/* -restore SAVEFILE */
			free(options.saveFile);
			options.saveFile = strdup(optarg);
			break;

		case 16:	/* --tooltips */
			options.tooltips = True;
			break;
		case 'x':	/* -x, --exit */
			options.exit = True;
			break;

		case 'D':	/* -D, --debug [LEVEL] */
			DPRINTF(1, "increasing debug verbosity\n");
			if (optarg == NULL) {
				options.debug++;
				break;
			}
			if ((val = strtol(optarg, &endptr, 0)) < 0)
				goto bad_option;
			if (endptr && *endptr)
				goto bad_option;
			options.debug = val;
			break;
		case 'v':	/* -v, --verbose [LEVEL] */
			DPRINTF(1, "increasing output verbosity\n");
			if (optarg == NULL) {
				options.output++;
				break;
			}
			if ((val = strtol(optarg, &endptr, 0)) < 0)
				goto bad_option;
			if (endptr && *endptr)
				goto bad_option;
			options.output = val;
			break;
		case 'h':	/* -h, --help, -?, --? */
			DPRINTF(1, "Setting command to CommandHelp\n");
			command = CommandHelp;
			break;
		case 'V':	/* -V, --version */
			if (options.command != CommandDefault)
				goto bad_command;
			if (command == CommandDefault)
				command = CommandVersion;
			options.command = CommandVersion;
			break;
		case 'C':	/* -C, --copying */
			if (options.command != CommandDefault)
				goto bad_command;
			if (command == CommandDefault)
				command = CommandCopying;
			options.command = CommandCopying;
			break;
		case '?':
		default:
		      bad_option:
			optind--;
			goto bad_nonopt;
		      bad_nonopt:
			if (options.output || options.debug) {
				if (optind < argc) {
					EPRINTF("syntax error near '");
					while (optind < argc) {
						fprintf(stderr, "%s", argv[optind++]);
						fprintf(stderr, "%s", (optind < argc) ? " " : "");
					}
					fprintf(stderr, "'\n");
				} else {
					EPRINTF("missing option or argument");
					fprintf(stderr, "\n");
				}
				fflush(stderr);
			      bad_usage:
				usage(argc, argv);
			}
			exit(EXIT_SYNTAXERR);
		      bad_command:
			fprintf(stderr, "%s: only one command option allowed\n", argv[0]);
			goto bad_usage;
		}
	}
	DPRINTF(1, "%s: option index = %d\n", argv[0], optind);
	DPRINTF(1, "%s: option count = %d\n", argv[0], argc);
	if (optind < argc) {
		EPRINTF("excess non-option arguments near '");
		while (optind < argc) {
			fprintf(stderr, "%s", argv[optind++]);
			fprintf(stderr, "%s", (optind < argc) ? " " : "");
		}
		fprintf(stderr, "'\n");
		usage(argc, argv);
		exit(EXIT_SYNTAXERR);
	}
	startup(argc, argv);
	get_defaults();

	switch (command) {
	case CommandDefault:
		options.command = CommandMenugen;
	case CommandMenugen:
		DPRINTF(1, "%s: just generating window manager root menu\n", argv[0]);
		do_generate(argc, argv);
		break;
	case CommandMonitor:
		DPRINTF(1, "%s: running a new instance\n", argv[0]);
		do_run(argc, argv);
		break;
	case CommandRefresh:
		DPRINTF(1, "asking existing instance to refresh\n");
		do_run(argc, argv);
		break;
	case CommandRestart:
		DPRINTF(1, "asking existing instance to restart\n");
		do_run(argc, argv);
		break;
	case CommandPopMenu:
		DPRINTF(1, "asking existing instance to pop menu\n");
		do_run(argc, argv);
		break;
	case CommandQuit:
		if (!options.display) {
			EPRINTF("cannot ask instance to quit without DISPLAY\n");
			exit(EXIT_FAILURE);
		}
		DPRINTF(1, "asking existing instance to quit\n");
		do_quit(argc, argv);
		break;
	case CommandHelp:
		DPRINTF(1, "printing help message\n");
		help(argc, argv);
		break;
	case CommandVersion:
		DPRINTF(1, "printing version message\n");
		version(argc, argv);
		break;
	case CommandCopying:
		DPRINTF(1, "printing copying message\n");
		copying(argc, argv);
		break;
	default:
		usage(argc, argv);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

/** @} */

// vim: set sw=8 tw=80 com=srO\:/**,mb\:*,ex\:*/,srO\:/*,mb\:*,ex\:*/,b\:TRANS fo+=tcqlorn foldmarker=@{,@} foldmethod=marker:
