#include "main.h"
#include <libintl.h>
#include <unistd.h>
#include <stdio.h>

char *outputfile = NULL;

short argFlags = 0;

void
args (int argc, char *argv[])
{
	int c;
	do
	{
		c = getopt(argc, argv, "vo:");

		switch (c)
		{
		case 'o':
			outputfile = optarg;
			break;
		case 'v':
			argFlags |= LOAD_VIRTUAL;
			break;
		case '?':
		case ':':
			errors++;
			break;
		case -1:
			break;
		}
	} while (c != -1);
}
