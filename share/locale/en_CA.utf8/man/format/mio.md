# Name

MiO - Mimik Object file


# Synopsis

The MiO format documents a lightweight named section based object file. Mainly
designed for use with executable linking, loading, and utilization. It is
important to note that the major MiO implementation supports loading from
compressed files within system supported algorithms.


# Description

A MiO file is logically a list of named virtual and data sections in an
arbitrary sequence. The two planes of sections -- data and virtual -- shall
always be considered separate and non-overlapping. Data sections have the
section header followed by the specified length of data. Whist virtual sections
shall have no following data and shall instead be considered an allocation of
zero filled data in a separately addressable domain.

## The File

A MiO file shall be a list of sections. **Note:** all integers shall be in
unsigned little-endian format.

## The Section

A section shall be as follows, in the order given:
 - Magic
 - Flags
 - Name
 - Size
 - Data (if a data section)

A data section shall not be trailed by any more than *size* bytes of data before
end of file or another section. And a virtual section must be followed by the
end of the file or another section.

### Magic

Shall always be:

+--------+------+------+------+------+
| Offset | +0B  | +1B  | +2B  | +3B  |
| Value  | 0x4d | 0x69 | 0x4f | 0xe1 |
+--------+------+------+------+------+

### Flags

Shall always be:

+--------------+---------+-------------+
| Offset (LSB) | +0b     | +1b ... +7b |
| Meaning      | Virtual | Reserved    |
+--------------+---------+-------------+

**NOTE** : The offsets start from the most right bit; `+0b` being the value `1`,
	`+1b` being `2` and so forth.

**Virtual** : If set, this is a virtual section where the section *size* defines
	the amount of virtual data to allocate into the virtual addressing space and
	named by this section. If unset, this is a data section where the section
	*size* specifies the amount of data following this section header that shall
	be attributed to this named section.

### Name

This shall be a null-terminated or fully filled 256 byte buffer containing the
sections declarative name. All names with the prefix `mio.` shall be reserved
for use in this document. All names with the prefix `.` shall not be reserved by
any system utilizing this format. Any special section with the `mio.` prefix
shall be supported in all implementing systems.

Additionally any system non-portable extension shall be prefixed as such:
 - Mimik - `mimik.`
 - Linux - `linux.`
 - BSD generic - `bsd.`
 - Unix generic - `unix.`

And so on for other systems.

Multiple sections may occur with the same name, if the name is address the
regions shall be considered logically contiguous but not contiguously addressed.

### Size

Shall be a 64bit size specifying the length of data this section names.

If a data section, then this shall state the amount of bytes in Data to
attribute to this section.

If a virtual section, then this shall state the amount of bytes to allocate in
the virtual addressable region named by this section.

### Data

If a data section this shall be *size* bytes trailing the Size field to
attribute to this named section. If a virtual section then this shall not be
present and the virtual memory region shall be attributed to this named section.


## Special Sections

### Architecture information

The section with the name `mio.arch` shall have the following structure of data
in the given order -- with no additional padding.

A 16bit major architecture number defining the **backwards incompatible**
architecture. Followed by a 16bit minor architecture number, where all higher
values are compatible with lower values. Then a 64bit bit-field of architecture
flags, which may be inter-compatible, incompatible, masked numbers, or any mix
of the given; this field is depended completely on the architecture major.

Then following the architecture information is the same structure but in-regards
to the running or execution system. A 16bit major system, 16bit minor system,
and 64bit system-specific bit-field. Note, major system are not compatible, but
all minor system must be backwards compatible with lower values.

Examples:
	x86-32 : 32bit x86, this is must match exactly.
	i586   : Pentium I class, this must match exactly or a higher number -- not
		lower.
	-      : No flags are given in this example

	Some System : Some System, this must be exactly the running system
	v6          : Version 6, this must be exactly the same or higher I.E this is
		implicitly v6+
	-           : No flags are given in this example

The following values are defined for these fields:

+-------------+------------+-----------------------------------------------+
| Value (hex) | Arch Major |                     Notes                     |
+-------------+------------+-----------------------------------------------+
| 0000        | Undefined  | This object does not contain executable code  |
| 0001        | 16bit x86  | Specifically 16bit x86 code                   |
+-------------+------------+-----------------------------------------------+


+---------------+-------------+------------+-------------------------+
| Arch Major(s) | Value (hex) | Arch Minor |          Notes          |
+---------------+-------------+------------+-------------------------+
| Undefined     | ----------- | ---------- | Minors shall be ignored |
| 16bit x86     | 0000        | i8086      | The original i8086      |
+---------------+-------------+------------+-------------------------+


+---------------+-------------+------+-------------------------------------+
| Arch Major(s) | Value (hex) | Flag |                Notes                |
+---------------+-------------+------+-------------------------------------+
| Undefined     | ----------- | ---- | Flags shall be ignored              |
| 16bit x86     | ----------- | ---- | Flags shall be considered an error  |
+---------------+-------------+------+-------------------------------------+


+-------------+-----------+-------------------------------------------------+
| Value (hex) | Sys Major |                      Notes                      |
+-------------+-----------+-------------------------------------------------+
| 0000        | Undefined | This object does not contain system useful code |
+-------------+-----------+-------------------------------------------------+


+--------------+-------------+-----------+-------------------------+
| Sys Major(s) | Value (hex) | Sys Minor |          Notes          |
+--------------+-------------+-----------+-------------------------+
| Undefined    | ----------- | --------- | Minors shall be ignored |
+--------------+-------------+-----------+-------------------------+


+--------------+-------------+------+-------------------------------------+
| Sys Major(s) | Value (hex) | Flag |                Notes                |
+--------------+-------------+------+-------------------------------------+
| Undefined    | ----------- | ---- | Flags shall be ignored              |
+--------------+-------------+------+-------------------------------------+

### Symbol Data

The section `mio.symbols` shall contain a list of named data or virtual
segments designed for use mainly in gaps. Each symbols shall be as follows:

+--------+--------+------+-----------------------------------------------+
|  Name  | Offset | Size |                    Meaning                    |
+--------+--------+------+-----------------------------------------------+
| Offset | +0B    | 8B   | Offset into the file for data symbols or the  |
|        |        |      | virtual data section                          |
| Size   | +8B    | 8B   | The amount of bytes taken up by the symbol    |
| Flags  | +16B   | 2B   | The specific flags for this symbol            |
| Name   | +18B   | 256B | The name of the symbol                        |
+--------+--------+------+-----------------------------------------------+

The flags word shall be defined as follows

+--------------+---------------+
| Offset (LSB) |    Meaning    |
+--------------+---------------+
| +0b     0001 | Virtual       |
| +1b     0002 | Readable      |
| +2b     0004 | Writable      |
| +3b     0008 | Executable    |
| +4b     0010 | Global        |
| +5b     0020 | Literal       |
| +6b     0040 | Thread Local  |
| +7b...       | Reserved      |
+--------------+---------------+

`Virtual` shall change the offset value from meaning the offset from the start
of the file, to meaning the offset from the start of the virtual data region.

`Readable` shall allow reading gaps access to this symbol, along with
`Writable`, and `Executable`.

`Global` shall allow this symbol to be used in gaps from other object files, if
the files in question do not already define this symbol. If this is set the
symbol name shall not be changed by any linking or loading utility. If not set
the name of this symbol must only be consistent to originating object file and
its gap; therefore during linking this name and the relating gaps should change
to a unique non-colliding name.

`Literal` this symbol's offset shall be treated as a literal values and not be
mapped and translated into a virtual memory address.

`Thread Local` refers to the symbols mapping requirements, it must be loaded and
linked in such a way that it is in a thread specific memory region.

**NOTE** : The offsets start from the most right bit; `+0b` being the value `1`,
	`+1b` being `2` and so forth.

### Gap Data

The section `mio.gaps` shall contain a list of gap structures used to at load
time to fill in missing symbol data. Gaps shall be preserved until loading to
allow for symbol movement and removal without needed relocation. Gaps are not
relocation and do not function similar to ELF or PE. A gap contains an offset
into a data section that shall be filled as specified by the gap information at
load time. The gap section shall contain a list of the following data:

+--------+--------+------+----------------------------------------------------+
|  Name  | Offset | Size |                      Meaning                       |
+--------+--------+------+----------------------------------------------------+
| Offset | +0B    | 8B   | The offset from the start of the file into a data  |
|        |        |      | section, defining the start of the gap.            |
| Type   | +8B    | 2B   | The type of this gap                               |
| Symbol | +10B   | 256B | The symbol of which to derive gap information from |
+--------+--------+------+----------------------------------------------------+

The *type* portion shall be as follows:

*literal* -- Meaning the value portion of the symbol entry shall be copied
	verbatim.

*displacement* -- Meaning the positive or negative (two's compliment) offset
	from the given gap end to the start (value) of the provided symbol after
	loading into memory. A filled-out gap of zero will be the first byte after
	the gap.

+-------------+-------------------------------------------+
| Value (hex) |                  Meaning                  |
+-------------+-------------------------------------------+
|  000        | A literal byte                            |
|  001        | A literal little endian 16bit value       |
|  002        | A literal little endian 32bit value       |
|  003        | A literal little endian 64bit value       |
|  004        | A literal little endian 128bit value      |
|  005        | A literal big endian 16bit value          |
|  006        | A literal big endian 32bit value          |
|  007        | A literal big endian 64bit value          |
|  008        | A literal big endian 128bit value         |
|  009        | A displacement byte                       |
|  00a        | A displacement little endian 16bit value  |
|  00b        | A displacement little endian 32bit value  |
|  00c        | A displacement little endian 64bit value  |
|  00d        | A displacement little endian 128bit value |
|  00e        | A displacement big endian 16bit value     |
|  00f        | A displacement big endian 32bit value     |
|  010        | A displacement big endian 64bit value     |
|  011        | A displacement big endian 128bit value    |
|  012-eff    | Reserved for future use                   |
|  f00-fff    | Reserved for implementation/system use    |
+-------------+-------------------------------------------+

The first four bits (most significant) shall be used as follows:

+--------------+-----------+----------+----------+----------+
| Offset (LSB) | +0b  0001 | +1b 0010 | +2b 0100 | +3b 1000 |
| Meaning      | Executing | Reading  | Writing  | Reserved |
+--------------+-----------+----------+----------+----------+

This allows for simple error checking of symbol permissions.

### Memory Paging Data

The section `mio.maps` shall be a list memory regions. Upon load time this list
shall be parsed to aid in gaps filling and loading of the binary or library into
memory. Each memory page shall be the following structure:

+----------+--------+------+-----------------------------------------------+
|   Name   | Offset | Size |                    Meaning                    |
+----------+--------+------+-----------------------------------------------+
| Flags    | +0B    | 1B   | The given flags for the structure             |
| Virtual  | +1B    | 8B   | The virtual address or alignment              |
| Physical | +9B    | 8B   | The physical address or alignment             |
| Size     | +17B   | 8B   | The size of the memory region                 |
| Amount   | +25B   | 8B   | Amount of data to load                        |
| From     | +33B   | 8B   | Offset into the file from where to load from  |
+----------+--------+------+-----------------------------------------------+

Flags shall be the following values:

+--------------+---------------------------------------+
| Offset (LSB) |                Meaning                |
+--------------+---------------------------------------+
| +0b 0x01     | Region is readable                    |
| +1b 0x02     | Region is writable                    |
| +2b 0x04     | Region is executable                  |
| +3b 0x08     | Region is thread specific             |
| +4b 0x10     | Virtual is an address not alignment   |
| +5b 0x20     | Physical is an address not alignment  |
| +6...7b 0xc0 | Reserved for future use               |
+--------------+---------------------------------------+

If Readable is set in flags then the loaded memory region shall be readable by
the process, Writable and Executable follows as such aswell. If Thread Specific
is set then upon a thead split the memory region shall be duplicated -- to the
same virtual address.

The memory region shall be loaded as such:
 - Virtual shall be a specific logical execution address if Virtual Is Address
 is set, else it shall be treated as an alignment for a chosen virtual address
 - Physical shall be a specific memory address if Physical Is Address is set,
 else it shall be treated as an alignment for a chosen physical address
 - The memory region shall be contiguous over Size amount of bytes and shall be
 initialized to zero where not loaded from the file
 - The given Amount of bytes shall be loaded from the file at the given Offset,
 if Amount is zero then no bytes shall be loaded -- the entire region zeroed --
 and the Offset value shall be ignored.


# Rationale

This format is designed to be simplistic and extendable, and may be slower than
other formats.

The split between virtual and data regions is designed almost entirely for the
`.bss` assembly section.


# Future Directions

Possible new special sections:
 - *mio.info*    : User informative information
 - *mio.sigs*    : Section data signatures
 - *mio.chks*    : Section data checksums
 - *mio.segs*    : Load time segmentation information
 - *mio.libs*    : Dynamic libraries and library paths
 - *mimik.rest*  : Mimik execution restrictions


# History

None.


# See Also

`include/mio.h` -- The C header file for MiO
