# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

catclose - close an open catalogue descriptor, part of libc


# Synopsis

```C
#include <nl_types.h>

int catclose (nl_catd catalogue);
```


# Description

*catclose* shall close *catalogue* releasing its data to the system. *catalogue* shall not be used after closure. *catclose* shall return zero on success.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*catclose* shall return negative one on error, and set errno.

See [fclose](fclose.3) for errno values.


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

[catopen](catopen.3) - Open a new catalogue descriptor
