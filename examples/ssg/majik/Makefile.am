noinst_PROGRAMS = majik_demo

majik_demo_SOURCES = elevation_map.h \
                     image_map.h     \
                     majik_demo.cxx

majik_demo_LDADD = -L$(top_builddir)/src/ssg -lssg \
	           -L$(top_builddir)/src/sg  -lsg

INCLUDES += -I$(top_builddir)/src/js \
            -I$(top_builddir)/src/sg \
            -I$(top_builddir)/src/ssg

EXTRA_DIST = majik_demo.dsp

