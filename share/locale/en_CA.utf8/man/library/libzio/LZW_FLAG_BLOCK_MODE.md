# Name

LZW_FLAG_BLOCK_MODE -- The block-mode bit


# Synopsys

```c
#include <zio.h>

#define LZW_FLAG_BLOCK_MODE 0x80
```


# Description

Enable block-mode for LZW compression, this is part of unix compress v2 and may
not be supported on older unix versions.


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

`library/libzio/lzw` -- The LZW format structure

`format/Z` -- The format itself
