# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

fgetc - Read character from stream, part of libc


# Synopsis

```C
#include <stdio.h>

int fgetc (FILE *stream);
```


# Description

*fgetc* shall read one character from *stream* and return it as an `int`. *fgetc* shall return EOF on error. *fgetc* shall flush the buffer, by means of [fflush](fflush.3), if it was in use for writing; which inturn seeks to EOF, user must seek between interleaved *fgetc* and *fputc* operations.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*fgetc* shall set errno and return EOF.

## EFAULT, *Resilient Build Only*

*stream* is NULL.

## EOVERFLOW

*stream* is at EOF.

## Others

Refer to [fflush](fflush.3) and [pread](pread.3).


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

[fgets](fgets.3) - Read buffer from stream
