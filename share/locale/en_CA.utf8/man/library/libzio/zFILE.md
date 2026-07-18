# Name

zFILE -- The core file access structure for libzio


# Synopsys

```c
#include <zio.h>

typedef struct zFILE zFILE;
```


# Description

*zFILE* is the core file-access type for libzio. If can be open via the `zopen`
family of functions. It supports reading and writing -- where allowed by system
and format -- as-well as seeking on select formats and underlying systems. It is
the equivalent to libc's *FILE*. Although, it also supports select file system
metadata functions -- `zchown`, `zchmod`, `zutimens`, etc -- as some formats
use underlying encoding to set these instead of the file system.

*zFILE*s may also be retrieved from `zopenat` where they themselves do not
encode but instead access the underlying archiving format.


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
