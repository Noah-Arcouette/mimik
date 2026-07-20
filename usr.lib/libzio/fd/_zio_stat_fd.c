#include "../_zio.h"
#include <sys/stat.h>

int
_zio_stat_fd (zFILE *restrict fp, struct stat *restrict statbuf)
{
	return fstat(fp->fd.fd, statbuf);
}
