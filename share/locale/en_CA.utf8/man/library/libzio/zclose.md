# Name

zclose -- Close a file


# Synopsys

```c
#include <zio.h>

extern int zclose (zFILE *fp);
```


# Description

*zclose* shall close the given file, which entails:
 - flushing any data, via `zflush`
 - seek to the end
 - closing any backing file descriptor
 - free any internally allocated data
 - disassociate any connected data


# Return Value

`0`
	No error occurred on closing

`EOF`
	An error occurred while closing


# Errors

Any errno value returnable by `library/libc/close`.

Any errno value returnable by `library/libzio/zflush`.

Aswell as the following:

`EINVAL`
	*fp* is invalid


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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fclose.html) -- The POSIX documentation
