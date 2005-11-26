/* Copyright (C) 2005 Mike Frysinger <vapier@gmail.com>
 */

#include <lzw_internal.h>

#define err(fmt, args...) do { warn(fmt, ## args); exit(-1); } while (0)

int main(int argc, char *argv[])
{
	int cnt;
	size_t numread;
	char buf[1024];
	lzwFile *lzw = lzw_open(argc == 2 ? argv[1] : "lot.Z", O_RDONLY);

	if (lzw == NULL)
		err("could not open file");

	while ((numread = lzw_read(lzw, buf, 50)) > 0) {
		for (cnt=0; cnt<numread; ++cnt)
			printf("%2.2X", (unsigned char)buf[cnt]);
		printf("\n");
	}
		

	if (lzw_close(lzw))
		err("could not close file");

	return 0;
}
