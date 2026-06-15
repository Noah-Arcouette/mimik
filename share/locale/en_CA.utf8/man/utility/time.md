# Name

time -- Return the execution time break down of a command


# Synopsys

```sh
$ time [-p] utility [arguments...]
```


# Description

*time* shall execution *utility* with the given *arguments* and return the
following break down:
 - Elapsed real time of the utilities execution
 - The user mode CPU time
 - The system mode CPU time

*time* is a utility and not an intrinsic and thus cannot time intrinsic or
complex commands, if *time* is used within a pipeline only the following
utility is timed and full timing of the pipeline should use `sh -c` as the
utility. Output and input redirection, pipelining, intrinsic timing, and
control operators may effect the results of the *time* utility in unspecified
and unpredictable manner.


# Options

**-p**
	Ensure the output format is as defined in STDERR.


# Operands

*utility*
	The utility to execute via the `exec` family of C functions.

*arguments*
	The list of arguments to pass to the utility.


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

Shall be used for diagnostic messages, and shall be, upon successful completion:
	"real %f\nuser %f\nsys %f\n", <real seconds>, <user seconds>,
	<system seconds>



# Asynchronous Events

Default.


# Extended Description

None.


# Exit Status

`0`
	Success.

`1-125`
	An error occurred in the *time* utility.

`126`
	The utility specified failed to invoke.

`127`
	The utility specified cannot be found.


# Consequences of Error

None.


# Application Usage

None.


# Examples

If a complex command is used generally the given form should be used:

`time sh -c -- 'complex-command-line'`


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`library/libc/times` -- The backing function of this utility

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/time.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=time) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/time.1.html) -- The GNU manual
