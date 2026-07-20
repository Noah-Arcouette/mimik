# Name

z_get_cores -- Attempt to get encoding/decoding cores


# Synopsys

```c
#include <zio.h>

extern int z_get_cores (zFILE *fp);
```


# Description

*z_get_cores* shall attempt to get the amount of cores used for encoding or
decoding the given file.


# Return Value

`>0`
	Successful, the amount of cores currently in use

`<=0`
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
