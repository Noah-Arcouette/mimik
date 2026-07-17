# Name

z_format_is_archived -- Test if a zio format is archived


# Synopsys

```c
#include <zio.h>

extern int z_format_is_archived (int format);
```


# Description

`z_format_is_archived` shall return based on the following table:

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
	The format is not archived, and should be opened with the `zopen` family of
	functions.

`1`
	The format is archived, and should be opened with the `zopendir` family of
	functions.


# Errors

None.


# Application Usage

This is designed to tell whether a format should be treated as a file or
directory, without going through the work of testing both.


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
