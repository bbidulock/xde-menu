#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.69)
AC_INIT([xde-menu],[0.8],[http://github.com/bbidulock/xde-menu],[xde-menu],[http://github.com/bbidulock/xde-menu/issues])
AC_REVISION([0.8])

AC_CONFIG_SRCDIR([src/xde-menu.c])
AC_CONFIG_HEADERS([autoconf.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([scripts])
AC_USE_SYSTEM_EXTENSIONS
AC_CANONICAL_TARGET

DATE='2018-09-22'
AC_SUBST([DATE])

BRANCH='0.8'
AC_SUBST([BRANCH])

# Initialize Automake
AM_INIT_AUTOMAKE([gnits 1.16 dist-lzip dist-xz no-dist-gzip std-options -Wall color-tests silent-rules tar-pax])
AM_MAINTAINER_MODE
AM_SILENT_RULES([yes])
AC_PREFIX_DEFAULT([/usr])

# Checks for programs.
AC_PROG_SED
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_PROG_AR
AC_PROG_MKDIR_P
AC_ARG_VAR([LD], [Linker loader command])

AC_ARG_VAR([MARKDOWN],[markdown command. @<:@default=markdown@:>@])
AC_CHECK_PROGS([MARKDOWN],[markdown],[${am_missing_run}markdown],[$PATH])

AC_ARG_VAR([ASCIIDOC],[asciidoc command. @<:@default=asciidoctor@:>@])
AC_CHECK_PROGS([ASCIIDOC],[asciidoc asciidoctor],[${am_missing_run}asciidoc],[$PATH])

AC_ARG_VAR([ASCIIDOC_BACKEND],[asciidoc backend @<:@default=NONE@:>@])
if test -z "$ASCIIDOC_BACKEND"; then
	case "$ASCIIDOC" in
		asciidoc) ASCIIDOC_BACKEND="--backend=html4" ;;
		asciidoctor) ASCIIDOC_BACKEND="--backend=html5" ;;
		*) AC_MSG_WARN([ASCIIDOC $ASCIIDOC is not supported.]) ;;
	esac
fi

AC_ARG_VAR([ASCIIMAN],[asciidoc to manpage converter. @<:@default=a2x@:>@])
AC_CHECK_PROGS([ASCIIMAN],[a2x asciidoctor],[${am_missing_run}a2x],[$PATH])

AC_ARG_VAR([ASCIIMAN_FORMAT],[asciidoc manpage option @<:@default=NONE@:>@])
if test -z "$ASCIIMAN_FORMAT"; then
	case "$ASCIIMAN" in
		a2x) ASCIIMAN_FORMAT="--format=manpage" ;;
		asciidoctor) ASCIIMAN_FORMAT="--backend=manpage" ;;
		*) AC_MSG_WARN([ASCIIMAN $ASCIIMAN is not supported.]) ;;
	esac
fi

AC_ARG_VAR([LINKS],[links command. @<:@default=lynx@:>@])
AC_CHECK_PROGS([LINKS],[lynx links],[${am_missing_run}lynx],[$PATH])
if test "$LINKS" = "links"; then
	LINKS="links -codepage utf-8"
fi

AC_DISABLE_STATIC
LT_PATH_LD
LT_PREREQ([2.4.2])
LT_INIT([dlopen])
LT_LANG([C])
AC_PROG_LIBTOOL
AC_SUBST([LIBTOOL_DEPS])

PKG_PROG_PKG_CONFIG([0.14.0])

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_PATH_X
AC_PATH_XTRA
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
