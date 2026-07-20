#include "../_zio.h"
#include <errno.h>

off_t
_zio_seek_none (zFILE *fp, off_t off, int whence)
{
	if (fp->backingImpl.seek)
	{
		return fp->backingImpl.seek(fp, off, whence);
	}
	errno = ENOTSUP;
	return -1;
}
