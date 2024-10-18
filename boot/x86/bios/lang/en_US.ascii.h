#ifndef __LANG_H__
#define __LANG_H__

// Warning: `\n` will not work in these strings
#define STAGE_TWO_READ_ERROR "Panic. Failed to read stage two. Halting."
#define STAGE_TWO_A20_ERROR "Panic. Failed to enable A20 line. Halting."


// the character to print per number, only up to hex for now
#define ALPHA "0123456789abcdef"
// maximum base our alpha can support
#define ALPHA_MAX_BASE 16

#define BASE_RANGE_ERROR "\n<Error: Base out of range>\n"

#define HALT_MSG "\nSystem halting.\n"


// Disk Errors
#define DISK_ERROR_SUCCESS           "Disk Error: Success\n"
#define DISK_ERROR_INVALID_COMMAND   "Disk Error: Invalid Command\n"
#define DISK_ERROR_ADDRESS_MARK      "Disk Error: Cannot Find Address Mark\n"
#define DISK_ERROR_WRITE_PROT        "Disk Error: Attempted Write On Write Protected Disk\n"
#define DISK_ERROR_SECTOR_NOT_FOUND  "Disk Error: Sector Not Found\n"
#define DISK_ERROR_RESET_FAILED      "Disk Error: Reset Failed\n"
#define DISK_ERROR_CHANGE_ACTIVE     "Disk Error: Disk Change Line 'Active'\n"
#define DISK_ERROR_PARAM_FAILED      "Disk Error: Drive Parameter Activity Failed\n"
#define DISK_ERROR_DMA_OVERRUN       "Disk Error: DMA Over-Run\n"
#define DISK_ERROR_DMA_BOUNDARY      "Disk Error: Attempt To DMA Over 64KB Boundary\n"
#define DISK_ERROR_BAD_SECTOR        "Disk Error: Bad Sector Detected\n"
#define DISK_ERROR_BAD_TRACK         "Disk Error: Bad Cylinder/Track Detected\n"
#define DISK_ERROR_MEDIA_NOT_FOUND   "Disk Error: Media Type Not Found\n"
#define DISK_ERROR_INVALID_SECTORS   "Disk Error: Invalid Number Of Sectors\n"
#define DISK_ERROR_CONTROL_MARK      "Disk Error: Control Data Address Mark Detected\n"
#define DISK_ERROR_DMA_RANGE         "Disk Error: DMA Out Of Range\n"
#define DISK_ERROR_ECC_ERROR         "Disk Error: CRC/ECC Data Error\n"
#define DISK_ERROR_ECC_CORRECTED     "Disk Error: ECC Corrected Data Error\n"
#define DISK_ERROR_CONTROLLER_FAILED "Disk Error: Controller Failure\n"
#define DISK_ERROR_SEEK_FAILED       "Disk Error: Seek Failed\n"
#define DISK_ERROR_TIMED_OUT         "Disk Error: Drive Timed Out, Assumed Not Ready\n"
#define DISK_ERROR_NOT_READY         "Disk Error: Drive Not Ready\n"
#define DISK_ERROR_UNDEFINED         "Disk Error: Undefined Error\n"
#define DISK_ERROR_WRITE_FAULT       "Disk Error: Write Fault\n"
#define DISK_ERROR_STATUS_ERROR      "Disk Error: Status Error\n"
#define DISK_ERROR_SENSE_FAILED      "Disk Error: Sense Operation Failed\n"
#define DISK_ERROR_UNKNOWN           "Disk Error: Unknown Error\n"

#define DISK_READ_AMOUNT "Disk Read Error: Did not read the requested amount of sectors\n"

// MBR Messages
#define MBR_SIGNATURE "MBR: No boot signature found\n"

// Partition Messages
#define PART_NO_PART "No bootable partition found\n"

// Boot Loader file reading
#define NO_KERNEL_FILE  "Boot loader kernel path not resolvable or failed to open, looking for `"
#define NO_KERNEL_FILE2 "'\n"

// Memory Map
#define MEMORY_MAP_HEADER "Address | Length | Type\n"
#define MEMORY_MAP_FAILED "e820 Failed: Memory map returned wrong signature\n"

#define MEMORY_MAP_USABLE_MSG       "Usable Memory"
#define MEMORY_MAP_RESERVED_MSG     "Reserved Memory"
#define MEMORY_MAP_ACPI_RECLAIM_MSG "ACPI Reclaimable Memory"
#define MEMORY_MAP_ACPI_NVS_MSG     "ACPI Non-Volatile Storage Memory"
#define MEMORY_MAP_BAD_MSG          "Bad Memory"
#define MEMORY_MAP_OTHER_MSG        "Unknown Memory"
#endif
