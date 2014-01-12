#!/bin/sh -xe

mkdir -p m4
autoreconf -i -f

# broken autotools wrongly clobbers our INSTALL
git checkout -f INSTALL || true
