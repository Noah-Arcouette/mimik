#include "main.h"
#include <libintl.h>
#include <locale.h>
#include <stdio.h>

long errors = 0;

const char *self;

int
main (int argc, char *argv[])
{
	self = argv[0];
	setlocale(LC_ALL, "");
	textdomain("ld");

	args(argc, argv);
	if (errors) return 1;

	return 1;
}
