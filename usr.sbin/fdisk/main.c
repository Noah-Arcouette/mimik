#include "main.h"
#include <libintl.h>
#include <unistd.h>
#include <locale.h>

const char *self;

int
main (int argc, char *argv[])
{
	self = argv[0];
	setlocale(LC_ALL, "");
	textdomain("fdisk");

	// disk file
	if (openDisk(argc, argv)) return 1;

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

	fclose(disk);

	return 0;
}
