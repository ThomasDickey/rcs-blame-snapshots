# Process this file with automake to produce a Makefile.

bin_PROGRAMS = blame

blame_SOURCES = \
	blame.c \
	data.h \
	date.c date.h \
	delta.c delta.h \
	hash.c hash.h \
	keyword.c keyword.h \
	lexer.l \
	lines.c lines.h \
	parser.y \
	rcs.c rcs.h \
	system.h \
	util.c util.h \
	vector.c vector.h \
	working.c working.h
blame_LDADD = $(top_builddir)/lib/libmisc.a
AM_YFLAGS = -d
AM_LFLAGS = -f
AM_CFLAGS = -Wall
if GCC
AM_CFLAGS += -W -Wno-format-y2k
endif
AM_CPPFLAGS = -I$(top_srcdir)/lib

BUILT_SOURCES = parser.h

AUTOMAKE_OPTIONS = $(top_builddir)/lib/ansi2knr
