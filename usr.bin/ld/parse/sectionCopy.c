#include "../parse.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdlib.h>
#include <errno.h>

long currentSection = -1;

int
parse_sectionCopy (const wchar_t *sym)
{
	struct MiO_Map map;
	map.flags    = 0;
	map.virtual  = 0;
	map.physical = 0;
	map.size     = 0;
	map.amount   = 0;
	// just after the to-be-made section
	map.from     = htole64(outputsz+sizeof(struct MiO));

	if (period >= 0)
	{
		map.flags  |= MIO_MAP_FLAG_VIRTUAL_IS_ADDRESS;
		map.virtual = htole64(period);
	}

	int64_t val;

	// ALIGN
	if (ltoken.type == LTYPE_ALIGN)
	{
		period = -1;

		lex();

		// (
		if (ltoken.type != LTYPE_OPEN_PAREN)
		{
			prettyprint(gettext("Expected an opening bracket\n"));
			errors++;
			recover();
			return 1;
		}
		lex();

		// expr
		if (!parse_expr(&val))
		{
			prettyprint(gettext("Expected an expression\n"));
			errors++;
			recover();
			return 1;
		}

		// )
		if (ltoken.type != LTYPE_CLOSE_PAREN)
		{
			prettyprint(gettext("Expected a closing bracket\n"));
			errors++;
			recover();
			return 1;
		}
		lex();

		// set the value
		map.flags  &= ~MIO_MAP_FLAG_VIRTUAL_IS_ADDRESS;
		map.virtual = htole64(val);
	}
	// expr
	else if (parse_expr(&val))
	{
		// set the value
		map.flags  |= MIO_MAP_FLAG_VIRTUAL_IS_ADDRESS;
		map.virtual = htole64(val);
	}
	// <nothing>

	// NOLOAD
	if (ltoken.type == LTYPE_NOLOAD)
	{
		// set it
		map.from   = htole64(virtualsz);
		map.flags |= MIO_MAP_FLAG_VIRTUAL;
		lex();
	}
	// <nothing>

	// :
	if (ltoken.type != LTYPE_COLON)
	{
		prettyprint(gettext("Expected a colon\n"));
		recover();
		errors++;
		return 1;
	}
	lex();

	// ALIGN
	if (ltoken.type == LTYPE_ALIGN)
	{
		lex();

		// (
		if (ltoken.type != LTYPE_OPEN_PAREN)
		{
			prettyprint(gettext("Expected an opening bracket\n"));
			errors++;
			recover();
			return 1;
		}
		lex();

		// expr
		if (!parse_expr(&val))
		{
			prettyprint(gettext("Expected an expression\n"));
			errors++;
			recover();
			return 1;
		}

		// )
		if (ltoken.type != LTYPE_CLOSE_PAREN)
		{
			prettyprint(gettext("Expected a closing bracket\n"));
			errors++;
			recover();
			return 1;
		}
		lex();

		// set the value
		map.flags   &= ~MIO_MAP_FLAG_PHYSICAL_IS_ADDRESS;
		map.physical = htole64(val);
	}
	// expr
	else if (parse_expr(&val))
	{
		// set the value
		map.flags   |= MIO_MAP_FLAG_PHYSICAL_IS_ADDRESS;
		map.physical = htole64(val);
		period = val;
	}
	// <nothing>

	// {
	if (ltoken.type != LTYPE_OPEN_CURLY)
	{
		prettyprint(gettext("Expected an opening curly bracket\n"));
		recover();
		errors++;
		return 1;
	}

	lex_symbolCanGlob = 1; // add * to symbol characters
	lex();

	// create section
	struct MiO m;
	m.magic = htole32(MIO_MAGIC);
	m.size = 0;

	m.flags = 0;
	if (map.flags & MIO_MAP_FLAG_VIRTUAL) m.flags = MIO_FLAG_VIRTUAL;

	memset(m.name, 0, sizeof(m.name));
	wcstombs((char *)m.name, sym, 256);

	long _currentSection = outputsz;
	emit(&m, sizeof(m));
	currentSection = _currentSection;

	while (ltoken.type != LTYPE_CLOSE_CURLY &&
		   ltoken.type != LTYPE_EOF)
	{
		// BYTE(expr) SHORT(expr) LONG(expr) QUAD(expr)
		int size = 0;
		if (ltoken.type == LTYPE_BYTE)       size = 1;
		else if (ltoken.type == LTYPE_SHORT) size = 2;
		else if (ltoken.type == LTYPE_LONG)  size = 4;
		else if (ltoken.type == LTYPE_QUAD)  size = 8;
		if (size)
		{
			lex(); // BYTE, SHORT, LONG, QUAD

			// (
			if (ltoken.type != LTYPE_OPEN_PAREN)
			{
				prettyprint(gettext("Expected a `(`\n"));
				errors++;
				recover();
				continue;
			}
			lex();

			// expr
			int64_t x;
			if (!parse_expr(&x))
			{
				prettyprint(gettext("Expected an expression\n"));
				errors++;
				recover();
				continue;
			}
			// write
			int8_t  u8;
			int16_t u16;
			int32_t u32;
			switch (size)
			{
			case 1:
				u8 = x;
				emit(&u8, 1);
				break;
			case 2:
				u16 = x;
				emit(&u16, 2);
				break;
			case 4:
				u32 = x;
				emit(&u32, 4);
				break;
			case 8:
				emit(&x, 8);
				break;
			}

			// )
			if (ltoken.type != LTYPE_CLOSE_PAREN)
			{
				prettyprint(gettext("Expected a `)`\n"));
				errors++;
				recover();
			}
			lex();
			continue;
		}

		// file(section...)
		if (ltoken.type == LTYPE_SYMBOL)
		{
			wchar_t *sectionFile = wcsdup(ltoken.buf);
			if (!sectionFile)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				errors++;
			}

			lex();
			if (ltoken.type != LTYPE_OPEN_PAREN)
			{
				prettyprint(gettext("Expected `(` after file name\n"));
				recover();
				errors++;
				free(sectionFile);
				continue;
			}
			lex();

			while (ltoken.type != LTYPE_EOF &&
				   ltoken.type != LTYPE_CLOSE_PAREN)
			{
				if (ltoken.type != LTYPE_SYMBOL)
				{
					prettyprint(gettext("Expected a symbol\n"));
					errors++;
					lex();
					free(sectionFile);
					continue;
				}
				// sections
				dumpSection(sectionFile, ltoken.buf, &map);

				lex();
			}
			free(sectionFile);
			lex(); // )
			continue;
		}

		// else, error
		prettyprint(gettext("Expected a section copy or literal data\n"));
		errors++;
		recover();
	}
	lex_symbolCanGlob = 0;
	lex(); // closing bracket

	// update period
	if ((long)(currentSection+sizeof(struct MiO)) <= outputsz)
	{
		struct MiO *s = &outputBuf[currentSection];

		map.amount = s->size;
		map.size   = s->size;

		if (period) period += le64toh(s->size);
	}

	currentSection = -1;

	// save the map
	newMap(&map);

	return 1;
}
