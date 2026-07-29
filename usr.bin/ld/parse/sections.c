#include "../parse.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>

int
parse_sections (void)
{
	if (ltoken.type != LTYPE_SECTIONS) return 0;
	lex();

	// {
	if (ltoken.type != LTYPE_OPEN_CURLY)
	{
		prettyprint("Expected opening curly bracket\n");
		errors++;
		recover();
		return 1;
	}
	lex();

	// until } or EOF
	while (ltoken.type != LTYPE_CLOSE_CURLY && ltoken.type != LTYPE_EOF)
	{
		// symbol = expr;
		// section [expr] [(noload)] : [expr]
		// {
		//    file(section...) // glob matching
		// }
		lex();
	}
	lex();

	return 1;
}
