#include "../_zio.h"
#include <unistd.h>
#include <stdlib.h>

int
_zio_close_fd (zFILE *fp)
{
	free(fp->fd.buf);
	close(fp->fd.fd);
	return 0;
}
