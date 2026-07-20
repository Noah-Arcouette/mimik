#include "../_zio.h"
#include <unistd.h>
#include <string.h>

size_t
_zio_write_fd (zFILE *restrict fp, const void *restrict buf, size_t amt)
{
	char   *inbuf = fp->fd.buf;
	size_t *bufsz = &fp->fd.bufsz;
	const ssize_t bufcp = fp->fd.bufcp;

	size_t amountWritten = 0;

	while (1)
	{
		size_t amountLeft = bufcp-*bufsz; // amount left to fill in buffer
		if (amt >= amountLeft)
		{
			// save it
			memcpy(inbuf+*bufsz, buf, amountLeft);
			*bufsz = 0;

			// dump it all
			if (write(fp->fd.fd, inbuf, bufcp) < bufcp)
			{
				return amountWritten;
			}
			amountWritten += bufcp;
			buf += amountLeft;
			amt -= amountLeft;
			continue;
		}
		// else
		memcpy(inbuf+*bufsz, buf, amt);
		*bufsz += amt;
		return amountWritten+amt;
	}
}
