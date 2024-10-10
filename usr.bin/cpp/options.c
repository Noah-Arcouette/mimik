#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void
options (int argc, char *const *argv)
{
	filename = "<command-line>";
	int c;
	opterr = 0; // no outputs
	lineno = 1;
	char *string;
	while (1)
	{
		c = getopt(argc, argv, ":U:D:");
		if (c < 0)
		{
			break; // leave on end of getopt
		}

		switch (c)
		{
		case '?':
			fprintf(stderr, "%s:%zu: Unknown option `%c'\n", filename, lineno, optopt);
			exit(1);
			break;
		case ':':
			fprintf(stderr, "%s:%zu: Option `%c' requires a parameter.\n", filename, lineno, optopt);
			exit(1);
			break;
		case 'U':
			string = "#undef ";
			while (*string) // print undefine
			{
				lineSplicing(*string);
				string++;
			}
			string = optarg;
			while (*string) // give the given value
			{
				lineSplicing(*string);
				string++;
			}
			lineSplicing('\n'); // newline
			break;
		case 'D':
			string = "#define ";
			while (*string) // print define
			{
				lineSplicing(*string);
				string++;
			}

			// convert first `=' to a space
			char *eq = strchr(optarg, '=');
			if (eq) // there may not be one
			{
				*eq = ' ';
			}

			string = optarg;
			while (*string) // give the given value
			{
				lineSplicing(*string);
				string++;
			}
			lineSplicing('\n');
			break;
		}
		lineno++;
	}
}
