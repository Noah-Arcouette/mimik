# Name

`.s` (x86 16bit specific) - An assembler source code specific with x86-16


# Synopsis

The x86 16bit assembler source for specifically the Mimik assembler. Note, this
is only for the assembler source and does not include hardware implementation,
form, or representation.


# Description

## Architecture Information

This document only applies in the context of `.arch x86_16`.

## Instructions

*literal* -- A literal may be either a symbol or an integer

`sjmp *literal*` -- Short (8bit displacement) jump


# Rationale

None.


# Future Directions

The rest of i8086, i80186, i80286, i386, etc.


# History

None.


# See Also

`format/s` -- The core assembler format

[8086 Datasheet](https://www.alldatasheet.com/datasheet-pdf/view/1154707/INTEL/8086.html) -- Copy of the i8086 datasheet
