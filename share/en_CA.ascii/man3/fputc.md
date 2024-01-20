# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

fputc - Write character to stream, part of libc


# Synopsis

```C
#include <stdio.h>

int fputc (int c, FILE *stream);
```


# Description

*fputc* shall write *c*, interpreted as an **unsigned char**, to *stream*. *fputc* shall return *c* on success, and EOF on error. *fputc* shall flush the buffer, by means of [fflush](fflush.3), if it was in use for reading.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*fputc* shall set errno and return EOF.

## EFAULT, *Resilient Build Only*

*stream* is NULL.

## Others

Refer to [fflush](fflush.3).


# Extended Description

*fputc* shall write to the stream's buffer, and shall flush if needed.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[fputs](fputs.3) - Write string to stream
