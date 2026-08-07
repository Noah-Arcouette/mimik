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
	if (!errors) compileCFiles();
	args_freeInclude();
	// if (!errors) compileIRFiles();
	// if (!errors) assemble();
	// if (!errors) linkfiles();
	args_freeFile();

	if (errors) return 1;
	return 0;
}
