# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

setbuf - Shorthand set stream buffering, part of libc


# Synopsis

```C
#include <stdio.h>

void setbuf (FILE *restrict stream, char *restrict buf);
```


# Description

*setbuf* shall the *stream*'s buffer to *buf*, if it is not NULL. *setbuf* shall set the size of the stream's buffer to `BUFSIZ`. The buffering type shall be fully-buffered if *buf* is non-NULL, and non-buffered if *buf* is NULL.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

The value of errno is un-specified.


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

[setvbuf](setvbuf.3) - Set buffering options
