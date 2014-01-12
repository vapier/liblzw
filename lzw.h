/**
 * @file lzw.h
 * @brief LZW header file
 * @internal
 */
/*
 * Written by Mike Frysinger <vapier@gmail.com>
 * Released into the public domain
 */

#ifndef _LZW_H
#define _LZW_H

#ifdef __cplusplus
extern "C" {
#endif

#define LZW_MAGIC_1 0x1F
#define LZW_MAGIC_2 0x9D
#define LZW_MAGIC   "\037\235"

#ifdef __IN_LIBLZW
# define HBITS   17			/* 50% occupancy */
# define HSIZE   (1<<HBITS)
# define HMASK   (HSIZE-1)
# define HPRIME  9941

typedef struct {
	int fd;
	int eof;

	unsigned char *inbuf, *outbuf, *stackp;
	unsigned char *unreadbuf;
	size_t stackp_diff;
	size_t insize, outpos;
	ssize_t rsize;

	unsigned char flags;
	int maxbits, block_mode;

	unsigned long int htab[HSIZE];
	unsigned short codetab[HSIZE];

	int n_bits, posbits, inbits, bitmask, finchar;
	long int maxcode, oldcode, incode, code, free_ent;
} lzwFile;

#else
typedef void lzwFile;
#endif

extern lzwFile *lzw_open(const char*, int, ...);
extern lzwFile* lzw_fdopen(int);
extern int lzw_close(lzwFile*);
extern ssize_t lzw_read(lzwFile*, void*, size_t);

#ifdef __cplusplus
}
#endif

#endif /* _LZW_H */
