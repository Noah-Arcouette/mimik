#include <libintl.h>
#include <unistd.h>
#include <locale.h>
#include "main.h"

const char *self;
int errors = 0;

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("as");

	self = argv[0];

	// parse arguments
	args(argc, argv);
	if (errors) return 1;

	// lexer testing
	struct token tok;
	createToken(&tok);
	for (int i = optind; i<argc; i++)
	{
		// parse(argv[i]);

		resetToken(&tok);
	}
	destroyToken(&tok);

	if (errors) return 1;

	// parser:
	//  - sections
	//  - architecture
	//  - symbols
	//  - gaps
	//  - emit data
	//  - reserve data
	//  - x86-16
	// create architecture section
	// create symbol section
	// create gap section
	// emit the mio file

	if (errors) return 1;
	return 0;
}
