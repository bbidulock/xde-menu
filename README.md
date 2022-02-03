[xde-menu -- read me first file.  2022-02-02]: #

xde-menu
===============

Package `xde-menu-0.14` was released under GPLv3 license
2022-02-02.

This package provides a number of "C"-language tools for working with
the _X Desktop Environment_.  Most of these tools were previously
written in `perl(1)` and were part of the `xde-tools` package.  They
have now been codified in "C" for speed and to provide access to
libraries not available from `perl(1)`.

For screenshots and examples, see [SAMPLES](samples).

The source for `xde-menu` is hosted on [GitHub][1].


Release
-------

This is the `xde-menu-0.14` package, released 2022-02-02.
This release, and the latest version, can be obtained from [GitHub][1],
using a command such as:

    $> git clone https://github.com/bbidulock/xde-menu.git

Please see the [RELEASE][3] and [NEWS][4] files for release notes and
history of user visible changes for the current version, and the
[ChangeLog][5] file for a more detailed history of implementation
changes.  The [TODO][6] file lists features not yet implemented and
other outstanding items.

Please see the [INSTALL][8] file for installation instructions.

When working from `git(1)`, please use this file.  An abbreviated
installation procedure that works for most applications appears below.

This release is published under GPLv3.  Please see the license in the
file [COPYING][10].


Quick Start
-----------

The quickest and easiest way to get `xde-menu` up and
running is to run the following commands:

    $> git clone https://github.com/bbidulock/xde-menu.git
    $> cd xde-menu
    $> ./autogen.sh
    $> ./configure
    $> make
    $> make DESTDIR="$pkgdir" install

This will configure, compile and install `xde-menu` the
quickest.  For those who like to spend the extra 15 seconds reading
`./configure --help`, some compile time options can be turned on and off
before the build.

For general information on GNU's `./configure`, see the file
[INSTALL][8].


Dependencies
------------

To build and install the package you will need a basic development
installation.  To build and install the package you will also need the
``libwnck``, ``libsm``, ``gnome-menus`` and ``gdk-pixbuf-xlib``
development packages.

To run the package, you should also build and install the
[``libwnck+``](https://github.com/bbidulock/libwnck+) package (for
enhanced functionality),
[``xdg-launch``](https://github.com/bbidulock/xdg-launch) package (for
light-weight window manager launch notification), and
[``xde-theme``](https://github.com/bbidulock/xde-theme) package (for
light-weight window manager style and theme change support).

To run the package, you will likely also want to build and install the
[``xde-helpers``](https://github.com/bbidulock/xde-helpers) package (for
XDG root menu definitions for _XDE_).


Running
-------

Read the manual page after installation:

    $> man xde-menu


Enjoy!


Issues
------

Report issues on GitHub [here][2].



[1]: https://github.com/bbidulock/xde-menu
[2]: https://github.com/bbidulock/xde-menu/issues
[3]: https://github.com/bbidulock/xde-menu/blob/0.14/RELEASE
[4]: https://github.com/bbidulock/xde-menu/blob/0.14/NEWS
[5]: https://github.com/bbidulock/xde-menu/blob/0.14/ChangeLog
[6]: https://github.com/bbidulock/xde-menu/blob/0.14/TODO
[7]: https://github.com/bbidulock/xde-menu/blob/0.14/COMPLIANCE
[8]: https://github.com/bbidulock/xde-menu/blob/0.14/INSTALL
[9]: https://github.com/bbidulock/xde-menu/blob/0.14/LICENSE
[10]: https://github.com/bbidulock/xde-menu/blob/0.14/COPYING

[ vim: set ft=markdown sw=4 tw=72 nocin nosi fo+=tcqlorn spell: ]: #
