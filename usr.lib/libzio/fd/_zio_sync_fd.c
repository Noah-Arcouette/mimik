#include "../_zio.h"
#include <unistd.h>

int
_zio_sync_fd (zFILE *fp)
{
	return fsync(fp->fd.fd);
}
