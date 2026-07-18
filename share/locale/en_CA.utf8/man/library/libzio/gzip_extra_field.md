# Name

gzip_extra_field -- A gzip file extra field


# Synopsys

```c
#include <zio.h>

struct gzip_extra_field
{
	uint16_t id;
	uint16_t len;
};
```


# Description

A gzip file extra field, tailing *gzip_extra_fields* if present.

All multibyte values are in little-endian format.

*id* the identified of the extra field type.

*len* the length, in bytes, of the following extra data.

Extra data bytes, specific to the extra field type.


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
