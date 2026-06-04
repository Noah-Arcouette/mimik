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

#endif
