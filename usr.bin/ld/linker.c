#include "main.h"
#include "lex.h"

void
linker (void)
{
	// open script file

	// ENTRY(symbol)
	// ARCH(arch)
	// UARCH(uarch)
	// ARCHFLAGS(archflag...)
	// SYS(sys)
	// USYS(usys)
	// SYSFLAGS(sysflag...)

	// SECTIONS {
	//   symbol = expr;
	//   section [expr] [(noload)] : [expr]
	//   {
	//      file(section...)
	//      ...
	//   }
	//   ...
	// }

	// close up script file
	lex_free();
}
