#ifndef __LIBC_UNISTD_H__
#define __LIBC_UNISTD_H__
#include <sys/types.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

// unistd/unlink.c
int unlink (const char *);

// unistd/link.c
int link (const char *src, const char *dst);

// null
off_t   lseek  (int, off_t, int);
int     close  (int);
ssize_t pwrite (int, const void *, size_t, off_t);

#endif
