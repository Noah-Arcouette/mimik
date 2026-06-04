# Name

MiO - Mimik Object file


# Synopsis

The MiO format documents a lightweight named section based object file. Mainly
designed for use with executable linking, loading, and utilization.


# Description

A MiO file is logically a list of named virtual and data sections in an
arbitrary sequence. The two planes of sections -- data and virtual -- shall
always be considered separate and non-overlapping. Data sections have the
section header followed by the specified length of data. Whist virtual sections
shall have no following data and shall instead be considered an allocation of
zero filled data in a separate addressable domain.

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

As of current, no special sections are defined.


# Rationale

This format is designed to be simplistic and extendable, and may be slower than
other formats.

The split between virtual and data regions is designed almost entirely for the
`.bss` assembly section.


# Future Directions

Possible new special sections:
 - *mio.symbols* : Named symbols
 - *mio.gaps*    : Load time data gaps
 - *mio.arch*    : Architecture and system information
 - *mio.info*    : User informative information
 - *mio.sigs*    : Section data signatures
 - *mio.chks*    : Section data checksums
 - *mio.maps*    : Load time paging information
 - *mio.segs*    : Load time segmentation information
 - *mio.libs*    : Dynamic libraries and library paths
 - *mimik.rest*  : Mimik execution restrictions


# History

None.


# See Also

`include/mio.h` -- The C header file for MiO
