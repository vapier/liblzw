/* Copyright (C) 2005 Mike Frysinger <vapier@gmail.com>
 *
 * Original code was ripped from ncompress-4.2.4.tar.gz,
 * and it is all public domain code, so have fun you wh0res.
 *
 * http://www.dogma.net/markn/articles/lzw/lzw.htm
 *
 * (N)compress42.c - File compression ala IEEE Computer, Mar 1992.
 *
 * Authors:
 *   Spencer W. Thomas   (decvax!harpo!utah-cs!utah-gr!thomas)
 *   Jim McKie           (decvax!mcvax!jim)
 *   Steve Davies        (decvax!vax135!petsd!peora!srd)
 *   Ken Turkowski       (decvax!decwrl!turtlevax!ken)
 *   James A. Woods      (decvax!ihnp4!ames!jaw)
 *   Joe Orost           (decvax!vax135!petsd!joe)
 *   Dave Mack           (csu@alembic.acs.com)
 *   Peter Jannesen, Network Communication Systems
 *                       (peter@ncs.nl)
 */

#ifdef __IN_LIBSTDF
# include <libstdf.h>
# define libstdf_hidden attribute_hidden
#else
# include "lzw_internal.h"
# define libstdf_hidden
#endif


/*
 * Misc common define cruft
 */
#define BUFSIZE      4
#define IN_BUFSIZE   (BUFSIZE + 64)
#define OUT_BUFSIZE  (BUFSIZE + 2048)
#define BITS         16
#define INIT_BITS    9			/* initial number of bits/code */
#define MAXCODE(n)   (1L << (n))
#define FIRST        257					/* first free entry */
#define CLEAR        256					/* table clear output code */


/*
 * Open LZW file
 */
libstdf_hidden
lzwFile *lzw_fdopen(int fd)
{
	lzwFile *ret;
	unsigned char buf[3];

	if (read(fd, buf, 3) != 3)
		goto err_out;

	if (buf[0] != LZW_MAGIC_1 || buf[1] != LZW_MAGIC_2 || buf[2] & 0x60)
		goto err_out;

	if ((ret = (lzwFile*)malloc(sizeof(lzwFile))) == NULL)
		goto err_out;

	memset(ret, 0x00, sizeof(*ret));
	ret->fd = fd;
	ret->eof = 0;
	ret->inbuf = (unsigned char*)malloc(sizeof(unsigned char) * IN_BUFSIZE);
	ret->outbuf = (unsigned char*)malloc(sizeof(unsigned char) * OUT_BUFSIZE);
	ret->stackp = NULL;
	ret->insize = 3; /* we read three bytes above */
	ret->outpos = 0;
	ret->rsize = 0;

	ret->flags = buf[2];
	ret->maxbits = ret->flags & 0x1f;    /* Mask for 'number of compresssion bits' */
	ret->block_mode = ret->flags & 0x80;

	ret->n_bits = INIT_BITS;
	ret->maxcode = MAXCODE(INIT_BITS) - 1;
	ret->bitmask = (1<<INIT_BITS)-1;
	ret->oldcode = -1;
	ret->finchar = 0;
	ret->posbits = 3<<3;
	ret->free_ent = ((ret->block_mode) ? FIRST : 256);

	/* initialize the first 256 entries in the table */
	memset(ret->codetab, 0x00, sizeof(ret->codetab));
	for (ret->code = 255; ret->code >= 0; --ret->code)
		ret->htab[ret->code] = ret->code;

	if (ret->inbuf == NULL || ret->outbuf == NULL) {
		errno = ENOMEM;
		goto err_out_free;
	}
	if (ret->maxbits > BITS) {
		errno = EINVAL;
		goto err_out_free;
	}

	return ret;

err_out:
	errno = EINVAL;
	return NULL;

err_out_free:
	if (ret->inbuf) free(ret->inbuf);
	if (ret->outbuf) free(ret->outbuf);
	free(ret);
	return NULL;
}

libstdf_hidden
lzwFile *lzw_open(const char *pathname, int flags, ...)
{
	mode_t mode = 0;
	int fd;

	if (flags & O_CREAT) {
		va_list ap;
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);
	}

	fd = open(pathname, flags, mode);
	if (fd == -1)
		return NULL;

	return lzw_fdopen(fd);
}


/*
 * Close LZW file
 */
libstdf_hidden
int lzw_close(lzwFile *lzw)
{
	int ret;
	if (lzw == NULL)
		return -1;
	ret = close(lzw->fd);
	free(lzw->inbuf);
	free(lzw->outbuf);
	free(lzw);
	return ret;
}


/*
 * Misc read-specific define cruft
 */

#ifndef	NOALLIGN
# define NOALLIGN	0
#endif

union bytes {
	long word;
	struct {
#if BYTE_ORDER == BIG_ENDIAN
		unsigned char b1, b2, b3, b4;
#elif BYTE_ORDER == LITTLE_ENDIAN
		unsigned char b4, b3, b2, b1;
#endif
	} bytes;
};

#if BYTE_ORDER == BIG_ENDIAN && NOALLIGN == 1
# define input(b,o,c,n,m) \
	do { \
		(c) = (*(long *)(&(b)[(o)>>3])>>((o)&0x7))&(m); \
		(o) += (n); \
	} while (0)
#else
# define input(b,o,c,n,m) \
	do { \
		unsigned char *p = &(b)[(o)>>3]; \
		(c) = ((((long)(p[0]))|((long)(p[1])<<8)| \
		       ((long)(p[2])<<16))>>((o)&0x7))&(m); \
		(o) += (n); \
	} while (0)
#endif

#define de_stack				((unsigned char *)&(lzw->htab[HSIZE-1]))

/*
 * Read LZW file
 */
libstdf_hidden
ssize_t lzw_read(lzwFile *lzw, void *readbuf, size_t count)
{
	size_t count_left = count;
	unsigned char *inbuf = lzw->inbuf;
	unsigned char *outbuf = lzw->outbuf;

	long int maxmaxcode = MAXCODE(lzw->maxbits);

	if (!count || lzw->eof)
		return 0;

	if (lzw->stackp != NULL) {
		if (lzw->outpos) {
			if (lzw->outpos >= count) {
				outbuf = lzw->unreadbuf;
				goto empty_existing_buffer;
			} else /*if (lzw->outpos < count)*/ {
				memcpy(readbuf, lzw->unreadbuf, lzw->outpos);
				goto resume_partial_reading;
			}
		}
		goto resume_reading;
	}

	do {
resetbuf:
		{
			int	i, e, o;
			e = lzw->insize - (o = (lzw->posbits >> 3));

			for (i = 0; i < e; ++i)
				inbuf[i] = inbuf[i+o];

			lzw->insize = e;
			lzw->posbits = 0;
		}

		if (lzw->insize < IN_BUFSIZE-BUFSIZE) {
			if ((lzw->rsize = read(lzw->fd, inbuf+lzw->insize, BUFSIZE)) < 0)
				return -1;
			lzw->insize += lzw->rsize;
		}

		lzw->inbits = ((lzw->rsize > 0) ? (lzw->insize - lzw->insize%lzw->n_bits)<<3 : 
		               (lzw->insize<<3) - (lzw->n_bits-1));

		while (lzw->inbits > lzw->posbits) {
			if (lzw->free_ent > lzw->maxcode) {
				lzw->posbits = ((lzw->posbits-1) + ((lzw->n_bits<<3) -
				                (lzw->posbits-1 + (lzw->n_bits<<3)) % (lzw->n_bits<<3)));

				++lzw->n_bits;
				if (lzw->n_bits == lzw->maxbits)
					lzw->maxcode = maxmaxcode;
				else
					lzw->maxcode = MAXCODE(lzw->n_bits)-1;

				lzw->bitmask = (1 << lzw->n_bits) - 1;
				goto resetbuf;
			}

			input(inbuf,lzw->posbits,lzw->code,lzw->n_bits,lzw->bitmask);

			if (lzw->oldcode == -1) {
				outbuf[lzw->outpos++] = lzw->finchar = lzw->oldcode = lzw->code;
				continue;
			}

			if (lzw->code == CLEAR && lzw->block_mode) {
				memset(lzw->codetab, 0x00, sizeof(lzw->codetab));
				lzw->free_ent = FIRST - 1;
				lzw->posbits = ((lzw->posbits-1) + ((lzw->n_bits<<3) -
				                (lzw->posbits-1 + (lzw->n_bits<<3)) % (lzw->n_bits<<3)));
				lzw->maxcode = MAXCODE(lzw->n_bits = INIT_BITS)-1;
				lzw->bitmask = (1 << lzw->n_bits) - 1;
				goto resetbuf;
			}

			lzw->incode = lzw->code;
			lzw->stackp = de_stack;

			/* Special case for KwKwK string.*/
			if (lzw->code >= lzw->free_ent) {
				if (lzw->code > lzw->free_ent) {
					errno = EINVAL;
					return -1;
				}

				*--lzw->stackp = lzw->finchar;
				lzw->code = lzw->oldcode;
			}

			/* Generate output characters in reverse order */
			while (lzw->code >= 256) {
				*--lzw->stackp = lzw->htab[lzw->code];
				lzw->code = lzw->codetab[lzw->code];
			}

			*--lzw->stackp = (lzw->finchar = lzw->htab[lzw->code]);

			/* And put them out in forward order */
			{
				lzw->stackp_diff = de_stack - lzw->stackp;

				if (lzw->outpos+lzw->stackp_diff >= BUFSIZE) {
					do {
						if (lzw->stackp_diff > BUFSIZE-lzw->outpos)
							lzw->stackp_diff = BUFSIZE-lzw->outpos;

						if (lzw->stackp_diff > 0) {
							memcpy(outbuf+lzw->outpos, lzw->stackp, lzw->stackp_diff);
							lzw->outpos += lzw->stackp_diff;
						}

						if (lzw->outpos >= BUFSIZE) {
							if (lzw->outpos < count_left) {
								memcpy(readbuf, outbuf, lzw->outpos);
resume_partial_reading:
								readbuf += lzw->outpos;
								count_left -= lzw->outpos;
							} else {
empty_existing_buffer:
								lzw->outpos -= count_left;
								memcpy(readbuf, outbuf, count_left);
								lzw->unreadbuf = outbuf + count_left;
								return count;
							}
resume_reading:
							lzw->outpos = 0;
						}
						lzw->stackp += lzw->stackp_diff;
					} while ((lzw->stackp_diff = (de_stack-lzw->stackp)) > 0);
				} else {
					memcpy(outbuf+lzw->outpos, lzw->stackp, lzw->stackp_diff);
					lzw->outpos += lzw->stackp_diff;
				}
			}

			/* Generate the new entry. */
			if ((lzw->code = lzw->free_ent) < maxmaxcode) {
				lzw->codetab[lzw->code] = lzw->oldcode;
				lzw->htab[lzw->code] = lzw->finchar;
				lzw->free_ent = lzw->code+1;
			}

			lzw->oldcode = lzw->incode;	/* Remember previous code. */
		}
    } while (lzw->rsize != 0);

	if (lzw->outpos < count_left) {
		lzw->eof = 1;
		memcpy(readbuf, outbuf, lzw->outpos);
		count_left -= lzw->outpos;
		return (count - count_left);
	} else {
		goto empty_existing_buffer;
	}
}
