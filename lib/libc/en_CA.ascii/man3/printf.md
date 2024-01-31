# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

printf - Print formatted string, part of libc


# Synopsis

```C
#include <stdio.h>

int printf (const char *restrict fmt, ...);
```


# Description

*printf* shall print the formatted string to standard output, see *vfprintf* for *fmt* formatting. *printf* shall return the amount of characters printed.


# Environment Variables

See *vfprintf*.


# Errors

See *vfprintf*.


# Extended Description

See *vfprintf*.


# Future Directions

See *vfprintf*.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[vfprintf](vfprintf.3) - The actual implementation for printf family of functions.
