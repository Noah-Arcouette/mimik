# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

strchr - Locate character in string, part of libc


# Synopsis

```C
#include <string.h>

char *strchr (const char *s, int c);
```


# Description

`strchr` shall return a pointer to the first occurrence of *c*, interpreted as a **char**, in string *s*. If there is no occurrence of *c* in *s* then a NULL pointer shall be returned.


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

[strrchr](strrchr.3) - A sister function to `strchr`, returns the last occurrence of *c*

[strpbrk](strpbrk.3) - A sister function to `strchr`, finds match from a list of *c*s
