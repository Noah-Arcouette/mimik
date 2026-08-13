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

	// pre-process only
	if (args_flags.preprocess_only)
	{
		preprocessOnly();
		args_freeFiles();
		args_freeIncludes();
		if (errors) return 1;
		return 0;
	}
	// else
	fprintf(stderr, gettext("%s: C compilation not implemented\n"), self);
	errors++;

	// .c, .i => .ir
	args_freeIncludes();
	// .ir => .s
	// .s => .o
	// .o, .a, .so => .so, exec

	args_freeFiles();

	if (errors) return 1;
	return 0;
}
