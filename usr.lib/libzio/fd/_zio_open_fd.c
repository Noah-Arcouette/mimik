#include "../_zio.h"
#include <stdlib.h>

int
_zio_open_fd (zFILE *fp)
{
	fp->fd.buf  = malloc(BUFSIZ);
	if (!fp->fd.buf) return 1;

	fp->fd.bufcp = BUFSIZ;
	fp->fd.bufsz = 0;
	fp->fd.bufof = 0;

	return 0;
}
