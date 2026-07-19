# Name

zseeko -- Seek into a file


# Synopsys

```c
#include <zio.h>

extern int zseeko (zFILE *fp, off_t offset, int whence);
```


# Description

*zseeko* shall attempt to seek into the file at the provided values.

The start of the seek shall be dependent on *whence* and may be the following
values:
 - `SEEK_SET` -- Start of the file
 - `SEEK_CUR` -- Current offset in the file
 - `SEEK_END` -- End of the file

The starting point shall be added by *offset* -- which may be negative -- to
produce the final seek value.

*zseeko* shall flush the file, clearing any ungets, and clearing the EOF flag.

*zseeko* shall grow the file will zero bytes, upon seeking past EOF.


# Return Value

`0`
	Seek was successful

`>0`
	Seek failed


# Errors

Any value set by `library/libc/fseeko`.

As-well as:

`ENOTSUP`
	Seeking not supported by underlying format.


# Application Usage

Seeking is almost always not possible while encoding, but where it is, it can be
extremely powerful.


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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fseeko.html) -- The POSIX documentation
