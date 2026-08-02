# Name

mio2bin -- Load a MiO executable into a flat binary


# Synopsys

```sh
$ mio2bin [-v] [-o outfile] file
```


# Description

*mio2bin* shall load *file* -- based on the internal loading information -- into
the output file as a flat binary suitable, for instance: in use for firmware or
ROM chips.

If **-o outfile** is provided it shall be the output file, else `*file*.bin`
shall be the output file.

If **-v** is set then virtual maps shall be loaded into the file and filled with
zeros.


# Options

**-o outfile**
	The given output file, defaults to *file* suffixed with `.bin`. If `-` is
	given then standard output shall be written to.

**-v**
	Load virtual maps.


# Operands

*file*
	The given file to load, if `-` then standard input shall be read from.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used if `-` is given for *file*.


# Input Files

The input file shall be a statically-linked loadable MiO regular file -- capable
of seeking -- without TLS data.


# Standard Output

Used if `-` is given to **-o**.


# Output Files

Shall be a flat loaded binary, with all internal gaps filled, and layout in the
way specified by internal loading information.


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

None.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`format/mio` -- The MiO file format
