# Name

gzip -- The gzip file header


# Synopsys

```c
#include <zio.h>

struct gzip
{
	#define GZIP_MAGIC (uint16_t)(0x8b1f)
	uint16_t magic;

	#define GZIP_METHOD_DEFLATE 8
	uint8_t method;

	#define GZIP_FLAG_TEXT        1
	#define GZIP_FLAG_HEADER_CRC  2
	#define GZIP_FLAG_EXTRA       4
	#define GZIP_FLAG_NAME        8
	#define GZIP_FLAG_COMMENT    16
	#define GZIP_FLAG_RESERVED  224
	uint8_t flags;

	uint32_t mtime;

	#define GZIP_EXTRA_DEFLATE_BEST 2
	#define GZIP_EXTRA_DEFLATE_FAST 4
	uint8_t eflags;

	#define GZIP_OS_FAT       0
	#define GZIP_OS_AMIGA     1
	#define GZIP_OS_OPENVMS   2
	#define GZIP_OS_UNIX      3
	#define GZIP_OS_VM_CMS    4
	#define GZIP_OS_ATARI_TOS 5
	#define GZIP_OS_HPFS      6
	#define GZIP_OS_MACINTOSH 7
	#define GZIP_OS_Z_SYSTEM  8
	#define GZIP_OS_CPM       9
	#define GZIP_OS_TOPS_20   10
	#define GZIP_OS_NTFS      11
	#define GZIP_OS_QDOS      12
	#define GZIP_OS_RISCOS    13
	#define GZIP_OS_MIMIK     225
	#define GZIP_OS_UNKNOWN   255
	uint8_t os;
};
```


# Description

The gzip file header, the start of all gzip files.

All multibyte values are in little-endian format.

*magic* must be set to `GZIP_MAGIC`.

*method* the compression method, only `GZIP_METHOD_DEFLATE` is defined.

*flags* is a bit field of:
 - `GZIP_FLAG_TEXT` -- Content is assumed to be text
 - `GZIP_FLAG_HEADER_CRC` -- The header contains a CRC
 - `GZIP_FLAG_EXTRA` -- The header contains extra fields
 - `GZIP_FLAG_NAME` -- The header contains the original file name
 - `GZIP_FLAG_COMMENT` -- The header contains a file comment

If any `GZIP_FLAG_RESERVED` are set, it shall be treated as a soft-error.

*mtime* shall be the unix time of the last file modification, or the beginning
of compression. If *mtime* is zero then it shall be treated as non-set.

*eflags* are the method specific bit field flags, for deflate it is:
 - `GZIP_EXTRA_DEFLATE_BEST` -- Best compression was used
 - `GZIP_EXTRA_DEFLATE_FAST` -- The fastest compression was used

*os* is the operating system or file system of which the file was compressed on:
 - `GZIP_OS_FAT` -- FAT based file system
 - `GZIP_OS_AMIGA` -- Amiga
 - `GZIP_OS_OPENVMS` -- Open VMS or VMS
 - `GZIP_OS_UNIX` -- Unix or Unix-Like
 - `GZIP_OS_VM_CMS` -- VM/CMS
 - `GZIP_OS_ATARI_TOS` -- Atari TOS
 - `GZIP_OS_HPFS` -- HPFS based file system
 - `GZIP_OS_MACINTOSH` -- Macintosh
 - `GZIP_OS_Z_SYSTEM` -- Z/System
 - `GZIP_OS_CPM` -- CP/M
 - `GZIP_OS_TOPS_20` -- TOPS 20
 - `GZIP_OS_NTFS` -- NTFS based file system
 - `GZIP_OS_QDOS` -- QDOS
 - `GZIP_OS_RISCOS` -- RISC-OS
 - `GZIP_OS_MIMIK` -- Mimik (non-standard)
 - `GZIP_OS_UNKNOWN` -- Unknown file system or operating system

The header is followed by, in order:

*gzip_extra_fields* if `GZIP_FLAG_EXTRA` is set.

A null-terminated original file name, if `GZIP_FLAG_NAME` is set.

A null-terminated file comment, if `GZIP_FLAG_COMMENT` is set.

The least two signification bytes of a CRC-32 of all data up to, but not
including, this field, if `GZIP_FLAG_HEADER_CRC` is set.

A compressed stream, Deflate if `GZIP_METHOD_DEFLATE` is used.

The *gzip_tail*.

EOF or another *gzip* if the file is being used as an archive.


# Application Usage

None.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`library/libzio` -- The library root

`format/gz` -- The format itself
