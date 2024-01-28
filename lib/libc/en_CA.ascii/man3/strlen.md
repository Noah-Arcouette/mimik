# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

strlen - Get length of string, part of libc


# Synopsis

```C
#include <string.h>

size_t strlen (const char *s);
```


# Description

`strlen` shall compute the length of *s*, not including the terminating character. An *s* value of NULL shall never be given.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

This function shall not set any errors.


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

[strnlen](strnlen.3) - The sister function to `strlen`, allows for fixed size *s*
