# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

read - Read data from file descriptor, part of libc and the System


# Synopsis

```C
#include <unistd.h>

ssize_t write (int fildes, char *buf, size_t size);
```


# Description

*read* shall attempt to read *size* bytes from file descriptor *fildes* to buffer *buf*. *read* shall return the actual amount of bytes written, or negative one on error.

The data shall be read at the read-write head. The read-write head shall be incremented by the amount of bytes read.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

Negative one shall be return and errno set.

## EFAULT, *Resilient Builds Only*

*buf* is NULL.

## ERANGE

*size* is greater then the maximum return value, `SSIZE_MAX`.

## Others

Refer to [read](read.2).


# Extended Description

The *read* function is implemented by the system, not necessarily the C standard library.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[open](open.3) - Open a new file descriptor

[fread](fread.3) - Buffered file reading

[read](read.2) - System implementation details for *read*
