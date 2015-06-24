SUBDIRS = tests

bin_SCRIPTS = liblzw-config

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = liblzw.pc

include_HEADERS = lzw.h
noinst_HEADERS = lzw_internal.h headers.h helpers.h

lib_LTLIBRARIES = liblzw.la
liblzw_la_SOURCES = lzw.c
liblzw_la_CFLAGS = -no-suppress
liblzw_la_LDFLAGS = -no-suppress -version-info 0:1:0 -no-undefined

EXTRA_DIST = AUTHORS COPYING ChangeLog INSTALL NEWS README.md UNLICENSE

ACLOCAL_FLAGS = -I m4
