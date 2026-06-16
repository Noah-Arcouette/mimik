#include <libintl.h>
#include <unistd.h>
#include <locale.h>
#include <stdio.h>
#include "main.h"

const char *self;
int errors = 0;

int
main (int argc, char *argv[])
{
	self = argv[0];

	setlocale(LC_ALL, "");
	textdomain("readmio");

	// parse arguments
	int c;
	do
	{
		c = getopt(argc, argv, "");
		switch (c)
		{
		case ':':
		case '?':
			return 1;
		}
	} while (c != -1);

	for (int i = optind; i<argc; i++)
	{
		printFile(argv[i]);
	}

	if (errors) return 1;
	return 0;
}
