#include "../_zio.h"
#include <sys/stat.h>

int
_zio_utimens_none (zFILE *fp, struct timespec t[2])
{
	switch (fp->backing)
	{
	case _ZFILE_BACKING_FD:
		return futimens(fp->fd, t);
	}
}
