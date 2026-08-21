#include "../parse.h"
#include "../main.h"
#include "x86_16.h"
#include <libintl.h>
#include <string.h>
#include <errno.h>
#include <mio.h>

int
parse_x86_16_mem16 (struct mem16 *mem16, int rwx)
{
	// [
	if (ltok.type != TOK_OPEN_SQUARE)
	{
		return 0;
	}
	lex();

	struct mem16 addr;
	addr.symbol = NULL;

	long val;
	if (ltok.type == TOK_REGISTER)
	{
		// %bx
		if (!wcscmp(ltok.buf, L"%bx"))
		{
			lex();
			addr.modrm = 0b111;

			// +
			if (ltok.type == TOK_PLUS)
			{
				lex();

				// %si
				if (!wcscmp(ltok.buf, L"%si"))
				{
					addr.modrm = 0b000;
					lex();
				}
				// %di
				else if (!wcscmp(ltok.buf, L"%di"))
				{
					addr.modrm = 0b001;
					lex();
				}
				else
				{
					prettyprint(gettext("Expected %%di or %%si\n"));
					errors++;
				}
			}
		}
		// %bp
		if (!wcscmp(ltok.buf, L"%bp"))
		{
			lex();
			addr.modrm = 0b110;

			// +
			if (ltok.type == TOK_PLUS)
			{
				lex();

				// %si
				if (!wcscmp(ltok.buf, L"%si"))
				{
					addr.modrm = 0b010;
					lex();
				}
				// %di
				else if (!wcscmp(ltok.buf, L"%di"))
				{
					addr.modrm = 0b011;
					lex();
				}
				else
				{
					prettyprint(gettext("Expected %%di or %%si\n"));
					errors++;
				}
			}
		}
		// %si
		if (!wcscmp(ltok.buf, L"%si"))
		{
			lex();
			addr.modrm = 0b100;
		}
		// %di
		if (!wcscmp(ltok.buf, L"%di"))
		{
			lex();
			addr.modrm = 0b101;
		}

		// ]
		if (ltok.type != TOK_CLOSE_SQUARE)
		{
			prettyprint(gettext("Expected a closing square bracket\n"));
			errors++;
		}
		else
		{
			lex();
		}

		// +
		if (ltok.type == TOK_PLUS)
		{
			lex();

			// number
			if (parse_number(&val))
			{
				// sign extend
				if (
					((val & 0xff80) == 0xff80) // sign extended
					|| !(val & 0xff00) // one byte
				)
				{
					addr.modrm |= 0b01000000;
					addr.displacement[0] = val&0xff;
				}
				else // two bytes
				{
					addr.modrm |= 0b10000000;
					addr.displacement[0] = (val   )&0xff;
					addr.displacement[1] = (val>>8)&0xff;
				}
			}
			// symbol
			else if (ltok.type == TOK_SYMBOL)
			{
				// 16bit
				addr.modrm |= 0b10000000;
				addr.displacement[0] = 0;
				addr.displacement[1] = 0;
				addr.symbol = wcsdup(ltok.buf);
				if (!addr.symbol)
				{
					prettyprint(gettext("%s\n"), strerror(errno));
				}
				addr.gapType = MIO_GAP_TYPE_LIT_LE16 | rwx;
				lex();
			}
			else
			{
				prettyprint(gettext("Expected a number or symbol\n"));
				errors++;
			}
		}
		// -
		if (ltok.type == TOK_MINUS)
		{
			lex();

			// number
			if (parse_number(&val))
			{
				val = -val; // negative

				// sign extend
				if (
					((val & 0xff80) == 0xff80) // sign extended
					|| !(val & 0xff00) // one byte
				)
				{
					addr.modrm |= 0b01000000;
					addr.displacement[0] = val&0xff;
				}
				else // two bytes
				{
					addr.modrm |= 0b10000000;
					addr.displacement[0] = (val   )&0xff;
					addr.displacement[1] = (val>>8)&0xff;
				}
			}
			else
			{
				prettyprint(gettext("Expected a number\n"));
				errors++;
			}
		}

		// check for [%bp], which isn't possible and must be changed to [%bp]+0
		if (addr.modrm == 0b110)
		{
			addr.modrm = 0b01000110;
			addr.displacement[0] = 0;
		}
	}
	// symbol
	else if (ltok.type == TOK_SYMBOL)
	{
		addr.modrm = 0x06;
		addr.displacement[0] = 0;
		addr.displacement[1] = 0;
		addr.symbol          = wcsdup(ltok.buf);
		if (!addr.symbol)
		{
			prettyprint(gettext("%s\n"), strerror(errno));
		}
		addr.gapType = MIO_GAP_TYPE_LIT_LE16 | rwx;
		lex();

		// ]
		if (ltok.type != TOK_CLOSE_SQUARE)
		{
			prettyprint(gettext("Expected a closing square bracket\n"));
			errors++;
		}
		else
		{
			lex();
		}
	}
	// number
	else if (parse_number(&val))
	{
		addr.modrm = 0x06;
		addr.displacement[0] = (val   )&0xff;
		addr.displacement[1] = (val>>8)&0xff;

		// ]
		if (ltok.type != TOK_CLOSE_SQUARE)
		{
			prettyprint(gettext("Expected a closing square bracket\n"));
			errors++;
		}
		else
		{
			lex();
		}
	}

	if (mem16)
	{
		memcpy(mem16, &addr, sizeof(struct mem16));
	}
	return 1;
}
