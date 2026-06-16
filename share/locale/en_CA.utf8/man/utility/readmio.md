# Name

readmio -- Dump the raw MiO information


# Synopsys

```sh
$ readmio [files...]
```


# Description

*readmio* shall print out the information of given MiO files to the best of its
understanding. This information is purely for debugging and should not be
considered structured enough for scripted parsing.


# Options

None.


# Operands

*files*
	A pathname to an input file or `-` for standard input.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Used on occurrence of `-` in the input *files*.


# Input Files

Input files shall be in the MiO format.


# Standard Output

Shall be the parsed data of each input file.


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
