# Name

strip -- Remove unnecessary information and optimize an object file


# Synopsys

```sh
$ strip [-O level|optimization] [files...]
```


# Description

Optimize a given object file.

The given optimizations are:

+------------------------+---------+-------------------------------------------+
|     *optimization*     | *level* |                  Meaning                  |
+------------------------+---------+-------------------------------------------+
| gc-static-symbols      |     2 3 | Remove unreference static symbols         |
| gc-empty-symbols       |   1 2 3 | Remove empty symbols                      |
| gc-empty-sections      |   1 2 3 | Remove empty sections                     |
| gc-empty-maps          |   1 2 3 | Remove empty memory maps                  |
| gc-literal-symbols     |   1 2 3 | Remove unreference literal symbols        |
| gc-global-symbols      |       3 | Remove unreference global symbols         |
| merge-literals         |   1 2 3 | Merge like literal symbols                |
| merge-symbols          |     2 3 | Merge like symbol data                    |
| merge-maps             |     2 3 | Merge like memory maps                    |
| reduce-symbols         |       3 | Reduce "unneeded" symbols flags           |
| reduce-gaps            |       3 | Reduce gaps flags and type                |
| reduce-entry           |       3 | Rename entry symbol to default            |
| resolve-literals       |   1 2 3 | Resolve literal symbol gaps               |
| resolve-displacements  |       3 | Resolve displacement gaps                 |
| remove-entry           |     2 3 | Remove default entry setting              |
| remove-arch            |       3 | Remove architecture if it matches current |
| split-zero-sections    |     2 3 | Create virtual sections from zero data    |
| compress-file          |   1 2 3 | Compress the object file                  |
+------------------------+---------+-------------------------------------------+


# Options

**-O level|optimization**
	Set the optimization level; enable, or disable a specific optimization.
	*level* may be between 0 (no optimization) and 3 (possibly breaking
	optimization) the default is 1


# Operands

*files*
	Shall be a list of one or more input files.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used if `-` is given as a *file*.


# Input Files

The given input files may only be a valid MiO file.


# Standard Output

If `-` is given as the input file than standard output shall be used.


# Output Files

Output files shall be valid MiO files.


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

Default.


# Application Usage

None.


# Examples

None.


# Rationale

None.


# Future Directions

Addition of optimizations for:
 - `mio.info`
 - `mio.sigs`
 - `mio.chks`
 - `mio.debug`
 - `mio.segs`
 - `mio.libs`
 - `mimik.rest`


# History

None.


# See Also

`format/mio` -- The MiO file format

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/strip.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=strip) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/strip.1.html) -- The GNU manual
