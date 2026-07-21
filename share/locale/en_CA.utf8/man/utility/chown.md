# Name

chown -- Change the file ownership


# Synopsys

```sh
$ chown [-fh] owner[:group] file...

$ chown [-f] -R [-H|-L|-P] owner[:group] file...
```


# Description

*chown* shall attempt to set the user, and group, ownership the given files.

If **-R** is specified, then each *file* that refers to a directory shall have
the directory tree walked recursively preforming the same owner and group
setting.


# Options

**-f**
	Do not report or exit upon an error setting file ownership.

**-h**
	For each file of which refers to a symbolic link, *chown* shall attempt to
	set the user and group of the symbolic link itself.

**-H**
	If **-R** is given, if one of the given *file*s is a symbolic link
	referring to a directory: *chown* shall attempt to set the underlying
	directory's ownership aswell as all files under the directory. But not
	follow any directory pointing symbolic links under the directory.

**-L**
	If **-R** is given, if one of the given *file*s, or a file found during
	file traversal, is a symbolic link referring to a directory: *chown* shall
	attempt to set the underlying directory's ownership aswell as all files
	under the directory.

**-P**
	If **-R** is given, if one of the given *file*s, or a file found during
	file traversal, is a symbolic link referring to a directory: *chown* shall
	attempt to set the symbolic link's ownership **but not** all files under
	the directory.

**-R**
	Recursively change the ownership of files under any directories that are
	given. If a symbolic link is encountered it shall not be followed, as if
	**-P** is supplied.


# Operands

*owner[:group]*
	A user ID or user name to set a given, or encountered, file's ownership to.
	A group ID or group name to set a given, or encountered, file's group to.
	The user and group data base shall always be check, if a numeric user or
	group name exists it shall be used over the evaluation of the given numeric
	value.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

None.


# Input Files

Not used.


# Standard Output

None.


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

If the executing user does not have the appropriate privileges to set the user
or group ownership, the command will fail.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`library/libc/chown` -- The backing function of this utility

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/chown.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=chown) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/chown.1.html) -- The GNU manual
