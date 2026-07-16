# Name

z_format_from_name -- Get format value from common name


# Synopsys

```c
#include <zio.h>

extern int z_format_from_name (const char *suffix);
```


# Description

`z_format_from_name` shall return based on the following information:

(case insensitive) `lzw` -- ZIO_FORMAT_LZW

(case insensitive) `deflate` -- ZIO_FORMAT_DEFLATE

(case insensitive) `gzip`, `gz` -- ZIO_FORMAT_GZIP


# Return Value

Shall either be a valid format value, or negative one upon error with `errno`
set.


# Errors

`EINVAL`
	Unknown value given.


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
