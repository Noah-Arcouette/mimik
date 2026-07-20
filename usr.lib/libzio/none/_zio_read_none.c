#include "../_zio.h"
#include <errno.h>

size_t
_zio_read_none (zFILE *restrict fp, void *restrict buf, size_t amt)
{
	if (fp->backingImpl.read)
	{
		return fp->backingImpl.read(fp, buf, amt);
	}
	errno = ENOTSUP;
	return -1;
}
