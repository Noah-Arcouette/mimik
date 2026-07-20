# Name

zflush -- Flush buffered data


# Synopsys

```c
#include <zio.h>

extern int zflush (zFILE *fp);
```


# Description

*zflush* shall attempt to write any buffered data, or discard any ungot data.


# Return Value

`0`
	No error occurred

`>0`
	An error occurred


# Errors

Any errno value returnable by `library/libc/write`.


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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fflush.html) -- The POSIX documentation
