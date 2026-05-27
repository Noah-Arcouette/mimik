#include "main.h"

int
main (int argc, char *argv[])
{
	// parse arguments
	if (args(argc, argv))
	{
		return 1;
	}

	// lexer
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

	return 1;
}
