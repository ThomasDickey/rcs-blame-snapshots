# Process this file with automake to produce a Makefile.

SUBDIRS = doc lib src tests

AM_ETAGSFLAGS = --c-kinds=+lx
ACLOCAL_AMFLAGS = -I m4

dist_noinst_DATA = blame.spec

RPMBUILD_FLAGS = 

rpm: $(PACKAGE).spec dist
	rpmbuild $(RPMBUILD_FLAGS) -ta $(distdir).tar.gz

mock: mock-fc6 mock-fc5 mock-fc4
mock-fc6: $(PACKAGE).spec dist-gzip
	TOPDIR="`rpm -E %_topdir`" || exit 1 && \
	rpmbuild --define='fedora 6' --define='dist .fc6' --nodeps -ts $(distdir).tar.gz && \
	mock -r fedora-6-i386-core.cfg --debug "$$TOPDIR/SRPMS/$(PACKAGE)-$(VERSION)-$(RELEASE).fc6.src.rpm"
mock-fc5: $(PACKAGE).spec dist-gzip
	TOPDIR="`rpm -E %_topdir`" || exit 1 && \
	rpmbuild --define='fedora 5' --define='dist .fc5' --nodeps -ts $(distdir).tar.gz && \
	mock -r fedora-5-i386-core.cfg --debug "$$TOPDIR/SRPMS/$(PACKAGE)-$(VERSION)-$(RELEASE).fc5.src.rpm"
mock-fc4: $(PACKAGE).spec dist-gzip
	TOPDIR="`rpm -E %_topdir`" || exit 1 && \
	rpmbuild --define='fedora 4' --define='dist .fc4' --nodeps -ts $(distdir).tar.gz && \
	mock -r fedora-4-i386-core.cfg --debug "$$TOPDIR/SRPMS/$(PACKAGE)-$(VERSION)-$(RELEASE).fc4.src.rpm"

$(PACKAGE).spec: NEWS
