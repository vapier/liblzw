/*
 * Written by Mike Frysinger <vapier@gmail.com>
 * Released into the public domain
 */

#ifndef _LIBLZW_HEADERS_H
#define _LIBLZW_HEADERS_H

#include "config.h"

#if defined(HAVE_STDINT_H)
# include <stdint.h>
#endif
#if defined(HAVE_INTTYPES_H)
# include <inttypes.h>
#endif
#if defined(HAVE_SYS_TYPES_H)
# include <sys/types.h>
#endif
#if defined(HAVE_SYS_STAT_H)
# include <sys/stat.h>
#endif
#if defined(HAVE_CTYPE_H)
# include <ctype.h>
#endif
#if defined(HAVE_ERRNO_H)
# include <errno.h>
#else
extern int errno;
#endif
#if defined(HAVE_UNISTD_H)
# include <unistd.h>
#endif
#if defined(HAVE_FCNTL_H)
# include <fcntl.h>
#endif
#if defined(HAVE_STDIO_H)
# include <stdio.h>
#endif
#if defined(HAVE_STDLIB_H)
# include <stdlib.h>
#endif
#if defined(HAVE_TIME_H)
# include <time.h>
#endif
#if defined(HAVE_STRING_H)
# include <string.h>
#endif
#if defined(HAVE_FEATURES_H)
# include <features.h>
#endif
#if defined(HAVE_STDARG_H)
# include <stdarg.h>
#endif
#if defined(HAVE_SYS_CDEFS_H)
# include <sys/cdefs.h>
#endif
#if defined(HAVE_ASSERT_H)
# include <assert.h>
#endif

/* i'll see you in hell windows */
#if !defined(O_BINARY)
# define O_BINARY 0x00
#endif

#endif /* _LIBLZW_HEADERS_H */
