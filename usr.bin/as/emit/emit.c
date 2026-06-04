#include "../emit.h"
#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char *emitbuf = NULL;
long  emitsz  = 0;

static long _emitcp = 0;

long
emitRaw (const void *buf, long sz)
{
	emitsz += sz;
	if (emitsz > _emitcp)
	{
		_emitcp = (3*emitsz)/2;

		void *buf = realloc(emitbuf, _emitcp);
		if (!buf)
		{
			// return the values to a known state
			emitsz -= sz;
			_emitcp = emitsz;

			int error = errno;
			fprintf(stderr, gettext("%s: Failed to allocate memory, %s\n"),
				self, strerror(error));
			errors++;
			return -1;
		}

		emitbuf = buf;
	}

	char *start = &emitbuf[emitsz-sz];
	memcpy(start, buf, sz);

	return emitsz-sz;
}

void
freeEmit (void)
{
	free(emitbuf);
	emitbuf = NULL;
	emitsz  = 0;
	_emitcp = 0;
}
