# Name

ZIO_FORMAT_GZIP -- A GZip file


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

**Note:** GZip files are generally opened as files, via `zopen`, but since
multiple gzip files may be concatenated together along with file names gzip
files may also be opened as directories via `zopendir`. Also note, GZip does not
contain file metadata other then modification time, thus it is recommended not
to use GZip as an archiving format as the metadata is insufficient.

If a GZip file with multiple files within it is opened via `zopen`, the first
entry shall be used as a normal file as it is impossible to detect if a gzip is
file-based or directory-based without seeking. After the first file is read
any reads after will fail with `EISDIR`. If `zopen` is used for writing, only
one file may be written as the end of the file will be set by `zclose` in file
based access.


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
