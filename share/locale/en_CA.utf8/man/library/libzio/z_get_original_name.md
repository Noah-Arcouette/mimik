# Name

z_get_original_name -- Attempt to get the original file name


# Synopsys

```c
#include <zio.h>

extern const char *z_get_original_name (zFILE *fp);
```


# Description

*z_get_original_name* shall attempt to get the original file name.


# Return Value

Either a static version -- note to be modified -- original file name, or NULL
upon error.


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
