# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

uname - obtain system information


# Synopsis

`uname [-amnrsv]`


# Description

*uname* shall return requested system information. This information shall describe the layer in which the user land and shell are built on-top of, ex: what ever level in the operating system's software stack defines the uname structure and procedure. The information shall be provided in the following order: `snrvm`.


# Options

## -a

If **-a** is given *uname* shall act as if `-mnrsv` are specified.

## -m

*uname* shall provide the machine architecture and relevant information.

## -n

*uname* shall provide the network name of the current system.

## -r

*uname* shall provide the release identifier of the current system.

## -s

*uname* shall provide the implementation identifier of the current system.

## -v

*uname* shall provide the version identifier of the current system.


# Operands

Operands shall not be considered.


# Environment Variables

## Lang

`Lang` shall be the default value for all LC variables. `Lang` shall be used to determine the locale for diagnostic messages.

## NLSPATH

`NLSPATH` shall be a list of paths to check for locale data.


# StdIn

The standard input shall not be used.


# StdOut

The requested system data.


# StdErr

Standard error shall be used for diagnostic messages.


# Input Files

No input files shall be used.


# Output Files

There shall be no output files.


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

[uname](uname.3) - Obtain the uname structure
