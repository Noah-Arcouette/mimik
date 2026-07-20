# Name

z_set_codeword_bits -- Attempt to set codeword bits


# Synopsys

```c
#include <zio.h>

extern int z_set_codeword_bits (zFILE *fp, int bits);
```


# Description

*z_set_codeword_bits* shall attempt to set the codeword bits used by a file.
*bits* must be greater than `0`.


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
