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

	// open input files
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

	// emit the output

	return 1;
}
