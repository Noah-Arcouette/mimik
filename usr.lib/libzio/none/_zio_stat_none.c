#include "../_zio.h"
#include <errno.h>

int
_zio_stat_none (zFILE *restrict fp, struct stat *restrict statbuf)
{
	if (fp->backingImpl.stat)
	{
		return fp->backingImpl.stat(fp, statbuf);
	}
	errno = ENOTSUP;
	return -1;
}
