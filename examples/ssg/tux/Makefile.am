noinst_PROGRAMS = tux_example

tux_example_SOURCES = tux_example.cxx

tux_example_LDADD = -L$(top_builddir)/src/ssg -lssg \
	            -L$(top_builddir)/src/sg  -lsg

INCLUDES += -I$(top_builddir)/src/sg -I$(top_builddir)/src/ssg

EXTRA_DIST = tux_example.dsp

