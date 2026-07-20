#include "_zio.h"

int
zseek (zFILE *fp, long offset, int whence)
{
	return zseeko(fp, (off_t)offset, whence);
}
