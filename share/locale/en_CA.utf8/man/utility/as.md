# Name

as -- assembler


# Synopsys

```sh
$ as [-o output] [input...]
```


# Description

*as* shall assemble the *input* source file(s) into an unlink ***MiO*** output
file.


# Options

**-o output**
	The given output file, may be `-` for standard output, by default the output
	file is `a.out`.


# Operands

*input*
	The input assembler files, may be `-` for standard input. If no input files
	are given a empty output object will be created.



# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used if a `-` is given as an input file.


# Input Files

Shall be in the assembler input format.


# Standard Output

Used if `-` is given as the output file.


# Output Files

A single output file shall be created, defaulting to `a.out` unless otherwise
specified, in the MiO object format without any linking taking place.


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

This application is designed for use in Mimik and only produces MiO files from
Mimik source import files.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`format/s` -- The assembler input format

`format/mio` -- The MiO output format
