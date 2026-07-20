# Name

z_set_compression_level -- Attempt to set compression level


# Synopsys

```c
#include <zio.h>

extern int z_set_compression_level (zFILE *fp, int level);
```


# Description

*z_set_compression_level* shall attempt to set the compression level of a file.
*level* must be greater than or equal to `0`.


# Return Value

`0`
	Success

`!0`
	Failed


# Errors

`ENOTSUP`
	Not supported by underlying format.

`EINVAL`
	One of the given values is invalid.


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
