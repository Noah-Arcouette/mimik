# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

_exit, _Exit - Hard quit of current process, part of libc and the System


# Synopsis

```C
#include <stdlib.h>

void _Exit (int status);

#include <unistd.h>

void _exit (int status);
```


# Description

*_Exit* shall be equivalent, in all ways, to *_exit*.

*_exit* shall quit the current process without further delay. This entails: No internal buffers shall be flushed, no internally allocated data shall be free, no exit-time functions shall be called, et cetera. *_exit* shall quit, at the operating system level, the current process.

Multiple calls to *_exit* shall never occur.

**Warning: Data loss will occur if this function is used in most to all cases, please use `void exit (int status);`**


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*_exit* shall never fail nor exit.


# Extended Description

The *_exit* function is implemented by the system, not necessarily the C standard library.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[exit](exit.3) - The C standard library exit function, properly closes internal data structures

[exit](exit.2) - The system implementation details of `_exit`
