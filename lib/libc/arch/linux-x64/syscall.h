#ifndef __LIB_C_SYSCALL_H__
#define __LIB_C_SYSCALL_H__

long __syscall1 (long nr, long r0);
long __syscall2 (long nr, long r0, long r1);
long __syscall3 (long nr, long r0, long r1, long r2);

#endif
