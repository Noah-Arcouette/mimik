#include "../_zio.h"

int
_zio_setup_none (zFILE *fp)
{
	fp->read    = &_zio_read_none;
	fp->write   = &_zio_write_none;
	fp->seek    = &_zio_seek_none;
	fp->stat    = &_zio_stat_none;
	fp->chown   = &_zio_chown_none;
	fp->chmod   = &_zio_chmod_none;
	fp->utimens = &_zio_utimens_none;
	return 0;
}
