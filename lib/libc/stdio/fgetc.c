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

    // implementing line-buffering has no benefit for reading

    // full buffering
    if (stream->flags & _FILE_FLAG_BUFFERED)
    {
        if (!stream->buffuse)
        {
            // fill buffer
            ssize_t amountRead = read(stream->fildes, stream->buff, stream->buffsz);
            if (amountRead < 0)
            {
                stream->flags |= _FILE_FLAG_ERROR;
                return EOF;
            }
            
            if (!amountRead) // zero is returned on EOF
            {
                stream->flags |= _FILE_FLAG_EOF;
                // buffuse is already zero
                return EOF;
            }
            stream->buffuse = (size_t)amountRead; // partial reads will not crash fgetc
        }

        // return next item
        return (int)stream->buff[--stream->buffuse];
    }

    // no buffering
    int ret;
    switch (read(stream->fildes, &ret, 1))
    {
        case 1:
            return ret;
        case 0:
            stream->flags |= _FILE_FLAG_EOF;
            return EOF;
        default:
            stream->flags |= _FILE_FLAG_ERROR; // could also be EOF
            return EOF;
    }
}
