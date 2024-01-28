# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

strpbrk - Locate character, from a list, in a string, part of libc


# Synopsis

```C
#include <string.h>

char *strpbrk (const char *s1, const char *s2);
```


# Description

`strpbrk` shall return a pointer to the first occurrence of any character in string *s2* in string *s1*. If there is no occurrence of any character in *s2* in *s1* then a NULL pointer shall be returned. `strpbrk` shall favor the leading characters in *s2*.


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

[strchr](strchr.3) - A sister function to `strpbrk`, returns the first occurrence of single *s2*

[strrchr.3](strrchr.3) - A sister function to `strpbrk`, returns the last occurrence of single *s2*
