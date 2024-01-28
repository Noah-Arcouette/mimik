# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

memchr - Find value in memory, part of libc

# Synopsis

```C
#include <string.h>

void *memchr (const void *s, int c, size_t n);
```


# Description

`memchr` shall return a pointer to the first occurrence of *c*, interpreted as an **unsigned char**, in buffer *s*. `memchr` shall not read more than *n* bytes from *s*. A NULL pointer shall be returned if no occurrence of *c* is found in the first *n* bytes of *s*.


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
