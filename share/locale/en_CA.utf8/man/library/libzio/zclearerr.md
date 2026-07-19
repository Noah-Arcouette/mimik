# Name

zclearerr -- Clear stream indicators


# Synopsys

```c
#include <zio.h>

extern void zclearerr (zFILE *fp);
```


# Description

*zclearerr* shall clear the error and EOF flag of a file. *zclearerr* shall not
modify *errno*.


# Return Value

None.


# Errors

*errno* will not be modified.


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

`library/libzio/zeof` -- Test the eof flag

`library/libzio/zerror` -- Test the error flag

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/clearerr.html) -- The POSIX clearerr documentation
