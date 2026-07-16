# Name

ZIO_FORMAT_DEFAULT_DEFLATE -- A raw deflate stream


# Synopsys

```c
#include <zio.h>

#define ZIO_FORMAT_DEFLATE 20
```


# Description

This format is generally not used on files that are meant to be used externally
in any way. Sometimes it is used as a save file format for games or for caches.
But please, at least use zlib format; zlib is minimal but detectable.


# Application Usage

None.


# Examples

None.


# Rationale

Sometimes useful to use in memory buffers or pipes.


# Future Directions

None.


# History

None.


# See Also

`library/libzio` -- The library root

`format/deflate` -- The format documentation
