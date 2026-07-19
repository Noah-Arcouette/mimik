#include "_zio.h"
#include <errno.h>

int
zchmod (zFILE *fp, mode_t mode)
{
	if (!fp)
	{
		errno = EINVAL;
		return -1;
	}

	// can it?
	if (!fp->chmod)
	{
		errno = ENOTSUP;
		return -1;
	}

	zlockfile(fp);
	int resp = fp->chmod(fp, mode);
	zunlockfile(fp);

	return resp;
}
