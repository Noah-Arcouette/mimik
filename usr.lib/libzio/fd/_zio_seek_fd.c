#include "../_zio.h"
#include <unistd.h>

off_t
_zio_seek_fd (zFILE *fp, off_t off, int whence)
{
	off_t resp = lseek(fp->fd.fd, off, whence);
	if (resp < 0)
	{
		fp->error = 1;
	}
	return resp;
}
