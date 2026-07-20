# Name

z_set_cores -- Attempt to set encoding/decoding cores


# Synopsys

```c
#include <zio.h>

extern int z_set_cores (zFILE *fp, int cores);
```


# Description

*z_set_cores* shall attempt to set the amount of cores used for encoding or
decoding the given file.


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
