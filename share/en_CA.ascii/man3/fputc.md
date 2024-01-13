# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

fputc - Write string to stdout, part of libc


# Synopsis

```C
#include <stdio.h>

int fputc (int c, FILE *stream);
```


# Description

*fputc* shall write *c*, interpreted as an **unsigned char**, to *stream*. *fputc* shall return *c* on success, and EOF on error.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*fputc* shall set errno and return EOF.

## EINVAL

*stream* is invalid.

## ENOMEM

No enough memory for writing.

## EFBIG

Writing will exceed the file limit.

## ENOSPC

No space left of underlying device.

## EBADF

Underlying file descriptor is invalid.


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
