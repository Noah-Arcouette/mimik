#include <libintl.h>
#include <unistd.h>
#include <locale.h>
#include "main.h"

const char *self;

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("as");

	self = argv[0];

	// parse arguments
	if (args(argc, argv))
	{
		return 1;
	}

	// lexer testing
	int errors = 0;
	struct token tok;
	createToken(&tok);
	for (int i = optind; i<argc; i++)
	{
		// errors += parse(argv[i]);

		resetToken(&tok);
	}
	destroyToken(&tok);


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

	return errors;
}
