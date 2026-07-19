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

	// can it?
	if (!fp->stat)
	{
		errno = ENOTSUP;
		return -1;
	}

	zlockfile(fp);
	int resp = fp->stat(fp, statbuf);
	zunlockfile(fp);

	return resp;
}
