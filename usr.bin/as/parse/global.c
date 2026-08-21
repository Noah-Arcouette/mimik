#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdlib.h>
#include <errno.h>

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
			wchar_t wname[256] = L"";
			if (mbstowcs(wname, (void *)s->name, 256) < 0)
			{
				fprintf(stderr, gettext("%s: Failed to convert `%s', %s\n"),
					self, (char *)s->name, strerror(errno));
				errors++;
				recover();
				return 1;
			}
			if (!wcsncmp(wname, ltok.buf, 256))
			{
				// mark it global
				found = 1;
				s->flags = htole16(le16toh(s->flags) | MIO_SYMBOL_FLAG_GLOBAL);
				break;
			}
		}

		if (!found)
		{
			prettyprint(gettext("Failed to find symbol to mark global\n"));
			errors++;
		}

		lex();
	}

	return 1;
}
