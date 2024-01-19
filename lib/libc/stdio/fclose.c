#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int
fclose (FILE *stream)
{
#ifdef RESILIENT
    if (!stream)
    {
        errno = EFAULT;
        return EOF;
    }
#endif

    if (!(stream->flags & _FILE_FLAG_IN_USE) )
    {
        errno = EINVAL;
        return EOF;
    }

    int ret    = fflush(stream);
    int reterr = errno;

    if ((stream->flags & _FILE_FLAG_BUFFERED) && 
       !(stream->flags & _FILE_FLAG_BUFF_SET))
    {
        free(stream->buff);
    }

    if (stream->flags & _FILE_FLAG_FILDES)
    {
        lseek(stream->fildes, 0, SEEK_END);
        close(stream->fildes);
    }
    
    stream->flags = 0;

    errno = reterr;
    return ret;
}
