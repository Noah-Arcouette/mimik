#include "../_zio.h"
#include <unistd.h>
#include <string.h>

size_t
_zio_write_none (zFILE *restrict fp, const void *restrict buf, size_t size)
{
	size_t amountWritten = 0;

	while (1)
	{
		size_t amountLeft = fp->bufcp-fp->bufsz;
		if (size > amountLeft)
		{
			memcpy(fp->buf+fp->bufsz, buf, amountLeft);

			// reset
			fp->bufsz = 0;
			size -= amountLeft;
			buf  += amountLeft;

			// write it
			switch (fp->backing)
			{
			case _ZFILE_BACKING_FD:
				if (write(fp->fd, fp->buf, fp->bufcp) == -1)
				{
					return amountWritten;
				}
				amountWritten += fp->bufcp;
				break;
			}
		}
		else
		{
			memcpy(fp->buf+fp->bufsz, buf, size);
			fp->bufsz = size;
			return amountWritten+size;
		}
	}
}
