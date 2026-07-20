#include "../_zio.h"
#include <errno.h>

size_t
_zio_read_fd (zFILE *restrict fp, void *restrict buf, size_t amt)
{
	errno = ENOSYS;
	return 0;
}
