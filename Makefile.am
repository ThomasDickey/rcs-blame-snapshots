# Process this file with automake to produce a Makefile.

SUBDIRS = doc lib src tests

AM_ETAGSFLAGS = --c-kinds=+lx
ACLOCAL_AMFLAGS = -I m4

dist_noinst_DATA = blame.spec

RPMBUILD_FLAGS = 

rpm: $(PACKAGE).spec dist
	rpmbuild $(RPMBUILD_FLAGS) -ta $(distdir).tar.gz
$(PACKAGE).spec: NEWS
