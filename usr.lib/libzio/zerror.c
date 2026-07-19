#include "_zio.h"

int
zerror (zFILE *fp)
{
	if (!fp) return 0;
	return (fp->flags & _ZFILE_FLAGS_ERROR);
}
