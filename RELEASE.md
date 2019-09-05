[xde-menu -- release notes.  2019-09-05]: #

xde-menu 0.11 -- Maintenance release of xde-menu
================================================

This is another release of the xde-menu package that provides XDG
compliant menu generation for a wide range of light-weight window
managers as well as providing a pop-up and system-tray GTK+ menu.  All
of the functionality is working, including many window-manager specific
sub-menus and startup notification completion.

This release is a maintenance release, primarily for bug fixes, that
addresses all outstanding issues at the time of release.  The package
will no longer build against libgnome-menu, but only libgnome-menu-3.0,
as the libgnome-menu build was failing and could not reasonably be fixed.
It removes deprecated m4 macros from configure.ac and removes deprecated
keywords from the desktop entry file.

Included in the release is an autoconf tarball for building the package
from source.  See the [NEWS](NEWS) and [TODO](TODO) file in the release
for more information.  Please report problems to the issues list on
[GitHub](https://github.com/bbidulock/xde-menu/issues).

[ vim: set ft=markdown sw=4 tw=72 nocin nosi fo+=tcqlorn spell: ]: #
