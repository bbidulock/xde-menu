[xde-menu -- read me first file.  @DATE]: #

xde-menu
===============

Package `xde-menu-0.4` was released under GPLv3 license 2016-08-11.

This package provides a number of "C"-language tools for working with
the _X Desktop Environment_.  Most of these tools were previously written
in `perl(1)` and were part of the `xde-tools` package.  They have now been
codified in "C" for speed and to provide access to libraries not
available from `perl(1)`.


Release
-------

This is the `xde-menu-0.4` package, released 2016-08-11.  This
release, and the latest version, can be obtained from the [GitHub
repository][1], using a command such as:

    $> git clone https://github.com/bbidulock/xde-menu.git

Please see the [NEWS][2] file for release notes and history of user
visible changes for the current version, and the [ChangeLog][3]
file for a more detailed history of implementation changes.  The
[TODO][4] file lists features not yet implemented and other
outstanding items.

Please see the [INSTALL][5] file for installation instructions.

When working from `git(1)`, please use this file.  An abbreviated
installation procedure that works for most applications appears below.

This release is published under GPLv3.  Please see the license in
the file [COPYING][6].


Quick Start
-----------

The quickest and easiest way to get `xde-menu` up and running
is to run the following commands:

    $> git clone https://github.com/bbidulock/xde-menu.git
    $> cd xde-menu
    $> ./autogen.sh
    $> ./configure --prefix=/usr --sysconfdir=/etc
    $> make V=0
    $> make DESTDIR="$pkgdir" install

This will configure, compile and install `xde-menu` the quickest.
For those who would like to spend the extra 15 seconds reading
the output of `./configure --help`, some compile options can be
turned on and off before the build.

For general information on GNU's `./configure`, see the file
[INSTALL][5].


Issues
------

Report problems at GitHub [here][7].



[1]: https://github.com/bbidulock/xde-menu
[2]: NEWS
[3]: ChangeLog
[4]: TODO
[5]: INSTALL
[6]: COPYING
[7]: https://github.com/bbidulock/xde-menu/issues

[ vim: set ft=markdown sw=4 tw=72 nocin nosi fo+=tcqlorn spell: ]: #
