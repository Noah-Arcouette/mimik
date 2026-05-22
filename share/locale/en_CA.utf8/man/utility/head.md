# Name

head -- print the start of a file


# Synopsys

```sh
$ head [-q] [-c bytes|-n lines] [file...]
```


# Description

*head* shall print out a number of **lines** or **bytes** from each *file*
specified. If not file is specified than standard input shall be used.


# Options

**-c bytes**
	Specify the amount of bytes to read from each file.

**-n lines**
	Specify the amount of lines to read from each file.

**-q**
	Suppress printing of headers.


# Operands

*file*
	The files to get the start of, if none is given than standard input shall
	be used.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used if `-` is given as a *file* or if no *file*s are given.


# Input Files

The input files may be any readable descriptor and may contain any data. The
line length is not restricted to {LINE_MAX} bytes.


# Standard Output

Shall be the first **bytes** or **lines** from each input.

If multiple file operands are given the output shall be preceded by:
`"\n==> %s <==\n", file`

Except for the first, wherein the initial newline shall not be printed.

The preceded head shall not be printed if **-q** is given.


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
	An error occured.

`0`
	Successful.


# Consequences of Error

None.


# Application Usage

None.


# Examples

To write the first ten lines of all files -- excepting the hidden files:

`head -- *`


# Rationale

**-q** is present in FreeBSD, GNU, and most likely other unix-likes. And is
useful when concatenating the heads of multiple files.


# Future Directions

None.


# History

None.


# See Also

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/head.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=head) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/head.1.html) -- The GNU manual
