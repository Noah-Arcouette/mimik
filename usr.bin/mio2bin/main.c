#include "main.h"
#include <libintl.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

const char *self;

long errors = 0;

char *buf   = NULL;
long  bufsz = 0;

int
main (int argc, char *argv[])
{
	self = argv[0];
	setlocale(LC_ALL, "");
	textdomain("mio2bin");

	// parse arguments
	args(argc, argv);
	if (errors) return 1;

	// open input file
	if ((optind+1) != argc)
	{
		fprintf(stderr, gettext("%s: exactly one input file is required\n"),
			self);
		return 1;
	}

	// read in the file
	readIn(argv[optind]);
	getSections();
	// relocateSymbols();
	// fillGaps();
	// executeMaps();
	// if (!errors) writeFile();

	free(buf);
	if (errors) return 1;
	return 0;
}
