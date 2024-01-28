# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

exit - Quit current process, part of libc


# Synopsis

```C
#include <stdlib.h>

void exit (int status);
```


# Description

*exit* shall run all functions queue by `atexit` in reverse order. All functions shall be called as many times as they are queued. Then it shall close the C run-time and terminate the current process with exit code *status*. *exit* shall never be ran more than once.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*exit* shall never fail nor exit.


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

[_exit](_exit.3) - Halt quit program

[atexit](atexit.3) - Queue function to run at exit
