#include "../_zio.h"
#include <sys/stat.h>

int
_zio_chmod_fd (zFILE *fp, mode_t mode)
{
	return fchmod(fp->fd.fd, mode);
}
