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

	// can it?
	if (!fp->utimens)
	{
		errno = ENOTSUP;
		return -1;
	}

	zlockfile(fp);
	int resp = fp->utimens(fp, t);
	zunlockfile(fp);

	return resp;
}
