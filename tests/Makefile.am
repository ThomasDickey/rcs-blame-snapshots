# Process this file with automake to produce a Makefile.

EXTRA_DIST = blame package.m4 testsuite $(TESTSUITE_AT) testdata
DISTCLEANFILES = atconfig atlocal
MAINTAINERCLEANFILES = $(TESTSUITE)

TESTSUITE = $(srcdir)/testsuite
TESTSUITE_AT = \
	testsuite.at \
	argv.at \
	rev.at \
	date.at \
	state.at \
	author.at \
	expand.at \
	suffixes.at \
	mixed.at \
	branch.at \
	rcs.at \
	working.at \
	pairing.at \
	rcsinit.at \
	version.at \
	log.at

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	@{ \
		echo '# Signature of the current package.'; \
		echo 'm4_define([AT_PACKAGE_NAME],      [@PACKAGE_NAME@])'; \
		echo 'm4_define([AT_PACKAGE_TARNAME],   [@PACKAGE_TARNAME@])'; \
		echo 'm4_define([AT_PACKAGE_VERSION],   [@PACKAGE_VERSION@])'; \
		echo 'm4_define([AT_PACKAGE_STRING],    [@PACKAGE_STRING@])'; \
		echo 'm4_define([AT_PACKAGE_BUGREPORT], [@PACKAGE_BUGREPORT@])'; \
	} >$(srcdir)/package.m4

AUTOM4TE = $(SHELL) $(top_srcdir)/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): package.m4 $(TESTSUITE_AT)
	$(AUTOTEST) -I $(srcdir) testsuite.at -o $@.tmp
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

clean-local:
	if [ -x $(TESTSUITE) ]; then $(SHELL) $(TESTSUITE) --clean; fi

check-local: atconfig atlocal $(TESTSUITE) $(top_builddir)/src/blame$(EXEEXT)
	$(SHELL) $(TESTSUITE)

# Run the test suite on the *installed* tree.
installcheck-local: atconfig atlocal $(TESTSUITE)
	$(SHELL) $(TESTSUITE) AUTOTEST_PATH=$(exec_prefix)/bin
