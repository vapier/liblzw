AC_INIT(liblzw, 0.1, [vapier@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADER(config.h)

AC_PROG_CC
AC_STDF_LIBTOOL

AC_CHECK_HEADERS([ \
stdint.h inttypes.h sys/types.h sys/stat.h ctype.h \
errno.h unistd.h fcntl.h stdio.h stdlib.h time.h \
string.h features.h stdarg.h sys/cdefs.h assert.h \
])

AM_STDF_VAPIER_DEV

AC_OUTPUT([
Makefile
liblzw-config
liblzw.pc
],[
chmod +x liblzw-config
])
