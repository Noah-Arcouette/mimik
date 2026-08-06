# Name

fdisk -- Format, partition, a disk


# Synopsys

```sh
$ fdisk disk [*options*]
```


# Description

*fdisk* shall read the information from the given *disk* before executing the
operations described by the given options.

*disk* shall always be ahead of the given options and shall always be read as a
path.


# Options

The **-z**, **-s**, and **-o** options shall have an argument of the following
format:
 1. An optional `+` or `-` meaning increment or decrement the original values by
 2. A numerical value in decimal, regarded as bytes
 3. Unless, suffixed with (case insensitive):
   - `ki` -- meaning 1024   bytes
   - `mi` -- meaning 1024^2 bytes
   - `gi` -- meaning 1024^3 bytes
   - `ti` -- meaning 1024^4 bytes
   - `k`  -- meaning 1000   bytes
   - `m`  -- meaning 1000^2 bytes
   - `g`  -- meaning 1000^3 bytes
   - `t`  -- meaning 1000^4 bytes
 4. They may also be followed by `b` (case insensitive) which shall have no
 effect

The **-A** and **-Z** options shall support the above format excluding step 1.

(basic partitioning)
**-p index**
	Select the partition with the given *index* for modification. If the
	partition selected was empty, create it containing the rest of the disk with
	type `fs`.

**-z size**
	Set the size of the selected partition.

**-s start**
	Change the start position of the partition -- will not move internal data.

**-t type**
	Set the type to the given value. Or set the type using one of the following
	aliases:
	 - `vbr`  -- A volume boot record
	 - `root` -- The operating system root partition
	 - `fs`   -- Generic file system

**-a flag**
	Set or clear a flag on the current partition.

**-d**
	Dry run, do not commit any changes after this flag. Note: the file will
	still be opened for writing.

**-l**
	List disk information, printing out any modifications made at this point.

(partition data)
**-f file**
	Shall load the given file into the selected partition, if the file does not
	fit in the current partition the partition may be grown so long as the
	selected partition is the last non-empty partition in the current
	partitioning mode.

**-o offset**
	Move the selected partition to the given offset, along with its data.

(disk geometry)
**-A alignment**
	Set partition alignment, defaults to `1MiB`.

**-Z size**
	Set the size of the disk.

**-S value**
	Set the amount of bytes per sector, defaults to `512`.

**-C value**
	Set the amount of cylinders per head.

**-H value**
	Set the amount of heads on disk.

(partition map)
**-i id**
	Set the disk identifier, format depends on the partitioning mode.

**-m mode**
	Enter partitioning mode, reading current map.

**-M mode**
	Create a new map, and enter it.

(MBR mode)
**-m mbr**
	Enter MBR partitioning mode.

**-M mbr**
	Create a new empty MBR, and enter it.

**-u code**
	Fill out the boot code of an MBR partition.

**-a boot**
	Make the partition bootable.


# Operands

*disk*
	The disk file to modify, must be seekable.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

None.


# Input Files

A partitioned or non-partition disk file.


# Standard Output

None.


# Output Files

Same as input.


# Standard Error

Use to print any diagnostic messages.


# Asynchronous Events

Default.


# Extended Description

None.


# Exit Status

`>0`
	An error occurred.

`0`
	Successful.


# Consequences of Error

Upon failure, the disk partition record may be corrupted. Extra care should be
used with the **-f** and **-o** options.


# Application Usage

Since misuse may result in permanent disk corruption this program is placed in
the administrative binary directory.


# Examples

None.


# Rationale

None.


# Future Directions

Inclusion of the following partition formats:
 - EBR
 - GPT
 - Amiga rigid disk
 - Apple partition map
 - *BSD and Solaris disk-label


# History

None.


# See Also

`format/mbr` -- The MBR format

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=fdisk) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/fdisk.1.html) -- The GNU manual
