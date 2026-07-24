# Name

file -- Detect the underlying format of a file


# Synopsys

```sh
$ file [-r man|ext|mime|type] [-dhz] [-M file] [-m file] file...

$ file -i [-r man|ext|mime|type] [-h] file...
```


# Description

*file* shall attempt to retrieve the underlying format of the given files.


# Options

**-d**
	Apply the tests from `/usr/share/locale/<LC_MESSAGES>/magic`. This is the
	default if **-m** or **-M** are not given.

**-h**
	If a given file is a symbolic link, identify it as such and do not
	dereference. If **-h** is not given and the symbolic link is broken -- the
	referenced file does not exist -- then it shall be identified as a link as
	if **-h** was given.

**-i**
	Do not run any tests on the given files.

**-M file**
	Use a different *file* as the given magic file instead of the system's, and
	do not run any tests other then those in *file*. if **-d** and **-M** are
	specified then **-M** shall act as **-m** does.

**-m file**
	Execute the tests in *file* before running the standard system tests.

**-r man|ext|mime|type**
	What information to retrieve:
	 - `man` -- The manual page name for the format
	 - `ext` -- The extensions for the format
	 - `mime` -- The mime type for the format
	 - `type` (default) -- The common name of the format

**-z**
	Attempt to open compressed files and identify the internal data.


# Operands

*file*
	A given file path to be tested, or `-` for standard input.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used if `-` is given as a *file*.


# Input Files

The input files may be of any type.


# Standard Output

Shall be the file name suffixed with a colon and space then the identified file
type and information, manual page, mime type, or format extension.


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

The *file* utility only guesses and is not always correct.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`format/mgc` -- The backing file format for tests

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/file.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=file) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/file.1.html) -- The GNU manual
