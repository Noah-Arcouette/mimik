#include <libintl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "main.h"

int argFlags = 0;
const char *outputFile = "a.out";
const char *scriptFile = "/usr/libexec/linker.ld";

#ifdef STRIP
char *stripcmd          = NULL;
static long stripcmdlen = 1;

static void
_push_strip (const char *str)
{
	stripcmdlen += strlen(str);
	void *buf = realloc(stripcmd, stripcmdlen);
	if (!buf)
	{
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		errors++;
		return;
	}

	if (stripcmd) // additional append
	{
		stripcmd = buf;
		strcat(stripcmd, str);
	}
	else // first append
	{
		stripcmd = buf;
		strcpy(stripcmd, str);
	}
}
#endif

void
args (int argc, char *argv[])
{
	setEntry("_start");

#ifdef STRIP
	const char *strip = getenv("STRIP");
	if (strip)
	{
		_push_strip(strip);
	}
	else
	{
		_push_strip("strip");
	}
#endif

	int c;
	do
	{
		c = getopt(argc, argv, "re:o:T:O:");

		switch (c)
		{
		case 'r':
			argFlags |= ARG_FLAGS_DONT_MAP;
			break;
		case 'e':
			setEntry(optarg);
			break;
		case 'o':
			outputFile = optarg;
			break;
		case 'T':
			scriptFile = optarg;
			break;
		case 'O':
		#ifdef STRIP
			_push_strip(" -O");
			_push_strip(optarg);
		#else
			fprintf(stderr, gettext(
				"%s: utility/strip not install LTO will not take effect\n"),
				self);
		#endif
			break;
		case '?':
		case ':':
			errors++;
			break;
		case -1:
			break;
		default:
			fprintf(stderr, gettext("%s: Unhandled option -- %c\n"), self, c);
			errors++;
			break;
		}
	} while (c != -1);

#ifdef STRIP
	// push the output file
	_push_strip(" ");
	_push_strip(outputFile);
#endif
}
