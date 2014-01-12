/*
 * Written by Mike Frysinger <vapier@gmail.com>
 * Released into the public domain
 */

#ifndef _LIBLZW_HELPERS_H
#define _LIBLZW_HELPERS_H

#define _warn(fmt, args...)  fprintf(stderr, fmt , ## args)
#define warn(fmt, args...)   _warn("liblzw: " fmt "\n" , ## args)
#define warnf(fmt, args...)  warn("%s(): " fmt, __FUNCTION__ , ## args)
#define warnp(fmt, args...)  warn(fmt ": %s" , ## args , strerror(errno))
#define warnfp(fmt, args...) warnp("%s(): " fmt, __FUNCTION__ , ## args)

#define dumphex(buf, cnt) \
	do { \
		size_t i = 0; \
		_warn("dumphex: "); \
		while (i < cnt) \
			_warn("%2.2X ", buf[i++]); \
		_warn("\n"); \
	} while (0)

#endif /* _LIBLZW_HELPERS_H */
