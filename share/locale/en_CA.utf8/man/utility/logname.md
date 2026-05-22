# Name

logname -- print the login name of the user


# Synopsys

```sh
$ logname
```


# Description

*logname* shall print the login name used by the calling user by use of
`getlogin()`. *logname* does **NOT** change if the *LOGNAME* environment
variable is set.


# Options

None.


# Operands

None.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

None.


# Input Files

Not used.


# Standard Output

Shall be the login named used at the calling user's log in.


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

The *LOGNAME* environment variable does not change this programs result, this is
to prevent from erroneous results.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`library/libc/getlogin` -- The backing function of this utility

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/logname.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=logname) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/logname.1.html) -- The GNU manual
