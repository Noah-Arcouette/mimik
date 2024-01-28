#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int 
setvbuf (FILE *restrict stream, char *restrict buf, int type, size_t size)
{
#ifdef RESILIENT
    if (!stream)
    {
        errno = EFAULT;
        return -1;
    }
#endif

    if (!(stream->flags & _FILE_FLAG_IN_USE))
    {
        errno = EINVAL;
        return -1;
    }

    if (buf)
    {
        // remove old buffer
        fflush(stream);
        free(stream->buff);

        // don't deallocate on close
        stream->flags |= _FILE_FLAG_BUFF_SET;
        
        // add new buffer
        stream->buffsz = size;
        stream->buff   = buf;
    }
    else if (stream->buffsz != size)
    {
        // remove old buffer
        fflush(stream);
        free(stream->buff);

        if (size)
        {
            // add new buffer
            stream->buff   = (char *)malloc(sizeof(char) * size);
            stream->buffsz = size;

            if (!stream->buff)
            {
                errno = ENOMEM;
                return -1;
            }
        }
    }

    switch (type)
    {
    case _IOFBF:
        if (!stream->buff)
        {
            errno = ENOMEM;
            return -1;
        }

        stream->flags &= ~_FILE_FLAG_LINE_BUFFERED;
        stream->flags |= _FILE_FLAG_BUFFERED;
        break;
    case _IOLBF:
        if (!stream->buff)
        {
            errno = ENOMEM;
            return -1;
        }
  
        stream->flags |= _FILE_FLAG_LINE_BUFFERED | _FILE_FLAG_BUFFERED;
        break;
    case _IONBF:
        if (stream->buff)
        {
            // remove buffer
            fflush(stream);
            free(stream->buff);
        }

        stream->flags &= ~(_FILE_FLAG_BUFFERED | _FILE_FLAG_LINE_BUFFERED);   
        break;
    default:
        stream->flags |= _FILE_FLAG_ERROR;
        errno = EINVAL;
        return -1;
    }

    return 0;
}

void
setbuf (FILE *restrict stream, char *restrict buf)
{
    if (buf)
    {
        setvbuf(stream, buf, _IOFBF, BUFSIZ);
        return;
    }

    setvbuf(stream, buf, _IONBF, 0);
}
