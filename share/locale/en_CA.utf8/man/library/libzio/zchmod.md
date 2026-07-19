# Name

zchmod -- Change file mode


# Synopsys

```c
#include <zio.h>

extern int zchmod (zFILE *fp, mode_t mode);
```


# Description

*zchmod* attempt to set file mode. May be dependent on user privileges and may
change underlying file system.


# Return Value

`0`
	Successful

`>0`
	Failed


# Errors

Any value set by `library/libc/fchmod`.

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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fchmod.html) -- The POSIX documentation
