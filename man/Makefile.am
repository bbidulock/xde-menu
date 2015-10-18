
xde_man_files = \
	xde-menu.man

nodist_man1_MANS = $(xde_man_files)
CLEANFILES = $(xde_man_files)
noinst_man1_MANS = mwm.man
noinst_man4_MANS = dtwmrc.man mwmrc.man

EXTRA_DIST = \
	xde-menu.pod \
	dtwmrc.man \
	mwm.man \
	mwmrc.man

SUFFIXES = .man .pod

.pod.man:
	pod2man --center="User Commands" \
		--date="$(DATE)" \
		--errors="none" \
		--fixed="CW" \
		--fixedbold="CB" \
		--fixeditalic="CI" \
		--fixedbolditalic="CX" \
		--nourls \
		--release="$(PACKAGE) $(VERSION)" \
		--section="1" \
		$< >$@

