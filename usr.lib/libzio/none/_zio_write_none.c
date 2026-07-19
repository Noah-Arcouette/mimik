#include "../_zio.h"
#include <unistd.h>

size_t
_zio_write_none (zFILE *restrict fp, const void *restrict buf, size_t size)
{
	switch (fp->backing)
	{
	case _ZFILE_BACKING_FD:
		return write(fp->fd, buf, size);
	}
}
