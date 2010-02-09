#!/bin/sh -xe

autoreconf -i -f

# broken autotools wrongly clobbers our INSTALL
git checkout -f INSTALL || true

if test -x ./test.sh ; then
	exec ./test.sh "$@"
fi
