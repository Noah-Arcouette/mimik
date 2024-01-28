# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

puts - Write string to stdout, part of libc


# Synopsis

```C
#include <stdio.h>

int puts (const char *restrict s);
```


# Description

*puts* shall write string *s* to stdout, stopping at and not including the NULL terminator.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*puts* shall set errno and return EOF.

For errno refer to [fwrite](fwrite.3).


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

[fputs](fputs.3) - Write string to stream

[fputc](fputc.3) - Write character to stream
