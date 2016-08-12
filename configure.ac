
AC_PREREQ(2.69)
AC_INIT([xde-menu],[0.4],[http://github.com/bbidulock/xde-menu],[xde-menu],[http://github.com/bbidulock/xde-menu/issues])
AC_REVISION([0.4])

AC_CONFIG_SRCDIR([src/xde-menu.c])
AC_CONFIG_HEADERS([autoconf.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([scripts])
AC_USE_SYSTEM_EXTENSIONS

DATE='2016-08-11'
AC_SUBST([DATE])

AM_INIT_AUTOMAKE([gnits 1.14 dist-xz no-dist-gzip std-options -Wall color-tests silent-rules tar-pax])
AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_PROG_AR
AC_PROG_MKDIR_P
LT_PATH_LD

AC_DISABLE_STATIC
LT_PREREQ([2.4.2])
LT_INIT([dlopen])
LT_LANG([C])
AC_SUBST([LIBTOOL_DEPS])

PKG_PROG_PKG_CONFIG([0.14.0])

# Checks for libraries.

# Checks for header files.
AC_PATH_X
AC_CHECK_HEADERS([fcntl.h locale.h stddef.h stdint.h stdlib.h string.h strings.h sys/ioctl.h sys/time.h syslog.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gethostname memmove select strcasecmp strchr strcspn strdup strerror strncasecmp strndup strpbrk strrchr strspn strstr strtol strtoul])

PKG_CHECK_MODULES([X11],[x11])
PKG_CHECK_MODULES([XEXT],[xext])
dnl PKG_CHECK_MODULES([XAU],[xau])
dnl PKG_CHECK_MODULES([XSCRNSAVER],[xscrnsaver])
dnl PKG_CHECK_MODULES([XDMCP],[xdmcp])
PKG_CHECK_MODULES([ICE],[ice])
PKG_CHECK_MODULES([SMLIB],[sm])
dnl PKG_CHECK_MODULES([XFT],[xft])
PKG_CHECK_MODULES([GDK],[gdk-pixbuf-xlib-2.0])
PKG_CHECK_MODULES([GLIB],[glib-2.0])
PKG_CHECK_MODULES([GOBJ],[gobject-2.0])
dnl PKG_CHECK_MODULES([DBUS_GLIB],[dbus-glib-1])
PKG_CHECK_MODULES([GIO],[gio-2.0])
PKG_CHECK_MODULES([GTK],[gtk+-2.0 >= 2.4.0])
PKG_CHECK_MODULES([WNCK],[libwnck-1.0])
PKG_CHECK_MODULES([CAIRO],[cairo])
dnl PKG_CHECK_MODULES([SYSTEMD],[libsystemd])

AC_ARG_ENABLE([gnome-menus3],
	AC_HELP_STRING([--disable-gnome-menus3],
		[Disable GNOME menus 3.0 (use 2.0 instead) @<:@default=auto@:>@]))
if test "x$enable_gnome_menus3" != xno ; then
	PKG_CHECK_MODULES([GNOME_MENU],[libgnome-menu-3.0],
		[AC_DEFINE([HAVE_GNOME_MENUS_3],[1],[Define to 1 to support GNOME menus 3.])],
		[enable_gnome_menus3=no])
fi
AC_MSG_CHECKING([for GNOME MENUS 3 support])
AC_MSG_RESULT([${enable_gnome_menus3:-yes}])

if test "x$enable_gnome_menus3" = xno ; then
	PKG_CHECK_MODULES([GNOME_MENU],[libgnome-menu])
fi

dnl AC_ARG_ENABLE([xrandr],
dnl 	AC_HELP_STRING([--disable-xrandr],
dnl 		[Disable XRANDR support @<:@default=auto@:>@]))
dnl if test "x$enable_xrandr" != xno ; then
dnl 	PKG_CHECK_MODULES([XRANDR],[xrandr],
dnl 		[AC_DEFINE([XRANDR],[1], [Define to 1 to support XRANDR extension.])],
dnl 		[enable_xrandr=no])
dnl fi
dnl AC_MSG_CHECKING([for XRANDR support])
dnl AC_MSG_RESULT([${enable_xrandr:-yes}])

dnl AC_ARG_ENABLE([xinerama],
dnl 	AC_HELP_STRING([--disable-xinerama],
dnl 		[Disable XINERAMA support @<:@default=auto@:>@]))
dnl if test "x$enable_xinerama" != xno ; then
dnl 	PKG_CHECK_MODULES([XINERAMA],[xinerama],
dnl 		[AC_DEFINE([XINERAMA],[1], [Define to 1 to support XINERAMA extension.])],
dnl 		[enable_xinerama=no])
dnl fi
dnl AC_MSG_CHECKING([for XINERAMA support])
dnl AC_MSG_RESULT([${enable_xinerama:-yes}])

AC_ARG_ENABLE([debug],
	AC_HELP_STRING([--enable-debug],
		[Enable debugging support @<:@default=disabled@:>@]))
if test "x$enable_debug" = xyes ; then
	AC_DEFINE_UNQUOTED([DEBUG],[],[Define to enable debugging])
fi
AC_MSG_CHECKING([for debug support])
AC_MSG_RESULT([${enable_debug:-no}])

test "x$prefix" = xNONE && prefix="$ac_default_prefix"

sharedir="$datadir"
eval "sharedir=\"$sharedir\""
eval "sharedir=\"$sharedir\""
eval "sharedir=\"$sharedir\""
AC_SUBST([sharedir])

xdgconfdir="$sysconfdir"
eval "xdgconfdir=\"$xdgconfdir\""
eval "xdgconfdir=\"$xdgconfdir\""
eval "xdgconfdir=\"$xdgconfdir\""
AC_SUBST([xdgconfdir])

xdgdatadir="$prefix"
eval "xdgdatadir=\"$xdgdatadir\""
eval "xdgdatadir=\"$xdgdatadir\""
eval "xdgdatadir=\"$xdgdatadir\""
AC_SUBST([xdgdatadir])

xdemoddir='${libdir}/xde-menu/modules'
AC_SUBST([xdemoddir])

autostartdir='$(xdgconfdir)/xdg/autostart'
AC_SUBST([autostartdir])

applicationsdir='$(xdgdatadir)/share/applications'
AC_SUBST([applicationsdir])

appdefaultsdir='$(sharedir)/X11/app-defaults'
AC_SUBST([appdefaultsdir])

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 man/Makefile
		 data/Makefile
		 ])
AC_OUTPUT

# vim: set ft=config:
