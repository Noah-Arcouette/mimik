#define LINUX_X64_ONLY
#   include <sys/syscall.h>
#undef LINUX_X64_ONLY

int
__errnoConvert (int error)
{
    switch (error)
    {
    case SYS_EPERM:
        return EPERM;
    case SYS_ENOENT:
        return ENOENT;
    case SYS_EACCES:
        return EACCES;
    case SYS_EDQUOT:
        return EDQUOT;
    case SYS_EEXIST:
        return EEXIST;
    case SYS_EFAULT:
        return EFAULT;
    case SYS_EIO:
        return EIO;
    case SYS_EMLINK:
        return EMLINK;
    case SYS_ENAMETOOLONG:
        return ENAMETOOLONG;
    case SYS_ENOMEM:
        return ENOMEM;
    case SYS_ENOSPC:
        return ENOSPC;
    case SYS_ENOTDIR:
        return ENOTDIR;
    case SYS_EROFS:
        return EROFS;
    case SYS_EXDEV:
        return EXDEV;
    case SYS_ELOOP:
        return ELOOP;
    case SYS_EISDIR:
        return EISDIR;
    case SYS_EBUSY:
        return EBUSY;
    case SYS_EBADF:
        return EBADF;
    case SYS_EINVAL:
        return EINVAL;
    case SYS_ENXIO:
        return ENXIO;
    case SYS_EOVERFLOW:
        return EOVERFLOW;
    case SYS_ESPIPE:
        return ESPIPE;
    case SYS_EINTR:
        return EINTR;
    case SYS_EAGAIN:
        return EAGAIN;
    case SYS_EDESTADDRREQ:
        return EDESTADDRREQ;
    case SYS_EFBIG:
        return EFBIG;
    case SYS_EPIPE:
        return EPIPE;
    default:
        return EUNKNOWN;
    }
}