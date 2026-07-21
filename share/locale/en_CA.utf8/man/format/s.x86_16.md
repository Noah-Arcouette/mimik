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

*reg16* -- An sixteen bit register:
 - `%ax` -- Accumulator
 - `%bx` -- Base
 - `%cx` -- Counter
 - `%dx` -- Data
 - `%sp` -- Stack Pointer
 - `%bp` -- Base Pointer
 - `%si` -- Source Index
 - `%di` -- Destination Index

*mem* -- A memory address or register:
 - `[%bx+%si]` with optional `+*literal*`
 - `[%bx+%di]` with optional `+*literal*`
 - `[%bp*%si]` with optional `+*literal*`
 - `[%bp+%di]` with optional `+*literal*`
 - `[%si]` with optional `+*literal*`
 - `[%di]` with optional `+*literal*`
 - `[%bp]` with optional `+*literal*`
 - `[%bx]` with optional `+*literal*`
 - `[*literal*]`

*algr* -- A standard algorithm operand, left side is always destination:
 - *reg8* *reg8*
 - *reg8* *mem*
 - *reg8* *literal*
 - *reg16* *reg16*
 - *reg16* *mem*
 - *reg16* *literal*
 - .byte *mem* *reg8*
 - .byte *mem* *literal*
 - .word *mem* *reg16*
 - .word *mem* *literal*

`sjmp *literal*` -- Short (8bit displacement) jump

`jmp *literal*` -- Near (16bit displacement) jump

`hlt` -- Halt until an interrupt

`cli` -- Clear interrupt allow flag

`nop` -- Do nothing


# Rationale

None.


# Future Directions

The rest of i8086, i80186, i80286, i386, etc.


# History

None.


# See Also

`format/s` -- The core assembler format

[8086 Datasheet](https://www.alldatasheet.com/datasheet-pdf/view/1154707/INTEL/8086.html) -- Copy of the i8086 datasheet
