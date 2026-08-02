#include "main.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdio.h>
#include <mio.h>

struct MiO_Symbol *symbol;
long               symbols = 0;

struct MiO_Gap *gap;
long            gaps = 0;

struct MiO_Map *map;
long            maps = 0;

void
getSections (void)
{
	long offset = 0;
	short mustBeThere;
	while (offset < bufsz)
	{
		struct MiO *section = (void *)&buf[offset];
		mustBeThere = 0;

		// mio.arch
		if (!strncmp((char *)section->name, (char *)MIO_SPECIAL_MIO_ARCH, 256))
		{
			// ignore it
		}
		// mio.entry
		else if (!strncmp((char *)section->name, (char *)MIO_SPECIAL_MIO_ENTRY,
			256))
		{
			// ignore it
		}
		// mio.symbols
		else if (!strncmp((char *)section->name,
			(char *)MIO_SPECIAL_MIO_SYMBOLS, 256))
		{
			symbol = (void *)&buf[offset+sizeof(struct MiO)];
			symbols = le64toh(section->size)/sizeof(struct MiO_Symbol);
		}
		// mio.gaps
		else if (!strncmp((char *)section->name, (char *)MIO_SPECIAL_MIO_GAPS,
			256))
		{
			gap = (void *)&buf[offset+sizeof(struct MiO)];
			gaps = le64toh(section->size)/sizeof(struct MiO_Gap);
		}
		// mio.maps
		else if (!strncmp((char *)section->name, (char *)MIO_SPECIAL_MIO_MAPS,
			256))
		{
			map = (void *)&buf[offset+sizeof(struct MiO)];
			maps = le64toh(section->size)/sizeof(struct MiO_Map);
		}
		// other specials
		else if (section->name[0] != '.')
		{
			fprintf(stderr, gettext("%s: Special section `%.*s' unhandled\n"),
				self, 256, section->name);
			errors++;
		}

		// move to next section
		if (section->flags & MIO_FLAG_VIRTUAL)
		{
			if (mustBeThere)
			{
				fprintf(stderr,
					gettext("%s: Refusing to use virtual section `%.*s'\n"),
					self, 256, section->name);
				errors++;
			}

			offset += sizeof(struct MiO);
		}
		else
		{
			offset += sizeof(struct MiO)+le64toh(section->size);
		}
	}

	if (!maps)
	{
		fprintf(stderr, gettext("%s: Input file is not loadable\n"), self);
		errors++;
	}
}
