#include <stdlib.h>
#include <string.h>
#include "defs.h"

void
freeSection (struct section *s)
{
	if (!s)
	{
		return;
	}

	// free data
	free(s->name);
	free(s->symbol);
	free(s->gap);
	free(s->data);

	// nulliy
	memset(s, 0, sizeof(struct section));
}

void
freeFile (struct inputfile *f)
{
	if (!f)
	{
		return;
	}

	// free data
	free(f->filename);
	free(f->section);
	free(f->data);

	// nullify
	memset(f, 0, sizeof(struct inputfile));
}

void
freeAll (void)
{
	// nothing to do for now
}
