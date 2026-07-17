# Name

zopen -- Open an alternatively encoded file, as a file


# Synopsys

```c
#include <zio.h>

zFILE *zopen (const char *restrict path, const char *restrict mode, int format);
```


# Description

`zopen` shall open the given *path* -- treated as a host file system path --
with the *format* given. *format* shall be any `ZIO_FORMAT*` that supports being
opened as a file. The underlying path may be of any file type, and seekability
shall be completely dependent on the file type and provided format.

For *mode* one of the following must be given as the first character:
 - `r` - Open for reading
 - `w` - Open for writing, truncate first or create file
 - `a` - Open for writing at end of file, or create file

The following may also be given after:
 - `+` - Shall allow reading and writing (if supported by underlying format and
	file)
 - `b` - Has no effect
 - `e` - FD_CLOEXEC shall be set on the open file descriptor
 - `x` - The underlying file shall be open in an exclusive manner
 - `s` - Open securely, fail on any corruption

If the *format* option is `-1` then the format shall be detected from the file
**contents** if possible.


# Return Value

A valid zFILE stream associated with the given path, or NULL upon error.


# Errors

Any errno value returnable by `library/libc/open`.

Aswell as the following:

`EINVAL`
	*format* was invalid, or failed to be auto-detected. *mode* was invalid.

`ENOSYS`
	*format* is not implemented on the system.

`ENOSUP`
	One of the *mode* options is not supported by the format.

`EBADMSG`
	The file is corrupted beyond usable means, or `s` was given and any
	corruption was detected.


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

[POSIX](https://pubs.opengroup.org/onlinepubs/9799919799/functions/fopen.html) -- The POSIX fopen documentation
