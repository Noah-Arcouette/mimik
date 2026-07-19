#include "../_zio.h"
#include <sys/stat.h>

int
_zio_stat_none (zFILE *restrict fp, struct stat *restrict statbuf)
{
	switch (fp->backing)
	{
	case _ZFILE_BACKING_FD:
		return fstat(fp->fd, statbuf);
	}
}
