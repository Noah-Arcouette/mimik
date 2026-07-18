# Name

lzw -- LZW -- unix compress -- file format


# Synopsys

```c
#include <zio.h>

struct lzw
{
	#define LZW_MAGIC (uint16_t)(0x9f1f)
	uint16_t magic;

	#define LZW_FLAG_CODE_BITS_MASK 0x1f
	#define LZW_FLAG_RESERVED       0x60
	#define LZW_FLAG_BLOCK_MODE     0x80
	uint8_t flags;
};
```


# Description

The *lzw* structure defines the header of the unix `.Z` format. All multibyte
entries are in little-endian format. The element *magic* must always be set to
`LZW_MAGIC`.

*flags* is a bit field, the first five bits -- `LZW_FLAG_CODE_BITS_MASK` -- are
the max amount of bits to use to encode a code-word. The `LZW_FLAG_BLOCK_MODE`
includes a special clear table entry allowing for better compression rates,
especially on larger files.

The header is always followed by the LZW encoded stream.


# Application Usage

This is mainly meant for internal usages.


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

`format/Z` -- The format itself
