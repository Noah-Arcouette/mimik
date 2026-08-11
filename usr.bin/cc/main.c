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
	// args(argc, argv);

	// Compile C files
	// Optimize IR
	// Translate IR
	// Assemble
	// Link

	return 0;
}
