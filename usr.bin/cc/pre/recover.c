#include "../pre.h"
#include <stdarg.h>

void
pre_recover (int n, ...)
{
	va_list ap;
	while (lex_token.type != LEX_TOKEN_TYPE_EOF)
	{
		va_start(ap, n);

		preproc();
		for (int i = 0; i<n; i++)
		{
			enum lex_tokenType t = va_arg(ap, enum lex_tokenType);

			if (lex_token.type == t) return;
		}

		va_end(ap);
	}
}
