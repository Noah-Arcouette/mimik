#include "_zio.h"
#include <errno.h>

void
zclearerr (zFILE *fp)
{
	if (!fp) return;

	int error = errno;
	zlockfile(fp);

	// unset the flags
	fp->eof   = 0;
	fp->error = 0;

	zunlockfile(fp);
	errno = error;
}
