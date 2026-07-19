#include "_zio.h"

void
zclearerr (zFILE *fp)
{
	if (!fp) return;

	// unset the flags
	fp->flags &= ~(_ZFILE_FLAGS_EOF | _ZFILE_FLAGS_ERROR);
}
