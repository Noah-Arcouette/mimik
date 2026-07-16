# Name

z_format_is_protected -- Test if a zio format is protected


# Synopsys

```c
#include <zio.h>

extern int z_format_is_protected (int format);
```


# Description

`z_format_is_protected` shall return based on the following table:

+--------------------+-------+
|       Format       | Value |
+--------------------+-------+
| ZIO_FORMAT_LZW     | 0     |
| ZIO_FORMAT_DEFLATE | 0     |
| ZIO_FORMAT_GZIP    | 0     |
| *unknown*          | 0     |
+--------------------+-------+

**Note:** If `ZIO_FORMAT_DEFAULT_*` -- any default format -- is given, the
returned value depends on the underlying format set.


# Return Value

`0`
	The format is not protected, and does not provided any level of data error
	correction

`1`
	The format is protected, and provides some level of error correction.


# Errors

None.


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
