#include "../parse.h"
#include "../main.h"
#include "../emit.h"
#include <libintl.h>

int
parse_data (void)
{
	// .byte
	if (ltok.type == TOK_BYTE)
	{
		lex();

		long val;
		while (1)
		{
			if (parse_number(&val))
			{
				char dat[1] = { val&0xff };
				emit(dat, 1);
			}
			else if (ltok.type == TOK_STRING)
			{
				char *s = ltok.buf+1;
				char d = '\\';
				while (*s)
				{
					d = *s;
					if (*s == '\\')
					{
						d = '\\';
						s++;
						switch (*s)
						{
						case '0':
							*s = '\0';
							break;
						case 'a':
							*s = '\a';
							break;
						case 'b':
							*s = '\b';
							break;
						case 'e':
							*s = '\e';
							break;
						case 'f':
							*s = '\f';
							break;
						case 'n':
							*s = '\n';
							break;
						case 'r':
							*s = '\r';
							break;
						case 't':
							*s = '\t';
							break;
						case 'v':
							*s = '\v';
							break;
						// case '\\': // just emit it
						// case '"': // just emit it
						}
					}

					if (*s != '"' || d == '\\') emit(s, 1);

					s++;
				}
				lex();
			}
			else if (ltok.type == TOK_SYMBOL)
			{
				emitGap(ltok.buf, MIO_GAP_TYPE_LIT_BYTE);
				lex();
			}
			else break;
		}

		return 1;
	}

	return 0;
}
