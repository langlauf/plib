noinst_PROGRAMS = example mod_demo

example_SOURCES  = example.cxx
mod_demo_SOURCES = mod_demo.cxx

example_LDADD  = -L$(top_builddir)/src/sl -lsm -lsl
mod_demo_LDADD = -L$(top_builddir)/src/sl -lsm -lsl

INCLUDES += -I$(top_builddir)/src/sl

EXTRA_DIST = Makefile.msc cuckoo.au scream.ub wheeee.ub zzap.wav Paravoka.mod \
             mod_demo.dsp example.dsp

