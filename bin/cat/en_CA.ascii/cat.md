# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

cat - concatenate files


# Synopsis

`cat [-u] [file...]`


# Description

The `cat` utility shall concatenate *file*(s), in sequence, to standard output. If `-` is given as a *file*, or no *file* is given, then read from standard input.


# Options

## -u

If **-u** is given disable all buffering.


# Operands

## file

Concatenate *file* in the sequence it appears to standard output. If `-` is given then standard input shall be read, but not closed nor reopened.


# Environment Variables

## Lang

`Lang` shall be the default value for all LC variables. `Lang` shall be used to determine the locale for diagnostic messages.

## NLSPATH

`NLSPATH` shall be a list of paths to check for locale data.


# StdIn

Standard in shall be used is no *file* is given, or if `-` is given as a *file*.


# StdOut

Standard output shall be the contents of *file* concatenated in sequence.


# StdErr

Standard error shall be used for diagnostic messages.


# Input Files

Input files shall be in no particular format.


# Output Files

No output files shall be produced.


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

[more](more.1) - A paging version of *cat*
