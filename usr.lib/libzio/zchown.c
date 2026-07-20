#include "_zio.h"
#include <errno.h>

int
zchown (zFILE *fp, uid_t user, gid_t group)
{
	if (!fp)
	{
		errno = EINVAL;
		return -1;
	}

	zlockfile(fp);

	if (!fp->formatImpl.chown)
	{
		errno = ENOTSUP;
		zunlockfile(fp);
		return -1;
	}

	if (fp->formatImpl.chown(fp, user, group))
	{
		zunlockfile(fp);
		return -1;
	}
	zunlockfile(fp);
	return 0;
}
