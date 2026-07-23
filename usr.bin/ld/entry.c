#include "main.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <stdio.h>
#include <mio.h>

static struct MiO_Entry entry;

void
setEntry (const char *name)
{
	if (strlen(name) > 256)
	{
		fprintf(stderr, gettext("%s: Entry name `%s' larger than allowed\n"),
			self, name);
		errors++;
		return;
	}
	strncpy((char *)entry.entry, name, 256);
}

void
emitEntrySection (void)
{
	struct MiO s;
	s.magic = htole32(MIO_MAGIC);
	s.flags = 0;
	strncpy((char *)s.name, (char *)MIO_SPECIAL_MIO_ENTRY, sizeof(s.name));
	s.size = htole64(sizeof(entry));

	emit(&s, sizeof(s));
	emit(&entry, sizeof(entry));
}
