# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

link - Create a hard-link, part of libc


# Synopsis

```C
#include <unistd.h>

int link (const char *src, const char *dst);
```


# Description

*link* shall create a hard-link to *src* at *dst*. On error *link* shall return negative one, and on success return zero.

# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

Negative one shall be return and errno set.

## EFAULT, *Resilient Builds Only*

*src* or *dst* is NULL.

## ENOENT

*src* or *dst* do not refer to valid file system entries.

## Others

Refer to [link](link.2).


# Extended Description

The *unlink* function is implemented by the system, not necessarily the C standard library.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[unlink](unlink.3) - Remove a hard-link

[rename](rename.3) - Rename a file system entry

[symlink](symlink.3) - Create a symbolic link

[unlink](unlink.2) - The system implementation details of `unlink`
