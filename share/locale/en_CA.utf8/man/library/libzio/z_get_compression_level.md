# Name

z_get_compression_level -- Attempt to get compression level


# Synopsys

```c
#include <zio.h>

extern int z_get_compression_level (zFILE *fp);
```


# Description

*z_get_compression_level* shall attempt to get the compression level for the
given file.


# Return Value

`>=0`
	Successful, the compression level used

`<0`
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
