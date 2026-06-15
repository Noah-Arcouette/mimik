# Name

sleep -- pause execution for a given interval


# Synopsys

```sh
$ sleep time
```


# Description

*sleep* shall pause execution for at least *time* seconds. *time* may not be
negative.


# Options

None.


# Operands

*time*
	The amount of time to pause for in a positive whole integer.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Not used.


# Input Files

None.


# Standard Output

Not used.


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

None.


# Examples

None.


# Rationale

None.


# Future Directions

Addition of time suffixes may be useful for future use cases.


# History

None.


# See Also

`library/libc/sleep` -- The backing function of this utility

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/sleep.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=sleep) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/sleep.1.html) -- The GNU manual
