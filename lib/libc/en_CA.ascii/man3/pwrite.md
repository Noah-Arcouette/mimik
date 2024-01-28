# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

pwrite - Write data, at offset, to file descriptor, part of libc


# Synopsis

```C
#include <unistd.h>

ssize_t pwrite (int fildes, const void *buf, size_t size, off_t offset);
```


# Description

*pwrite* shall write *buf*, of size *size*, to file descriptor *fildes* at seek offset *offset* from the start of the file descriptor. *pwrite* shall return the amount of data written, or negative one on error.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*pwrite* shall set errno and return negative one.

For errno refer to [write](write.3) and [lseek](lseek.3).


# Extended Description

There is no extended description.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[pread](pread.3) - Read, at an offset, from a file descriptor

[write](write.3) - Write buffer to file descriptor

[lseek](lseek.3) - Seek a specific point in a file descriptor
