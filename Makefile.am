
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src man data

EXTRA_DIST = INSTALL COPYING AUTHORS AUTHORS.in NEWS NEWS.in README README.in THANKS THANKS.in TODO TODO.in ChangeLog MENUS.html MENUS.asciidoc

ChangeLog:
	( \
	  echo -e "# created with git log --stat=76 -M -C|fmt -sct -w80\n" ; \
	  git log --stat=76 -M -C|fmt -sct -w80 \
	)>$@

AUTHORS.in:
	( \
	  echo "\@PACKAGE\@ -- authors file.  \@DATE\@" ; \
	  echo "" ; \
	  git log|grep '^Author:'|awk '{if(!authors[$$0]){print$$0;authors[$$0]=1;}}'|tac \
	)>$@

README: README.in
	sed -r -e 's:\@PACKAGE\@:$(PACKAGE):g;s:\@VERSION\@:$(VERSION):g;s:\@DATE\@:$(DATE):g' $< >$@

NEWS: NEWS.in
	sed -r -e 's:\@PACKAGE\@:$(PACKAGE):g;s:\@VERSION\@:$(VERSION):g;s:\@DATE\@:$(DATE):g' $< >$@

AUTHORS: AUTHORS.in
	sed -r -e 's:\@PACKAGE\@:$(PACKAGE):g;s:\@VERSION\@:$(VERSION):g;s:\@DATE\@:$(DATE):g' $< >$@

THANKS: THANKS.in
	sed -r -e 's:\@PACKAGE\@:$(PACKAGE):g;s:\@VERSION\@:$(VERSION):g;s:\@DATE\@:$(DATE):g' $< >$@

TODO: TODO.in
	sed -r -e 's:\@PACKAGE\@:$(PACKAGE):g;s:\@VERSION\@:$(VERSION):g;s:\@DATE\@:$(DATE):g' $< >$@

MENUS.html: MENUS.asciidoc
	asciidoc -o - $< >$@

dist_noinst_SCRIPTS = autogen.sh configure.sh rebuild.sh

scritps = \
	xde-menugen \
	xde-menu-monitor \
	xde-menu-popmenu \
	xde-menu-quit \
	xde-menu-refresh \
	xde-menu-replace \
	xde-menu-restart

dist_bin_SCRIPTS = $(scripts)
AM_INSTALLCHECK_STD_OPTIONS_EXEMPT = $(scripts)

