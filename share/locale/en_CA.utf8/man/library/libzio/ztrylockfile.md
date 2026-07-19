# Name

ztrylockfile -- Try to lock a file


# Synopsys

```c
#include <zio.h>

extern int ztrylockfile (zFILE *fp);
```


# Description

*ztrylockfile* shall attempt to lock the file returning upon any contention or
acquire.


# Return Value

`0`
	A lock was acquired

`>0`
	For one reason or another, a lock could not be obtained at the moment.


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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/ftrylockfile.html) -- The POSIX documentation
