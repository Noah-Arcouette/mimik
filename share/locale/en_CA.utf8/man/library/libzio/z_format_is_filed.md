# Name

z_format_is_filed -- Test if a zio format is filed


# Synopsys

```c
#include <zio.h>

extern int z_format_is_filed (int format);
```


# Description

`z_format_is_filed` shall return based on the following table:

+--------------------+-------+
|       Format       | Value |
+--------------------+-------+
| ZIO_FORMAT_NONE    | 1     |
| ZIO_FORMAT_LZW     | 1     |
| ZIO_FORMAT_DEFLATE | 1     |
| ZIO_FORMAT_GZIP    | 1     |
| *unknown*          | 0     |
+--------------------+-------+

**Note:** If `ZIO_FORMAT_DEFAULT_*` -- any default format -- is given, the
returned value depends on the underlying format set.


# Return Value

`0`
	The format is not archived, and may not be opened with the `zopen` family of functions.

`1`
	The format is archived, and may be opened with the `zopen` family of
	functions.


# Errors

None.


# Application Usage

This is designed to tell if a given format may be opened with `zopen` family
of functions; note, a format may support both file-based and directory-based
opening and access methods.


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
