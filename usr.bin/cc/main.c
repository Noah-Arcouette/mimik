#include "main.h"
#include "args.h"
#include <libintl.h>
#include <locale.h>

const char *self;

int errors = 0;

int
main (int argc, char *argv[])
{
	self = argv[0];
	setlocale(LC_ALL, "");
	textdomain("cc");

	// parse the command line arguments
	args(argc, argv);

	// .c, .i => .ir
	// .ir => .s
	// .s => .o
	// .o, .a, .so => .so, exec

	args_freeFiles();

	if (errors) return 1;
	return 0;
}
