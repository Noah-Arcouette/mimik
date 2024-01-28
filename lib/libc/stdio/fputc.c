#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int 
fputc (int c, FILE *stream)
{
#ifdef RESILIENT
	if (!stream)
	{
		errno = EFAULT;
		return EOF;
	}
#endif

	if (stream->flags & _FILE_FLAG_LAST_READ)
	{
		if (fflush(stream) == EOF)
		{
			return EOF;
		}
	}

	stream->flags |= _FILE_FLAG_LAST_WRITE;

	if (stream->flags & _FILE_FLAG_BUFFERED)
	{
		stream->buff[stream->buffuse++] = (unsigned char)c;

		if (
			((stream->flags & _FILE_FLAG_LINE_BUFFERED) && (c == '\n')) ||
			(stream->buffuse >= stream->buffsz)
		)
		{
			if (fflush(stream) == EOF)
			{
				return EOF;
			}
		}
	}
	else // not buffered
	{
		if (write(stream->fildes, &c, 1) < 0) // write one character
		{
			stream->flags |= _FILE_FLAG_ERROR;
			return EOF;
		}
	}

	return c;
}
