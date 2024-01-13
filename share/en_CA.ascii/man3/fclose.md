# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

fclose - Disassociate stream, part of libc


# Synopsis

```C
#include <stdio.h>

int fclose (FILE *stream);
```


# Description

*fclose* shall flush *stream*, disassociate the stream's buffer, unallocated any pre-allocated data, close any associated file descriptor, attempt to reach EOF, and free FILE for latter use. Zero shall be returned on success and EOF on failure. Any latter operations on *stream*, without a call to [fopen](fopen.3) or associated functions, will fail.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*fclose* shall set errno and return EOF.

Refer to [fflush](fflush.3) for errno information.


# Extended Description

Buffers set via [setbuf](setbuf.3) and [setvbuf](setvbuf.3) shall not be freed.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also
