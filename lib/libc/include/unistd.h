#ifndef __LIBC_UNISTD_H__
#define __LIBC_UNISTD_H__
#include <sys/types.h>

// lseek:whence
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

// arch/unlink.c
int unlink (const char *);

// arch/link.c
int link (const char *src, const char *dst);

// arch/lseek.c
off_t lseek (int fildes, off_t, int whence);

// arch/exit.c
void _exit (int status);

// arch/close.c
int close (int fildes);

// arch/write.c
ssize_t write (int fildes, const void *buf, size_t);

// arch/read.c
ssize_t read (int fildes, void *buf, size_t);

// unistd/pwrite.c
ssize_t pwrite (int fildes, const void *buf, size_t, off_t);

#endif
