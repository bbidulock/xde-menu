
xde_man1_files = \
	xde-menu.man

alias_man_files = \
	xde-menugen.man \
	xde-menu-monitor.man \
	xde-menu-popmenu.man \
	xde-menu-quit.man \
	xde-menu-refresh.man \
	xde-menu-replace.man \
	xde-menu-restart.man

nodist_man1_MANS = $(xde_man1_files) $(alias_man_files)
CLEANFILES = $(xde_man1_files) $(alias_man_files)
noinst_man1_MANS = mwm.man
noinst_man4_MANS = dtwmrc.man mwmrc.man

$(alias_man_files):
	echo ".so man1/xde-menu.1" >$@

EXTRA_DIST = \
	xde-menu.pod \
	dtwmrc.man \
	mwm.man \
	mwmrc.man

$(xde_man1_files): %.man: %.pod
	$(AM_V_GEN)pod2man --center="User Commands" \
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

#$(xde_man5_files): %.man: %.pod
#	$(AM_V_GEN)pod2man --center="Standards, Environments and Macros" \
#		--date="$(DATE)" \
#		--errors="none" \
#		--fixed="CW" \
#		--fixedbold="CB" \
#		--fixeditalic="CI" \
#		--fixedbolditalic="CX" \
#		--nourls \
#		--release="$(PACKAGE) $(VERSION)" \
#		--section="5" \
#		$< >$@

