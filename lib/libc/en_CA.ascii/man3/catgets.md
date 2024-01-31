# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

catgets - Get message from catalogue, part of libc


# Synopsis

```C
#include <nl_types.h>

char *catgets (nl_catd catd, int set, int msg, const char *s);
```


# Description

*catgets* shall return the message identified by *set* and *msg* from open message catalogue *catd*. Upon any error *s* shall be returned.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*catgets* shall return *s* upon error and set errno.

## ENOMSG

No message identified by *set* and *msg* in *catd*.

## Others

Refer to [fread](fread.3).


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

[catopen](catopen.3) - Open a new catalogue descriptor

[catclose](catclose.3) - Close a catalogue descriptor
