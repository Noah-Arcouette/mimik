#include "_zio.h"
#include <errno.h>

int
zutimens (zFILE *fp, struct timespec t[2])
{
	if (!fp)
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	if (!fp->formatImpl.utimens)
	{
		zunlockfile(fp);
		errno = ENOTSUP;
		return -1;
	}

	if (fp->formatImpl.utimens(fp, t))
	{
		int error = errno;
		zunlockfile(fp);
		errno = error;
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
