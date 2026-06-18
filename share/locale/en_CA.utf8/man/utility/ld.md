# Name

ld -- Link together multiple compilation units into one.


# Synopsys

```sh
$ ld [*options*] [files...]
```


# Description

Link together multiple compilation units into one. By default creating a
loadable and executable binary.


# Options

**-r**
	Create an unlinked object file -- suitable to be passed back to *ld* -- for
	output.

**-e entry**
	Set the executable entry point, default: `_start`.

**-o output**
	Set the output file path, default `a.out`.

**-T script**
	Change the default linker script file. Default: `/usr/libexec/linker.ld`.


# Operands

*files*
	Shall be a list of one or more input files.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used if `-` is given as a *file*.


# Input Files

The given input files may be one of the following:
 - `.o` -- An unlinked, unloadable, MiO file; to be linked into the output

`.o` files may be any MiO file, presumably create by `ld`, `c17`, or
`as`.


# Standard Output

If `-` is given as the output file than standard output shall be used.


# Output Files

The output file shall be a MiO file. If **-r** is given it shall be non-loadable
but able to be relinked, otherwise it shall be a loadable object. The linking
shall take place as described in the provided or default linker script.


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

Upon error, no output files shall be created.


# Application Usage

None.


# Examples

None.


# Rationale

None.


# Future Directions

Addition of embedding informative data (**-I**), execution restrictive data
(**-E**), section checksum data (**-C**), and section signature data (**-S**).

Addition for archive input support, IR input support -- mainly for unity
builds, and shared library support.

Addition of library search support: **-l library**, **-L link-search-path**,
**-R load-search-path**, **-Bdynamic | -Bstatic**.


# History

None.


# See Also

`format/mio` -- The MiO file format

`format/ld` -- The linker script format

`utility/c17` -- The C compiler utility

`utility/as` -- The assembler utility

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=ld) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/ld.1.html) -- The GNU manual
