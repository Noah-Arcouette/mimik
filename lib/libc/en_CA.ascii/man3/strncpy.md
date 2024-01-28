# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

strncpy - Copy source string to fixed size destination buffer, part of libc

# Synopsis

```C
#include <string.h>

char *strncpy (char *restrict dst, const char *restrict src, size_t n);
```


# Description

`strncpy` shall copy the string contents of string *src* to buffer *dst*. The function shall stop on NULL character, or on character index *n*.
`strncpy` shall return a pointer to the start of *dst*.
The user shall be responsible for the allocation of the buffer *dst*, its size being that of *n*. The *dst* buffer may not be NULL terminated.


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

[strcpy](strcpy.3) - A sister function to `strncpy`, for non-fixed length *dst* buffer

[stpncpy](stpncpy.3) - A sister function to `strncpy`, returns end of *dst*
