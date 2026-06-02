# Name

readlink -- Display the contents of a symbolic link


# Synopsys

```sh
$ readlink [-n] file
```


# Description

If *file* is a symbolic link, then the utility shall print where the link leads
to -- the link contents. If **-n** is given then there shall be no final
newline the link content.

If *file* is not a symbolic link then the utility shall fail.


# Options

**-n**
	Do not print newline after the link contents.


# Operands

*file*
	The symbolic link to print the contents of.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

None.


# Input Files

Not used.


# Standard Output

Shall be the link contents, where the link leads to, of the *file* given.


# Output Files

Not used.


# Standard Error

Use to print any diagnostic messages.


# Asynchronous Events

Default.


# Extended Description

None.


# Exit Status

`>0`
	An error occurred.

`0`
	Successful.


# Consequences of Error

None.


# Application Usage

This application is designed to obtain the link contents in an easily digestible
form.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`utility/ls` -- A generic utility also capable of displaying link contents

`utility/realpath` -- A utility to produce the full real path of a file, which
	will follow link contents

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/readlink.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=readlink) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/readlink.1.html) -- The GNU manual
