AC_INIT(liblzw, 0.1, [vapier@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADER(config.h)

AC_PROG_CC
dnl Next four lines is a hack to prevent libtool checking for CXX/F77
m4_undefine([AC_PROG_CXX])
m4_defun([AC_PROG_CXX],[])
m4_undefine([AC_PROG_F77])
m4_defun([AC_PROG_F77],[])
AC_PROG_LIBTOOL
AC_ENABLE_SHARED
AC_ENABLE_STATIC

AC_CHECK_HEADERS([ \
stdint.h inttypes.h sys/types.h sys/stat.h ctype.h \
errno.h unistd.h fcntl.h stdio.h stdlib.h time.h \
string.h features.h stdarg.h sys/cdefs.h assert.h \
])

dnl Let's get anal with compiling while on my dev box
if test "x$HOSTNAME" = "xvapier" ; then
	CFLAGS="$CFLAGS -Wall -Werror"
fi


AC_OUTPUT([
Makefile
liblzw-config
liblzw.pc
],[
chmod +x liblzw-config
])
