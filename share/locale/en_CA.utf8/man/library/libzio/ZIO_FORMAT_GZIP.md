# Name

ZIO_FORMAT_DEFAULT_GZIP -- A GZip file


# Synopsys

```c
#include <zio.h>

#define ZIO_FORMAT_GZIP 21
```


# Description

This format is contains slightly more variable length data portions than it
should, though it is ubiquitous on all machines. It uses Deflate as its
compression, though it has room for others none are defined. GZip files are the
most common format to see, and they include: data checksums, header checksums,
original file size, original file name, arbitrary implementation data, a file
"comment", original file system, last modified, and a bit more.


# Application Usage

The format is completely write-streamable so long as modification timestamp and
original file name are set before the first write call.


# Examples

None.


# Rationale

Very common, needed for POSIX, and is ubiquitous in networking.


# Future Directions

None.


# History

None.


# See Also

`library/libzio` -- The library root

`format/gzip` -- The format documentation
