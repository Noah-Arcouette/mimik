# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

tee - Create a copy of standard input


# Synopsis

`tee [-aiu] [file...]`


# Description

The `tee` utility shall copy the standard input to *file*(s), and mirror the standard input to standard output. The *file*(s) shall be over written to, unless **-a** is specified then all *file*(s) after shall be appended to.


# Options

## -a

If **-a** is given append to all *file*s after instead of over writing.

## -i

If **-i** is given ignore interrupt signal, **SIGINT**.

## -u

If **-u** is given read and write one byte at a time.


# Operands

## file

The contents of standard input shall be written to all *file* operands.


# Environment Variables

## Lang

`Lang` shall be the default value for all LC variables. `Lang` shall be used to determine the locale for diagnostic messages.

## NLSPATH

`NLSPATH` shall be a list of paths to check for locale data.


# StdIn

Standard input shall be read and written to all *file* operands and to standard output.


# StdOut

The contents of standard input shall be written to standard output.


# StdErr

Standard error shall be used for diagnostic messages.


# Input Files

No input files shall be used.


# Output Files

All output *file*(s), and standard output, shall be a copy of standard input.


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

[cat](cat.1) - Concatenate files to standard output
