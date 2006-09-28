#!/bin/sh

if test -d .svn ; then
	if test -d ../m4 ; then
		rm -rf m4 || exit 1
		mkdir -p m4 || exit 1
		cp ../m4/*.m4 m4/ || exit 1
	fi
fi

aclocal -I m4 || exit 1
autoheader || exit 1
libtoolize --automake -c -f || exit 1
autoconf || exit 1
automake -a -c || exit 1

if test -x ./test.sh ; then
	exec ./test.sh "$@"
fi
