# Name

zunlockfile -- Unlock a file


# Synopsys

```c
#include <zio.h>

extern void zunlockfile (zFILE *fp);
```


# Description

*zunlockfile* shall unlock the given file, if a file was given that is not
locked by the current thread nothing shall be unlocked as this is a definite
error condition or bug.


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

`library/libzio/zlockfile` -- Lock a file

`library/libzio/ztrylockfile` -- Try to lock a file

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/funlockfile.html) -- The POSIX documentation
