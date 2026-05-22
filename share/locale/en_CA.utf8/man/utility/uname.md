# Name

uname -- return system identification information


# Synopsys

```sh
$ uname [-amnrsv]
```


# Description

The *uname* utility shall write the selected system identification information.
If no options are given the utility will act as if **-s** was given. *uname*
shall always print the information in the given order: system name, node name,
release, version, machine.


# Options

**-a**
	Behave as if **-mnrsv** was given.

**-m**
	Print the name of the hardware type.

**-n**
	Print the communication node name.

**-r**
	Print the system release level.

**-s**
	Print the system implementation name.

**-v**
	Print the system version.


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

Use to print the string names in the order: system name, node name, release,
version, machine.


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

None.


# History

None.


# See Also

`library/libc/uname` -- The underlying function

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/uname.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=uname) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/uname.1.html) -- The GNU manual
