#include <unistd.h>
#include "main.h"

struct arguments arguments = {
	.outputfile = "a.out"
};

int
args (int argc, char *argv[])
{
	int errors = 0;

	int c;
	do
	{
		c = getopt(argc, argv, "o:");

		switch (c)
		{
		case 'o':
			arguments.outputfile = optarg;
			break;
		case '?':
		case ':':
			errors++;
			break;
		}
	} while (c != -1);

	return errors;
}
