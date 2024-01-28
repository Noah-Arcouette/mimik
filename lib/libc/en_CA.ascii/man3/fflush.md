# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

fflush - Flush the contents of a stream buffer, part of libc


# Synopsis

```C
#include <stdio.h>

int fflush (FILE *stream);
```


# Description

*fflush* shall flush the contents of *stream*. If the buffer is in writing mode the contents shall be written to the associated file descriptor. If the buffer is in reading mode the contents shall be discarded and the seek value set to the end of the file descriptor. If *stream* is NULL then *fflush* shall flush the buffers for all streams in use.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*fflush* shall set errno and return negative one on error.

## EINVAL

*stream* is currently not in use.

## Others

Refer to [pwrite](pwrite.3).


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
