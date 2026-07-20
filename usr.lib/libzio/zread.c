#include "_zio.h"
#include <errno.h>

size_t
zread (void *restrict buf, size_t size, size_t n, zFILE *restrict fp)
{
	if (!fp || !buf)
	{
		errno = EINVAL;
		return 0;
	}

	zlockfile(fp);

	if (!fp->formatImpl.read || !fp->readable)
	{
		fp->error = 1;
		zunlockfile(fp);
		errno = ENOTSUP;
		return 0;
	}

	if (fp->rw == _ZFILE_RW_WRITING)
	{
		if (fp->formatImpl.flush)
		{
			if (fp->formatImpl.flush(fp)) // failed to flush
			{
				int error = errno;
				zunlockfile(fp);
				errno = error;
				return 0;
			}
		}
		// flush was good
		fp->rw = _ZFILE_RW_READING;
	}

	size_t amount = fp->formatImpl.read(fp, buf, size*n)/size;
	int error = errno;
	zunlockfile(fp);
	errno = error;
	return amount;
}
