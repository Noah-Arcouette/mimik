# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

atexit - Call a function at process exit, part of libc


# Synopsis

```C
#include <stdlib.h>

int atexit (void (*func)(void));
```


# Description

*atexit* shall queue *func* to run at exit time. All queued functions shall be ran in reverse order to their addition, before the C run-time is closed and the process quits. The process shall wait for *func* to return before continuing the exit of the program.

At least thirty two functions may be queue by *atexit*, but the amount may be larger; ATEXIT_MAX shall be used to access this value at compile time or [sysconf](sysconf.3) at run time. There is no, portable, way to tell the amount of queue functions.

*atexit* shall return zero at success, and negative one on failure.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*atexit* shall set errno and return negative one.

## EFAULT

*func* is NULL.

## ERANGE

Maximum amount of at-exit functions are already set, ATEXIT_MAX.


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

[exit](exit.3) - Quit the current process

[sysconf](sysconf.3) - Get relevant system configuration options
