# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

echo - echo operands to standard output


# Synopsis

`echo [string...]`


# Description

The `echo` utility shall write *string*(s), delimited by spaces, to the standard output; then a newline character.


# Options

This utility shall not have any options.


# Operands

## string

*string* shall be written to standard output, with the following special characters:
 - `\a` Alert
 - `\b` Backspace
 - `\c` Halt all parsing and do not print a final newline
 - `\f` Form-feed
 - `\n` Newline
 - `\r` Carriage return
 - `\t` Horizontal tab
 - `\v` Vertical tab
 - `\\` Single backslash character
 - `\0num` Octal character code, `num` continues until non-octal digit or 8-bit overflow

Note: Sequencies starting with `\` but not appearing in the provided list shall be interpreted literally, example `\gibberish` shall be printed as `\gibberish`.


# Environment Variables

Environment variable shall not be used my this utility.


# StdIn

Standard input shall not be used.


# StdOut

Standard output shall be the concatenation of *string*(s) plus a newline.


# StdErr

Standard error shall not be used.


# Input Files

There are no input files.


# Output Files

No output files shall be generated.


# Exit Status

Exit status shall always be zero. There are no fail cases.


# Extended Description

There is no extended description.


# Future Directions

There are no future directions.


# Compliance

This utility shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright © 2001-2018 IEEE and The Open Group


# See Also

[printf](printf.1) - A better form of `echo`, it is recommended to use `printf` instead of echo.
