#ifndef __INCLUDE_MIO_H__
#define __INCLUDE_MIO_H__
#include <stdint.h>
/// @note All multi-byte data is in little endian form

/// @brief A mio section header
struct MiO
{
	#define MIO_MAGIC "MiO\xe1"
	uint8_t magic[4]; // always MIO_MAGIC

	#define MIO_FLAG_VIRTUAL 0b00000001
	uint8_t flags;

	uint8_t name[256];

	uint64_t size;
};

#define MIO_SPECIAL_MIO_ARCH (uint8_t *)"mio.arch"
/// @brief The mio architecture data
struct MiO_Arch
{
	uint16_t arch; // The architecture
	uint16_t uarch; // The architecture minor
	uint64_t archflags; // The architecture flags

	uint16_t sys; // The system
	uint16_t usys; // The system minor
	uint64_t sysflags; // The system flags
} __attribute__((packed));

// Undefined for mio architecture
#define MIO_ARCH_ARCH_UNDEFINED 0
#define MIO_ARCH_SYS_UNDEFINED  0

// x86* specific definitions
#define MIO_ARCH_ARCH_X86_16          0x0001 // x86 16bit major
#define MIO_ARCH_ARCH_X86_UARCH_I8086 0x0000 // i8086 minor

#define MIO_SPECIAL_MIO_GAPS (uint8_t *)"mio.gaps"
/// @brief A single MiO gap
struct MiO_Gap
{
	/// A positive offset in bytes from the start of the file into a data
	/// section defining where the gap starts
	uint64_t offset;

	/// The type of this gap
	uint16_t type;

	/// The symbol to reference the given data for
	char symbol[256];
};

#define MIO_GAP_TYPE_LIT_BYTE   0x0000 // literal byte
#define MIO_GAP_TYPE_LIT_LE16   0x0001 // literal little-endian 16bit
#define MIO_GAP_TYPE_LIT_LE32   0x0002 // literal little-endian 32bit
#define MIO_GAP_TYPE_LIT_LE64   0x0003 // literal little-endian 64bit
#define MIO_GAP_TYPE_LIT_LE128  0x0004 // literal little-endian 128bit
#define MIO_GAP_TYPE_LIT_BE16   0x0005 // literal big-endian 16bit
#define MIO_GAP_TYPE_LIT_BE32   0x0006 // literal big-endian 32bit
#define MIO_GAP_TYPE_LIT_BE64   0x0007 // literal big-endian 64bit
#define MIO_GAP_TYPE_LIT_BE128  0x0008 // literal big-endian 128bit
#define MIO_GAP_TYPE_DISP_BYTE  0x0009 // displacement byte
#define MIO_GAP_TYPE_DISP_LE16  0x000a // displacement little-endian 16bit
#define MIO_GAP_TYPE_DISP_LE32  0x000b // displacement little-endian 32bit
#define MIO_GAP_TYPE_DISP_LE64  0x000c // displacement little-endian 64bit
#define MIO_GAP_TYPE_DISP_LE128 0x000d // displacement little-endian 128bit
#define MIO_GAP_TYPE_DISP_BE16  0x000e // displacement big-endian 16bit
#define MIO_GAP_TYPE_DISP_BE32  0x000f // displacement big-endian 32bit
#define MIO_GAP_TYPE_DISP_BE64  0x0010 // displacement big-endian 64bit
#define MIO_GAP_TYPE_DISP_BE128 0x0011 // displacement big-endian 128bit

#endif
