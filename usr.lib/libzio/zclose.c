#include "_zio.h"
#include <stdlib.h>
#include <errno.h>

int
zclose (zFILE *fp)
{
	if (!fp)
	{
		errno = EINVAL;
		return 1;
	}

	zlockfile(fp);

	// flush data
	if (fp->formatImpl.flush) fp->formatImpl.flush(fp);
	if (fp->backingImpl.flush) fp->backingImpl.flush(fp);

	// seek to end
	if (fp->formatImpl.seek) fp->formatImpl.seek(fp, 0, SEEK_END);
	if (fp->backingImpl.seek) fp->backingImpl.seek(fp, 0, SEEK_END);

	// close
	if (fp->formatImpl.close) fp->formatImpl.close(fp);
	if (fp->backingImpl.close) fp->backingImpl.close(fp);

	// free
	free(fp);
	return 0;
}
