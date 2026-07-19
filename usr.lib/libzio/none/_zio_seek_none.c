#include "../_zio.h"
#include <unistd.h>

off_t
_zio_seek_none (zFILE *fp, off_t offset, int whence)
{
	switch (fp->backing)
	{
	case _ZFILE_BACKING_FD:
		return lseek(fp->fd, offset, whence);
	}
}
