# Name

zutimens -- Change file access and modification times


# Synopsys

```c
#include <zio.h>

extern int zutimens (zFILE *restrict fp, struct timespec t[2]);
```


# Description

*zutimens* attempt to set file access and modification times. May be dependent
on user privileges and may change underlying file system.

`t[0]` is access time, `t[1]` is modification time.


# Return Value

`0`
	Successful

`>0`
	Failed


# Errors

Any value set by `library/libc/futimens`.

As-well as:

`ENOTSUP`
	Not supported by underlying format.

`EBADMSG`
	Internal metadata structures were corrupt.


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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/futimens.html) -- The POSIX documentation
