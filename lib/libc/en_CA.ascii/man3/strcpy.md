# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

strcpy - Copy source string to destination, part of libc

# Synopsis

```C
#include <string.h>

char *strcpy (char *restrict dst, const char *restrict src);
```


# Description

`strcpy` shall copy the string contents of string *src* to buffer *dst*. The function shall stop on NULL character.
`strcpy` shall return a pointer to the start of *dst*.
The user shall be responsible for the allocation of the buffer *dst*, its size being `strlen(src)+1`.


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

[strncpy](strncpy.3) - A sister function to `strcpy`, allows for fixed length *dst*

[stpcpy](stpcpy.3) - A sister function to `strcpy`, returns end of *dst*
