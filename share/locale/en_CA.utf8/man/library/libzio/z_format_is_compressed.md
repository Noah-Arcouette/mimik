# Name

z_format_is_compressed -- Test if a zio format is compressed


# Synopsys

```c
#include <zio.h>

extern int z_format_is_compressed (int format);
```


# Description

`z_format_is_compressed` shall return based on the following table:

+------------------------------+-------+
|            Format            | Value |
+------------------------------+-------+
| ZIO_FORMAT_DEFAULT_COMPRESS  | 1     |
| ZIO_FORMAT_NONE              | 0     |
| ZIO_FORMAT_LZW               | 1     |
| ZIO_FORMAT_DEFLATE           | 1     |
| ZIO_FORMAT_GZIP              | 1     |
| *unknown*                    | 0     |
+------------------------------+-------+

**Note:** If `ZIO_FORMAT_DEFAULT_*` -- any default format -- is given, the
returned value depends on the underlying format set. Unless
`ZIO_FORMAT_DEFAULT_COMPRESS` is given, the default compression algorithm
**must** always compress.


# Return Value

`0`
	The format is not compressed, and does not provided any level of data
	compression.

`1`
	The format is compressed, and provides some level of data compression.


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
