# Name

gzip_extra_fields -- The gzip file extra fields


# Synopsys

```c
#include <zio.h>

struct gzip_extra_fields
{
	uint16_t len;
} __attribute__((packed));
```


# Description

The gzip file extra fields, only present if `GZIP_FLAG_EXTRA` is set. Is placed
after the header.

All multibyte values are in little-endian format.

*len* the length, in bytes, of all the following extra fields.

*gzip_extra_field* structures of length bytes.


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

`library/libzio/gzip` -- The library root

`format/gz` -- The format itself
