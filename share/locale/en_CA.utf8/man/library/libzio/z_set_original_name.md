# Name

z_set_original_name -- Attempt to set the original file name


# Synopsys

```c
#include <zio.h>

extern int z_set_original_name (zFILE *fp, const char *name);
```


# Description

*z_set_original_name* shall attempt to set the original file name of the given
file. *name* shall be copied and need not be preserved.


# Return Value

`0`
	Successful

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
