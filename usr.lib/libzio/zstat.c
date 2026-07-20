#include "_zio.h"
#include <errno.h>

int
zstat (zFILE *restrict fp, struct stat *restrict statbuf)
{
	if (!fp || !statbuf)
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	if (!fp->formatImpl.stat)
	{
		zunlockfile(fp);
		errno = ENOTSUP;
		return -1;
	}

	if (fp->formatImpl.stat(fp, statbuf))
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
