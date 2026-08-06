#include "main.h"
#include <libintl.h>
#include <unistd.h>
#include <locale.h>

const char *self;

long errors = 0;

int
main (int argc, char *argv[])
{
	self = argv[0];
	setlocale(LC_ALL, "");
	textdomain("fdisk");

	// disk file
	if (openDisk(argc, argv)) return 1;

	int c;
	argv++;
	do
	{
		c = getopt(argc, argv, "+p:z:s:t:a:o:f:A:Z:C:H:S:dli:m:M:u:");

		switch (c)
		{
			// -p
			// -z
			// -s
			// -t
			// -a

			// -o
			// -f

			// -A
			// -Z
			// -C
			// -H
			// -S

			// -d
			// -l

			// -i
			// -m
			// -M

			// (mbr)
			// -u
		case ':':
		case '?':
			errors++;
			break;
		case -1:
			break;
		default:
			fprintf(stderr, gettext("%s: Unhandled option -- %c\n"), self, c);
			errors++;
			break;
		}

		// error?
		if (errors)
		{
			fprintf(stderr, gettext(
"%s: Aborting.\n"
"%s: Last argv index, %d\n"
				), self, self, optind);
			break;
		}
	} while (c != -1);

	fclose(disk);

	if (errors) return 1;
	return 0;
}
