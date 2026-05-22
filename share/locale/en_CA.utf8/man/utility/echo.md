# Name

echo -- print to the console


# Synopsys

```sh
$ echo [string...]
```


# Description

*echo* shall print all the given *string*s followed by a newline. If no
operands are given then only a newline is printed.


# Options

All options, including `-` and `--`, shall be tread as operands.


# Operands

*string*
	The string to be printed to the standard output. *echo* shall treat the
	following sequences as described:
	`\a` -- Write an alert
	`\b` -- Write a backspace
	`\c` -- The final newline shall not be written
	`\f` -- Write a formfeed
	`\n` -- Write a newline
	`\r` -- Write a carriage return
	`\t` -- Write a tab
	`\v` -- Write a vertical tab
	`\\` -- Write a backslash
	`\0num` -- Write the character *num* -- interpreted as an octal


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

None.


# Input Files

Not used.


# Standard Output

Shall be the given arguments followed by a newline.


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

This application is mainly designed for simple output, more complex parsing
should be replaced with the use of the *printf* utility.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`utility/printf` -- A more powerful output method

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/echo.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=echo) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/echo.1.html) -- The GNU manual
