#!/bin/bash

for f in \
	`find . -name Makefile.in -o -name Makefile | grep -v tests` \
	.{libs,deps} \
	`find . -name '*.o' -o -name '*.la' -o -name '*.lo' -o -name '*.loT'` \
	aclocal.m4* autom4te.cache \
	configure config.* tests/ascii.out \
	liblzw-config liblzw.pc liblzw-doc.c \
	depcomp install-sh ltmain.sh missing mkinstalldirs libtool \
	config.h* stamp-h* \
	`find -name 'cmake.*'` `find -name '*.cmake'` \
	CMakeTmp CMakeCache.txt CMakeOutput.log \
; do
	rm -rf $f
done
