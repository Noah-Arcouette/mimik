#include <libintl.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"

int argFlags = 0;
const char *entry      = "_start";
const char *outputFile = "a.out";
const char *scriptFile = "/usr/libexec/linker.ld";

void
args (int argc, char *argv[])
{
	int c;
	do
	{
		c = getopt(argc, argv, "re:o:T:");

		switch (c)
		{
		case 'r':
			argFlags |= ARG_FLAGS_DONT_MAP;
			break;
		case 'e':
			entry = optarg;
			break;
		case 'o':
			outputFile = optarg;
			break;
		case 'T':
			scriptFile = optarg;
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
}
