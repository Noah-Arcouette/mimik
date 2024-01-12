# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

setvbuf - Set stream buffering, part of libc


# Synopsis

```C
#include <stdio.h>

int setvbuf (FILE *restrict stream, char *restrict buf, int type, size_t size);
```


# Description

*setvbuf* shall the *stream*'s buffer to *buf*, if it is not NULL. *setvbuf* shall set the size of the stream's buffer to *size*. The buffering type shall be set to *type*, as follows:

 - _IOFBF - Fully-buffered
 - _IOLBF - Line-buffered
 - _IONBF - Non-buffered

*setvbuf* shall return zero on success, and negative one on error.

# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*setvbuf* shall set errno and return negative one on error.

## EINVAL

*stream* or *type* is invalid.

## ENOMEM

No enough memory for buffering option, or memory allocated has failed.


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

[setbuf](setbuf.3) - Short hand for setting buffering
