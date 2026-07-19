# Name

zstat -- Get file metadata


# Synopsys

```c
#include <zio.h>

extern int zstat (zFILE *restrict fp, struct stat *statbuf);
```


# Description

*zstat* retrieves a stat structure form of metadata from the given file. Note,
this may be dependent on the underlying file system.


# Return Value

`0`
	Stat was successful

`>0`
	Stat failed


# Errors

Any value set by `library/libc/fstat`.

As-well as:

`ENOTSUP`
	Stating not supported by underlying format.

`EBADMSG`
	Internal metadata was corrupt.


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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fstat.html) -- The POSIX documentation
