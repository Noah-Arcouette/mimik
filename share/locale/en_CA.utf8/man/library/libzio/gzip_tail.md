# Name

gzip_tail -- The gzip file tailer


# Synopsys

```c
#include <zio.h>

struct gzip_tail
{
	uint32_t crc;
	uint32_t size;
} __attribute__((packed));
```


# Description

The gzip file tailer, is always at the end of the file member.

All multibyte values are in little-endian format.

*crc* the CRC-32 of all uncompressed data in the member.

*size* the size of all uncompressed data in the member, modulo 2^32.


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
