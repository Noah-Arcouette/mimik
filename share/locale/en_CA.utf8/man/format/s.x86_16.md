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

*reg8* -- An eight bit register:
 - `%ah` -- The high 8bits of `%ax`
 - `%al` -- The low 8bits of `%ax`
 - `%bh` -- The high 8bits of `%bx`
 - `%bl` -- The low 8bits of `%bx`
 - `%ch` -- The high 8bits of `%cx`
 - `%cl` -- The low 8bits of `%cx`
 - `%dh` -- The high 8bits of `%dx`
 - `%dl` -- The low 8bits of `%dx`

`sjmp *literal*` -- Short (8bit displacement) jump

`jmp *literal*` -- Near (16bit displacement) jump

`hlt` -- Halt until an interrupt

`cli` -- Clear interrupt allow flag


# Rationale

None.


# Future Directions

The rest of i8086, i80186, i80286, i386, etc.


# History

None.


# See Also

`format/s` -- The core assembler format

[8086 Datasheet](https://www.alldatasheet.com/datasheet-pdf/view/1154707/INTEL/8086.html) -- Copy of the i8086 datasheet
