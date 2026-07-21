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

	// print stuff out
	do
	{
		lex();

		switch (ltoken.type)
		{
		// symbols
		case LTYPE_OPEN_CURLY:
		case LTYPE_CLOSE_CURLY:
		case LTYPE_EQUAL:
		case LTYPE_SEMICOLON:
		case LTYPE_COLON:
		case LTYPE_OPEN_PAREN:
		case LTYPE_CLOSE_PAREN:
		case LTYPE_PLUS:
		case LTYPE_SUBTRACT:
		case LTYPE_DIVIDE:
		case LTYPE_MULTIPLY:
		case LTYPE_PERIOD:
			printf("%c ", ltoken.type);
			break;
		// others
		case LTYPE_EOF:
			printf("eof\n");
			break;
		case LTYPE_UNKNOWN:
			printf("unk<%s> ", ltoken.buf);
			break;
		// macros
		case LTYPE_ENTRY:
			printf("entry ");
			break;
		case LTYPE_ARCH:
			printf("arch ");
			break;
		case LTYPE_UARCH:
			printf("uarch ");
			break;
		case LTYPE_ARCHFLAGS:
			printf("archflags ");
			break;
		case LTYPE_SYS:
			printf("sys ");
			break;
		case LTYPE_USYS:
			printf("usys ");
			break;
		case LTYPE_SYSFLAGS:
			printf("sysflags ");
			break;
		// values
		case LTYPE_SYMBOL:
			printf("sym<%s> ", ltoken.buf);
			break;
		case LTYPE_INTEGER:
			printf("int<%s> ", ltoken.buf);
			break;
		}
	} while (ltoken.type != LTYPE_EOF);

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
