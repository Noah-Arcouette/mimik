# Name

tty -- return user's terminal name


# Synopsys

```sh
$ tty
```


# Description

*tty* shall print the TTY name of the current user, or `not a tty` if not
connected to a TTY.


# Options

None.


# Operands

None.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Not used.


# Input Files

None.


# Standard Output

Shall either be the result of `"%s\n", ttyname()` or `"not a tty\n"`


# Output Files

Not used.


# Standard Error

Use to print any diagnostic messages.


# Asynchronous Events

Default.


# Extended Description

None.


# Exit Status

`>1`
	An error occurred.

`1`
	Error not connected to a TTY.

`0`
	Successful TTY name was print.


# Consequences of Error

None.


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

`library/libc/ttyname` -- The underlying function

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/tty.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=tty) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/tty.1.html) -- The GNU manual
