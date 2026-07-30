#include "parse.h"
#include "main.h"
#include "lex.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

long virtualsz = 0;

void
reserve (long amt)
{
	virtualsz += amt;

	if (currentSection >= 0 &&
		((long)(currentSection+sizeof(struct MiO)) <= outputsz))
	{
		struct MiO *s = &outputBuf[currentSection];
		uint64_t size = le64toh(s->size);
		size += amt;
		s->size = htole64(size);

		if (!(s->flags & MIO_FLAG_VIRTUAL))
		{
			prettyprint(gettext("Attempted to reserve in data section\n"));
			errors++;
		}
	}
}
