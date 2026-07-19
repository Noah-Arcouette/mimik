# Name

zerror -- Test the error flag of a file


# Synopsys

```c
#include <zio.h>

extern int zerror (zFILE *fp);
```


# Description

*zerror* shall test the error flag of a given stream. *zerror* shall not change
the value of *errno*.


# Return Value

`0`
	No error has be set on the stream.

`>0`
	An error has be set on the stream.


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

`library/libzio/zclearerr` -- Clear the error flag

`library/libzio/zeof` -- Test the EOF flag

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/ferror.html) -- The POSIX ferror documentation
