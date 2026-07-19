#include "_zio.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int
zclose (zFILE *fp)
{
	if (!fp)
	{
		errno = EINVAL;
		return EOF;
	}

	// lock
	zlockfile(fp);

	// flush (don't need unlocked because its our lock)
	while (zflush(fp) == EOF)
	{
		// continue blocking
		if (errno != EAGAIN && errno != EWOULDBLOCK) break;
	}

	// seek
	zseek(fp, 0, SEEK_END);

	// close backing
	switch (fp->backing)
	{
	case _ZFILE_BACKING_FD:
		close(fp->fd);
		break;
	}

	// free
	free(fp);
	return 0;
}
