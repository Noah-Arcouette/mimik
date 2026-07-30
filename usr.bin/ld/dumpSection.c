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

	// emit/reserve section (mark it)
	inpsection->name[0] = '\0';
	if (inpvirtual)
	{
		reserve(le64toh(inpsection->size));
	}
	else
	{
		char *dat = inpfile->data+offset+sizeof(struct MiO);
		emit(dat, le64toh(inpsection->size));
	}

	// copy symbols (mark them)
	// copy gaps (mark them)
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
