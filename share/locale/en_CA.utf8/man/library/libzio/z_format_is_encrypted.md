# Name

z_format_is_encrypted -- Test if a zio format is encrypted


# Synopsys

```c
#include <zio.h>

extern int z_format_is_encrypted (int format);
```


# Description

`z_format_is_encrypted` shall return based on the following table:

+--------------------+-------+
|       Format       | Value |
+--------------------+-------+
| ZIO_FORMAT_NONE    | 0     |
| ZIO_FORMAT_LZW     | 0     |
| ZIO_FORMAT_DEFLATE | 0     |
| ZIO_FORMAT_GZIP    | 0     |
| *unknown*          | 0     |
+--------------------+-------+

**Note:** If `ZIO_FORMAT_DEFAULT_*` -- any default format -- is given, the
returned value depends on the underlying format set.


# Return Value

`0`
	The format is not encrypted, and does not provided any level of data
	security.

`1`
	The format is encrypted, and provides some level of data security. Other
	functions may be necessary to determine the type.


# Errors

None.


# Application Usage

None.


# Examples

None.


# Rationale

None.


# Future Directions

Addition of `z_format_uses_password` or `z_format_uses_signature` or other types
to determine the specific security methods.


# History

None.


# See Also

`library/libzio` -- The library root
