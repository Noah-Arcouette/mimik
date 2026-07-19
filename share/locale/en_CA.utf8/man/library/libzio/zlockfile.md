# Name

zlockfile -- Yield until a lock is acquired


# Synopsys

```c
#include <zio.h>

extern void zlockfile (zFILE *fp);
```


# Description

*zlockfile* shall attempt to lock a file -- yielding on failure -- until a lock
is achieved.


# Return Value

None.


# Errors

None.


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

`library/libzio/zunlockfile` -- Unlock a lock

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/flockfile.html) -- The POSIX documentation
