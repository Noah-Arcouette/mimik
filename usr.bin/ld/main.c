#include "main.h"
#include <libintl.h>
#include <unistd.h>
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

	// open input files
	for (int i = optind; i<argc; i++)
	{
		openInputFile(argv[i]);
	}
	// resolve conflicting symbols (rename static, crash on global)

	// run the linker script:
	// expressions and literal symbols
	// ENTRY
	// SECTIONS:
	//  - section
	//  - memory
	//  - symbols
	//  - gaps
	// ARCH, UARCH, ARCHFLAGS
	// SYS, USYS, SYSFLAGS

	// check for unused symbols and section

	// raw input data isn't needed anymore
	closeInputFiles();

	// emit architecture section
	// emit gaps section
	// emit symbols section
	// emit maps section
	// emit the output

	if (errors) return 1;
	return 0;
}
