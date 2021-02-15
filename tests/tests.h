/*
 * Written by Mike Frysinger <vapier@gmail.com>
 * Released into the public domain.
 */

#include "headers.h"
#include "helpers.h"
#include <lzw.h>

#define err(fmt, args...) do { warn(fmt "\n", ## args); exit(-1); } while (0)
#define errp(fmt, args...) err(fmt ": %s", strerror(errno), ## args)
