#!/bin/sh -xe

if test -d .svn ; then
	if test -d ../m4 ; then
		rm -rf m4
		mkdir -p m4
		cp ../m4/*.m4 m4/
		cp ../m4/*.at tests/
	fi
fi

autoreconf -i -f

# broken autotools wrongly clobbers our INSTALL
svn revert INSTALL >& /dev/null || true

if test -x ./test.sh ; then
	exec ./test.sh "$@"
fi
