#include "_zio.h"
#include <errno.h>

int
zerror (zFILE *fp)
{
	if (!fp) return 0;

	int error = errno;

	zlockfile(fp);
	int val = fp->error;
	zunlockfile(fp);

	errno = error;
	return val;
}
