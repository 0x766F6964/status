#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "status.h"

void
die(const char *errstr, ...)
{
	va_list ap;

	va_start(ap, errstr);
	vfprintf(stderr, errstr, ap);
	va_end(ap);
	exit(1);
}

const char *
bprintf(const char *fmt, ...)
{
	size_t ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	return (ret < 0)? NULL : buf;
}

int
pscanf(const char *path, const char *fmt, ...)
{
	FILE *fp;
	va_list ap;
	int ret;

	if (!(fp = fopen(path, "r")))
		return -1;

	va_start(ap, fmt);
	ret = vfscanf(fp, fmt, ap);
	va_end(ap);
	fclose(fp);

	return (ret == EOF) ? -1 : ret;
}