#ifndef __LIB_C_SYSCALL_H__
#define __LIB_C_SYSCALL_H__
#ifndef LINUX_X64_ONLY
#   warning "Use of syscall.h is inherently un-portable, please seek another method or define LINUX_X64_ONLY around syscall.h"
#endif
#define SYS_EXIT   0x3c
#define SYS_LINK   0x56
#define SYS_UNLINK 0x57
#define SYS_LSEEK  0x08

long __syscall1 (long nr, long r0);
long __syscall2 (long nr, long r0, long r1);
long __syscall3 (long nr, long r0, long r1, long r2);

#endif
