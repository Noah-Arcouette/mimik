# Name

`.ld` - Linker description


# Synopsis

This format is used to describe the linker actions taken by the utility `ld`.
It is a plain text format that is generally controlled by a set of macros,
sections, and expressions.


# Description

## Definitions

**symbol** - An object file symbol, must be globally visible.

**architecture** - A supported architecture major.

**micro-architecture** - A supported architecture minor.

**architecture flag** - A supported architecture flag.

**system** - A supported system major.

**micro-system** - A supported system minor.

**system flag** - A supported system flag.

**section** - A defined section within the object file or output file.

## Plain Macros

A plain macro shall not be placed within any of the sections defined in this
document. They, and their purpose, shall be as follows:

*Note:* ellipses indicate a repeated entry separated by spaces.

ENTRY(**symbol**) - Define the entry point of execution in the file.

ARCH(**architecture**)
UARCH(**micro-architecture**)
ARCHFLAGS(**architecture flag**...) - Define the executable architecture of this
	file.

SYS(**system**)
USYS(**micro-system**)
SYSFLAGS(**system flag**...) - Define the executable system of this	file.

## Sections Section

Shall be in the form:

SECTIONS
{
	*entries*
	...
}

Where entries may be:

**symbol** = *expr*;

If the symbol `.` is used, then the address mark shall be changed. Else, the
symbol defined shall be set to the *expr* given.

Or

**section** *[expr]* *[(NOLOAD)]* : *[expr]*
{
	*file*(*section*...)
	...
}

The first *expr* shall be, if provided, the physical address of loading. If not
given then the section defined shall be placed after the last defined address
mark.

If *(NOLOAD)* is provided, then the defined section shall be that of a virtual
section, and be filled with zeros upon loading.

The second *expr*, if provided, shall be the logical address of loading. If not
given then the section defined shall be placed after the last defined address
mark.

*file* shall be a glob-matched input file, and may be a file from inside an
archive.

*section* shall be a glob-match **section** from the stated input file, multiple
may be present if separated by a space.

*expr*, in all contexts, shall be as follows:
 - An integer supported by `strtol`
 - *expr* + *expr* -- Addition
 - *expr* - *expr* -- Subtraction
 - *expr* / *expr* -- Division
 - *expr* * *expr* -- Multiplication
 - **symbol** -- Of which the logical address or literal value shall be used.
 - ( *expr* ) -- Enforced differing order of operations, else standard rules
 	apply
 - . -- The logical address of current address mark, which is given explicitly
	or by the definition of a new section.


# Rationale

This document is inline with other common linkers, though currently missing
portion not yet needed, and including features specific for Mimik.


# Future Directions

The inclusion of a Memory Section, and literal data emission within sections.


# History

None.


# See Also

`utility/ld` -- The linker itself

[GNU](https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html) -- GNU Linker Script

[LLVM](https://lld.llvm.org/) -- LLVM linker

[Generic](https://wiki.osdev.org/Linker_Scripts) -- Generic linker documentation and guide
