#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int
fgetc (FILE *stream)
{
#ifdef RESILIENT
    if (!stream)
    {
        errno = EFAULT;
        return EOF;
    }
#endif

    if (stream->flags & _FILE_FLAG_LAST_WRITE)
    {
        if (fflush(stream) == EOF)
        {
            return EOF;
        }
    }

    if (stream->flags & _FILE_FLAG_EOF)
    {
        errno = EOVERFLOW;
        return EOF;
    }

    stream->flags |= _FILE_FLAG_LAST_READ;
    if (!stream->buffuse)
    {
        // fill buffer
        ssize_t amountRead = read(stream->fildes, stream->buff, stream->buffsz);
        if (amountRead < 0)
        {
            stream->flags |= _FILE_FLAG_ERROR;
            return EOF;
        }
        
        if ((size_t)amountRead != stream->buffsz)
        {
            stream->flags |= _FILE_FLAG_EOF;
        }
        stream->buffuse = (size_t)amountRead;
    }

    // return next item
    return (int)stream->buff[--stream->buffuse];
}
