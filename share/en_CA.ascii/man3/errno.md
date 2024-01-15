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

## E2BIG

Argument list is too long.

## EACCESS

Permission denied.

## EADDRINUSE

Address already in use.

## EADDRNOTAVAIL

Address not available.

## EAFNOSUPPORT

Address family is not supported.

## EAGAIN

Resource unavailable, try again.

## EALREADY

Connection already in progress.

## EBADF

Bad file descriptor.

## EBADMSG

Bad message.

## EBUSY

Device or resource busy.

## ECANCELED

Operation canceled.

## ECHILD

No child processes.

## ECONNABORTED

Connection aborted.

## ECONNRESET

Connection reset.

## EDEADLK

Resource deadlock would occur.

## EDESTADDRREQ

Destination address required.

## EDOM

Mathematics argument out of domain of function.

## EDQUOT

Reserved.

## EEXIST

File exists.

## EFBIG

File too large.

## EHOSTUNREACH

Host is unreachable.

## EIDRM

Identifier removed.

## EILSEQ

Illegal byte sequence.

## EINPROGRESS

Operation in progress.

## EINTR

Interrupted function.

## EINVAL

Invalid argument.

## EIO

Input output error.

## EISCONN

Socket is connected.

## EISDIR

Is a directory.

## ELOOP

Too many levels of symbolic links.

## EMFILE

File descriptor value too large.

## EMLINK

Too many links.

## EMSGSIZE

Message too large.

## EMULTIHOP

Reserved.

## ENAMETOOLONG

Filename too long.

## ENETDOWN

Network is down.

## ENETRESET

Connection aborted by network.

## ENETUNREACH

Network unreachable.

## ENFILE

Too many files open by system.

## ENOBUFS

No buffer space available.

## ENODATA

No message is available on the STREAM head read queue.

## ENODEV

No such device.

## ENOENT

No such file or directory.

## ENOEXEC

Executable file format error.

## ENOLCK

No locks available.

## ENOLINK

Reserved.

## ENOMEM

Not enough space.

## ENOMSG

No message of the desired type.

## ENOPROTOOPT

Protocol not available.

## ENOSPC

No space left on device.

## ENOSR

No STREAM resources.

## ENOSTR

Not a STREAM

## ENOSYS

Functionality not supported.

## ENOTCONN

The socket is not connected.

## ENOTDIR

Not a directory or a symbolic link to a directory.

## ENOTEMPTY

Directory not emptry.

## ENOTRECOVERABLE

State not recoverable.

## ENOTSOCK

Not a socket.

## ENOSUP

Not supported.

## ENOTTY

Inappropriate input output control operation.

## ENXIO

No such device or address.

## EOPNOTSUPP

Operation not supported on socket

## EOVERFLOW

Value too large to be stored in data type.

## EOWNERDEAD

Previous owner died.

## EPERM

Operation not permitted.

## EPIPE

Broken pipe.

## EPROTO

Protocol error.

## EPROTONOSUPPORT

Protocol not supported.

## EPROTOTYPE

Protocol wrong type for socket.

## ERANGE

Result too large.

## EROFS

Read-only file system.

## ESPIPE

Invalid seek.

## ESRCH

No such process.

## ESTALE

Reserved.

## ETIME

Stream `ioctl` timeout.

## ETIMEDOUT

Connection timed out.

## ETXTBSY

Text file busy.

## EWOULDBLOCK

Operation would block.

## EXDEV

Cross-device link.


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
