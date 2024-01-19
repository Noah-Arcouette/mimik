# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

errno - Error numbers, part of libc


# Synopsis

```C
#include <errno.h>

extern int errno;
```


# Description

*errno* shall hold any error value set by a running program. *errno* shall be set to any of these defined macros.

## EFAULT(2)

Pointer is NULL, or faulty.

## EINVAL(3)

Invalid argument.

## ENOMEM(4)

Memory or storage, has or will, exceeded maximum.

## ENFILE(5)

Maximum streams already open.

## ENOENT(6)

File system entry, or its constituent entries, are invalid or do not exist.

## ERANGE(7)

The operation will cause an overflow, or exceed a set maximum.


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
