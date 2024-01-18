# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

unlink - Remove a hard-link, part of libc


# Synopsis

```C
#include <unistd.h>

int unlink (const char *path);
```


# Description

*unlink* shall remove the hard-link pointed to by *path*. *unlink* shall return zero on success, and negative one on error. On error the file pointed to by *path* shall not be modified in any way.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

Negative one shall be return and errno set.

## EACCES

The program does not have the proper access to unlink *path*.

## EBUSY

*path* is currently in use.

## ELOOP

A loop exists in symbolic link resolution.

## ENAMETOOLONG

*path* is over the system file path limit, `NAME_MAX`.

## ENOENT

*path* does not exist.

## ENOTDIR

A component of *path* is not resolvable, an attempt to enter a non-directory entry.

## EPERM

Permissions does not allow unlinking of *path*.

## EROFS

*path* resides on a read-only file system.

## EFAULT

*path* is NULL.


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

[link](link.3) - Create a hard-link

[rmdir](rmdir.3) - Facilitate the unlinking of a directory

[unlink](unlink.2) - The system implementation details of `unlink`
