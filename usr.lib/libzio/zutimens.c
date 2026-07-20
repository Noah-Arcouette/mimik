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
		errno = ENOTSUP;
		zunlockfile(fp);
		return -1;
	}

	if (fp->formatImpl.utimens(fp, t))
	{
		zunlockfile(fp);
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
