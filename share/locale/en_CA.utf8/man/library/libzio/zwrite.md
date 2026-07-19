# Name

zwrite -- Write to a file


# Synopsys

```c
#include <zio.h>

extern size_t zwrite (const char *restrict buf, size_t size, size_t n,
	zFILE *restrict fp);
```


# Description

*zwrite* shall write to the file given. It shall write *n* amount of *size*
elements via the equivalent of *zputc*.


# Return Value

Shall return the amount of elements written, **not** bytes. A short amount of
written elements is caused via an error, the error flag is also set upon error.

If *n* or *size* is zero, then zero shall be immediately returned and the stream
left untouched.


# Errors

Any errno value returnable by `library/libzio/zputc`.


# Application Usage

None.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`library/libzio` -- The library root

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fwrite.html) -- The POSIX fwrite documentation
