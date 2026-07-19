# Name

zchown -- Change file ownership


# Synopsys

```c
#include <zio.h>

extern int zchown (zFILE *fp, uid_t user, gid_t group);
```


# Description

*zchown* attempt to set file ownership. May be dependent on user privileges and
may change underlying file system.


# Return Value

`0`
	Successful

`>0`
	Failed


# Errors

Any value set by `library/libc/fchown`.

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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fchown.html) -- The POSIX documentation
