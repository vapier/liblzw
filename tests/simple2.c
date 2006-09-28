/* Copyright (C) 2005-2006 Mike Frysinger <vapier@gmail.com>
 */

#include <lzw_internal.h>

#define err(fmt, args...) do { warn(fmt, ## args); exit(-1); } while (0)

int main(int argc, char *argv[])
{
	int cnt;
	size_t numread;
	char buf[1024];
	lzwFile *lzw = lzw_open(argc == 2 ? argv[1] : "simple2.Z", O_RDONLY);

	if (lzw == NULL)
		err("could not open file");

	for (cnt=0; cnt<20; ++cnt) {
		memset(buf, 0x41, sizeof(buf));
		numread = lzw_read(lzw, buf, 10);
		if (numread <= 0) {
			printf("EOF\n");
			break;
		}
		buf[12] = '\0';
		printf("%zi: %s\n", numread, buf);
		if (numread != 10)
			printf("short read!\n");
	}

	if (lzw_close(lzw))
		err("could not close file");

	return 0;
}
