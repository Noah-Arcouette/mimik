# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

strcat - Concatenate two strings, part of libc


# Synopsis

```C
#include <string.h>

char *strcat (char *restrict s1, const char *restrict s2);
```


# Description

`strcat` shall append the string *s2* to the end of *s1*, over-writing *s1*'s NULL terminator. The string *s1* shall be large enough to store `strlen(s1)+strlen(s2)+1` bytes, this allocations must be provided by the user. `strcat` shall return *s1*.


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

[strncat](strncat.3) - The sister function to `strcat`, allows for fixed length *s2*
