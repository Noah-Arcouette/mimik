# Name

zseek -- Seek into a file using a long


# Synopsys

```c
#include <zio.h>

extern int zseek (zFILE *fp, long offset, int whence);
```


# Description

Same as `zseeko(fp, (off_t)offset, whence)`, see `library/libzio/zseeko`.


# Return Value

See `library/libzio/zseeko`.


# Errors

See `library/libzio/zseeko`.


# Application Usage

See `library/libzio/zseeko`.


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

`library/libzio/zseeko` -- The full documentation

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fseek.html) -- The POSIX documentation
