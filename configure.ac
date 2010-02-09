AC_INIT([liblzw], [0.2], [vapier@gmail.com])
AM_INIT_AUTOMAKE([1.11 dist-lzma no-dist-gzip silent-rules])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADER([config.h])

AC_PROG_CC
AC_C_BIGENDIAN

AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL
AC_ENABLE_SHARED
AC_ENABLE_STATIC

AC_CHECK_HEADERS_ONCE(m4_flatten([
	assert.h
	ctype.h
	errno.h
	fcntl.h
	features.h
	inttypes.h
	stdarg.h
	stdint.h
	stdio.h
	stdlib.h
	string.h
	time.h
	unistd.h
	sys/cdefs.h
	sys/stat.h
	sys/types.h
]))

dnl Let's get anal with compiling while on my dev box
AS_CASE([$HOSTNAME],
	[vapier*], [CFLAGS="$CFLAGS -Wall -Wextra -Wnonnull -Wundef -Werror"])

AM_MISSING_PROG([AUTOM4TE], [autom4te])
AC_CONFIG_TESTDIR(tests)

AC_CONFIG_FILES([
	Makefile
	tests/Makefile
	tests/package.m4
	liblzw.pc
])
AC_CONFIG_FILES([liblzw-config], [chmod +x liblzw-config])

AC_OUTPUT
