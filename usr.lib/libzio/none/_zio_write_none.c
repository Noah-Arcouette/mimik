#include "../_zio.h"
#include <errno.h>

size_t
_zio_write_none (zFILE *restrict fp, const void *restrict buf, size_t amt)
{
	if (fp->backingImpl.write)
	{
		return fp->backingImpl.write(fp, buf, amt);
	}
	errno = ENOTSUP;
	return -1;
}
