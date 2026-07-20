# Name

z_get_codeword_bits -- Attempt to get the codeword bits used


# Synopsys

```c
#include <zio.h>

extern int z_get_codeword_bits (zFILE *fp);
```


# Description

*z_get_codeword_bits* shall attempt to get the codeword bits for the given file.


# Return Value

`>0`
	Successful, the codeword bits used

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
