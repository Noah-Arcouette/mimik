#include "_zio.h"
#include <errno.h>

size_t
zwrite (const void *restrict buf, size_t size, size_t n, zFILE *restrict fp)
{
	if (!fp || !buf)
	{
		errno = EINVAL;
		return 0;
	}

	zlockfile(fp);

	if (!fp->formatImpl.write || !fp->writable)
	{
		fp->error = 1;
		zunlockfile(fp);
		errno = ENOTSUP;
		return 0;
	}

	size_t amount = fp->formatImpl.write(fp, buf, size*n)/size;
	int error = errno;
	zunlockfile(fp);
	errno = error;
	return amount;
}
