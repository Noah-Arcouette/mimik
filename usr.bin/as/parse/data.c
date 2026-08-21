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
				wchar_t *s = ltok.buf+1;
				wchar_t d = L'\\';
				while (*s != L'\0')
				{
					d = *s;
					if (*s == L'\\')
					{
						d = L'\\';
						s++;
						switch (*s)
						{
						case L'0':
							*s = L'\0';
							break;
						case L'a':
							*s = L'\a';
							break;
						case L'b':
							*s = L'\b';
							break;
						case L'e':
							*s = L'\e';
							break;
						case L'f':
							*s = L'\f';
							break;
						case L'n':
							*s = L'\n';
							break;
						case L'r':
							*s = L'\r';
							break;
						case L't':
							*s = L'\t';
							break;
						case L'v':
							*s = L'\v';
							break;
						// case '\\': // just emit it
						// case '"': // just emit it
						}
					}

					if (*s != L'"' || d == L'\\') emit(s, 1);

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
