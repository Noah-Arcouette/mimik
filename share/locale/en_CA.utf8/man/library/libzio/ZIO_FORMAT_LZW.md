# Name

ZIO_FORMAT_LZW -- The unix `compress` format


# Synopsys

```c
#include <zio.h>

#define ZIO_FORMAT_LZW 10
```


# Description

This format is used by POSIX as the default, it is legacy, and generally should
not be used unless for compatibility. The format itself also contains a bug, but
everyone just includes the bug for compatibility.


# Application Usage

None.


# Examples

None.


# Rationale

Required by POSIX.


# Future Directions

None.


# History

None.


# See Also

`library/libzio` -- The library root

`format/lzw` -- The format documentation
