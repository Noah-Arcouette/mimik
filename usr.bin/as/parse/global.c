#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <string.h>
#include <endian.h>

int
parse_global (void)
{
	if (ltok.type != TOK_GLOBAL) return 0;
	lex();

	while (ltok.type == TOK_SYMBOL)
	{
		// find the symbol
		int found = 0;
		for (size_t i = 0; i<symbols; i++)
		{
			struct MiO_Symbol *s = &symbol[i];

			// found the symbol
			if (!strncmp((void *)s->name, ltok.buf, sizeof(s->name)))
			{
				// mark it global
				found = 1;
				s->flags = htole16(le16toh(s->flags) | MIO_SYMBOL_FLAG_GLOBAL);
				break;
			}
		}

		if (!found)
		{
			prettyprint("Failed to find symbol to mark global\n");
			errors++;
		}

		lex();
	}

	return 1;
}
