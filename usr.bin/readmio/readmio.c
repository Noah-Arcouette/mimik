#include <errno.h>
#include <stdio.h>
#include "defs.h"

const char *self = "/usr/bin/readmio";

int
main (int argc, const char **argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	// for each input file
	FILE *f;
	for (int i = 1; i<argc; i++)
	{
		// open file
		f = fopen(argv[i], "r");
		if (!f)
		{
			printError(errno, "Failed to open file `%s'.\n", argv[i]);
			continue; // skip it
		}
		// else
		printf("\n%s:\n", argv[i]); // say what file we're in


		// close when finished
		fclose(f);
	}
}
