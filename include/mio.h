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

#endif
