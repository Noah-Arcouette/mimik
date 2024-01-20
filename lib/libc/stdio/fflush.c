#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int
fflush (FILE *stream)
{
    if (!stream)
    {
        for (size_t i = 0; i<FOPEN_MAX; i++)
        {
            if (__stdio_files[i].flags & _FILE_FLAG_IN_USE)
            {
                if (fflush(&__stdio_files[i]))
                {
                    return EOF;
                }
            }
        }
        return 0;
    }

    if (!(stream->flags & _FILE_FLAG_IN_USE))
    {
        errno = EINVAL;
        stream->flags |= _FILE_FLAG_ERROR;
        return EOF;
    }

    // flush read buffer
    if (stream->flags & _FILE_FLAG_LAST_READ)
    {
        if (stream->flags & _FILE_FLAG_FILDES)
        {
            if (lseek(stream->fildes, 0, SEEK_END) >= 0)
            {
                stream->flags |= _FILE_FLAG_EOF;
            }
        }

        stream->buffuse = 0;
        stream->flags  &= ~_FILE_FLAG_LAST_READ;
        return 0;
    }

    // flush write buffer
    if (stream->flags & _FILE_FLAG_LAST_WRITE)
    {
        if (!(stream->flags & _FILE_FLAG_FILDES))
        {
            return 0;
        }

        if (stream->flags & _FILE_FLAG_BUFFERED)
        {
            if (write(stream->fildes, stream->buff, stream->buffuse) != (ssize_t)stream->buffuse)
            {
                stream->flags |= _FILE_FLAG_ERROR;
                return EOF;
            }

            stream->buffuse = 0;
        }

        stream->flags  &= ~_FILE_FLAG_LAST_WRITE;
        return 0;
    }

    // nothing to flush
    return 0;
}
