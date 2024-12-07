#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "defs.h"

void
printError (int errnum, const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);

	fprintf(stderr, "%s: ", self);
	vfprintf(stderr, fmt, va);

	if (errnum)
		fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));

	va_end(va);
}
