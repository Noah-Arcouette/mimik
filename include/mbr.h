#ifndef __INCLUDE_MBR_H__
#define __INCLUDE_MBR_H__
#include <stdint.h>

/// @note all multi-byte values are in little-endian

struct mbr_part
{
	#define MBR_PART_FLAG_BOOTABLE 0x80
	uint8_t flags;

	uint8_t firstCHS[3];
	#define MBR_PART_TYPE_FREE     0x00
	#define MBR_PART_TYPE_VBR      0xe2
	#define MBR_PART_TYPE_ROOT     0xe7
	#define MBR_PART_TYPE_FS       0xe9
	#define MBR_PART_TYPE_GPT_PROT 0xee
	#define MBR_PART_TYPE_ESP      0xef
	uint8_t type;
	uint8_t lastCHS[3];

	uint32_t firstLBA;
	uint32_t sectors;
} __attribute__((packed));

#define MBR_MAGIC 0xaa55
struct mbr
{
	uint8_t  bootcode[440];
	uint32_t id;
	uint16_t reserved;
	struct mbr_part part[4];
	uint16_t magic;
} __attribute__((packed));

#endif
