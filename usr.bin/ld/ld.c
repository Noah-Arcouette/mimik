#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

const char *self = "ld";

int
main (int argc, const char **const argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	atexit(freeAll);
	for (int i = 1; i<argc; i++)
	{
		ld_input(argv[i]);
	}

	return errors;
}
