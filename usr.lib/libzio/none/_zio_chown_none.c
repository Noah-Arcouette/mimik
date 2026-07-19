#include "../_zio.h"
#include <unistd.h>

int
_zio_chown_none (zFILE *fp, uid_t user, gid_t group)
{
	switch (fp->backing)
	{
	case _ZFILE_BACKING_FD:
		return fchown(fp->fd, user, group);
	}
}
