SUBDIRS = src examples

EXTRA_DIST = README README.win32 CHANGES LICENSE NOTICE acsite.m4 \
             plib.dsp plib.dsw

dist-hook:
	tar cf - doc \
             examples/ssg/tux/data \
             examples/ssg/majik/data \
             examples/fnt/data     \
	   | ( cd $(distdir) ; tar xf - )

