#include "parse.h"
#include "main.h"
#include "lex.h"
#include <libintl.h>
#include <fnmatch.h>
#include <endian.h>
#include <string.h>
#include <stdio.h>

static void
_dumpSectionCopy (struct inputFile *inpfile, struct MiO *inpsection,
	long offset, struct MiO_Map *map)
{
	int inpvirtual = inpsection->flags & MIO_FLAG_VIRTUAL;
	// run the check
	if (inpvirtual && !(map->flags & MIO_MAP_FLAG_VIRTUAL))
	{
		prettyprint(gettext(
"Cannot dump virtual section `%s:%.*s' into non-virtual map, \
did you forget `NOLOAD'?\n"),
			inpfile->path, 256, inpsection->name);
		errors++;
		return;
	}

	int maptls = map->flags & MIO_MAP_FLAG_THREAD_LOCAL;
	if (maptls > 0) maptls = 1;
	if (map->size == 0)
	{
		maptls = -1; // not set
	}

	// emit/reserve section (mark it)
	inpsection->name[0] = '\0';
	long sectionSize = le64toh(inpsection->size);

	long newSectionStart;

	if (inpvirtual)
	{
		newSectionStart = virtualsz;
		reserve(sectionSize);
	}
	else
	{
		newSectionStart = outputsz;
		char *dat = inpfile->data+offset+sizeof(struct MiO);
		emit(dat, sectionSize);
	}

	long sectionStart = offset+sizeof(struct MiO);
	long sectionEnd   = sectionStart+sectionSize;

	// copy symbols (mark them)
	for (long i = 0; i<inpfile->symbols; i++)
	{
		struct MiO_Symbol *inpsym = &inpfile->symbol[i];

		int symFlags = le16toh(inpsym->flags);

		// literals don't count
		if (symFlags & MIO_SYMBOL_FLAG_LITERAL) continue;

		// can't mix data and virtual
		if ((symFlags & MIO_SYMBOL_FLAG_VIRTUAL) != inpvirtual) continue;

		long symStart = le64toh(inpsym->value);

		// symbol is not in the section
		if (symStart < sectionStart || symStart > sectionEnd) continue;

		// relocate the symbol
		long symReloc = symStart-sectionStart+newSectionStart;

		// move the symbol over
		newSymbol(symReloc, le64toh(inpsym->size), symFlags,
			(char *)inpsym->name);

		// mark the symbol
		inpsym->name[0] = '\0';

		// set flags
		if (symFlags & MIO_SYMBOL_FLAG_EXECUTABLE)
		{
			map->flags |= MIO_MAP_FLAG_EXECUTABLE;
		}
		if (symFlags & MIO_SYMBOL_FLAG_READABLE)
		{
			map->flags |= MIO_MAP_FLAG_READABLE;
		}
		if (symFlags & MIO_SYMBOL_FLAG_WRITABLE)
		{
			map->flags |= MIO_MAP_FLAG_WRITABLE;
		}

		switch (maptls)
		{
		case 1:
			if (!(symFlags & MIO_SYMBOL_FLAG_THREAD_LOCAL))
			{
				prettyprint(gettext(
					"Refusing to move non-TLS `%s:%.*s' into TLS map\n"),
					inpfile->path, 256, inpsection->name);
				errors++;
			}
			break;
		case 0:
			if (symFlags & MIO_SYMBOL_FLAG_THREAD_LOCAL)
			{
				prettyprint(gettext(
					"Refusing to move TLS `%s:%.*s' into non-TLS map\n"),
					inpfile->path, 256, inpsection->name);
				errors++;
			}
			break;
		case -1:
			maptls = symFlags & MIO_SYMBOL_FLAG_THREAD_LOCAL;
			if (maptls)
			{
				map->flags |= MIO_MAP_FLAG_THREAD_LOCAL;
			}
			break;
		}
	}

	// copy gaps (mark them)
	if (inpvirtual) return;
	// else
	for (long i = 0; i<inpfile->gaps; i++)
	{
		struct MiO_Gap *inpgap = &inpfile->gap[i];

		long gapOffset = le64toh(inpgap->offset);

		// gap is not in the section
		if (gapOffset < sectionStart || gapOffset > sectionEnd) continue;

		// relocate the gap
		long gapReloc = gapOffset-sectionStart+newSectionStart;

		// move the gap over
		newGap(gapReloc, le16toh(inpgap->type), (char *)inpgap->symbol);

		// mark the gap
		inpgap->symbol[0] = '\0';
	}
}

void
dumpSection (const char *file, const char *section, struct MiO_Map *map)
{
	for (long i = 0; i<inputs; i++)
	{
		struct inputFile *inpfile = &input[i];
		if (!fnmatch(file, inpfile->path, 0))
		{
			long offset = 0;
			while (offset < inpfile->size)
			{
				struct MiO *inpsection = inpfile->data+offset;

				// make the section name terminated
				char name[257];
				strncpy(name, (char *)inpsection->name, 256);
				name[256] = '\0';

				if (
					name[0] == '.' && // don't copy special sections
					name[0] && // don't copy empty sections
					!fnmatch(section, name, 0))
				{
					_dumpSectionCopy(inpfile, inpsection, offset, map);
				}

				// goto next section
				if (inpsection->flags & MIO_FLAG_VIRTUAL)
				{
					offset += sizeof(struct MiO);
				}
				else
				{
					offset += le64toh(inpsection->size)+sizeof(struct MiO);
				}
			}
		}
	}
}
