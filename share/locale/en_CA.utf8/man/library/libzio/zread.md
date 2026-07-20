# Name

zread -- Read from a file


# Synopsys

```c
#include <zio.h>

extern size_t zread (char *restrict buf, size_t size, size_t n,
	zFILE *restrict fp);
```


# Description

*zread* shall read frp, the file given. It shall read *n* amount of *size*
elements via the equivalent of *zputc*.


# Return Value

Shall return the amount of elements read, **not** bytes. A short amount of read
elements is caused via an error, the error flag is also set upon error. It also
may be short because of EOF being reached.

If *n* or *size* is zero, then zero shall be immediately returned and the stream
left untouched.


# Errors

Any errno value returnable by `library/libzio/zgetc`.


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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fread.html) -- The POSIX fwrite documentation
