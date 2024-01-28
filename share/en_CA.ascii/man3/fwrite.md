# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

fwrite - Write data to stream, part of libc


# Synopsis

```C
#include <stdio.h>

size_t fwrite (const void *restrict buf, size_t itemsz, size_t items, FILE *restrict stream);
```


# Description

*fwrite* shall write *items* amount of data from *buf* to *stream*. For each item, *itemsz* bytes shall be written. *fwrite* shall return the amount of items written, which may not be the same as *items* if an error occurs.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*fwrite* shall set errno and return the amount of items written.

For errno refer to [fputc](fputc.3).


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

[fread](fread.3) - Read from stream
