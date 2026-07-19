#include "_zio.h"
#include <errno.h>

void
zclearerr (zFILE *fp)
{
	if (!fp) return;

	int error = errno;
	zlockfile(fp);

	// unset the flags
	fp->flags &= ~(_ZFILE_FLAGS_EOF | _ZFILE_FLAGS_ERROR);

	zunlockfile(fp);
	errno = error;
}
