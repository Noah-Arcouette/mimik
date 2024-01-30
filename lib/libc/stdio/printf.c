#include <stdio.h>
#include <stdarg.h>

int
printf (const char *fmt, ...)
{
	va_list vargs;
	va_start(vargs, fmt);

	int ret = vfprintf(stdout, fmt, vargs);

	va_end(vargs);

	return ret;
}

int
fprintf (FILE *restrict file, const char *restrict fmt, ...)
{
	va_list vargs;
	va_start(vargs, fmt);

	int ret = vfprintf(file, fmt, vargs);

	va_end(vargs);

	return ret;
}
