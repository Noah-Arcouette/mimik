#include "../_zio.h"
#include <unistd.h>

int
_zio_chmod_none (zFILE *fp, mode_t mode)
{
	switch (fp->backing)
	{
	case _ZFILE_BACKING_FD:
		return fchmod(fp->fd, mode);
	}
}
