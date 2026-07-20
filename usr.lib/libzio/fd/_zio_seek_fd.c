#include "../_zio.h"
#include <unistd.h>

off_t
_zio_seek_fd (zFILE *fp, off_t off, int whence)
{
	return lseek(fp->fd.fd, off, whence);
}
