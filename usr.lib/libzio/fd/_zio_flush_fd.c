#include "../_zio.h"
#include <unistd.h>

int
_zio_flush_fd (zFILE *fp)
{
	ssize_t bufsz = fp->fd.bufsz;
	fp->fd.bufof = 0;
	fp->fd.bufsz = 0;

	if (fp->rw == _ZFILE_RW_WRITING)
	{
		// write the end to the file
		if (write(fp->fd.fd, fp->fd.buf, bufsz) < bufsz)
		{
			fp->error = 1;
			return 1;
		}
	}
	return 0;
}
