#include "../_zio.h"
#include <sys/stat.h>

int
_zio_utimens_fd (zFILE *fp, struct timespec t[2])
{
	return futimens(fp->fd.fd, t);
}
