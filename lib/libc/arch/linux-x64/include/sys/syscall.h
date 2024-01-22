#ifndef __LIB_C_SYSCALL_H__
#define __LIB_C_SYSCALL_H__
#ifndef LINUX_X64_ONLY
#   warning "Use of syscall.h is inherently un-portable, please seek another method or define LINUX_X64_ONLY around syscall.h"
#endif
#include <errno.h>
#define SYS_EXIT   0x3c
#define SYS_LINK   0x56
#define SYS_UNLINK 0x57
#define SYS_LSEEK  0x08
#define SYS_CLOSE  0x03
#define SYS_WRITE  0x01

long __syscall1 (long nr, long r0);
long __syscall2 (long nr, long r0, long r1);
long __syscall3 (long nr, long r0, long r1, long r2);

#define SYS_EPERM         -1
#define SYS_ENOENT        -2
#define SYS_EACCES       -13
#define SYS_EDQUOT      -122
#define SYS_EEXIST       -17
#define SYS_EFAULT       -14
#define SYS_EIO           -5
#define SYS_EMLINK       -31
#define SYS_ENAMETOOLONG -36
#define SYS_ENOMEM       -12
#define SYS_ENOSPC       -28
#define SYS_ENOTDIR      -20
#define SYS_EROFS        -30
#define SYS_EXDEV        -18
#define SYS_ELOOP        -40
#define SYS_EISDIR       -21
#define SYS_EBUSY        -16
#define SYS_EBADF         -9
#define SYS_EINVAL       -22
#define SYS_ENXIO         -6
#define SYS_EOVERFLOW    -75
#define SYS_ESPIPE       -29
#define SYS_EINTR         -4
#define SYS_EPIPE        -32
#define SYS_EFBIG        -27
#define SYS_EWOULDBLOCK  SYS_EAGAIN
#define SYS_EDESTADDRREQ -89
#define SYS_EAGAIN       -11

int
__errnoConvert (int error);
#endif
