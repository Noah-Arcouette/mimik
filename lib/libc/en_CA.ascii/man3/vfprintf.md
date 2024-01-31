# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

vfprintf - Print formatted string to file with variable arguments, part of libc


# Synopsis

```C
#include <stdio.h>
#include <stdarg.h>

int vfprintf (const FILE *restrict file, const char *restrict fmt, va_list vargs);
```


# Description

*vfprintf* shall format *vargs* and write, as described by *fmt*, to *file*. *vfprintf* shall return the amount of characters written, or negative one upon error.


# Environment Variables

## Lang

The *Lang* environment variable shall be used to format information into the current locale.


# Errors

*vfprintf* shall return negative upon error.

For errno value see [fputc](fputc.3).


# Extended Description

## String Format Specifiers

*vfprintf* shall echo the characters in *fmt* until a `%` character is found, it will then switch to format parsing. The format description shall be on the following character, after the initial `%`, until *vfprintf* is returned to echoing.

### s

*vfprintf* shall emit a string, and halt format parsing returning to echoing.

### d

*vfprintf* shall emit a decimal signed integer, and halt format parsing returning to echoing.

### %

*vfprintf* shall emit a single `%` character, and halt format parsing returning to echoing.

### Else

The *vfprintf* operation on an unknown format string is to emit `%`, and halt parsing returning to echoing.


# Future Directions

Full POSIX compliance.


# Compliance

The described operations comply with, although the *vfprintf* function itself is not fully compliant with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also
