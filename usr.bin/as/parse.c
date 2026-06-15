#include <libintl.h>
#include <endian.h>
#include "parse.h"
#include "emit.h"
#include "main.h"

void
parse (void)
{
	lex();
	do
	{
		// sections
		if (parse_section()) continue;

		// architecture
		if (parse_architecture()) continue;

		// emit data
		// reserve data

		// global
		if (parse_global()) continue;

		// x86-16
	#ifdef X86_16
		if (le16toh(currentArchitecture.arch) == MIO_ARCH_ARCH_X86_16)
		{
			parse_x86_16();
		}
	#endif

		// label
		if (parse_label()) continue;

		// ignore newline
		if (ltok.type == TOK_NEWLINE)
		{
			lex();
			continue;
		}

		// loose token
		prettyprint(gettext("Uncaught token\n"));
		errors++;
		recover();
	} while (ltok.type != TOK_EOF);
}
