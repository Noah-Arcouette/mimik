#include "../_zio.h"
#include <unistd.h>

int
_zio_chown_fd (zFILE *fp, uid_t user, gid_t group)
{
	return fchown(fp->fd.fd, user, group);
}
