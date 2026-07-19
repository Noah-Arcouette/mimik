# Name

zeof -- Test the EOF flag of a file


# Synopsys

```c
#include <zio.h>

extern int zeof (zFILE *fp);
```


# Description

*zerror* shall test the EOF flag of a given stream. *zerror* shall not change
the value of *errno*.


# Return Value

`0`
	EOF not set on the file.

`>0`
	End-Of-File has been reached on the file.


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

`library/libzio/zclearerr` -- Clear the EOF flag

`library/libzio/zerror` -- Test the error flag

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/feof.html) -- The POSIX feof documentation
