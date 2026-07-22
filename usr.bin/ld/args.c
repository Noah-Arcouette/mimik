#include <libintl.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"

int argFlags = 0;
const char *outputFile = "a.out";
const char *scriptFile = "/usr/libexec/linker.ld";

void
args (int argc, char *argv[])
{
	setEntry("_start");
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
			setEntry(optarg);
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
