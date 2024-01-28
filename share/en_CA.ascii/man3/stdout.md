# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

stdout - The standard output stream, part of libc


# Synopsis

```C
#include <stdio.h>

extern FILE *stdout;
```


# Description

*stdout* shall be opened for writing and be line-buffered, unless otherwise stated. *stdout* shall be user for application output, or output that shall be included in a given pipeline.


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

[stdin](stdin.3) - The standard input stream

[stderr](stderr.3) - The standard error stream
