noinst_PROGRAMS = load save

load_SOURCES = load.cxx
save_SOURCES = save.cxx

load_LDADD = -L$(top_builddir)/src/ssg -lssg \
	     -L$(top_builddir)/src/sg  -lsg
save_LDADD = -L$(top_builddir)/src/ssg -lssg \
	     -L$(top_builddir)/src/sg  -lsg

INCLUDES += -I$(top_builddir)/src/sg -I$(top_builddir)/src/ssg

