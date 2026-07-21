#include "main.h"
#include "lex.h"
#include <libintl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void
linker (void)
{
	// open script file
	lfp = fopen(scriptFile, "r");
	if (!lfp)
	{
		fprintf(stderr, gettext("%s: Failed to open script file, %s\n"),
			self, strerror(errno));
		errors++;
		return;
	}
	lfilename = scriptFile;

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
	//      file(section...) // glob matching
	//      ...
	//   }
	//   ...
	// }

	// close up script file
	lex_free();
}
