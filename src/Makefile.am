
AM_CFLAGS = $(X11_CFLAGS) $(XEXT_CFLAGS) $(CAIRO_CFLAGS) $(GDK_CFLAGS) $(GTK_CFLAGS) $(WNCK_CFLAGS) $(GNOME_MENU_CFLAGS)
AM_LDFLAGS = $(GNOME_MENU_LIBS) $(WNCK_LIBS) $(GTK_LIBS) $(GDK_LIBS) $(CAIRO_LIBS) $(XEXT_LIBS) $(X11_LIBS)

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
	xde-menu-afterstep.la \
	xde-menu-awesome.la \
	xde-menu-blackbox.la \
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
	xde-menu-icewm.la \
	xde-menu-jwm.la \
	xde-menu-matwm2.la \
	xde-menu-metacity.la \
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
	xde-menu-wmaker.la \
	xde-menu-wmakerold.la \
	xde-menu-wmx.la \
	xde-menu-yeahwm.la

#module_ldflags = -module -export-dynamic -release $(VERSION) -shared -rpath $(xdemoddir) -avoid-version
module_ldflags = -module -export-dynamic -shared -rpath $(xdemoddir) -avoid-version

xde_menu_2bwm_la_CPPFLAGS = -DNAME=\"xde-2bwm\"
xde_menu_2bwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_2bwm_la_SOURCES = xde-menu.h xde_2bwm.c
xde_menu_2bwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_2bwm_la_LDFLAGS = $(module_ldflags)

xde_menu_adwm_la_CPPFLAGS = -DNAME=\"xde-adwm\"
xde_menu_adwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_adwm_la_SOURCES = xde-menu.h xde_adwm.c
xde_menu_adwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_adwm_la_LDFLAGS = $(module_ldflags)

xde_menu_afterstep_la_CPPFLAGS = -DNAME=\"xde-afterstep\"
xde_menu_afterstep_la_CFLAGS = $(AM_CFLAGS)
xde_menu_afterstep_la_SOURCES = xde-menu.h xde_afterstep.c
xde_menu_afterstep_la_LIBADD = $(AM_LDFLAGS)
xde_menu_afterstep_la_LDFLAGS = $(module_ldflags)

xde_menu_awesome_la_CPPFLAGS = -DNAME=\"xde-awesome\"
xde_menu_awesome_la_CFLAGS = $(AM_CFLAGS)
xde_menu_awesome_la_SOURCES = xde-menu.h xde_awesome.c
xde_menu_awesome_la_LIBADD = $(AM_LDFLAGS)
xde_menu_awesome_la_LDFLAGS = $(module_ldflags)

xde_menu_blackbox_la_CPPFLAGS = -DNAME=\"xde-blackbox\"
xde_menu_blackbox_la_CFLAGS = $(AM_CFLAGS)
xde_menu_blackbox_la_SOURCES = xde-menu.h xde_blackbox.c
xde_menu_blackbox_la_LIBADD = $(AM_LDFLAGS)
xde_menu_blackbox_la_LDFLAGS = $(module_ldflags)

xde_menu_ctwm_la_CPPFLAGS = -DNAME=\"xde-ctwm\"
xde_menu_ctwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_ctwm_la_SOURCES = xde-menu.h xde_ctwm.c
xde_menu_ctwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_ctwm_la_LDFLAGS = $(module_ldflags)

xde_menu_cwm_la_CPPFLAGS = -DNAME=\"xde-cwm\"
xde_menu_cwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_cwm_la_SOURCES = xde-menu.h xde_cwm.c
xde_menu_cwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_cwm_la_LDFLAGS = $(module_ldflags)

xde_menu_dtwm_la_CPPFLAGS = -DNAME=\"xde-dtwm\"
xde_menu_dtwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_dtwm_la_SOURCES = xde-menu.h xde_dtwm.c
xde_menu_dtwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_dtwm_la_LDFLAGS = $(module_ldflags)

xde_menu_dwm_la_CPPFLAGS = -DNAME=\"xde-dwm\"
xde_menu_dwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_dwm_la_SOURCES = xde-menu.h xde_dwm.c
xde_menu_dwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_dwm_la_LDFLAGS = $(module_ldflags)

xde_menu_echinus_la_CPPFLAGS = -DNAME=\"xde-echinus\"
xde_menu_echinus_la_CFLAGS = $(AM_CFLAGS)
xde_menu_echinus_la_SOURCES = xde-menu.h xde_echinus.c
xde_menu_echinus_la_LIBADD = $(AM_LDFLAGS)
xde_menu_echinus_la_LDFLAGS = $(module_ldflags)

xde_menu_etwm_la_CPPFLAGS = -DNAME=\"xde-etwm\"
xde_menu_etwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_etwm_la_SOURCES = xde-menu.h xde_etwm.c
xde_menu_etwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_etwm_la_LDFLAGS = $(module_ldflags)

xde_menu_ewmh_la_CPPFLAGS = -DNAME=\"xde-ewmh\"
xde_menu_ewmh_la_CFLAGS = $(AM_CFLAGS)
xde_menu_ewmh_la_SOURCES = xde-menu.h xde_ewmh.c
xde_menu_ewmh_la_LIBADD = $(AM_LDFLAGS)
xde_menu_ewmh_la_LDFLAGS = $(module_ldflags)

xde_menu_fluxbox_la_CPPFLAGS = -DNAME=\"xde-fluxbox\"
xde_menu_fluxbox_la_CFLAGS = $(AM_CFLAGS)
xde_menu_fluxbox_la_SOURCES = xde-menu.h xde_fluxbox.c
xde_menu_fluxbox_la_LIBADD = $(AM_LDFLAGS)
xde_menu_fluxbox_la_LDFLAGS = $(module_ldflags)

xde_menu_flwm_la_CPPFLAGS = -DNAME=\"xde-flwm\"
xde_menu_flwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_flwm_la_SOURCES = xde-menu.h xde_flwm.c
xde_menu_flwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_flwm_la_LDFLAGS = $(module_ldflags)

xde_menu_fvwm_la_CPPFLAGS = -DNAME=\"xde-fvwm\"
xde_menu_fvwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_fvwm_la_SOURCES = xde-menu.h xde_fvwm.c
xde_menu_fvwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_fvwm_la_LDFLAGS = $(module_ldflags)

xde_menu_icewm_la_CPPFLAGS = -DNAME=\"xde-icewm\"
xde_menu_icewm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_icewm_la_SOURCES = xde-menu.h xde_icewm.c
xde_menu_icewm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_icewm_la_LDFLAGS = $(module_ldflags)

xde_menu_jwm_la_CPPFLAGS = -DNAME=\"xde-jwm\"
xde_menu_jwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_jwm_la_SOURCES = xde-menu.h xde_jwm.c
xde_menu_jwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_jwm_la_LDFLAGS = $(module_ldflags)

xde_menu_matwm2_la_CPPFLAGS = -DNAME=\"xde-matwm2\"
xde_menu_matwm2_la_CFLAGS = $(AM_CFLAGS)
xde_menu_matwm2_la_SOURCES = xde-menu.h xde_matwm2.c
xde_menu_matwm2_la_LIBADD = $(AM_LDFLAGS)
xde_menu_matwm2_la_LDFLAGS = $(module_ldflags)

xde_menu_metacity_la_CPPFLAGS = -DNAME=\"xde-metacity\"
xde_menu_metacity_la_CFLAGS = $(AM_CFLAGS) $(GLIB_CFLAGS) $(GOBJ_CFLAGS) $(GIO_CFLAGS)
xde_menu_metacity_la_SOURCES = xde-menu.h xde_metacity.c
xde_menu_metacity_la_LIBADD = $(AM_LDFLAGS)
xde_menu_metacity_la_LDFLAGS = $(module_ldflags)

xde_menu_mwm_la_CPPFLAGS = -DNAME=\"xde-mwm\"
xde_menu_mwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_mwm_la_SOURCES = xde-menu.h xde_mwm.c
xde_menu_mwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_mwm_la_LDFLAGS = $(module_ldflags)

xde_menu_openbox_la_CPPFLAGS = -DNAME=\"xde-openbox\"
xde_menu_openbox_la_CFLAGS = $(AM_CFLAGS)
xde_menu_openbox_la_SOURCES = xde-menu.h xde_openbox.c
xde_menu_openbox_la_LIBADD = $(AM_LDFLAGS)
xde_menu_openbox_la_LDFLAGS = $(module_ldflags)

xde_menu_openboxold_la_CPPFLAGS = -DNAME=\"xde-openboxold\"
xde_menu_openboxold_la_CFLAGS = $(AM_CFLAGS)
xde_menu_openboxold_la_SOURCES = xde-menu.h xde_openboxold.c
xde_menu_openboxold_la_LIBADD = $(AM_LDFLAGS)
xde_menu_openboxold_la_LDFLAGS = $(module_ldflags)

xde_menu_pekwm_la_CPPFLAGS = -DNAME=\"xde-pekwm\"
xde_menu_pekwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_pekwm_la_SOURCES = xde-menu.h xde_pekwm.c
xde_menu_pekwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_pekwm_la_LDFLAGS = $(module_ldflags)

xde_menu_perlpanel_la_CPPFLAGS = -DNAME=\"xde-perlpanel\"
xde_menu_perlpanel_la_CFLAGS = $(AM_CFLAGS)
xde_menu_perlpanel_la_SOURCES = xde-menu.h xde_perlpanel.c
xde_menu_perlpanel_la_LIBADD = $(AM_LDFLAGS)
xde_menu_perlpanel_la_LDFLAGS = $(module_ldflags)

xde_menu_spectrwm_la_CPPFLAGS = -DNAME=\"xde-spectrwm\"
xde_menu_spectrwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_spectrwm_la_SOURCES = xde-menu.h xde_spectrwm.c
xde_menu_spectrwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_spectrwm_la_LDFLAGS = $(module_ldflags)

xde_menu_twm_la_CPPFLAGS = -DNAME=\"xde-twm\"
xde_menu_twm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_twm_la_SOURCES = xde-menu.h xde_twm.c
xde_menu_twm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_twm_la_LDFLAGS = $(module_ldflags)

xde_menu_uwm_la_CPPFLAGS = -DNAME=\"xde-uwm\"
xde_menu_uwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_uwm_la_SOURCES = xde-menu.h xde_uwm.c
xde_menu_uwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_uwm_la_LDFLAGS = $(module_ldflags)

xde_menu_vtwm_la_CPPFLAGS = -DNAME=\"xde-vtwm\"
xde_menu_vtwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_vtwm_la_SOURCES = xde-menu.h xde_vtwm.c
xde_menu_vtwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_vtwm_la_LDFLAGS = $(module_ldflags)

xde_menu_waimea_la_CPPFLAGS = -DNAME=\"xde-waimea\"
xde_menu_waimea_la_CFLAGS = $(AM_CFLAGS)
xde_menu_waimea_la_SOURCES = xde-menu.h xde_waimea.c
xde_menu_waimea_la_LIBADD = $(AM_LDFLAGS)
xde_menu_waimea_la_LDFLAGS = $(module_ldflags)

xde_menu_wind_la_CPPFLAGS = -DNAME=\"xde-wind\"
xde_menu_wind_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wind_la_SOURCES = xde-menu.h xde_wind.c
xde_menu_wind_la_LIBADD = $(AM_LDFLAGS)
xde_menu_wind_la_LDFLAGS = $(module_ldflags)

xde_menu_wmaker_la_CPPFLAGS = -DNAME=\"xde-wmaker\"
xde_menu_wmaker_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wmaker_la_SOURCES = xde-menu.h xde_wmaker.c
xde_menu_wmaker_la_LIBADD = $(AM_LDFLAGS)
xde_menu_wmaker_la_LDFLAGS = $(module_ldflags)

xde_menu_wmakerold_la_CPPFLAGS = -DNAME=\"xde-wmakerold\"
xde_menu_wmakerold_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wmakerold_la_SOURCES = xde-menu.h xde_wmakerold.c
xde_menu_wmakerold_la_LIBADD = $(AM_LDFLAGS)
xde_menu_wmakerold_la_LDFLAGS = $(module_ldflags)

xde_menu_wmx_la_CPPFLAGS = -DNAME=\"xde-wmx\"
xde_menu_wmx_la_CFLAGS = $(AM_CFLAGS)
xde_menu_wmx_la_SOURCES = xde-menu.h xde_wmx.c
xde_menu_wmx_la_LIBADD = $(AM_LDFLAGS)
xde_menu_wmx_la_LDFLAGS = $(module_ldflags)

xde_menu_yeahwm_la_CPPFLAGS = -DNAME=\"xde-yeahwm\"
xde_menu_yeahwm_la_CFLAGS = $(AM_CFLAGS)
xde_menu_yeahwm_la_SOURCES = xde-menu.h xde_yeahwm.c
xde_menu_yeahwm_la_LIBADD = $(AM_LDFLAGS)
xde_menu_yeahwm_la_LDFLAGS = $(module_ldflags)

