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
parse_sectionCopy (const char *sym)
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
	lex();

	// create section
	struct MiO m;
	m.magic = htole32(MIO_MAGIC);
	m.size = 0;

	m.flags = 0;
	if (map.flags & MIO_MAP_FLAG_VIRTUAL) m.flags = MIO_FLAG_VIRTUAL;

	memset(m.name, 0, sizeof(m.name));
	strncpy((char *)m.name, sym, sizeof(m.name));

	long _currentSection = outputsz;
	emit(&m, sizeof(m));
	currentSection = _currentSection;

	while (ltoken.type != LTYPE_CLOSE_CURLY &&
		   ltoken.type != LTYPE_EOF)
	{
		// BYTE(expr) SHORT(expr) LONG(expr) QUAD(expr)
		// file(section...)
		lex();
	}

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

	return 1;
}
