#include "../_zio.h"
#include <unistd.h>

size_t
_zio_read_none (zFILE *restrict fp, void *restrict buf, size_t size)
{
	switch (fp->backing)
	{
	case _ZFILE_BACKING_FD:
		return read(fp->fd, buf, size);
	}
}
