#include "_zio.h"

int
zerror (zFILE *fp)
{
	return (fp->flags & _ZFILE_FLAGS_ERROR);
}
