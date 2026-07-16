# Name

z_format_from_suffix -- Get format value from suffix


# Synopsys

```c
#include <zio.h>

extern int z_format_from_suffix (const char *suffix);
```


# Description

`z_format_from_suffix` shall return based on the following information:

`Z` -- ZIO_FORMAT_LZW

(case insensitive) `deflate` -- ZIO_FORMAT_DEFLATE

(case insensitive) `gz`, `gzip` -- ZIO_FORMAT_GZIP

**Note:** any of the above given may also be preceded by a single period.


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
