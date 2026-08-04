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

*sreg* -- A segmentation register
 - `%es` -- Extra segment
 - `%cs` -- Code segment
 - `%ds` -- Data segment
 - `%ss` -- Stack segment

*mem* -- A memory address or register:
 - `[%bx+%si]` with optional `+*literal*` or `-*literal*`
 - `[%bx+%di]` with optional `+*literal*` or `-*literal*`
 - `[%bp+%si]` with optional `+*literal*` or `-*literal*`
 - `[%bp+%di]` with optional `+*literal*` or `-*literal*`
 - `[%si]` with optional `+*literal*` or `-*literal*`
 - `[%di]` with optional `+*literal*` or `-*literal*`
 - `[%bp]` with optional `+*literal*` or `-*literal*`
 - `[%bx]` with optional `+*literal*` or `-*literal*`
 - `[*literal*]`

*algr* -- A standard algorithm operand, left side is always destination:
 - *reg8* *reg8*
 - *reg8* *mem*
 - *reg8* *literal*
 - *reg16* *reg16*
 - *reg16* *mem*
 - *reg16* *literal*
 - *mem* *reg8*
 - .byte *mem* *literal*
 - *mem* *reg16*
 - .word *mem* *literal*

`mov *reg16* *reg16*`
`mov *reg16* *literal*`
`mov *reg16* *mem*`
`mov *reg16* *sreg*`
`mov *reg8* *reg8*`
`mov *reg8* *literal*`
`mov *reg8* *mem*`
`mov *mem* *reg16*`
`mov *mem* *reg8*`
`mov *mem* *sreg*`
`mov .byte *mem* *literal*`
`mov .word *mem* *literal*` -- Move data around, first operand is always
	destination

`add *algr*` -- Add on the given values
`adc *algr*` -- Add with carry on the given values
`sub *algr*` -- Subtract on the given values
`ssb *algr*` -- Subtract with borrow on the given values
`cmp *algr*` -- Compare on the given values
`and *algr*` -- And on the given values
`or *algr*`  -- Or on the given values
`xor *algr*` -- Exclusive or on the given values

`sjmp *symbol*` -- Short (8bit displacement) jump

`jmp *reg16*`
`jmp *mem*`
`jmp *symbol*` -- Near (16bit displacement) jump

`ljmp *mem*`
`ljmp *literal* *literal*` -- Long jump into offset (first) and segment (second)

`je *symbol*` -- Jump if equal
`jz *symbol*` -- Jump if zero
`jl *symbol*` -- Jump if lesser than
`jnge *symbol*` -- Jump if not greater than or equal
`jle *symbol*` -- Jump if lesser than or equal
`jng *symbol*` -- Jump if not greater than
`jb *symbol*` -- Jump if below
`jnae *symbol*` -- Jump if not above or equal
`jbe *symbol*` -- Jump if below or equal
`jna *symbol*` -- Jump if not above
`jp *symbol*` -- Jump if parity
`jpe *symbol*` -- Jump if parity even
`jo *symbol*` -- Jump if overflow
`js *symbol*` -- Jump if signed
`jne *symbol*` -- Jump if not equal
`jnz *symbol*` -- Jump if not zero
`jnl *symbol*` -- Jump if not lesser than
`jge *symbol*` -- Jump if greater than or equal
`jnle *symbol*` -- Jump if not lesser than or equal
`jg *symbol*` -- Jump if greater
`jnb *symbol*` -- Jump if not below
`jae *symbol*` -- Jump if above or equal
`jnbe *symbol*` -- Jump if not below or equal
`ja *symbol*` -- Jump if above
`jnp *symbol*` -- Jump if not parity
`jpo *symbol*` -- Jump if parity odd
`jno *symbol*` -- Jump if not overflow
`jns *symbol*` -- Jump if not signed
`loop *symbol*` -- Loop if `%cx` (and decrement `%cx`)
`loopz *symbol*` -- Loop if `%cx` and zero (and decrement `%cx`)
`loope *symbol*` -- Loop if `%cx` and equal (and decrement `%cx`)
`loopnz *symbol*` -- Loop if `%cx` and not zero (and decrement `%cx`)
`loopne *symbol*` -- Loop if `%cx` and not equal (and decrement `%cx`)
`jcxz *symbol*` -- Jump if `%cx`

`int *number*` -- Trigger an interrupt of the given vector

`movs .byte`
`movs .word` -- Move `%cx` amount of bytes from `%ds:%si` to `%es:%di`

`cmps .byte`
`cmps .word` -- Compare `%cx` amount of bytes from `%ds:%si` to `%es:%di`

`scas .byte`
`scas .word` -- Scan `%cx` amount of bytes from `%ds:%si` to `%es:%di`

`lods .byte`
`lods .word` -- Load `%cx` amount of bytes from `%ds:%si` to `%es:%di`

`stos .byte`
`stos .word` -- Store `%cx` amount of bytes from `%ds:%si` to `%es:%di`

`ret` -- Return from `call`

`clc` -- Clear carry flag
`cmc` -- Compliment carry flag
`stc` -- Set carry flag

`cld` -- Clear direction flag
`std` -- Set direction flag

`cli` -- Clear interrupt flag
`sti` -- Set interrupt flag
`hlt` -- Halt until an interrupt
`wait` -- Wait for co-processor

`nop` -- Do nothing

`es` -- Access data within the extra segment (for next instruction)
`cs` -- Access data within the code segment (for next instruction)
`ss` -- Access data within the stack segment (for next instruction)
`ds` -- Access data within the data segment (for next instruction)

`lock` -- Lock the system bus (for next instruction)

`repz` -- Repeat until zero
`repnz` -- Repeat until non-zero


# Rationale

None.


# Future Directions

The rest of i8086, i80186, i80286, i386, etc.


# History

None.


# See Also

`format/s` -- The core assembler format

[8086 Datasheet](https://www.alldatasheet.com/datasheet-pdf/view/1154707/INTEL/8086.html) -- Copy of the i8086 datasheet
