# Name

BIOS - (IBM-PC x86-16) Basic Input-Output System


# Synopsis

This is the ABI for relations with the BIOS, for generic calling conventions see
`abi/x86-16.md`.

The BIOS was originally used as the hardware independent way of access the
keyboard, tty display, and hard-disks. The DOS family of operating systems
started as an addition to this specification to allow for basic process control,
and file management. But today, the BIOS is the **legacy** way of a
bootstrapping the operating system on x86 systems.

BIOS is almost strictly 16bit in all ways, though newer systems allow 32bit
access, 64bit (long mode) is completely neglected. It is not recommend to rely
on the BIOS other than for system bootstrapping.


# Description

## Start Up

This is funky, and generally not well followed by any implementation. There are
two data structures the BIOS *might* care about: the MBR and FAT.

The BIOS first looks for a valid MBR, and if it finds one, it *may* load it
into address `0x7c00` through `0x7e00` directly with the given values set:

`%cs:%ip` = 0x7c00
`%dl` - The disk drive we booted from, should always be `0`, thus some BIOSes
	assume you know it should be `0` and don't set this to any useful value.
`%es:%di` - Points to the PnP information (sometimes)

The BIOS may also look for the first active partition in the MBR and load that
to `0x7c00` through `0x7e00` instead -- this is known as a volume boot record --
with the same values as above, and addition of:

`%es:%si` - Points to the MBR partition data of the volume, the pointer contents
should be copied as we do not know where they are stored.

**Note:** For compatibly, all MBR boot loaders should relocate themselves and
load the first active partition as some BIOSes do. And put the actual loader
into the VBR.

Some BIOSes require more than a valid MBR -- especially USB-capable BIOSes. They
require a valid FAT header. And will refuse to load the MBR or VBR without one.

## BIOS Data and the condition of RAM

Upon BIOS start, the RAM is restricted to 1MiB, and the A20-line must be enabled
before more RAM can be accessible.

The contents of memory are as such:

+-----------+-----------+------------+-----------------------------+
|   Start   |    End    |    Size    |         Description         |
+-----------+-----------+------------+-----------------------------+
| 00000000  | 000003ff  |    1   KiB | The Interrupt Vector Table  |
| 00000400  | 000004ff  |  256     B | BIOS Data Area              |
| 00000500  | 00007bff  | ~ 30   KiB | Usable memory               |
| 00007c00  | 00007dff  |  512     B | The MBR or VBR              |
| 00007e00  | 0007ffff  |  480.5 KiB | Usable Memory               |
| 00080000  | 0009ffff  |  128   KiB | Extended BIOS Data Area     |
|           |           |            | (undocumented)              |
| 000a0000  | 000bffff  |  128   KiB | Video memory                |
| 000c0000  | 000effff  |  192   KiB | BIOS expansions             |
| 000f0000  | 000fffff  |   64   KiB | BIOS motherboard ROM        |
+-----------+-----------+------------+-----------------------------+

The BIOS Data Area is as such:

+-----------+--------+-----------------------------+
|  Address  |  Size  |         Description         |
+-----------+--------+-----------------------------+
| 00000400  |  2 B   | serial 0 IO port, or zero   |
| 00000402  |  2 B   | serial 1 IO port, or zero   |
| 00000404  |  2 B   | serial 2 IO port, or zero   |
| 00000406  |  2 B   | serial 3 IO port, or zero   |
| 00000408  |  2 B   | parallel 0 IO port, or zero |
| 0000040a  |  2 B   | parallel 1 IO port, or zero |
| 0000040c  |  2 B   | parallel 2 IO port, or zero |
| 00000413  |  4 B   | Kilobytes of usable memory  |
| 00000449  |  1 B   | Display mode                |
| 0000044a  |  2 B   | Amount of text columns      |
| 00000463  |  2 B   | Base IO port for VGA        |
| 00000475  |  1 B   | Number of hard-disks        |
+-----------+--------+-----------------------------+

## Interaction with the BIOS

Almost all interactions with the BIOS are in the format of the x86 real-mode
vectored interrupts. And as such, please modify the vector table carefully
during the boot process.

Each BIOS defined vectored is treated as a *sub-system*, with individual
functions being picked via the `ah` register. If an error occurs the carry-flag
with be set, otherwise it will be cleared. `ah` is also a common errno-like
register.

### Int 0x10

`%ah=0x0e` -- Teletype output
	+-------+------------------------------+
	| `%ah` | 0x0e                         |
	| `%al` | The ASCII character to print |
	| `%bh` | The page number              |
	| `%bl` | The color (in graphic mode)  |
	+-------+------------------------------+

### Int 0x13

Errors codes:
	+------+------------------------------------+
	| 0x00 | Success                            |
	| 0x01 | Invalid command                    |
	| 0x02 | Cannot find address mark           |
	| 0x03 | Disk is write protected            |
	| 0x04 | Sector not found                   |
	| 0x05 | Reset failed                       |
	| 0x06 | Disk change line active            |
	| 0x07 | Drive parameter activity failed    |
	| 0x08 | DMA over-run                       |
	| 0x09 | Attempt to DMA over 64KiB boundary |
	| 0x0a | Bad sector detected                |
	| 0x0b | Bad cylinder detected              |
	| 0x0c | Media type not found               |
	| 0x0d | Invalid number of sectors          |
	| 0x0e | Control data address mark detected |
	| 0x0f | DMA out of range                   |
	| 0x10 | CRC/ECC data error                 |
	| 0x11 | ECC corrected data error           |
	| 0x20 | Controller failure                 |
	| 0x40 | Seek failure                       |
	| 0x80 | Drive timed out                    |
	| 0xaa | Drive not ready                    |
	| 0xbb | Undefined error                    |
	| 0xcc | Write fault                        |
	| 0xe0 | status error                       |
	| 0xff | Sense operation failed             |
	+------+------------------------------------+

CHS addresses:
	+-------------------+---------------------+
	| `%dh`             | Head [0, 255]       |
	| `%cx` Mask 0xffc0 | Cylinders [0, 1023] |
	| `%cl` Mask 0x3f   | Sectors [1, 63]     |
	+-------------------+---------------------+

Drive numbers:
	+-------------+---------------+
	| 0x00 - 0x7f | Floppy Drives |
	| 0x80 - 0xdf | Hard Disks    |
	|    0xe0     | CD/DVD        |
	| 0xe1 - 0xff | Hard Disks    |
	+-------------+---------------+

	USB devices can either mimic Floppies, DVDs, or Hard-Disks depending on the
	BIOS and the contents of the USB. Generally:
		ISO 9660     -> DVD
		MBR with VBR -> Hard-Disk
		FAT          -> Floppy

`%ah=0x02` -- C/H/S Read
	+-----------+-----------------------------+
	|   `%ah`   | 0x02                        |
	|   `%al`   | Sectors to read (max of 18) |
	|   `%ch`   | Cylinder                    |
	|   `%cl`   | Sector                      |
	|   `%dh`   | Head                        |
	|   `%dl`   | Drive                       |
	| `%es:%bx` | Buffer to fill              |
	+-----------+-----------------------------+
	See CHS addressing


# Rationale

Many things were removed from this document as these are the only ones in use by
the mimik boot loader, feel free to add more.


# Future Directions

None.


# History

None.


# See Also

`format/mbr` -- The MBR format

`format/fat` -- The FAT format

`abi/x86-16` -- The Mimik x86-16bit calling conventions

[OSDev](https://wiki.osdev.org/Expanded_Main_Page) -- OSDev (very good resource)

[Wikipedia](https://en.wikipedia.org/wiki/BIOS_interrupt_call) -- More BIOS interrupts
