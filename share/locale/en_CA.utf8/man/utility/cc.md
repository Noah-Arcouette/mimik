# Name

cc, c17 -- The C-language compiler


# Synopsys

```sh
$ cc [*options*...] [*files*...]
```


# Description

*options* may be interspersed with *files*.

The C compiler shall take the input files and apply some level of compilation.


# Options

**-c**, **-B object**
	Do not link the output file, this shall create output files for each input
	file ending in `.o` instead of the original suffix.

**-I path**
	Search *path* first before the standard places for inclusion directives.

**-I nodefault**
	Do not search the default places for inclusion directives.

**-m i8086**
	Produce an output compatible with the i8086 CPU.

**-o outfile**
	Set the output file, default is `a.out` unless otherwise stated.


# Operands

*file*
	The input files may be ending in:
		`.s` -- An assembler file
		`.c` -- A C source file
		`.o` -- An object file


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used if a `-` is given as an input file.


# Input Files

See *file* operand.


# Standard Output

Used if `-` is given as the output file.


# Output Files

The output files may be ending in:
	`.s`  -- Assembler source
	`.o`  -- Object file
	none  -- An executable


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

No output file shall be created upon output.


# Application Usage

None.


# Examples

None.


# Rationale

None.


# Future Directions

POSIX compliance.


# History

None.


# See Also

`format/c` -- The C file format

`format/mio` -- The MiO output format

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/c17.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=cc) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/gcc.1.html) -- The GNU manual
