/* Simple app to show how to uncompress an entire file.  Same thing
 * as running: uncompress -d -c file
 *
 * Written by Mike Frysinger <vapier@gmail.com>
 * Released into the public domain
 */

#include "tests.h"

int main(int argc, char *argv[])
{
	size_t numread;
	unsigned char buf[1024];
	lzwFile *lzw;

	if (argc != 2)
		err("Usage: uncompress <file>");

	lzw = lzw_open(argv[1], O_RDONLY | O_BINARY);

	if (lzw == NULL)
		err("could not open file");

	while ((numread = lzw_read(lzw, buf, sizeof(buf))) > 0)
		if (fwrite(buf, 1, numread, stdout) != numread)
			errp("fwrite() failed");

	if (lzw_close(lzw))
		err("could not close file");

	return 0;
}
