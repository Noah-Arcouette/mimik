#include "parse.h"
#include "main.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>
#include <stdio.h>
#include <errno.h>
#include <mio.h>

struct MiO_Symbol *outputSymbol   = NULL;
size_t             outputSymbolsz = 0;
size_t             outputSymbolcp = 0;

void
newSymbol (int64_t val, long size, int type, const char *name)
{
	// period
	if (!strcmp(name, "."))
	{
		period = val;
		return;
	}

	outputSymbolsz++;
	if (outputSymbolsz > outputSymbolcp)
	{
		outputSymbolcp = 3*outputSymbolsz/2;
		void *buf = realloc(outputSymbol, sizeof(struct MiO_Symbol)*
			outputSymbolcp);
		if (!buf)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			outputSymbolsz--;
			outputSymbolcp = outputSymbolsz;
			return;
		}
		outputSymbol = buf;
	}

	struct MiO_Symbol *s = &outputSymbol[outputSymbolsz-1];
	s->value = htole64(val);
	s->size  = htole64(size);
	s->flags = htole16(type);
	memset(s->name, 0, sizeof(s->name));
	strncpy((char *)s->name, name, sizeof(s->name));

	if (strlen(name) > sizeof(s->name))
	{
		fprintf(stderr, gettext("%s: Symbol name `%s' greater than allowed\n"),
			self, name);
		errors++;
	}
}
