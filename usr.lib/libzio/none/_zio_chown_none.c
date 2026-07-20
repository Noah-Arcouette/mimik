#include "../_zio.h"
#include <errno.h>

int
_zio_chown_none (zFILE *fp, uid_t user, gid_t group)
{
	if (fp->backingImpl.chown)
	{
		return fp->backingImpl.chown(fp, user, group);
	}
	errno = ENOTSUP;
	return -1;
}
