#include "../parse.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdlib.h>
#include <errno.h>

int
parse_sectionCopy (const char *sym)
{
	// ALIGN(expr)
	// expr
	// <nothing>

	// (NOLOAD)
	// <nothing>

	// :

	// ALIGN(expr)
	// expr
	// <nothing>

	// {

	// file(section...)
	// BYTE(expr) SHORT(expr) LONG(expr) QUAD(expr)
	// }

	// update period

	return 0;
}
