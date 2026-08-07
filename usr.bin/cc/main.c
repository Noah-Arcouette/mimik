#include "main.h"
#include "args.h"
#include <libintl.h>
#include <locale.h>

const char *self;
long errors = 0;

int
main (int argc, char *argv[])
{
	self = argv[0];
	textdomain("cc");
	setlocale(LC_ALL, "");

	args(argc, argv);
	// compile C files
	args_freeInclude();
	// optimize IR
	// compile IR
	// assemble
	// link
	args_freeFile();

	if (errors) return 1;
	return 0;
}
