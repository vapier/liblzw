EXTRA_DIST = $(TESTSUITE_AT) testsuite.at $(TESTSUITE) \
	tests.h \
	lot.good.bz2 lot.Z \
	simple.good.bz2 simple.Z \
	simple2.good.bz2 simple2.Z
TESTSUITE = $(srcdir)/testsuite
DISTCLEANFILES = atconfig

TESTSUITE_AT = \
	local.at \
	stdf_bzcheck.at \
	testsuite.at

check-local: atconfig $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' $(TESTSUITEFLAGS)

installcheck-local: atconfig $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(bindir)' $(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || $(SHELL) '$(TESTSUITE)' --clean

AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(TESTSUITE_AT)
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at
	mv $@.tmp $@

check_PROGRAMS = lot simple simple2 uncompress
INCLUDES = -I$(top_srcdir)
LDADD = ../liblzw.la
