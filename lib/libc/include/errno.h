#ifndef __LIB_C_ERRNO_H__
#define __LIB_C_ERRNO_H__
extern int errno;
#define EFAULT        2
#define EINVAL        3
#define ENOMEM        4
#define ENFILE        5
#define ENOENT        6
#define ERANGE        7
#define EPERM         8
#define EACCES        9
#define EDQUOT       10
#define EEXIST       11
#define EIO          12
#define EMLINK       13
#define ENAMETOOLONG 14
#define ENOSPC       15
#define ENOTDIR      16
#define EROFS        17
#define EXDEV        18
#define ENOSYS       19
#define EUNKNOWN     20
#define EBUSY        21
#define ELOOP        22
#define EISDIR       23
#define EBADF        24
#define ENXIO        25
#define EOVERFLOW    ERANGE
#define ESPIPE       26
#define EINTR        27
#define EPIPE        28
#define EFBIG        29
#define EDESTADDRREQ 30
#define EAGAIN       31
#define ENOBUFS      32
#define ECONNRESET   33
#define EBADMSG      34
#endif
