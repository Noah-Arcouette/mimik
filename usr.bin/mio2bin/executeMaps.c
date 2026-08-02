#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

static long outbufcp = 0;
long  outbufsz = 0;
char *outbuf   = NULL;

void
_fill (long pos)
{
	if (pos <= outbufsz) return;

	long oldsz = outbufsz;
	outbufsz = pos;
	if (outbufsz > outbufcp)
	{
		outbufcp = 3*outbufsz/2;
		void *newbuf = realloc(outbuf, outbufcp);
		if (!newbuf)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			outbufcp = 0;
			outbufsz = 0;
			errors++;
			return;
		}
		outbuf = newbuf;
		memset(outbuf+oldsz, 0, pos-oldsz);
	}
}

void
_write (char *dat, long amount, long pos)
{
	if (pos >= outbufsz) return;

	memcpy(outbuf+pos, dat, amount);
}

void
executeMaps (void)
{
	for (long i = 0; i<maps; i++)
	{
		struct MiO_Map *m = &map[i];

		if (m->flags & MIO_MAP_FLAG_VIRTUAL)
		{
			if (argFlags & LOAD_VIRTUAL)
			{
				_fill(le64toh(m->physical)+le64toh(m->size));
			}
		}
		else
		{
			long physical = le64toh(m->physical);
			_fill(physical+le64toh(m->size));
			_write(buf+le64toh(m->from), le64toh(m->amount), physical);
		}
	}

	void *newbuf = realloc(outbuf, outbufsz);
	if (newbuf) outbuf = newbuf; // we don't really care if it fails
}
