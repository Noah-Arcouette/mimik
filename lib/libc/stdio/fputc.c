#include "stdio.h"
#include <errno.h>

int 
fputc (int c, FILE *stream)
{
#ifdef RESILIENT
    if (!stream)
    {
        errno = EINVAL;
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

    stream->buff[stream->buffuse++] = (unsigned char)c;
    if (stream->buffuse >= stream->buffsz)
    {
        if (fflush(stream) == EOF)
        {
            return EOF;
        }
    }
    return c;
}
