#include "main.h"
#include <libintl.h>
#include <string.h>
#include <stdio.h>
#include <mio.h>

struct MiO_Entry entry;

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
