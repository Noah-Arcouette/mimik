#include "../_zio.h"
#include <errno.h>

int
_zio_utimens_none (zFILE *fp, struct timespec t[2])
{
	if (fp->backingImpl.utimens)
	{
		return fp->backingImpl.utimens(fp, t);
	}
	errno = ENOTSUP;
	return -1;
}
