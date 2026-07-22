#include <libintl.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include "../main.h"
#include "../lex.h"

/**
 * Return the seek of the current lexer file
 * @file prettyprint.c
 * @param off The offset to return to
 */
static void
_fixSeek (long off)
{
	if (fseek(lfp, off, SEEK_SET) == -1)
	{
		int error = errno;
		fprintf(stderr, gettext("%s: Failed to seek, %s\n"),
			lfilename,
			strerror(error));
		errors++;
	}
}

void
prettyprint (const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	// try to seek into the file

	// save the current offset
	long off = ftell(lfp);
	if (off == -1) goto _fallback;

	// seek to the start
	if (fseek(lfp, 0, SEEK_SET) == -1)
	{
		int error = errno;
		fprintf(stderr, gettext("%s: Failed to seek, %s\n"),
			lfilename,
			strerror(error));
		errors++;
		goto _fallback;
	}

	// find the line
	long clineno = 1;
	while (clineno < ltoken.lineno)
	{
		int c = fgetc(lfp);

		if (c == '\n') clineno++;
		if (c == EOF)
		{
			int error = errno;
			if (ferror(lfp))
			{
				fprintf(stderr, gettext("%s: Failed to read, %s\n"),
					lfilename,
					strerror(error));
				errors++;
				_fixSeek(off); // fix seek then fallback to the other
				goto _fallback;
			}

			break;
		}
	}

	// print the line with highlighting
	fprintf(stderr, gettext("%s:%zu: "), lfilename, ltoken.lineno);
	long coffset = 0;
	while (1)
	{
		int c = fgetc(lfp);

		if (c == EOF)
		{
			int error = errno;
			if (ferror(lfp))
			{
				fprintf(stderr, gettext("%s: Failed to read, %s\n"),
					lfilename,
					strerror(error));
				errors++;

				// don't do the fallback because we're already starting printing
			}

			break;
		}

		// don't print a newline because there may not be one,
		// so we shouldn't assume
		if (c == '\n') break;

		// add underlining
		if (coffset == ltoken.offset)
		{
			fprintf(stderr, gettext("\x1b[4m"));
		}
		if (coffset == ltoken.offset+ltoken.length)
		{
			fprintf(stderr, gettext("\x1b[0m"));
		}
		coffset++;

		putc(c, stderr);
	}
	// clear the underlining just in case
	fprintf(stderr, gettext("\x1b[0m\n\t"));
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);

	// fix the seek
	_fixSeek(off);

	va_end(ap);

	return;

_fallback:
	// fall back print function
	fprintf(stderr, gettext("%s:%zu:%zu-%zu: "),
		lfilename,
		ltoken.lineno,
		ltoken.offset,
		ltoken.offset+ltoken.length);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);

	va_end(ap);
}
