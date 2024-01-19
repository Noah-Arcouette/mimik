# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

lseek - Move or shift a file descriptors read-write head, part of libc and the System


# Synopsis

```C
#include <unistd.h>

off_t lseek (int fildes, off_t offset, int whence);
```


# Description

The *lseek* function shall move or shift the read-write head of the file descriptor *fildes* by *offset*. How *lseek* shifts or moves the read-write head shall be determined by *whence*, as such:
 - `SEEK_SET` shall interpret offset as starting from the beginning of the file.
 - `SEEK_CUR` shall interpret offset from the current position of the read-write head.
 - `SEEK_END` shall interpret offset as starting from the end of the file.

*lseek* shall not extend the size of the file, but allow for the read-write head to exceed the file's end; reads from the exceeded seek shall produce zero until data is written.

*lseek* shall return the measure of bytes from the beginning of the file, or return negative one on error and not modify the read-write head.


# Environment Variables

Environment variables shall not be consider or modified by this function.


# Errors

Negative one shall be return and errno set.

## EINVAL

The *whence* value is unsupported, or the returning offset will be negative.

## Others

Refer to [lseek](lseek.2).


# Extended Description

The *lseek* function is implemented by the system, not necessarily the C standard library.

A write to a file descriptor thats read-write head is beyond its end may cause it to be extended.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[open](open.3) - Open a new file descriptor

[lseek](lseek.2) - The system implementation details of `lseek`
