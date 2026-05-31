# Name

tee -- save standard input


# Synopsys

```sh
$ tee [-ai] [file...]
```


# Description

The *tee* utility shall write the contents of standard input, without buffering
to the given files and out to standard output. The output files shall be written
to unless **-a** is given, then the output files shall be appended to.


# Options

**-a**
	Append to the output files.

**-i**
	Ignore the SIGINT signal.


# Operands

*file*
	The given output file path or paths to be written to in an unbuffered
	manner. All given *file*s shall be treated as paths a given `-` shall not be
	treated as standard input.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Standard input may be any format or content, and shall be read in an unbuffered
manner.


# Input Files

None.


# Standard Output

Shall be the contents of the standard input.


# Output Files

Shall be the contents of the standard input. The files shall be created if non-
existent. If **-a** is given the files shall be appended to and not truncated.


# Standard Error

Use to print any diagnostic messages.


# Asynchronous Events

Default. Except if **-i** is given, if so then SIGINT shall be ignored.


# Extended Description

None.


# Exit Status

`>0`
	An error occurred.

`0`
	Successful.


# Consequences of Error

If an error occurs, the erroring file may have partial writes but the others
shall continue to be written to; a non-zero exit status shall occur upon any
error.


# Application Usage

*tee* is meant for use in pipelines to produce a copy of a different utility's
output, while still passing it out to the pipeline.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`utility/cat` -- Emit the contents of given files

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/tee.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=tee) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/tee.1.html) -- The GNU manual
