#include "_zio.h"
#include <errno.h>

size_t
zwrite (const void *restrict buf, size_t size, size_t n, zFILE *restrict fp)
{
	if (!fp)
	{
		errno = EINVAL;
		return 0;
	}

	if (size == 0 || n == 0) return 0;

	zlockfile(fp);
	if (!buf)
	{
		fp->flags |= _ZFILE_FLAGS_ERROR;
		errno = EINVAL;
		zunlockfile(fp);
		return 0;
	}

	if (!fp->write)
	{
		fp->flags |= _ZFILE_FLAGS_ERROR;
		errno = ENOTSUP;
		zunlockfile(fp);
		return 0;
	}

	if (!(fp->flags & _ZFILE_FLAGS_WRITABLE))
	{
		fp->flags |= _ZFILE_FLAGS_ERROR;
		errno = ENOTSUP;
		zunlockfile(fp);
		return 0;
	}

	size_t amt = fp->write(fp, buf, size*n)/size;

	zunlockfile(fp);
	return amt;
}
