#include "../lex.h"
#include <stdarg.h>

void
lex_recover (int n, ...)
{
	va_list ap;
	while (lex_token.type != LEX_TOKEN_TYPE_EOF)
	{
		va_start(ap, n);

		for (int i = 0; i<n; i++)
		{
			enum lex_tokenType t = va_arg(ap, enum lex_tokenType);

			if (lex_token.type == t) return;
		}

		lex();
		va_end(ap);
	}
}
