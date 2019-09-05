
AM_CFLAGS = $(X11_CFLAGS) $(XEXT_CFLAGS) $(CAIRO_CFLAGS) $(GIO_UNIX_CFLAGS) $(GDK_CFLAGS) $(GTK_CFLAGS) $(WNCK_CFLAGS) $(GNOME_MENU_CFLAGS) $(UNIQUE_CFLAGS)
AM_LDFLAGS = $(UNIQUE_LIBS) $(GNOME_MENU_LIBS) $(WNCK_LIBS) $(GTK_LIBS) $(GDK_LIBS) $(GIO_UNIX_LIBS) $(CAIRO_LIBS) $(XEXT_LIBS) $(X11_LIBS)

bin_PROGRAMS = \
	xde-menu

xde_menu_CPPFLAGS = -DNAME=\"xde-menu\"
xde_menu_SOURCES = xde-menu.h xde-menu.c
xde_menu_CFLAGS = $(AM_CFLAGS) $(ICE_CFLAGS) $(SMLIB_CFLAGS)
xde_menu_LDADD = $(SMLIB_LIBS) $(ICE_LIBS) $(AM_LDFLAGS)
xde_menu_LDFLAGS = -export-dynamic -R $(xdemoddir) -ldl

xdemod_LTLIBRARIES = \
	xde-menu-2bwm.la \
	xde-menu-adwm.la \
	xde-menu-aewm.la \
	xde-menu-aewm++.la \
	xde-menu-afterstep.la \
	xde-menu-awesome.la \
	xde-menu-blackbox.la \
	xde-menu-bspwm.la \
	xde-menu-ctwm.la \
	xde-menu-cwm.la \
	xde-menu-dtwm.la \
	xde-menu-dwm.la \
	xde-menu-echinus.la \
	xde-menu-etwm.la \
	xde-menu-ewmh.la \
	xde-menu-fluxbox.la \
	xde-menu-flwm.la \
	xde-menu-fvwm.la \
	xde-menu-glasswm.la \
	xde-menu-goomwwm.la \
	xde-menu-herbstluftwm.la \
	xde-menu-i3.la \
	xde-menu-icewm.la \
	xde-menu-jwm.la \
	xde-menu-larswm.la \
	xde-menu-matwm2.la \
	xde-menu-metacity.la \
	xde-menu-mvwm.la \
	xde-menu-mwm.la \
	xde-menu-openbox.la \
	xde-menu-openboxold.la \
	xde-menu-pekwm.la \
	xde-menu-perlpanel.la \
	xde-menu-spectrwm.la \
	xde-menu-twm.la \
	xde-menu-uwm.la \
	xde-menu-vtwm.la \
	xde-menu-waimea.la \
	xde-menu-wind.la \
	xde-menu-wm2.la \
	xde-menu-wmaker.la \
	xde-menu-wmakerold.la \
	xde-menu-wmii.la \
	xde-menu-wmx.la \
	xde-menu-xdwm.la \
	xde-menu-yeahwm.la

#module_ldflags = -module -export-dynamic -release $(VERSION) -shared -rpath $(xdemoddir) -avoid-version
module_ldflags = -module -export-dynamic -shared -rpath $(xdemoddir) -avoid-version

module_libadd = 

xde_menu_2bwm_la_CPPFLAGS = -DNAME=\"xde-2bwm\"
xde_menu_2bwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_2bwm_la_SOURCES = xde_2bwm.c
xde_menu_2bwm_la_LIBADD = $(module_libadd)
xde_menu_2bwm_la_LDFLAGS = $(module_ldflags)

xde_menu_adwm_la_CPPFLAGS = -DNAME=\"xde-adwm\"
xde_menu_adwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_adwm_la_SOURCES = xde_adwm.c
xde_menu_adwm_la_LIBADD = $(module_libadd)
xde_menu_adwm_la_LDFLAGS = $(module_ldflags)

xde_menu_aewm_la_CPPFLAGS = -DNAME=\"xde-aewm\"
xde_menu_aewm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_aewm_la_SOURCES = xde_aewm.c
xde_menu_aewm_la_LIBADD = $(module_libadd)
xde_menu_aewm_la_LDFLAGS = $(module_ldflags)

xde_menu_aewm___la_CPPFLAGS = -DNAME=\"xde-aewm++\"
xde_menu_aewm___la_CFLAGS = $(AM_CFLAGS)
xde_menu_aewm___la_SOURCES = xde_aewm++.c
xde_menu_aewm___la_LIBADD = $(module_libadd)
xde_menu_aewm___la_LDFLAGS = $(module_ldflags)

xde_menu_afterstep_la_CPPFLAGS = -DNAME=\"xde-afterstep\"
xde_menu_afterstep_la_CFLAGS = $(AM_CFLAGS)
xde_menu_afterstep_la_SOURCES = xde_afterstep.c
xde_menu_afterstep_la_LIBADD = $(module_libadd)
xde_menu_afterstep_la_LDFLAGS = $(module_ldflags)

xde_menu_awesome_la_CPPFLAGS = -DNAME=\"xde-awesome\"
xde_menu_awesome_la_CFLAGS = $(AM_CFLAGS)
xde_menu_awesome_la_SOURCES = xde_awesome.c
xde_menu_awesome_la_LIBADD = $(module_libadd)
xde_menu_awesome_la_LDFLAGS = $(module_ldflags)

xde_menu_blackbox_la_CPPFLAGS = -DNAME=\"xde-blackbox\"
xde_menu_blackbox_la_CFLAGS = $(AM_CFLAGS)
xde_menu_blackbox_la_SOURCES = xde_blackbox.c
xde_menu_blackbox_la_LIBADD = $(module_libadd)
xde_menu_blackbox_la_LDFLAGS = $(module_ldflags)

xde_menu_bspwm_la_CPPFLAGS = -DNAME=\"xde-bspwm\"
xde_menu_bspwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_bspwm_la_SOURCES = xde_bspwm.c
xde_menu_bspwm_la_LIBADD = $(module_libadd)
xde_menu_bspwm_la_LDFLAGS = $(module_ldflags)

xde_menu_ctwm_la_CPPFLAGS = -DNAME=\"xde-ctwm\"
xde_menu_ctwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_ctwm_la_SOURCES = xde_ctwm.c
xde_menu_ctwm_la_LIBADD = $(module_libadd)
xde_menu_ctwm_la_LDFLAGS = $(module_ldflags)

xde_menu_cwm_la_CPPFLAGS = -DNAME=\"xde-cwm\"
xde_menu_cwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_cwm_la_SOURCES = xde_cwm.c
xde_menu_cwm_la_LIBADD = $(module_libadd)
xde_menu_cwm_la_LDFLAGS = $(module_ldflags)

xde_menu_dtwm_la_CPPFLAGS = -DNAME=\"xde-dtwm\"
xde_menu_dtwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_dtwm_la_SOURCES = xde_dtwm.c
xde_menu_dtwm_la_LIBADD = $(module_libadd)
xde_menu_dtwm_la_LDFLAGS = $(module_ldflags)

xde_menu_dwm_la_CPPFLAGS = -DNAME=\"xde-dwm\"
xde_menu_dwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_dwm_la_SOURCES = xde_dwm.c
xde_menu_dwm_la_LIBADD = $(module_libadd)
xde_menu_dwm_la_LDFLAGS = $(module_ldflags)

xde_menu_echinus_la_CPPFLAGS = -DNAME=\"xde-echinus\"
xde_menu_echinus_la_CFLAGS = $(AM_CFLAGS)
xde_menu_echinus_la_SOURCES = xde_echinus.c
xde_menu_echinus_la_LIBADD = $(module_libadd)
xde_menu_echinus_la_LDFLAGS = $(module_ldflags)

xde_menu_etwm_la_CPPFLAGS = -DNAME=\"xde-etwm\"
xde_menu_etwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_etwm_la_SOURCES = xde_etwm.c
xde_menu_etwm_la_LIBADD = $(module_libadd)
xde_menu_etwm_la_LDFLAGS = $(module_ldflags)

xde_menu_ewmh_la_CPPFLAGS = -DNAME=\"xde-ewmh\"
xde_menu_ewmh_la_CFLAGS = $(AM_CFLAGS)
xde_menu_ewmh_la_SOURCES = xde_ewmh.c
xde_menu_ewmh_la_LIBADD = $(module_libadd)
xde_menu_ewmh_la_LDFLAGS = $(module_ldflags)

xde_menu_fluxbox_la_CPPFLAGS = -DNAME=\"xde-fluxbox\"
xde_menu_fluxbox_la_CFLAGS = $(AM_CFLAGS)
xde_menu_fluxbox_la_SOURCES = xde_fluxbox.c
xde_menu_fluxbox_la_LIBADD = $(module_libadd)
xde_menu_fluxbox_la_LDFLAGS = $(module_ldflags)

xde_menu_flwm_la_CPPFLAGS = -DNAME=\"xde-flwm\"
xde_menu_flwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_flwm_la_SOURCES = xde_flwm.c
xde_menu_flwm_la_LIBADD = $(module_libadd)
xde_menu_flwm_la_LDFLAGS = $(module_ldflags)

xde_menu_fvwm_la_CPPFLAGS = -DNAME=\"xde-fvwm\"
xde_menu_fvwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_fvwm_la_SOURCES = xde_fvwm.c
xde_menu_fvwm_la_LIBADD = $(module_libadd)
xde_menu_fvwm_la_LDFLAGS = $(module_ldflags)

xde_menu_glasswm_la_CPPFLAGS = -DNAME=\"xde-glasswm\"
xde_menu_glasswm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_glasswm_la_SOURCES = xde_glasswm.c
xde_menu_glasswm_la_LIBADD = $(module_libadd)
xde_menu_glasswm_la_LDFLAGS = $(module_ldflags)

xde_menu_goomwwm_la_CPPFLAGS = -DNAME=\"xde-goomwwm\"
xde_menu_goomwwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_goomwwm_la_SOURCES = xde_goomwwm.c
xde_menu_goomwwm_la_LIBADD = $(module_libadd)
xde_menu_goomwwm_la_LDFLAGS = $(module_ldflags)

xde_menu_herbstluftwm_la_CPPFLAGS = -DNAME=\"xde-herbstluftwm\"
xde_menu_herbstluftwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_herbstluftwm_la_SOURCES = xde_herbstluftwm.c
xde_menu_herbstluftwm_la_LIBADD = $(module_libadd)
xde_menu_herbstluftwm_la_LDFLAGS = $(module_ldflags)

xde_menu_i3_la_CPPFLAGS = -DNAME=\"xde-i3\"
xde_menu_i3_la_CFLAGS = $(AM_CFLAGS)
xde_menu_i3_la_SOURCES = xde_i3.c
xde_menu_i3_la_LIBADD = $(module_libadd)
xde_menu_i3_la_LDFLAGS = $(module_ldflags)

xde_menu_icewm_la_CPPFLAGS = -DNAME=\"xde-icewm\"
xde_menu_icewm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_icewm_la_SOURCES = xde_icewm.c
xde_menu_icewm_la_LIBADD = $(module_libadd)
xde_menu_icewm_la_LDFLAGS = $(module_ldflags)

xde_menu_jwm_la_CPPFLAGS = -DNAME=\"xde-jwm\"
xde_menu_jwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_jwm_la_SOURCES = xde_jwm.c
xde_menu_jwm_la_LIBADD = $(module_libadd)
xde_menu_jwm_la_LDFLAGS = $(module_ldflags)

xde_menu_larswm_la_CPPFLAGS = -DNAME=\"xde-larswm\"
xde_menu_larswm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_larswm_la_SOURCES = xde_larswm.c
xde_menu_larswm_la_LIBADD = $(module_libadd)
xde_menu_larswm_la_LDFLAGS = $(module_ldflags)

xde_menu_matwm2_la_CPPFLAGS = -DNAME=\"xde-matwm2\"
xde_menu_matwm2_la_CFLAGS = $(AM_CFLAGS)
xde_menu_matwm2_la_SOURCES = xde_matwm2.c
xde_menu_matwm2_la_LIBADD = $(module_libadd)
xde_menu_matwm2_la_LDFLAGS = $(module_ldflags)

xde_menu_metacity_la_CPPFLAGS = -DNAME=\"xde-metacity\"
xde_menu_metacity_la_CFLAGS = $(AM_CFLAGS) $(GLIB_CFLAGS) $(GOBJ_CFLAGS) $(GIO_CFLAGS)
xde_menu_metacity_la_SOURCES = xde_metacity.c
xde_menu_metacity_la_LIBADD = $(module_libadd)
xde_menu_metacity_la_LDFLAGS = $(module_ldflags)

xde_menu_mvwm_la_CPPFLAGS = -DNAME=\"xde-mvwm\"
xde_menu_mvwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_mvwm_la_SOURCES = xde_mvwm.c
xde_menu_mvwm_la_LIBADD = $(module_libadd)
xde_menu_mvwm_la_LDFLAGS = $(module_ldflags)

xde_menu_mwm_la_CPPFLAGS = -DNAME=\"xde-mwm\"
xde_menu_mwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_mwm_la_SOURCES = xde_mwm.c
xde_menu_mwm_la_LIBADD = $(module_libadd)
xde_menu_mwm_la_LDFLAGS = $(module_ldflags)

xde_menu_openbox_la_CPPFLAGS = -DNAME=\"xde-openbox\"
xde_menu_openbox_la_CFLAGS = $(AM_CFLAGS)
xde_menu_openbox_la_SOURCES = xde_openbox.c
xde_menu_openbox_la_LIBADD = $(module_libadd)
xde_menu_openbox_la_LDFLAGS = $(module_ldflags)

xde_menu_openboxold_la_CPPFLAGS = -DNAME=\"xde-openboxold\"
xde_menu_openboxold_la_CFLAGS = $(AM_CFLAGS)
xde_menu_openboxold_la_SOURCES = xde_openboxold.c
xde_menu_openboxold_la_LIBADD = $(module_libadd)
xde_menu_openboxold_la_LDFLAGS = $(module_ldflags)

xde_menu_pekwm_la_CPPFLAGS = -DNAME=\"xde-pekwm\"
xde_menu_pekwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_pekwm_la_SOURCES = xde_pekwm.c
xde_menu_pekwm_la_LIBADD = $(module_libadd)
xde_menu_pekwm_la_LDFLAGS = $(module_ldflags)

xde_menu_perlpanel_la_CPPFLAGS = -DNAME=\"xde-perlpanel\"
xde_menu_perlpanel_la_CFLAGS = $(AM_CFLAGS)
xde_menu_perlpanel_la_SOURCES = xde_perlpanel.c
xde_menu_perlpanel_la_LIBADD = $(module_libadd)
xde_menu_perlpanel_la_LDFLAGS = $(module_ldflags)

xde_menu_spectrwm_la_CPPFLAGS = -DNAME=\"xde-spectrwm\"
xde_menu_spectrwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_spectrwm_la_SOURCES = xde_spectrwm.c
xde_menu_spectrwm_la_LIBADD = $(module_libadd)
xde_menu_spectrwm_la_LDFLAGS = $(module_ldflags)

xde_menu_twm_la_CPPFLAGS = -DNAME=\"xde-twm\"
xde_menu_twm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_twm_la_SOURCES = xde_twm.c
xde_menu_twm_la_LIBADD = $(module_libadd)
xde_menu_twm_la_LDFLAGS = $(module_ldflags)

xde_menu_uwm_la_CPPFLAGS = -DNAME=\"xde-uwm\"
xde_menu_uwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_uwm_la_SOURCES = xde_uwm.c
xde_menu_uwm_la_LIBADD = $(module_libadd)
xde_menu_uwm_la_LDFLAGS = $(module_ldflags)

xde_menu_vtwm_la_CPPFLAGS = -DNAME=\"xde-vtwm\"
xde_menu_vtwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_vtwm_la_SOURCES = xde_vtwm.c
xde_menu_vtwm_la_LIBADD = $(module_libadd)
xde_menu_vtwm_la_LDFLAGS = $(module_ldflags)

xde_menu_wm2_la_CPPFLAGS = -DNAME=\"xde-wm2\"
xde_menu_wm2_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wm2_la_SOURCES = xde_wm2.c
xde_menu_wm2_la_LIBADD = $(module_libadd)
xde_menu_wm2_la_LDFLAGS = $(module_ldflags)

xde_menu_waimea_la_CPPFLAGS = -DNAME=\"xde-waimea\"
xde_menu_waimea_la_CFLAGS = $(AM_CFLAGS)
xde_menu_waimea_la_SOURCES = xde_waimea.c
xde_menu_waimea_la_LIBADD = $(module_libadd)
xde_menu_waimea_la_LDFLAGS = $(module_ldflags)

xde_menu_wind_la_CPPFLAGS = -DNAME=\"xde-wind\"
xde_menu_wind_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wind_la_SOURCES = xde_wind.c
xde_menu_wind_la_LIBADD = $(module_libadd)
xde_menu_wind_la_LDFLAGS = $(module_ldflags)

xde_menu_wmaker_la_CPPFLAGS = -DNAME=\"xde-wmaker\"
xde_menu_wmaker_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wmaker_la_SOURCES = xde_wmaker.c
xde_menu_wmaker_la_LIBADD = $(module_libadd)
xde_menu_wmaker_la_LDFLAGS = $(module_ldflags)

xde_menu_wmakerold_la_CPPFLAGS = -DNAME=\"xde-wmakerold\"
xde_menu_wmakerold_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wmakerold_la_SOURCES = xde_wmakerold.c
xde_menu_wmakerold_la_LIBADD = $(module_libadd)
xde_menu_wmakerold_la_LDFLAGS = $(module_ldflags)

xde_menu_wmii_la_CPPFLAGS = -DNAME=\"xde-wmii\"
xde_menu_wmii_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wmii_la_SOURCES = xde_wmii.c
xde_menu_wmii_la_LIBADD = $(module_libadd)
xde_menu_wmii_la_LDFLAGS = $(module_ldflags)

xde_menu_wmx_la_CPPFLAGS = -DNAME=\"xde-wmx\"
xde_menu_wmx_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wmx_la_SOURCES = xde_wmx.c
xde_menu_wmx_la_LIBADD = $(module_libadd)
xde_menu_wmx_la_LDFLAGS = $(module_ldflags)

xde_menu_xdwm_la_CPPFLAGS = -DNAME=\"xde-xdwm\"
xde_menu_xdwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_xdwm_la_SOURCES = xde_xdwm.c
xde_menu_xdwm_la_LIBADD = $(module_libadd)
xde_menu_xdwm_la_LDFLAGS = $(module_ldflags)

xde_menu_yeahwm_la_CPPFLAGS = -DNAME=\"xde-yeahwm\"
xde_menu_yeahwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_yeahwm_la_SOURCES = xde_yeahwm.c
xde_menu_yeahwm_la_LIBADD = $(module_libadd)
xde_menu_yeahwm_la_LDFLAGS = $(module_ldflags)

install-exec-hook:
	ln $(DESTDIR)$(bindir)/xde-menu $(DESTDIR)$(bindir)/xde-menugen$(EXEEXT)
	ln $(DESTDIR)$(bindir)/xde-menu $(DESTDIR)$(bindir)/xde-menu-monitor$(EXEEXT)
	ln $(DESTDIR)$(bindir)/xde-menu $(DESTDIR)$(bindir)/xde-menu-popmenu$(EXEEXT)
	ln $(DESTDIR)$(bindir)/xde-menu $(DESTDIR)$(bindir)/xde-menu-quit$(EXEEXT)
	ln $(DESTDIR)$(bindir)/xde-menu $(DESTDIR)$(bindir)/xde-menu-refresh$(EXEEXT)
	ln $(DESTDIR)$(bindir)/xde-menu $(DESTDIR)$(bindir)/xde-menu-replace$(EXEEXT)
	ln $(DESTDIR)$(bindir)/xde-menu $(DESTDIR)$(bindir)/xde-menu-restart$(EXEEXT)

uninstall-hook:
	rm -f $(DESTDIR)$(bindir)/xde-menugen$(EXEEXT)
	rm -f $(DESTDIR)$(bindir)/xde-menu-monitor$(EXEEXT)
	rm -f $(DESTDIR)$(bindir)/xde-menu-popmenu$(EXEEXT)
	rm -f $(DESTDIR)$(bindir)/xde-menu-quit$(EXEEXT)
	rm -f $(DESTDIR)$(bindir)/xde-menu-refresh$(EXEEXT)
	rm -f $(DESTDIR)$(bindir)/xde-menu-replace$(EXEEXT)
	rm -f $(DESTDIR)$(bindir)/xde-menu-restart$(EXEEXT)
