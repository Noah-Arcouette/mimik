# Name

`.s` - Assembler sources


# Synopsis

An assembler input file, specifically for the Mimik assembler. Note, different
assemblers have highly incompatible inputs formats. See the MiO format
documentation for more information about the assembler output.


# Description

Assembler source files are built of three main components: directives, labels,
and instructions.


## Directives

Directives are always in the form:
`.directive input1 input2 input3 ... inputN`

The acceptable directives for standard assembler file are:

`.arch ARCHITECTURE`
	This shall set the current architecture major of the output file, and may
	allow other directives or instructions not specified in this document.
	Multiple architecture majors may be given -- in separate directive lines --
	and will override each other in the sequence given; the final architecture
	directive shall be the final output directive in the object file produced.
	Note, all architecture majors must be incompatible with each other, whilst
	minors must be backwards compatible.

`.uarch MICRO-ARCHITECTURE`
	This shall set the architecture minor -- note, many architecture majors
	allow for this to be derived from the source inputs. The micro-architecture
	are backwards compatible with lower values; please refer to architecture
	specific documentation for these values.

`.archflag FLAGS...`
	Shall set a group of given architecture flags similar to the micro-
	architecture, but able to be used with multiple architecture minors.

`.sys SYSTEM`
	This shall set the system major of the output object file. Note, all
	system majors must be incompatible with each other, whilst minors must be
	backwards compatible.

`.usys MICRO-ARCHITECTURE`
	This shall set the system minor. The micro-systems are backwards compatible
	with lower values; please refer to system specific documentation for these
	values.

`.sysflag FLAGS...`
	Shall set a group of given system flags similar to the micro-systems, but
	able to be used with multiple systems minors.

`.section NAME [FLAGS]`
	Enter an object file section with the given name setting important flags.
	Multiple sections may have the same name without error. The flags may be
	optional, and the acceptable flags are, in no particular order:
		**r** -- Allow all defined symbols in this section to be readable
		**w** -- Allow all defined symbols in this section to be writeable
		**x** -- Allow all defined symbols in this section to be executable
		**v** -- Define a virtual section, without true data
		**-** -- Do nothing, may be used for padding

`.global SYMBOLS...`
	Set the global flag on the given symbol(s). Note, the symbols must be
	defined prior to the global directive line.

## Labels

A label shall be defined as such:
`SYMBOL:`

This shall create a symbol with the values defined in the FLAGS portion of the
section directive. Multiple labels with the same given symbol name shall be
invalid. Labels may work in either virtual or physical sections and may contain
data or reservations.

## Instructions

Instructions are entirely dependent on the current architecture major -- again
note that, multiple architecture major and thus instruction sets may be in the
same assembler input, only the last architecture major shall be that of the
output object file. Instructions may only occur in data sections not virtual.


# Rationale

This assembler source description is relatively simplistic with few safe guards.
Assembler sources are meant to be used as a last resort if a higher language
can not be used.


# Future Directions

Raw data output directives are a must that currently are not talked about in
this document; this is the same with data reservations.


# History

None.


# See Also

`format/mio` -- Assembler output files

`format/s.x86_16` -- x86 16bit instruction set

`utility/as` -- The assembler utility
