# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

stdin - The standard input stream, part of libc


# Synopsis

```C
#include <stdio.h>

extern FILE *stdin;
```


# Description

*stdin* shall be opened for reading and be fully-buffered, unless otherwise stated. *stdin* shall be used for buffer input to the given application: the input section of a pipeline, a file, or user input.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

This function shall not set any errors.


# Extended Description

The file descriptor underlying *stdin* may be line buffered by the associated driver, if it points to an interactive device, exp: TTY.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[stderr](stderr.3) - The standard error stream

[stdout](stdout.3) - The standard output stream
