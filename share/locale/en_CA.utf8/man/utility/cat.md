# Name

cat -- concatenate files


# Synopsys

```sh
$ cat [-u] [file...]
```


# Description

*cat* shall read the contents of the given *file*s and emit them to standard
output in the given sequence. Standard input is used as the input file if none
is given.


# Options

**-u**
	Disable all buffering, reading each byte and writing byte without delay.


# Operands

*file*
	A pathname to an input file or `-` for standard input. Multiple `-`s may be
	given in the operands, and at no point shall *cat* close or reopen the
	standard input file.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used on occurrence of `-` in the input *file*s or if no operands are given.


# Input Files

Input files may be of any type or content.


# Standard Output

Shall be the contents of the input files emitted in the order of occurrence in
the operands.


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

The **-u** option is designed mainly for use in fifo devices such as:
```sh
mkfifo foo
cat -u foo > /dev/tty13 &
cat -u > foo
```


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`utility/more` -- Display files on a page by page basis

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/cat.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=cat) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/cat.1.html) -- The GNU manual
