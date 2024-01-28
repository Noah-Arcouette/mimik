# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

link - Link file


# Synopsis

`link source dest`


# Description

The `link` utility shall link *source* to *dest*, by invoking the `link` function.


# Options

This utility shall not have any options.


# Operands

## source

*source* shall be passed, as the first operand, to the C99 link function.

## dest

*dest* shall be passed, as the second operand, to the C99 link function.


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

Standard error shall be used for diagnostic messages.


# Input Files

Input files are not modified nor read in any way.


# Output Files

*dest* shall be created as a hard-link of *source*.


# Exit Status

## 0

An exit status of zero shall be success.

## >0

An exit status above zero shall be failure.


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

[unlink](unlink.1) - The opposite of link

[ln](ln.1) - A similar, better, utility

[link](link.3) - The link function manual
