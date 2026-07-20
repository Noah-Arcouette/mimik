#include "_zio.h"
#include <errno.h>

int
zeof (zFILE *fp)
{
	if (!fp) return 0;

	int error = errno;

	zlockfile(fp);
	int val = fp->eof;
	zunlockfile(fp);

	errno = error;
	return val;
}
