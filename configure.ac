AC_INIT([liblzw], [0.3], [https://github.com/vapier/liblzw/issues])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE([-Wall 1.15 dist-xz foreign no-dist-gzip silent-rules])
AM_SILENT_RULES([yes])

AC_LIBTOOL_WIN32_DLL
AM_PROG_AR
LT_INIT
AC_ENABLE_SHARED
AC_ENABLE_STATIC

AC_PROG_CC

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

dnl Do this at the end so -Werror isn't used in configure tests.
AC_MSG_CHECKING([whether to enable -Werror])
AC_ARG_ENABLE(
	[werror],
	[AS_HELP_STRING([--enable-werror], [Enable -Werror when compiling.])],
	[],
	[
		dnl Enable on my dev box.
		AS_CASE([$HOSTNAME$USER], [vapier*vapier], [enable_werror=vapier]
	)]
)
AS_IF(
	[test "$enable_werror" != "no"],
	[AS_VAR_APPEND([CFLAGS], [" -Wall -Wextra -Wnonnull -Wundef -Werror"])]
)
AC_MSG_RESULT([$enable_werror])

AM_MISSING_PROG([AUTOM4TE], [autom4te])
AC_CONFIG_TESTDIR(tests)

AC_CONFIG_FILES([
	Makefile
	tests/Makefile
	tests/package.m4
	liblzw.pc
])

AC_OUTPUT
