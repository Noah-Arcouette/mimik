#include "_zio.h"

int
zeof (zFILE *fp)
{
	if (!fp) return 0;
	return (fp->flags & _ZFILE_FLAGS_EOF);
}
