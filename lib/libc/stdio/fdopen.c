#include "stdio.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

FILE *
fdopen (int fildes, const char *mode)
{
    if (!mode)
    {
        errno = EINVAL;
        return (FILE *)NULL;
    }

    short flags = _FILE_FLAG_IN_USE | _FILE_FLAG_FILDES | _FILE_FLAG_BUFFERED;
    off_t seek = 0;

    while (*mode)
    {
        switch (*mode)
        {
        case 'r':
            flags |= _FILE_FLAG_OP_READ;
            break;
        case 'w':
            flags |= _FILE_FLAG_OP_WRITE;
            break;
        case '+':
            flags |= _FILE_FLAG_OP_WRITE | _FILE_FLAG_OP_READ;
            break;
        case 'a':
            seek = lseek(fildes, 0, SEEK_END);
            if (seek < 0)
            {
                return (FILE *)NULL;
            }
            flags |= _FILE_FLAG_OP_APPEND | _FILE_FLAG_OP_WRITE;
            break;
        case 't':
            flags |= _FILE_FLAG_TEMPORARY;
            break;
        case 'b':
            break;
        default:
            errno = EINVAL;
            return (FILE *)NULL;
        }

        mode++;
    }

    if ((flags & _FILE_FLAG_OP_READ) && (flags & _FILE_FLAG_OP_WRITE))
    {
        if (fcntl(fildes, F_SETFL, O_RDWR) < 0)
        {
            return (FILE *)NULL;
        }
    }
    else if (flags & _FILE_FLAG_OP_READ)
    {
        if (fcntl(fildes, F_SETFL, O_RDONLY) < 0)
        {
            return (FILE *)NULL;
        }
    }
    else if (flags & _FILE_FLAG_OP_WRITE)
    {
        if (fcntl(fildes, F_SETFL, O_WRONLY) < 0)
        {
            return (FILE *)NULL;
        }
    }
    else
    {
        errno = EINVAL;
        return (FILE *)NULL;
    }

    for (size_t i = 0; i<FOPEN_MAX; i++)
    {
        if (!(__stdio_files[i].flags & _FILE_FLAG_IN_USE))
        {
            // open file
            __stdio_files[i].flags  = flags;
            __stdio_files[i].fildes = fildes;
            __stdio_files[i].seek   = seek;

            __stdio_files[i].buffsz  = BUFSIZ;
            __stdio_files[i].buffuse = 0;
            __stdio_files[i].buff    = (char*)malloc(sizeof(char) * BUFSIZ);

            if (__stdio_files[i].buff)
            {
                // remove entry
                __stdio_files[i].flags = 0;

                errno = ENOMEM;
                return (FILE *)NULL;
            }
            return &__stdio_files[i];
        }
    }

    errno = EMFILE;
    return (FILE *)NULL;
}
