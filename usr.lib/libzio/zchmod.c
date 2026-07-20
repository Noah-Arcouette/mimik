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
		errno = ENOTSUP;
		zunlockfile(fp);
		return -1;
	}

	if (fp->formatImpl.chmod(fp, mode))
	{
		zunlockfile(fp);
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
