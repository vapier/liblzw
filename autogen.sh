#!/bin/sh -xe

# Clobber files to avoid sticking to old autotools versions.
rm -f aclocal.m4 Makefile Makefile.in configure

mkdir -p m4
autoreconf -i -f

# Broken autotools wrongly clobbers our INSTALL.
git checkout -f INSTALL || true
