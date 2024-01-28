# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

close - Close file descriptor, part of libc and the System


# Synopsis

```C
#include <unistd.h>

int close (int fildes);
```


# Description

*close* shall deem *fildes* inoperable, closing all associated data structures in the process. All locks shall be unlocked. The file descriptor shall be returned to the close file descriptors pool and be valid for a subsequential call to `open`.

If *fildes* refers to a pipe or FIFO the data shall be discarded. All attached pipes shall be detached from *fildes*, causing a hangup on the other side of the pipe.

*close* shall return zero on success and negative one on failure.

# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

*close* shall set errno and return negative one.

Refer to [close](close.2) for errno.

# Extended Description

There is no extended description.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[fclose](fclose.3) - Close file stream

[close](close.2) - System implementation details of *close*

[open](open.3) - Open a file descriptor
