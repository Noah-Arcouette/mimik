# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

false - Exits false


# Synopsis

`false [error]`


# Description

The *false* utility shall exit false.


# Options

The *false* utility shall not parse any options.


# Operands

## error

Error will be the returned exit status as a positive integer.


# Environment Variables

## Lang

`Lang` shall be the default value for all LC variables. `Lang` shall be used to determine the locale for diagnostic messages.

## NLSPATH

`NLSPATH` shall be a list of paths to check for locale data.


# StdIn

Standard input shall not be used.


# StdOut

Standard output shall not be used.


# StdErr

Standard Error will be used for diagnostic messages.


# Input Files

Input files are not modified nor read in any way.


# Output Files

There are no output files produced by this utility.


# Exit Status

The exit status shall always be non-zero, or the interpreted value of error if given.


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

[true](true.1) - The opposite of false
