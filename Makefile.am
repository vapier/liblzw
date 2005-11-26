bin_SCRIPTS = liblzw-config

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = liblzw.pc

include_HEADERS = lzw.h
noinst_HEADERS = lzw_internal.h

lib_LTLIBRARIES = liblzw.la

liblzw_la_SOURCES = lzw.c
liblzw_la_LDFLAGS = -version-info 0:1:0

EXTRA_DIST = AUTHORS COPYING ChangeLog INSTALL NEWS README

AUTOMAKE_OPTIONS = dist-bzip2 no-dist-gzip
