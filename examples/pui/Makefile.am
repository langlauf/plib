noinst_PROGRAMS = simple complex

simple_SOURCES  = simple.cxx

complex_SOURCES = complex.cxx

simple_LDADD =  -L$(top_builddir)/src/pui \
                -L$(top_builddir)/src/sg  \
                -L$(top_builddir)/src/fnt \
                -lpu -lfnt -lsg

complex_LDADD = -L$(top_builddir)/src/pui \
                -L$(top_builddir)/src/sg  \
                -L$(top_builddir)/src/fnt \
                -lpu -lfnt -lsg

INCLUDES += -I$(top_builddir)/src/sg  \
            -I$(top_builddir)/src/fnt \
            -I$(top_builddir)/src/pui

EXTRA_DIST = complex.dsp simple.dsp


