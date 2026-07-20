#include "../_zio.h"
#include <errno.h>

int
_zio_chmod_none (zFILE *fp, mode_t mode)
{
	if (fp->backingImpl.chmod)
	{
		return fp->backingImpl.chmod(fp, mode);
	}
	errno = ENOTSUP;
	return -1;
}
