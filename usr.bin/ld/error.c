#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

size_t errors = 0;

void
error (int errnum, const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);

	fprintf(stderr, "%s: ", self);
	vfprintf(stderr, fmt, va);
	if (errnum)
	{
		fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
	}
	errors++;

	va_end(va);
}
