# Basics

* HOMEPAGE: https://github.com/vapier/liblzw
* BUGS:     https://github.com/vapier/liblzw/issues
* AUTHOR:   Mike Frysinger <vapier@gmail.com>

# About

liblzw is a small library that provides an API for reading
[LZW](http://en.wikipedia.org/wiki/LZW) compressed (.Z) files.  The API is
similar to that of [zlib](http://www.zlib.net/) (for reading .gz files) and
[libbzip2](http://www.bzip.org/) (for reading .bz2 files) which themselves
are just like the classical UNIX functions for reading files
(e.g. open/read/fopen/fread/etc...).

The core compression code was taken from the canonical
[ncompress](https://github.com/vapier/ncompress) program.

# License

Since the compression algorithms were ripped out of the public-domain package
[ncompress](https://github.com/vapier/ncompress), liblzw has also been released
into the public-domain for people to do with as they will. Just please send me
bugfixes as you find them :).

See the [UNLICENSE](UNLICENSE) file for more details.

# Patents

All existing patents on the LZW algorithm have
[expired world-wide](http://en.wikipedia.org/wiki/LZW#Patent_issues).
So LZW is now patent free.
