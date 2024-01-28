# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

strncat - Concatenate string with buffer, part of libc


# Synopsis

```C
#include <string.h>

char *strncat (char *restrict s1, const char *restrict s2, size_t n);
```


# Description

`strncat` shall append the buffer *s2* to the end of the string *s1*, over-writing its NULL terminator. `strncat` shall not append more than *n* bytes, and may not append a NULL terminator.
The user shall allocate space in *s1* for `strlen(s1)+n` bytes. `strncat` shall return *s1*.


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

[strcat](strcat.3) - The sister function to `strncat`, allows for non-fixed length *s2*
