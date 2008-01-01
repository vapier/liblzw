AC_INIT(liblzw, 0.1.2, [vapier@gmail.com])
AM_INIT_AUTOMAKE([1.10 dist-bzip2 no-dist-gzip])dnl dist-lzma
AC_CONFIG_HEADER(config.h)

AC_PROG_CC
AC_C_BIGENDIAN

AC_STDF_LIBTOOL

AC_CHECK_HEADERS([ \
stdint.h inttypes.h sys/types.h sys/stat.h ctype.h \
errno.h unistd.h fcntl.h stdio.h stdlib.h time.h \
string.h features.h stdarg.h sys/cdefs.h assert.h \
])

AM_STDF_VAPIER_DEV

AM_MISSING_PROG([AUTOM4TE], [autom4te])
AC_CONFIG_TESTDIR(tests)

AC_OUTPUT([
Makefile
tests/Makefile
liblzw-config
liblzw.pc
],[
chmod +x liblzw-config
])
