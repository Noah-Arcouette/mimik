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

	zlockfile(fp);

	if (!fp->formatImpl.chmod)
	{
		zunlockfile(fp);
		errno = ENOTSUP;
		return -1;
	}

	if (fp->formatImpl.chmod(fp, mode))
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
