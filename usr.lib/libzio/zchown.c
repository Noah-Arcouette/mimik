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

	// can it?
	if (!fp->chown)
	{
		errno = ENOTSUP;
		return -1;
	}

	zlockfile(fp);
	int resp = fp->chown(fp, user, group);
	zunlockfile(fp);

	return resp;
}
