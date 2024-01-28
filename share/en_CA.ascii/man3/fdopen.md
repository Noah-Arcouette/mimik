# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

fdopen - Attach file descriptor to a stream, part of libc


# Synopsis

```C
#include <stdio.h>

FILE *fdopen (int fildes, const char *mode);
```


# Description

*fdopen* shall attach file descriptor *fildes* to a fully-buffered stream. Each character in the *mode* field shall be used as such:

 - `r` - Open for reading
 - `w` - Open for writing
 - `a` - Open for appending, at EOF
 - `+` - Open for reading and writing
 - `b` - Ignored, for compatibility
 - `t` - Open temporarily

*fdopen* shall fail is the underlying file descriptor cannot be open for these permissions. The EOF and ERROR flags on the stream shall be cleared. The function shall return `(FILE *)NULL` on error, or a new valid stream.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*fdopen* shall set *errno* and return `(FILE *)NULL` on error.

## EINVAL

The *mode* value(s) are invalid.

## ENOMEM

No enough memory for internal stream buffer.

## ENFILE

Maximum streams open, FOPEN_MAX.

## Others

Refer to [lseek](lseek.3) and [fcntl](fcntl.3).


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

[fopen](fopen.3) - Open a new file as a stream

[open](open.3) - Open a new file descriptor
