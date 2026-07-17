# Name

z_suffix_from_format -- Return the file name suffix from the given format


# Synopsys

```c
#include <zio.h>

extern const char *z_suffix_from_format (int format);
```


# Description

`z_suffix_from_format` shall return based on the following table:

+--------------------+-----------+
|       Format       |   Value   |
+--------------------+-----------+
| ZIO_FORMAT_NONE    | ""        |
| ZIO_FORMAT_LZW     | "Z"       |
| ZIO_FORMAT_DEFLATE | "deflate" |
| ZIO_FORMAT_GZIP    | "gz"      |
| *unknown*          | NULL      |
+--------------------+-----------+

**Note:** If `ZIO_FORMAT_DEFAULT_*` -- any default format -- is given, the
returned value depends on the underlying format set.


# Return Value

Either the given suffix of the format. Or NULL with `errno` set, upon error. If
a suffix is returned the string shall be treated as a constant and should not
be changed.


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
