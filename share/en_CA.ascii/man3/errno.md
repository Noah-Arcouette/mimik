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

## ERANGE / EOVERFLOW (7)

The operation will cause an overflow, or exceed a set maximum.

## EPERM(8)

Current permissions disallow action.

## EACCES(9)

Insufficient permissions for actions.

## EDQUOT(10)

Resource quota would be exceeded.

## EEXIST(11)

Resource already exists.

## EIO(12)

Resource action, input-output, error.

## EMLINK(13)

Hard-link maximum, for given the resource, reached.

## ENAMETOOLONG(14)

Resource name would exceed the given limit.

## ENOSPC(15)

Underlying resource capacity is at its maximum.

## ENOTDIR(16)

A path, or one of its constituent parts, is not a directory but is required to be.

## EROFS(17)

Write action would occur to a read-only resource.

## EXDEV(18)

Mono-resource action is trying to span multiple resources; commonly a cross-device hard-link.

## ENOSYS(19)

Action not implemented by the system.

## EUNKNOWN(20)

An unknown error occurred, or cannot be represented.

## EBUSY(21)

Actions is trying to be applied to a busy resource, and requires isolated access to the resource.

## ELOOP(22)

Resource, commonly symbolic links, resolution depth exceeded.

## EISDIR(23)

Actions may not be applied to a directory.

## EBADF(24)

Resource, commonly file, descriptor invalid.

## ENXIO(25)

Underlying resource does not exist.

## ESPIPE(26)

Resource does not have seek action.

## EINTR(27)

Action interrupted.

## EPIPE(28)

Broken pipe.

## EFBIG(29)

Resource to large.

## EDESTADDRREQ(30)

No destination address.

## EAGAIN(31)

Resource temporarily unavailable, try again.

## ENOBUFS(32)

Buffer full.

## ECONNRESET(33)

Connection externally reset.

## EBADMSG(34)

Malformed message.


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
