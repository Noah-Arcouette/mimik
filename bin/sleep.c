#include <libintl.h>
#include <locale.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("sleep");

	// check for weird arguments
	int c;
	do
	{
		switch (c = getopt(argc, argv, ""))
		{
		case ':':
		case '?':
			return 1;
		}
	} while (c != -1);

	// make sure there's only one input
	if (argc-optind != 1)
	{
		fprintf(stderr, gettext("%s: Expected only one operand\n"), argv[0]);
		return 1;
	}

	// get the number and check the number from the operand
	long t = strtol(argv[optind], NULL, 0);
	if (t < 0 || t > UINT_MAX)
	{
		fprintf(stderr,
			gettext("%s: Time does not fit into an unsigned int\n"), argv[0]);
		return 1;
	}

	unsigned x;
	if ((x = sleep(t)) != 0)
	{
		fprintf(stderr,
			gettext("%s: Premature wake up, %us left\n"), argv[0], x);
		return 1;
	}

	return 0;
}
