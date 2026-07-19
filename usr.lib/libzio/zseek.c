#include "_zio.h"
#include <limits.h>
#include <errno.h>

int
zseek (zFILE *fp, long offset, int whence)
{
	return zseeko(fp, (off_t)offset, whence);
}
