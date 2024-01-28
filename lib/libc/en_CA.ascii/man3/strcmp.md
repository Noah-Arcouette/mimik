# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

strcmp - Compare the value of two strings, part of libc


# Synopsis

```C
#include <string.h>

int strcmp (const char *s1, const char *s2);
```


# Description

The string values of *s1* and *s2* shall be compared, if they are equal then zero shall be return. 
If the strings are not equal then the return value shall be positive if *s1* is lexicographically larger than *s2*, and vise versa for negative.


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

[strncmp](strncmp.3) - The sister function to `strcmp`, allows for fixed length strings
